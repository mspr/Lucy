#include "query.h"

Query::Query(const QString& name)
  : _name(name)
{
  Q_ASSERT(!_name.isEmpty());
}

QString Query::name() const
{
  return _name;
}

void Query::setName(const QString& name)
{
  Q_ASSERT(!name.isEmpty());
  _name = name;
}

void Query::execute()
{
  QString queryStr = "SELECT * FROM public.\"Person\" WHERE";

//  QSqlQuery query;
//  query.prepare(queryStr);
//  query.bindValue(":firstName", QVariant::fromValue(_firstName));
}
