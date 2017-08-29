#include "project.h"
#include "projectxmlwriter.h"
#include "domain_object/domainobject.h"
#include "domain_object/domainobject_p.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"

#include "QDebug"

Project::Project(const QString& fileName, const QString& name)
  : _fileName(fileName)
  , _name(name)
  , _currentTree(nullptr)
{
}

Project::Project(const QString& name)
  : _name(name)
  , _currentTree(nullptr)
{
}

Project::~Project()
{
  qDeleteAll(_trees);
  _trees.clear();
}

void Project::setFileName(const QString& fileName)
{
  Q_ASSERT(!fileName.isEmpty());
  _fileName = fileName;
}

QString Project::fileName() const
{
  return _fileName;
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

  add_impl(tree);

  emit treeAdded(tree->droid());
}

void Project::add(Person* person)
{
  Q_ASSERT(person != nullptr);

  add_impl(person);
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

void Project::setCurrentTree(int id)
{
  Tree* currentTree = tree(id);
  Q_ASSERT(currentTree != nullptr);

  if (_currentTree != currentTree)
  {
    _currentTree = currentTree;
    emit updated();
  }
}

void Project::setCurrentTree(QUuid droid)
{
  Tree* currentTree = tree(droid);
  Q_ASSERT(currentTree != nullptr);

  if (_currentTree != currentTree)
  {
    _currentTree = currentTree;
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
    if (fileName().isEmpty())
      _fileName = _name + ".lcy";

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
