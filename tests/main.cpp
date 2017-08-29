#include "project/testproject.h"

#include <QTest>

int main(int argc, char* argv[])
{
  TestProject testProject;
  QTest::qExec(&testProject, argc, argv);

  return 0;
}
