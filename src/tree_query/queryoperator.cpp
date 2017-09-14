#include "queryoperator.h"

QueryOperator::QueryOperator(const QString& text)
  : _text(text)
{
  Q_ASSERT(!_text.isEmpty());
}

QString QueryOperator::text() const
{
  return _text;
}

void QueryOperator::setText(const QString& text)
{
  Q_ASSERT(!text.isEmpty());
  _text = text;
}
