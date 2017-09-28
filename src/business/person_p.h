#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QDate>

namespace Business
{
  class Person;
  struct PersonInfo;
  enum class Gender;
  class Tree;
  class Birth;
  class Job;

  class Person_p : public DomainObject_p
  {
    DECLARE_FACADE(Person)

    public:
      Person_p(Person* facade, const PersonInfo& personInfo);

      PersonInfo info() const;

      Gender gender() const;
      void setGender(Gender gender);

      QString firstName() const;
      void setFirstName(const QString& firstName);

      QString lastName() const;
      void setLastName(const QString& lastName);

      Birth* birth() const;
      void setBirth(Birth* birth);

      QDate deathDate() const;
      void setDeathDate(const QDate& deathDate);

      QString deathPlace() const;
      void setDeathPlace(const QString& deathPlace);

      Person* father() const;
      Person* mother() const;
      void setParent(Person* parent);
      Person* child() const;

      Tree* tree() const;
      void setTree(Tree* tree);

      QList<Job*> jobs() const;
      void addJob(Job* job);

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QSqlQuery prepareInsertIntoDatabaseQuery() override;
      virtual QSqlQuery prepareUpdateInDatabaseQuery() override;
      virtual QString databaseTableName() const override;

    private:
      void setFather(Person* father);
      void setMother(Person* mother);
      void setChild(Person* child);

    private:
      Tree* _tree;
      Gender _gender;
      QString _firstName;
      QString _lastName;
      Birth* _birth;
      QDate _deathDate;
      QString _deathPlace;
      Person* _father;
      Person* _mother;
      Person* _child;
      QList<Job*> _jobs;
  };

} // Business

#endif // PERSON_P_H
