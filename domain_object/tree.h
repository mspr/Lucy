#ifndef TREE_H
#define TREE_H

#include "domainobject.h"

#include <QString>

class Tree_p;

class Tree : public DomainObject
{
  DECLARE_PIMPL(Tree)

  public:
    Tree(const QString& name);

  public:
    QString name() const;
};

#endif // TREE_H
