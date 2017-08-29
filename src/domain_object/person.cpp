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

QString Person::lastName() const
{
  return d()->lastName();
}

QDate Person::birthDate() const
{
  return d()->birthDate();
}

Person* Person::father() const
{
  return d()->father();
}

Person* Person::mother() const
{
  return d()->mother();
}

Tree* Person::tree() const
{
  return d()->tree();
}

void Person::setTree(Tree* tree)
{
  d()->setTree(tree);
}

void Person::setFather(Person* father)
{
  d()->setFather(father);
}

void Person::setMother(Person* mother)
{
  d()->setMother(mother);
}
