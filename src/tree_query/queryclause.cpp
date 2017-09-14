#include "queryclause.h"

QueryClause::QueryClause()
{
}

QueryField* QueryClause::field() const
{
  return _field;
}

QueryOperator* QueryClause::queryOperator() const
{
  return _operator;
}

QVariant QueryClause::value() const
{
  return _value;
}
