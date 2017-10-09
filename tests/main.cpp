#include "business/testperson.h"
#include "business/testtree.h"
#include "project/testproject.h"
#include "tree_query/testquerylistmodel.h"
#include "tree_query/testqueryclausetablemodel.h"

#include <QTest>

int main(int argc, char* argv[])
{
  Q_ASSERT(argc == 4);

  argv[3] = (char*)"testPerson.xml";
  TestPerson testPerson;
  QTest::qExec(&testPerson, argc, argv);

  argv[3] = (char*)"testTree.xml";
  TestTree testTree;
  QTest::qExec(&testTree, argc, argv);

  argv[3] = (char*)"testProject.xml";
  TestProject testProject;
  QTest::qExec(&testProject, argc, argv);

  argv[3] = (char*)"testQueryListModel.xml";
  TestQueryListModel testQueryListModel;
  QTest::qExec(&testQueryListModel, argc, argv);

  argv[3] = (char*)"testQueryClauseTableModel.xml";
  TestQueryClauseTableModel testQueryClauseTableModel;
  QTest::qExec(&testQueryClauseTableModel, argc, argv);

  return 0;
}
