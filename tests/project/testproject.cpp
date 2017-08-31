#include "testproject.h"
#include "project/project.h"
#include "domain_object/tree.h"

#include <QtTest/QTest>

void TestProject::createProject()
{
  const QString projectName = "projectName";

  Project project(projectName);

  QCOMPARE(project.name(), projectName);
  QCOMPARE(project.isDirty(), false);
  QCOMPARE(project.fileName().isEmpty(), true);
  QCOMPARE(project.trees().count(), 0);
  QCOMPARE(project.currentTree(), nullptr);
}

void TestProject::setFileName()
{
  const QString fileName = "project.lcy";

  Project project("projectName");
  QVERIFY(project.fileName() != fileName);

  project.setFileName(fileName);

  QCOMPARE(project.fileName(), fileName);
}

void TestProject::addTree()
{
  Project project("projectName");

  QCOMPARE(project.trees().count(), 0);

  Tree* tree = new Tree("treeName");
  project.add(tree);

  QCOMPARE(project.trees().count(), 1);
  QCOMPARE(project.trees().first(), tree);
}

void TestProject::addTree_currentTree()
{
  Project project("projectName");

  QCOMPARE(project.currentTree(), nullptr);

  Tree* tree = new Tree("treeName");
  project.add(tree);

  QCOMPARE(project.currentTree(), tree);
}

void TestProject::setCurrentTree()
{
  Project project("projectName");

  Tree* tree1 = new Tree("treeName1");
  project.add(tree1);
  Tree* tree2 = new Tree("treeName2");
  project.add(tree2);

  QCOMPARE(project.currentTree(), tree1);

  project.setCurrentTree(tree2);

  QCOMPARE(project.currentTree(), tree2);
}
