#include "testtree.h"
#include "business/tree.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/gender.h"
#include "business/birth.h"

#include <QtTest/QTest>

using namespace Business;

void TestTree::countGenerations_empty()
{
  Tree tree("treeName");

  QCOMPARE(tree.countGenerations(), 0);
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
  Birth birth(QDate());

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
