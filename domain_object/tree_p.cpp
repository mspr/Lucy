#include "tree_p.h"

#include <QSqlQuery>
#include <QVariant>

Tree_p::Tree_p(const int id)
  : DomainObject_p(id)
{
}

void Tree_p::load_impl()
{
  QString queryStr = "SELECT * FROM public.\"Tree\" WHERE \"Id\" = :id";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":id", QVariant::fromValue(_id));

  if (query.exec())
  {
      while (query.next())
      {
          _name = query.value(0).toString();
          _rootId = query.value(1).toInt();
      }
  }
}

QString Tree_p::name() const
{
  return _name;
}
