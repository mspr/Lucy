#include "project.h"
#include "domain_object/domainobject.h"
#include "domain_object/domainobject_p.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"

Project::Project()
  : _currentTreeId(-1)
{
}

Project::~Project()
{
  qDeleteAll(_objectsToDelete.begin(), _objectsToDelete.end());
  _objectsToDelete.clear();

  qDeleteAll(_objectsToUpdate.begin(), _objectsToUpdate.end());
  _objectsToUpdate.clear();

  qDeleteAll(_objectsToAdd.begin(), _objectsToAdd.end());
  _objectsToAdd.clear();
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
    connect(object->getD(), DomainObject_p::dirty, this, Project::updated);
  }
}

void Project::setCurrentTree(int id)
{
  if (_currentTreeId != id)
  {
    _currentTreeId = id;
    emit updated();
  }
}

int Project::currentTree() const
{
  return _currentTreeId;
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

QList<Tree*> Project::trees() const
{
  return _trees;
}

void Project::commit()
{
  for (int i=0; i<_objectsToDelete.count(); ++i)
    _objectsToDelete.at(i)->getD()->deleteFromDatabase();

  for (int i=0; i<_objectsToUpdate.count(); ++i)
    _objectsToUpdate.at(i)->getD()->updateInDatabase();

  for (int i=0; i<_objectsToAdd.count(); ++i)
    _objectsToAdd.at(i)->getD()->insertIntoDatabase();
}
