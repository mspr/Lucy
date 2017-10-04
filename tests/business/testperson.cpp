#include "testperson.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/gender.h"
#include "business/birth.h"

#include <QtTest/QTest>

using namespace Business;

void TestPerson::createPerson()
{
  const QString firstName = "Maxime";
  const QString lastName = "Spriet";
  const Gender gender = Gender::Masculine;
  Birth* birth = new Birth(QDate());

  PersonInfo maximeInfo(firstName, lastName, gender, birth);
  Person person(maximeInfo);

  QCOMPARE(person.firstName(), firstName);
  QCOMPARE(person.lastName(), lastName);
  QCOMPARE(person.gender(), gender);
  QCOMPARE(person.birth(), birth);
  QCOMPARE(person.tree(), nullptr);
  QCOMPARE(person.father(), nullptr);
  QCOMPARE(person.mother(), nullptr);
  QCOMPARE(person.child(), nullptr);
  QCOMPARE(person.isNew(), true);
}
