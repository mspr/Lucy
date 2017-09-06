#include "testproject.h"
#include "project/project.h"
#include "business/tree.h"
#include "business/person.h"

#include <QtTest/QTest>

using namespace Business;

void TestProject::createProject()
{
  const QString projectName = "projectName";

  Project project(projectName);

  QCOMPARE(project.name(), projectName);
  QCOMPARE(project.isDirty(), false);
  QCOMPARE(project.fileInfo().fileName().isEmpty(), true);
  QCOMPARE(project.trees().count(), 0);
  QCOMPARE(project.currentTree(), nullptr);
}

void TestProject::fileFormat()
{
  QCOMPARE(Project::fileFormat(), QString("lcy"));
}

void TestProject::setFileInfo()
{
  const QFileInfo fileInfo("project.lcy");

  Project project("projectName");
  QVERIFY(project.fileInfo() != fileInfo);

  project.setFileInfo(fileInfo);

  QCOMPARE(project.fileInfo(), fileInfo);
}

void TestProject::addTree()
{
  Project project("projectName");

  QCOMPARE(project.trees().count(), 0);

  Tree* tree = new Tree("treeName");
  project.add(tree);

  QCOMPARE(project.trees().count(), 1);
  QCOMPARE(project.trees().first(), tree);
  QCOMPARE(project.isDirty(), true);
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

void TestProject::save_not_dirty()
{
  const QString projectName = "projectName";
  const QString projectFullPath = projectName + "." + Project::fileFormat();

  Project project(projectName);

  QCOMPARE(project.isDirty(), false);

  project.save();

  QCOMPARE(QFile::exists(projectFullPath), false);
}

void TestProject::save_dirty()
{
  const QString projectName = "projectName";
  const QString projectFullPath = projectName + "." + Project::fileFormat();

  Project project(projectName);

  Tree* tree = new Tree("treeName");
  Person* person = new Person("Maxime", "Spriet", QDate());
  tree->addPerson(person);
  tree->setReference(person);

  project.add(tree);
  project.add(person);

  QCOMPARE(project.isDirty(), true);

  project.save();

  QCOMPARE(QFile::exists(projectFullPath), true);
}

void TestProject::cleanupTestCase()
{
  QDir dir("./");
  dir.setNameFilters(QStringList() << "*.lcy");
  dir.setFilter(QDir::Files);

  foreach(const QString file, dir.entryList())
    dir.remove(file);
}
