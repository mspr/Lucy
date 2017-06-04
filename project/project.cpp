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
  _objectsToAdd.append(tree);
}

void Project::add(Person* person)
{
  _objectsToAdd.append(person);
}

void Project::addTree(int treeId)
{
  Tree* tree = new Tree(treeId);
  _trees.append(tree);
  _objectsToAdd.append(tree);
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
