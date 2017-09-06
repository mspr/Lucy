#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QDate>

namespace Business
{
  class Person;
  class Tree;

  class Person_p : public DomainObject_p
  {
    DECLARE_FACADE(Person)

    public:
      Person_p(Person* facade, const QString& firstName, const QString& lastName, const QDate& birthDate);

      QString firstName() const;
      QString lastName() const;
      QDate birthDate() const;
      QString birthPlace() const;
      QDate deathDate() const;
      QString deathPlace() const;
      Person* father() const;
      Person* mother() const;
      Tree* tree() const;

      void setTree(Tree* tree);
      void setFirstName(const QString& firstName);
      void setLastName(const QString& lastName);
      void setBirthDate(const QDate& birthDate);
      void setBirthPlace(const QString& birthPlace);
      void setDeathDate(const QDate& deathDate);
      void setDeathPlace(const QString& deathPlace);
      void setFather(Person* father);
      void setMother(Person* mother);

      virtual void insertIntoDatabase();
      virtual void updateInDatabase();

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
  };

} // Business

#endif // PERSON_P_H
