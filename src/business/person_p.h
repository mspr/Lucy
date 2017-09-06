#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QDate>

namespace Business
{
  class Person;
  class Tree;
  class Job;

  class Person_p : public DomainObject_p
  {
    DECLARE_FACADE(Person)

    public:
      Person_p(Person* facade, const QString& firstName, const QString& lastName, const QDate& birthDate);

      QString firstName() const;
      void setFirstName(const QString& firstName);

      QString lastName() const;
      void setLastName(const QString& lastName);

      QDate birthDate() const;
      void setBirthDate(const QDate& birthDate);

      QString birthPlace() const;
      void setBirthPlace(const QString& birthPlace);

      QDate deathDate() const;
      void setDeathDate(const QDate& deathDate);

      QString deathPlace() const;
      void setDeathPlace(const QString& deathPlace);

      Person* father() const;
      void setFather(Person* father);

      Person* mother() const;
      void setMother(Person* mother);

      Tree* tree() const;
      void setTree(Tree* tree);

      QList<Job*> jobs() const;
      void addJob(Job* job);

      virtual void insertIntoDatabase() override;
      virtual void updateInDatabase() override;

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QString databaseTableName() const override;

    private:
      Tree* _tree;
      QString _firstName;
      QString _lastName;
      QDate _birthDate;
      QString _birthPlace;
      QDate _deathDate;
      QString _deathPlace;
      Person* _father;
      Person* _mother;
      QList<Job*> _jobs;
  };

} // Business

#endif // PERSON_P_H
