#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QDate>

namespace Business
{
  class Person;
  enum class Gender;
  class Tree;
  class Birth;
  class Job;

  class Person_p : public DomainObject_p
  {
    DECLARE_FACADE(Person)

    public:
      Person_p(Person* facade, Gender gender, const QString& firstName, const QString& lastName, Birth* birth);

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
      void setFather(Person* father);
      Person* mother() const;
      void setMother(Person* mother);
      void setParent(Person* parent);

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
      Tree* _tree;
      Gender _gender;
      QString _firstName;
      QString _lastName;
      Birth* _birth;
      QDate _deathDate;
      QString _deathPlace;
      Person* _father;
      Person* _mother;
      QList<Job*> _jobs;
  };

} // Business

#endif // PERSON_P_H
