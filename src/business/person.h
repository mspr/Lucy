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
    DECLARE_PIMPL(Person)

    public:
      Person(const PersonInfo& personInfo);

      Gender gender() const;
      void setGender(Gender gender);

      QString firstName() const;
      void setFirstName(const QString& firstName);

      QString lastName() const;
      void setLastName(const QString& lastName);

      Birth* birth() const;
      void setBirth(Birth* birth);

      Tree* tree() const;
      void setTree(Tree* tree);

      Person* father() const;
      void setFather(Person* father);
      Person* mother() const;
      void setMother(Person* mother);
      void setParent(Person* parent);

      QList<Job*> jobs() const;
      void addJob(Job* job);
  };

} // Business

#endif // PERSON_H
