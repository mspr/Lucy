#include "person.h"
#include "person_p.h"

DEFINE_PIMPL(Person)

Person::Person(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : Person()
{
  _pimpl->setFirstName(firstName);
  _pimpl->setLastName(lastName);
  _pimpl->setBirthDate(birthDate);
}
