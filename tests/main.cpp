#include "project/testproject.h"
#include "tree_query/testquerylistmodel.h"
#include "tree_query/testqueryclausetablemodel.h"

#include <QTest>

int main(int argc, char* argv[])
{
  TestProject testProject;
  QTest::qExec(&testProject, argc, argv);

  TestQueryListModel testQueryListModel;
  QTest::qExec(&testQueryListModel, argc, argv);

  TestQueryClauseTableModel testQueryClauseTableModel;
  QTest::qExec(&testQueryClauseTableModel, argc, argv);

  return 0;
}
