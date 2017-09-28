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
    void add(Business::Person* person);
    void setCurrentTree(Business::Tree* tree);

    void remove(Business::Person* person);

    QList<Business::Tree*> trees() const;
    Business::Tree* currentTree() const;
    Business::Tree* tree(QUuid droid) const;
    Business::Tree* tree(const int id) const;

    void save();

    static QString fileFormat();

  signals:
    void treeAdded(QUuid droid);
    void dirty();
    void saved();

  private:
    void add_impl(Business::DomainObject* object);
    void commit();

  private slots:
    void setDirty();

  private:
    QFileInfo _fileInfo;
    QString _name;
    bool _isDirty;
    QList<Business::Tree*> _trees;
    QList<Business::DomainObject*> _objects;
    Business::Tree* _currentTree;
};

#endif // PROJECT_H
