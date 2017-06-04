#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

Tree::Tree(const QString& name)
  : DomainObject()
{
  _pimpl->setName(name);
}

QString Tree::name() const
{
  return d()->name();
}
