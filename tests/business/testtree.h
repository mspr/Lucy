#ifndef TESTTREE_H
#define TESTTREE_H

#include <QObject>

class TestTree : public QObject
{
  Q_OBJECT

  private slots:
    void createTree();
    void setReference();
    void countGenerations_reference_only();
    void countGenerations();
};

#endif // TESTTREE_H
