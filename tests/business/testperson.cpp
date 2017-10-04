#include "testperson.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/gender.h"
#include "business/birth.h"
#include "business/tree.h"

#include <QtTest/QTest>

using namespace Business;

void TestPerson::createPerson()
{
  const QString firstName = "Maxime";
  const QString lastName = "Spriet";
  const Gender gender = Gender::Masculine;
  Birth* birth = new Birth(QDate());

  PersonInfo maximeInfo(firstName, lastName, gender, birth);
  Person maxime(maximeInfo);

  QCOMPARE(maxime.firstName(), firstName);
  QCOMPARE(maxime.lastName(), lastName);
  QCOMPARE(maxime.gender(), gender);
  QCOMPARE(maxime.birth(), birth);
  QCOMPARE(maxime.tree(), nullptr);
  QCOMPARE(maxime.hasParents(), false);
  QCOMPARE(maxime.hasFather(), false);
  QCOMPARE(maxime.father(), nullptr);
  QCOMPARE(maxime.hasMother(), false);
  QCOMPARE(maxime.mother(), nullptr);
  QCOMPARE(maxime.child(), nullptr);
  QCOMPARE(maxime.isNew(), true);
}

void TestPerson::setTree()
{
  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person* maxime = new Person(maximeInfo);

  Tree tree("TreeName");
  maxime->setTree(&tree);

  QCOMPARE(maxime->tree(), &tree);
}

void TestPerson::setFirstName()
{
  const QString newFirstName = "Max";

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person maxime(maximeInfo);

  QVERIFY(maxime.firstName() != newFirstName);

  maxime.setFirstName(newFirstName);

  QCOMPARE(maxime.firstName(), newFirstName);
}

void TestPerson::setLastName()
{
  const QString newLastName = "Thual";

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person maxime(maximeInfo);

  QVERIFY(maxime.lastName() != newLastName);

  maxime.setLastName(newLastName);

  QCOMPARE(maxime.lastName(), newLastName);
}

void TestPerson::setGender()
{
  const Gender newGender = Gender::Feminine;

  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person maxime(maximeInfo);

  QVERIFY(maxime.gender() != newGender);

  maxime.setGender(newGender);

  QCOMPARE(maxime.gender(), newGender);
}

void TestPerson::setFather()
{
  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person maxime(maximeInfo);

  PersonInfo jeanPierreInfo("Jean Pierre", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person jeanPierre(jeanPierreInfo);

  maxime.setParent(&jeanPierre);

  QCOMPARE(maxime.hasParents(), true);
  QCOMPARE(maxime.hasFather(), true);
  QCOMPARE(maxime.father(), &jeanPierre);
  QCOMPARE(jeanPierre.child(), &maxime);
}

void TestPerson::setMother()
{
  PersonInfo maximeInfo("Maxime", "Spriet", Gender::Masculine, new Birth(QDate()));
  Person maxime(maximeInfo);

  PersonInfo claudineInfo("Claudine", "Thual", Gender::Feminine, new Birth(QDate()));
  Person claudine(claudineInfo);

  maxime.setParent(&claudine);

  QCOMPARE(maxime.hasMother(), true);
  QCOMPARE(maxime.mother(), &claudine);
  QCOMPARE(claudine.child(), &maxime);
}
