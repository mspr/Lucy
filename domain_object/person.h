#ifndef PERSON_H
#define PERSON_H

#include "domainobject.h"

class Person_p;

class Person : public DomainObject
{
  DECLARE_PIMPL(Person)

  public:
    Person(const QString& firstName, const QString& lastName, const QDate& birthDate);
};

#endif // PERSON_H
