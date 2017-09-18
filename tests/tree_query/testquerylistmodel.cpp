#include "testquerylistmodel.h"
#include "tree_query/querylistmodel.h"

#include <QtTest/QTest>

void TestQueryListModel::columnCount()
{
  QueryListModel model;

  QCOMPARE(model.columnCount(QModelIndex()), 1);
}

void TestQueryListModel::rowCount_empty_model()
{
  QueryListModel model;

  QCOMPARE(model.rowCount(QModelIndex()), 0);
}
