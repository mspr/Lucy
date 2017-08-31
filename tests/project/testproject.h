#ifndef TESTINTERVAL_H
#define TESTINTERVAL_H

#include <QObject>

class TestProject : public QObject
{
  Q_OBJECT

  private slots:
    void createProject();
    void setFileName();
    void addTree();
    void addTree_currentTree();
    void setCurrentTree();
};

#endif // TESTINTERVAL_H
