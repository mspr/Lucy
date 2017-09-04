#include "person.h"
#include "person_p.h"

DEFINE_PIMPL(Person)

Person::Person(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : _pimpl(new Person_p(this, firstName, lastName, birthDate))
{
}

QString Person::firstName() const
{
  return d()->firstName();
}

void Person::setFirstName(const QString& firstName)
{
  d()->setFirstName(firstName);
}

QString Person::lastName() const
{
  return d()->lastName();
}

void Person::setLastName(const QString& lastName)
{
  d()->setLastName(lastName);
}

QDate Person::birthDate() const
{
  return d()->birthDate();
}

void Person::setBirthDate(const QDate& birthDate)
{
  d()->setBirthDate(birthDate);
}

Tree* Person::tree() const
{
  return d()->tree();
}

void Person::setTree(Tree* tree)
{
  d()->setTree(tree);
}

Person* Person::father() const
{
  return d()->father();
}

void Person::setFather(Person* father)
{
  d()->setFather(father);
}

Person* Person::mother() const
{
  return d()->mother();
}

void Person::setMother(Person* mother)
{
  d()->setMother(mother);
}
