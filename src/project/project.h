#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QUuid>
#include <QFileInfo>

class Person;
class Tree;
class DomainObject;

class Project : public QObject
{
  Q_OBJECT

  public:
    Project(const QString& name);
    ~Project();

    QFileInfo fileInfo() const;
    QString name() const;
    bool isDirty() const;

    void setFileInfo(const QFileInfo& fileInfo);

    void add(Tree* tree);
    void add(Person* person);
    void setCurrentTree(Tree* tree);

    QList<Tree*> trees() const;
    Tree* currentTree() const;
    Tree* tree(QUuid droid) const;
    Tree* tree(const int id) const;

    void save();

    static QString fileFormat();

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
    QFileInfo _fileInfo;
    QString _name;
    QList<Tree*> _trees;
    QList<DomainObject*> _objectsToDelete;
    QList<DomainObject*> _objectsToAdd;
    QList<DomainObject*> _objectsToUpdate;
    Tree* _currentTree;
};

#endif // PROJECT_H
