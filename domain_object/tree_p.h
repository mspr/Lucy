#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

#include <QString>

class Tree_p : public DomainObject_p
{
  public:
    Tree_p(const int id);

    QString name() const;

  protected:
    virtual void load_impl() override;

  private:
    int _id;
    QString _name;
};

#endif // TREE_P_H
