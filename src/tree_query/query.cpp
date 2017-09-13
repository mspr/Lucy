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
