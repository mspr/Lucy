#include "person_p.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Person_p::Person_p(const int id)
  : DomainObject_p(id)
{
}

Person_p::Person_p(const QString& firstName, const QString& lastName, const QDate& birthDate)
  : DomainObject_p()
  , _firstName(firstName)
  , _lastName(lastName)
  , _birthDate(birthDate)
{
}

QString Person_p::firstName() const
{
  return _firstName;
}

QString Person_p::lastName() const
{
  return _lastName;
}

QDate Person_p::birthDate() const
{
  return _birthDate;
}

Person* Person_p::father() const
{
  return _father;
}

Person* Person_p::mother() const
{
  return _mother;
}

void Person_p::load_impl(QSqlQuery& query)
{
    _firstName = query.value(1).toString();
    _birthDate = query.value(2).toDate();
    _lastName = query.value(3).toString();
}

QString Person_p::databaseTableName() const
{
  return "Person";
}

void Person_p::insertIntoDatabase()
{
  QString queryStr = "INSERT INTO public.\"Person\" (\"FirstName\", \"BirthDate\", \"LastName\") VALUES (:firstName, :birthDate, :lastName);";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":firstName", QVariant::fromValue(_firstName));
  query.bindValue(":lastName", QVariant::fromValue(_lastName));
  query.bindValue(":birthDate", QVariant::fromValue(_birthDate));

  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _isLoaded = true;
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert Person into database:" << sqlError.text();
  }
}

void Person_p::updateInDatabase()
{

}

void Person_p::setFirstName(const QString& firstName)
{
  _firstName = firstName;
  setDirty();
}

void Person_p::setLastName(const QString& lastName)
{
  _lastName = lastName;
  setDirty();
}

void Person_p::setBirthDate(const QDate& birthDate)
{
  _birthDate = birthDate;
  setDirty();
}

void Person_p::setFather(Person* father)
{
  Q_ASSERT(father != nullptr);
  _father = father;
}

void Person_p::setMother(Person* mother)
{
  Q_ASSERT(mother != nullptr);
  _mother = mother;
}
