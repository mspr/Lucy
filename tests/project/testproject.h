#ifndef TESTPROJECT_H
#define TESTPROJECT_H

#include <QObject>

class TestProject : public QObject
{
  Q_OBJECT

  private slots:
    void createProject();
    void fileFormat();
    void setFileInfo();
    void addTree();
    void addTree_currentTree();
    void setCurrentTree();
    void tree_from_droid();
    void tree_from_id();
    void save_not_dirty();
    void save_dirty();
    void cleanupTestCase();
};

#endif // TESTPROJECT_H
