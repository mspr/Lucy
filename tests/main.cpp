#include "business/testperson.h"
#include "business/testtree.h"
#include "project/testproject.h"
#include "tree_query/testquerylistmodel.h"
#include "tree_query/testqueryclausetablemodel.h"

#include <QTest>

int main(int argc, char* argv[])
{
  TestPerson testPerson;
  QTest::qExec(&testPerson, argc, argv);

  TestTree testTree;
  QTest::qExec(&testTree, argc, argv);

  TestProject testProject;
  QTest::qExec(&testProject, argc, argv);

  TestQueryListModel testQueryListModel;
  QTest::qExec(&testQueryListModel, argc, argv);

  TestQueryClauseTableModel testQueryClauseTableModel;
  QTest::qExec(&testQueryClauseTableModel, argc, argv);

  return 0;
}
