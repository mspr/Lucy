#ifndef PROJECT_H
#define PROJECT_H

#include <QList>

class Project
{
  public:
    Project();

  private:
    QList<int> _treeIds;
    int _currentTreeId;
};

#endif // PROJECT_H
