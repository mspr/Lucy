#include "person_p.h"

#include <QSqlQuery>
#include <QVariant>

Person_p::Person_p(const int id)
  : DomainObject_p(id)
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

}

void Person_p::updateInDatabase()
{

}

void Person_p::setFirstName(const QString& firstName)
{
  _firstName = firstName;
}

void Person_p::setLastName(const QString& lastName)
{
  _lastName = lastName;
}

void Person_p::setBirthDate(const QDate& birthDate)
{
  _birthDate = birthDate;
}
