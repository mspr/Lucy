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

void TestProject::tree_from_droid()
{
  Project project("projectName");

  Tree* tree = new Tree("treeName1");
  const QUuid droid = tree->droid();

  QCOMPARE(project.tree(droid), nullptr);

  project.add(tree);

  QCOMPARE(project.tree(droid), tree);
}

void TestProject::tree_from_id()
{
  Project project("projectName");

  Tree* tree = new Tree(5);
  const int id = tree->id();

  QCOMPARE(project.tree(id), nullptr);

  project.add(tree);

  QCOMPARE(project.tree(id), tree);
}
