#ifndef PERSON_H
#define PERSON_H

#include "domainobject.h"

#include <QDate>

namespace Business
{
  class Person_p;
  class Tree;
  class Birth;
  class Job;

  class Person : public DomainObject
  {
    DECLARE_PIMPL(Person)

    public:
      Person(const QString& firstName, const QString& lastName, Birth* birth);

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

      QList<Job*> jobs() const;
      void addJob(Job* job);
  };

} // Business

#endif // PERSON_H
