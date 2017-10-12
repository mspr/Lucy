#include "project.h"
#include "projectxmlwriter.h"
#include "business/domainobject.h"
#include "business/domainobject_p.h"
#include "business/person.h"
#include "business/tree.h"

using namespace Business;

Project::Project(const QString& name)
  : _name(name)
  , _isDirty(false)
  , _currentTree(nullptr)
{
  Q_ASSERT(!_name.isEmpty());
  connect(this, Project::treeAdded, this, Project::setDirty);
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
  return _isDirty;
}

void Project::add(Tree* tree)
{
  Q_ASSERT(tree != nullptr);

  _trees.append(tree);
  if (_trees.count() == 1)
    setCurrentTree(tree);

  connect(tree->getD(), DomainObject_p::dirty, this, Project::setDirty);

  emit treeAdded(tree->droid());
}

void Project::setCurrentTree(Tree* tree)
{
  Q_ASSERT(tree != nullptr);

  if (_currentTree != tree)
  {
    _currentTree = tree;
    setDirty();

    emit currentTreeChanged();
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

void Project::setDirty()
{
  _isDirty = true;
  emit dirty();
}

void Project::save()
{
  if (isDirty())
  {
    if (fileInfo().fileName().isEmpty())
      _fileInfo = QFileInfo(_name + "." + fileFormat());

    commit();

    ProjectXmlWriter::write(this);

    emit saved();
  }
}

void Project::commit()
{
  for (int i=0; i<_trees.count(); ++i)
  {
    Tree* tree = _trees.at(i);
    const QList<Person*> persons = tree->persons();

    for (int j=0; j<persons.count(); ++j)
    {
      Person* person = persons.at(j);
      person->getD()->commit();
    }

    tree->getD()->commit();
  }

  _isDirty = false;
}
