#include "domainobject_p.h"

#include <QSqlQuery>
#include <QVariant>

DomainObject_p::DomainObject_p(const int id)
  : _id(id),
    _isLoaded(false)
{
}

DomainObject_p::DomainObject_p()
{
}

DomainObject_p::~DomainObject_p()
{
}

void DomainObject_p::tryLoad()
{
  if (!_isLoaded)
  {
    QString queryStr = "SELECT * FROM public.\"" + databaseTableName() + "\" WHERE \"Id\" = :id";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":id", QVariant::fromValue(_id));

    if (query.exec())
    {
      load_impl(query);

      _isLoaded = true;
    }
    else
    {
    }
  }
}

void DomainObject_p::deleteFromDatabase()
{
  QString queryStr = "DELETE FROM public.\"" + databaseTableName() + "\" WHERE \"Id\" = :id";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":id", QVariant::fromValue(_id));

  query.exec();
}
