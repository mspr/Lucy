#include "project.h"
#include "domain_object/domainobject.h"
#include "domain_object/domainobject_p.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"

Project::Project()
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
  _trees.append(tree);

  if (tree->id() == -1)
    _objectsToAdd.append(tree);

  emit treeAdded(tree->droid());
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

void Project::add(Person* person)
{
  if (person->id() == -1)
    _objectsToAdd.append(person);
}

void Project::setCurrentTree(int id)
{
  _currentTreeId = id;
}

int Project::currentTree() const
{
  return _currentTreeId;
}

QList<Tree*> Project::trees() const
{
  return _trees;
}

void Project::commit()
{
  for (int i=0; i<_objectsToDelete.count(); ++i)
  {
    _objectsToDelete.at(i)->getD()->deleteFromDatabase();
  }

  for (int i=0; i<_objectsToUpdate.count(); ++i)
  {
    _objectsToUpdate.at(i)->getD()->updateInDatabase();
  }

  for (int i=0; i<_objectsToAdd.count(); ++i)
  {
    _objectsToAdd.at(i)->getD()->insertIntoDatabase();
  }
}
