#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QUuid>

class Person;
class Tree;
class DomainObject;

class Project : public QObject
{
  Q_OBJECT

  public:
    Project();
    ~Project();

    void add(Tree* tree);
    void add(Person* person);
    void setCurrentTree(int id);

    QList<Tree*> trees() const;
    int currentTree() const;
    Tree* tree(QUuid droid) const;

    void commit();

  signals:
    void treeAdded(QUuid droid);
    void updated();

  private:
    void add_impl(DomainObject* object);

  private:
    QList<Tree*> _trees;
    QList<DomainObject*> _objectsToDelete;
    QList<DomainObject*> _objectsToAdd;
    QList<DomainObject*> _objectsToUpdate;
    int _currentTreeId;
};

#endif // PROJECT_H
