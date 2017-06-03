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
          _name = query.value(0).toString();
      }
  }
}
