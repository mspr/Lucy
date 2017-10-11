#ifndef PERSON_H
#define PERSON_H

#include "domainobject.h"

#include <QDate>

namespace Business
{
  class Person_p;
  struct PersonInfo;
  enum class Gender;
  class Tree;
  class Birth;
  class Job;

  class Person : public DomainObject
  {
    Q_OBJECT

    DECLARE_PIMPL(Person)

    public:
      Person(const PersonInfo& personInfo);

      PersonInfo info() const;

      Gender gender() const;
      void setGender(Gender gender);

      QString firstName() const;
      void setFirstName(const QString& firstName);

      QString lastName() const;
      void setLastName(const QString& lastName);

      Birth* birth() const;

      Tree* tree() const;
      void setTree(Tree* tree);

      Person* father() const;
      bool hasFather() const;
      Person* mother() const;
      bool hasMother() const;
      void setParent(Person* parent);
      bool hasParents() const;
      Person* child() const;
      bool hasChild() const;

      QList<Job*> jobs() const;
      void addJob(Job* job);
  };

} // Business

Q_DECLARE_METATYPE(Business::Person*)

#endif // PERSON_H
