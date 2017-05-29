#include "tree.h"
#include "tree_p.h"

Tree::Tree(const int id)
{
}

QString Tree::name() const
{
  return d()->name();
}
