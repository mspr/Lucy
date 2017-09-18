#include "testqueryclausetablemodel.h"
#include "tree_query/queryclausetablemodel.h"

#include <QtTest/QTest>

void TestQueryClauseTableModel::createModel()
{
  QueryClauseTableModel model;

  QCOMPARE(model.columnCount(QModelIndex()), 3);
  QCOMPARE(model.rowCount(QModelIndex()), 0);
}
