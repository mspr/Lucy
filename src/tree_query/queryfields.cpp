#include "queryfields.h"
#include "queryfield.h"

QueryFields::QueryFields(QObject* parent)
  : QObject(parent)
{
  _fields.append(new QueryField("Age", QMetaType::Int));
}

QueryFields::~QueryFields()
{
  qDeleteAll(_fields);
  _fields.clear();
}

QueryField* QueryFields::field(const QUuid& droid) const
{
  for (int i=0; i<_fields.count(); ++i)
  {
    if (_fields.at(i)->droid() == droid)
      return _fields.at(i);
  }

  return nullptr;
}

QList<QueryField*> QueryFields::fields() const
{
  return _fields;
}

QList<QString> QueryFields::fieldNames() const
{
  QList<QString> names;

  for (int i=0; i<_fields.count(); ++i)
    names.append(_fields.at(i)->name());

  return names;
}
