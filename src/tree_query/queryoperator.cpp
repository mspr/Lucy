#include "queryoperator.h"

QueryOperator::QueryOperator(const QString& text)
  : _text(text)
{
}

QString QueryOperator::toString() const
{
  return _text;
}
