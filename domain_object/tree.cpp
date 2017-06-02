#include "tree.h"
#include "tree_p.h"

DEFINE_PIMPL(Tree)

QString Tree::name() const
{
  return d()->name();
}
