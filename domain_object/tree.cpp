#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

Tree::Tree(const int id)
{
}

QString Tree::name() const
{
  return d()->name();
}
