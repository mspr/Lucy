#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QUuid>
#include <QFileInfo>

namespace Business { class Tree; }

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

  signals:
    void treeAdded(QUuid droid);
    void dirty();
    void saved();

  private:
    void commit();

  private slots:
    void setDirty();

  private:
    QFileInfo _fileInfo;
    QString _name;
    bool _isDirty;
    QList<Business::Tree*> _trees;
    Business::Tree* _currentTree;
};

#endif // PROJECT_H
