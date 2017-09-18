#include "testquerylistmodel.h"
#include "tree_query/querylistmodel.h"

#include <QtTest/QTest>

void TestQueryListModel::createModel()
{
  QueryListModel model;

  QCOMPARE(model.columnCount(QModelIndex()), 1);
  QCOMPARE(model.rowCount(QModelIndex()), 0);
}

void TestQueryListModel::createNewQuery()
{
  QueryListModel model;

  model.createNewQuery("queryName");

  QCOMPARE(model.rowCount(QModelIndex()), 1);
}
