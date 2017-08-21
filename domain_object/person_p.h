#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QDate>

class Person;

class Person_p : public DomainObject_p
{
  public:
    Person_p(const int id);
    Person_p(const QString& firstName, const QString& lastName, const QDate& birthDate);

    QString firstName() const;
    QString lastName() const;
    QDate birthDate() const;
    Person* father() const;
    Person* mother() const;

    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setBirthDate(const QDate& birthDate);
    void setFather(Person* father);
    void setMother(Person* mother);

    virtual void insertIntoDatabase();
    virtual void updateInDatabase();

  protected:
    virtual void load_impl(QSqlQuery& query) override;
    virtual QString databaseTableName() const override;

  private:
    QString _firstName;
    QString _lastName;
    QDate _birthDate;
    Person* _father;
    Person* _mother;
};

#endif // PERSON_P_H
