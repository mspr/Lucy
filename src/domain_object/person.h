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
    void setFirstName(const QString& firstName);

    QString lastName() const;
    void setLastName(const QString& lastName);

    QDate birthDate() const;
    void setBirthDate(const QDate& birthDate);

    Tree* tree() const;
    void setTree(Tree* tree);

    Person* father() const;
    void setFather(Person* father);

    Person* mother() const;
    void setMother(Person* mother);
};

#endif // PERSON_H
