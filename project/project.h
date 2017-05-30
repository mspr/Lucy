#ifndef PROJECT_H
#define PROJECT_H

#include "domain_object/tree.h"

class Project
{
  public:
    Project();

    void AddTree(int treeId);
    void setCurrentTree(int id);

  private:
    QList<Tree> _trees;
    int _currentTreeId;
};

#endif // PROJECT_H
