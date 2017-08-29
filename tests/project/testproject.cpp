#include "testproject.h"
#include "project/project.h"

#include <QtTest/QTest>

void TestProject::setFileName()
{
  const QString projectName = "project";
  const QString fileName = "projectName";

  Project project(projectName);
  QVERIFY(project.fileName() != fileName);

  project.setFileName(fileName);

  QVERIFY(project.fileName() == fileName);
}
