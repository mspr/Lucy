#include "project.h"

Project::Project()
{
}

void Project::AddTree(int treeId)
{
  _trees.append(Tree(treeId));
}

void Project::setCurrentTree(int id)
{
  _currentTreeId = id;
}

int Project::currentTree() const
{
  return _currentTreeId;
}

QList<Tree> Project::trees() const
{
  return _trees;
}
