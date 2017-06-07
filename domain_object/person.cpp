#include "person.h"
#include "person_p.h"

DEFINE_PIMPL(Person)

Person::Person(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : _pimpl(new Person_p(firstName, lastName, birthDate))
{
}

QString Person::firstName() const
{
  return d()->firstName();
}

QString Person::lastName() const
{
  return d()->lastName();
}

QDate Person::birthDate() const
{
  return d()->birthDate();
}
