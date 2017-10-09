#include "testtree.h"
#include "business/tree.h"
#include "business/tree_p.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/gender.h"
#include "business/birth.h"

#include <QtTest/QTest>
#include <QSignalSpy>

using namespace Business;

void TestTree::createTree()
{
  const QString treeName = "treeName";

  Tree tree(treeName);

  QCOMPARE(tree.name(), treeName);
  QCOMPARE(tree.isNew(), true);
  QCOMPARE(tree.persons().isEmpty(), true);
  QCOMPARE(tree.reference(), nullptr);
  QCOMPARE(tree.countGenerations(), 0);
}

void TestTree::setName()
{
  const QString newTreeName = "newTreeName";

  Tree tree("treeName");

  QVERIFY(tree.name() != newTreeName);

  tree.setName(newTreeName);

  QCOMPARE(tree.name(), newTreeName);
}

void TestTree::addPerson()
{
  Tree tree("treeName");

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);
  tree.add(maxime);

  QCOMPARE(tree.persons().count(), 1);
  QCOMPARE(tree.persons().first(), maxime);
}

void TestTree::removePerson()
{
  Tree tree("treeName");
  QSignalSpy spy(tree.getD(), SIGNAL(personRemoved(Person*)));

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);
  tree.add(maxime);

  tree.remove(maxime);

  QCOMPARE(tree.persons().isEmpty(), true);
  QCOMPARE(spy.count(), 1);
  const QList<QVariant> arguments = spy.takeFirst();
  Person* person = qvariant_cast<Person*>(arguments.at(0));
  QCOMPARE(person, maxime);

  delete maxime;
}

void TestTree::setReference()
{
  Tree tree("treeName");

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);
  tree.add(maxime);

  QCOMPARE(tree.reference(), nullptr);

  tree.setReference(maxime);

  QCOMPARE(tree.reference(), maxime);
}

void TestTree::countGenerations_reference_only()
{
  Tree tree("treeName");

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);
  tree.add(maxime);
  tree.setReference(maxime);

  QCOMPARE(tree.countGenerations(), 1);
}

void TestTree::countGenerations()
{
  Tree tree("treeName");

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);
  tree.add(maxime);
  tree.setReference(maxime);

  PersonInfo jeanPierreInfo("Jean Pierre", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* jeanPierre = new Person(jeanPierreInfo);
  maxime->setParent(jeanPierre);
  tree.add(jeanPierre);

  PersonInfo mauriceInfo("Maurice", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maurice = new Person(mauriceInfo);
  jeanPierre->setParent(maurice);
  tree.add(maurice);

  PersonInfo claudineInfo("Claudine", "Thual", Gender::Feminine, new Birth(QDate()));
  Person* claudine = new Person(claudineInfo);
  maxime->setParent(claudine);
  tree.add(claudine);

  QCOMPARE(tree.countGenerations(), 3);
}
