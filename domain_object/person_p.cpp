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

void Person_p::load_impl(QSqlQuery& query)
{
    while (query.next())
    {
        _firstName = query.value(0).toString();
        _birthDate = query.value(1).toDate();
        _lastName = query.value(2).toString();
    }
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
