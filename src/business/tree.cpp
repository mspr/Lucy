#include "tree.h"
#include "tree_p.h"

using namespace Business;

DEFINE_PIMPL(Tree)

Tree::Tree(const QString& name)
  : _pimpl(new Tree_p(this, name))
{
}

QString Tree::name() const
{
  return d()->name();
}

void Tree::setName(const QString& name)
{
  d()->setName(name);
}

QList<Person*> Tree::persons() const
{
  return d()->persons();
}

void Tree::add(Person* person)
{
  d()->add(person);
}

void Tree::remove(Person* person)
{
  d()->remove(person);
}

Person* Tree::reference() const
{
  return d()->reference();
}

void Tree::setReference(Person* person)
{
  d()->setReference(person);
}

int Tree::countGenerations() const
{
  return d()->countGenerations();
}
