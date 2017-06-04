#ifndef PROJECT_H
#define PROJECT_H

#include <QList>

class Person;
class Tree;
class DomainObject;

class Project
{
  public:
    Project();
    ~Project();

    void add(Tree* tree);
    void add(Person* person);
    void addTree(int treeId);
    void setCurrentTree(int id);

    QList<Tree*> trees() const;
    int currentTree() const;

    void commit();

  private:
    QList<Tree*> _trees;
    QList<DomainObject*> _objectsToDelete;
    QList<DomainObject*> _objectsToAdd;
    QList<DomainObject*> _objectsToUpdate;
    int _currentTreeId;
};

#endif // PROJECT_H
