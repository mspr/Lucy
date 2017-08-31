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
    Project(const QString& name);
    ~Project();

    QString fileName() const;
    QString name() const;
    bool isDirty() const;

    void setFileName(const QString& fileName);

    void add(Tree* tree);
    void setCurrentTree(Tree* tree);

    QList<Tree*> trees() const;
    Tree* currentTree() const;
    Tree* tree(QUuid droid) const;
    Tree* tree(const int id) const;

    void save();

  public slots:
    void onObjectDirty();

  signals:
    void treeAdded(QUuid droid);
    void updated();
    void upToDate();

  private:
    void add_impl(DomainObject* object);

    void commit();

  private:
    QString _fileName;
    QString _name;
    QList<Tree*> _trees;
    QList<DomainObject*> _objectsToDelete;
    QList<DomainObject*> _objectsToAdd;
    QList<DomainObject*> _objectsToUpdate;
    Tree* _currentTree;
};

#endif // PROJECT_H
