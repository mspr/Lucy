#include "queryfield.h"

QueryField::QueryField(const QString& name, QMetaType::Type type, QObject* parent)
  : QObject(parent)
  , _droid(QUuid::createUuid())
  , _name(name)
  , _type(type)
{
  Q_ASSERT(!_name.isEmpty());
}

QUuid QueryField::droid() const
{
  return _droid;
}

QString QueryField::name() const
{
  return _name;
}

QMetaType::Type QueryField::type() const
{
  return _type;
}
