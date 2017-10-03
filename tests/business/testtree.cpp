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

  PersonInfo maximeInfo;
  maximeInfo.firstName = "Maxime";
  maximeInfo.lastName = "Spriet";
  maximeInfo.gender = Gender::Masculine;
  maximeInfo.birth = new Birth(QDate());
  Person maxime(maximeInfo);
  tree.add(&maxime);
  tree.setReference(&maxime);

  QCOMPARE(tree.countGenerations(), 1);
}

void TestTree::countGenerations()
{
  Tree tree("treeName");
  Birth birth(QDate());

//  PersonInfo maximeInfo;
//  maximeInfo.firstName = "Maxime";
//  maximeInfo.lastName = "Spriet";
//  maximeInfo.gender = Gender::Masculine;
//  maximeInfo.birth = &birth;
//  Person maxime(maximeInfo);
//  tree.add(&maxime);
//  tree.setReference(&maxime);

//  PersonInfo jeanPierreInfo;
//  jeanPierreInfo.firstName = "Jean Pierre";
//  jeanPierreInfo.lastName = "Spriet";
//  jeanPierreInfo.gender = Gender::Masculine;
//  jeanPierreInfo.birth = &birth;
//  Person jeanPierre(jeanPierreInfo);
//  maxime.setParent(&jeanPierre);
//  tree.add(&jeanPierre);

//  PersonInfo MauriceInfo;
//  MauriceInfo.firstName = "Maurice";
//  MauriceInfo.lastName = "Spriet";
//  MauriceInfo.gender = Gender::Masculine;
//  MauriceInfo.birth = &birth;
//  Person maurice(MauriceInfo);
//  jeanPierre.setParent(&maurice);
//  tree.add(&maurice);

//  PersonInfo claudineInfo;
//  claudineInfo.firstName = "Claudine";
//  claudineInfo.lastName = "Thual";
//  claudineInfo.gender = Gender::Feminine;
//  claudineInfo.birth = &birth;
//  Person claudine(claudineInfo);
//  maxime.setParent(&claudine);
//  tree.add(&claudine);

  QCOMPARE(tree.countGenerations(), 3);
}
