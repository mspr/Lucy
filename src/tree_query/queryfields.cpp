#include "queryfields.h"

QList<QueryField> QueryFields::_fields = QueryFields::initializeFields();

QList<QueryField> QueryFields::initializeFields()
{
  QList<QueryField> fields;

  fields.append(QueryField("Age", QMetaType::Int));

  return fields;
}

QList<QueryField> QueryFields::fields()
{
  return _fields;
}
