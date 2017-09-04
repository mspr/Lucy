#include "project.h"
#include "projectxmlwriter.h"
#include "domain_object/domainobject.h"
#include "domain_object/domainobject_p.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"

#include <QDebug>

using namespace Business;

Project::Project(const QString& name)
  : _name(name)
  , _currentTree(nullptr)
{
  Q_ASSERT(!_name.isEmpty());
}

Project::~Project()
{
  qDeleteAll(_trees);
  _trees.clear();
}

void Project::setFileInfo(const QFileInfo& fileInfo)
{
  Q_ASSERT(!fileInfo.baseName().isEmpty());
  Q_ASSERT(fileInfo.completeSuffix() == fileFormat());

  _fileInfo = fileInfo;
}

QFileInfo Project::fileInfo() const
{
  return _fileInfo;
}

/*static*/ QString Project::fileFormat()
{
  return "lcy";
}

QString Project::name() const
{
  return _name;
}

bool Project::isDirty() const
{
  return !_objectsToDelete.isEmpty() || !_objectsToUpdate.isEmpty() || !_objectsToAdd.isEmpty();
}

void Project::add(Tree* tree)
{
  Q_ASSERT(tree != nullptr);

  _trees.append(tree);
  if (_trees.count() == 1)
    setCurrentTree(tree);

  add_impl(tree);

  emit treeAdded(tree->droid());
}

void Project::add_impl(DomainObject* object)
{
  Q_ASSERT(object != nullptr);

  if (object->id() == -1)
  {
    _objectsToAdd.append(object);
    emit updated();
  }
  else
  {
    connect(object->getD(), DomainObject_p::dirty, this, Project::onObjectDirty);
  }
}

void Project::setCurrentTree(Tree* tree)
{
  Q_ASSERT(tree != nullptr);

  if (_currentTree != tree)
  {
    _currentTree = tree;
    emit updated();
  }
}

Tree* Project::currentTree() const
{
  return _currentTree;
}

Tree* Project::tree(QUuid droid) const
{
  Tree* treeFound = nullptr;

  for (int i=0; i<_trees.count(); ++i)
  {
    Tree* tree = _trees.at(i);
    if (tree->droid() == droid)
    {
      treeFound = tree;
      break;
    }
  }

  return treeFound;
}

Tree* Project::tree(const int id) const
{
  Tree* treeFound = nullptr;

  for (int i=0; i<_trees.count(); ++i)
  {
    Tree* tree = _trees.at(i);
    if (tree->id() == id)
    {
      treeFound = tree;
      break;
    }
  }

  return treeFound;
}

QList<Tree*> Project::trees() const
{
  return _trees;
}

void Project::onObjectDirty()
{
  DomainObject* dirtyObject = dynamic_cast<DomainObject*>(sender());
  Q_ASSERT(dirtyObject != nullptr);

  _objectsToUpdate.append(dirtyObject);

  emit updated();
}

void Project::save()
{
  if (isDirty())
  {
    if (fileInfo().fileName().isEmpty())
      _fileInfo = QFileInfo(_name + fileFormat());

    commit();

    ProjectXmlWriter::write(this);

    qInfo() << "Project " << name() << " has been saved.";
  }
}

void Project::commit()
{
  for (int i=0; i<_objectsToDelete.count(); ++i)
    _objectsToDelete.at(i)->getD()->deleteFromDatabase();

  for (int i=0; i<_objectsToUpdate.count(); ++i)
    _objectsToUpdate.at(i)->getD()->updateInDatabase();

  for (int i=0; i<_objectsToAdd.count(); ++i)
    _objectsToAdd.at(i)->getD()->insertIntoDatabase();

  emit upToDate();
}
