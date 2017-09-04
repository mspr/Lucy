#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QUuid>
#include <QFileInfo>

namespace Business { class Person; }
namespace Business { class Tree; }
namespace Business { class DomainObject; }

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

    void add(Business::Tree* tree);
    void setCurrentTree(Business::Tree* tree);

    QList<Business::Tree*> trees() const;
    Business::Tree* currentTree() const;
    Business::Tree* tree(QUuid droid) const;
    Business::Tree* tree(const int id) const;

    void save();

    static QString fileFormat();

  public slots:
    void onObjectDirty();

  signals:
    void treeAdded(QUuid droid);
    void updated();
    void upToDate();

  private:
    void add_impl(Business::DomainObject* object);

    void commit();

  private:
    QFileInfo _fileInfo;
    QString _name;
    QList<Business::Tree*> _trees;
    QList<Business::DomainObject*> _objectsToDelete;
    QList<Business::DomainObject*> _objectsToAdd;
    QList<Business::DomainObject*> _objectsToUpdate;
    Business::Tree* _currentTree;
};

#endif // PROJECT_H
