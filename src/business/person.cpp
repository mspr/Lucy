#include "person.h"
#include "person_p.h"
#include "personinfo.h"

using namespace Business;

DEFINE_PIMPL(Person)

Person::Person(const PersonInfo& personInfo)
  : _pimpl(new Person_p(this, personInfo))
{
}

PersonInfo Person::info() const
{
  return d()->info();
}

Gender Person::gender() const
{
  return d()->gender();
}

void Person::setGender(Gender gender)
{
  d()->setGender(gender);
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

Birth* Person::birth() const
{
  return d()->birth();
}

void Person::setBirth(Birth* birth)
{
  d()->setBirth(birth);
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

void Person::setParent(Person* parent)
{
  d()->setParent(parent);
}

QList<Job*> Person::jobs() const
{
  return d()->jobs();
}

void Person::addJob(Job* job)
{
  d()->addJob(job);
}
