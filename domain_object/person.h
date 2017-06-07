#ifndef PERSON_H
#define PERSON_H

#include "domainobject.h"

#include <QDate>

class Person_p;

class Person : public DomainObject
{
  DECLARE_PIMPL(Person)

  public:
    Person(const QString& firstName, const QString& lastName, const QDate& birthDate);

    QString firstName() const;
    QString lastName() const;
    QDate birthDate() const;
};

#endif // PERSON_H
