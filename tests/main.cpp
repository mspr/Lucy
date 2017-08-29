#include "project/testproject.h"

#include <QTest>

int main(int argc, char* argv[])
{
  Q_UNUSED(argc)
  Q_UNUSED(argv)

  TestProject testProject;
  QTest::qExec(&testProject, argc, argv);

	return 0;
}
