#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

Tree::Tree(const QString& name, Person* reference)
  : Tree()
{
  _pimpl->setName(name);
  _pimpl->setReference(reference);
}

QString Tree::name() const
{
  return d()->name();
}
