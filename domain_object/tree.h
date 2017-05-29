#ifndef TREE_H
#define TREE_H

#include "domainobject.h"

#include <QString>

class Tree_p;

class Tree
{
  DEFINE_PIMPL(Tree_p)

  public:
    Tree(const int id);

    QString name() const;
};

#endif // TREE_H
