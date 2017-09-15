#include "query.h"
#include "queryclause.h"
#include "queryfield.h"
#include "queryoperator.h"

#include <QSqlQuery>

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
  if (_clauses.count() == 0)
    return;

  QString queryStr = "SELECT * FROM public.\"Person\" WHERE 1 ";

  for (int i=0; i<_clauses.count(); ++i)
  {
    QueryClause* clause = _clauses.at(i);
    const QString fieldName = clause->field()->name();
    const QString operatorSqlText = clause->queryOperator()->sqlText();
    const QVariant value = clause->value();

    queryStr += " AND " + fieldName + operatorSqlText + value.toString();
  }

  queryStr += ";";

  QSqlQuery query;
  query.prepare(queryStr);
  if (query.exec())
  {
    QList<int> personIds;

    if (query.next())
    {
      const int personId = query.value(0).toInt();
      personIds.append(personId);
    }
  }
}