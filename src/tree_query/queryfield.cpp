#include "queryfield.h"

QueryField::QueryField(const QString& name)
  : _name(name)
{
  Q_ASSERT(!_name.isEmpty());
}

QString QueryField::name() const
{
  return _name;
}
