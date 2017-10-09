#ifndef TREE_H
#define TREE_H

#include "domainobject.h"

namespace Business
{
  class Tree_p;
  class Person;

  class Tree : public DomainObject
  {
    DECLARE_PIMPL(Tree)

    public:
      Tree(const QString& name);

    public:
      QString name() const;
      void setName(const QString& name);

      QList<Person*> persons() const;
      void add(Person* person);
      void remove(Person* person);
      Person* reference() const;
      void setReference(Person* person);

      int countGenerations() const;
  };

} // Business

#endif // TREE_H
