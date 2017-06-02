#ifndef TREE_H
#define TREE_H

#include "domainobject.h"

#include <QString>

class Tree_p;

class Tree
{
  DECLARE_PIMPL(Tree)

  public:
    QString name() const;
};

#endif // TREE_H
