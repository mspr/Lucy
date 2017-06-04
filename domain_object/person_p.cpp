#include "person_p.h"

#include <QSqlQuery>
#include <QVariant>

Person_p::Person_p(const int id)
  : DomainObject_p(id)
{
}

void Person_p::load_impl()
{
  QString queryStr = "SELECT * FROM public.\"Person\" WHERE \"Id\" = :id";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":id", QVariant::fromValue(_id));

  if (query.exec())
  {
      while (query.next())
      {
          _firstName = query.value(0).toString();
          _birthDate = query.value(1).toDate();
          _lastName = query.value(2).toString();
      }
  }
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
