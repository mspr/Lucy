#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

Tree::Tree(const QString& name)
  : _pimpl(new Tree_p(this, name))
{
}

void Tree::setName(const QString& name)
{
  d()->setName(name);
}

void Tree::addPerson(Person* person)
{
  d()->addPerson(person);
}

void Tree::setReference(Person* person)
{
  d()->setReference(person);
}

QString Tree::name() const
{
  return d()->name();
}

QList<Person*> Tree::persons() const
{
  return d()->persons();
}

Person* Tree::reference() const
{
  return d()->reference();
}
