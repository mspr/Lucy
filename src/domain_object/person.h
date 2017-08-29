#ifndef PERSON_H
#define PERSON_H

#include "domainobject.h"

#include <QDate>

class Person_p;
class Tree;

class Person : public DomainObject
{
  DECLARE_PIMPL(Person)

  public:
    Person(const QString& firstName, const QString& lastName, const QDate& birthDate);

    QString firstName() const;
    QString lastName() const;
    QDate birthDate() const;
    Person* father() const;
    Person* mother() const;
    Tree* tree() const;

    void setTree(Tree* tree);
    void setFather(Person* father);
    void setMother(Person* mother);
};

#endif // PERSON_H
