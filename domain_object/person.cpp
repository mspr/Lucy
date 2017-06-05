#include "person.h"
#include "person_p.h"

DEFINE_PIMPL(Person)

Person::Person(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : _pimpl(new Person_p(firstName, lastName, birthDate))
{
}
