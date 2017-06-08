#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

Tree::Tree(const QString& name, Person* reference)
  : _pimpl(new Tree_p(name, reference))
{
}

void Tree::setName(const QString& name)
{
  d()->setName(name);
}

Person* Tree::reference() const
{
  return d()->reference();
}

QString Tree::name() const
{
  return d()->name();
}
