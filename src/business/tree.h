#ifndef TREE_H
#define TREE_H

#include "domainobject.h"

#include <QString>

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
      QList<Person*> persons() const;
      Person* reference() const;

      void setName(const QString& name);
      void addPerson(Person* person);
      void setReference(Person* person);
  };

} // Business

#endif // TREE_H
