#include "person.h"
#include "person_p.h"

Person::Person(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : DomainObject()
{
  _pimpl->setFirstName(firstName);
  _pimpl->setLastName(lastName);
  _pimpl->setBirthDate(birthDate);
}
