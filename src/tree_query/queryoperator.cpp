#include "queryoperator.h"

QueryOperator::QueryOperator(const QString& text, const QString& sqlText, QObject* parent)
  : QObject(parent)
  , _text(text)
  , _sqlText(sqlText)
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

QString QueryOperator::sqlText() const
{
  return _sqlText;
}

void QueryOperator::setSqlText(const QString& sqlText)
{
  Q_ASSERT(!sqlText.isEmpty());
  _sqlText = sqlText;
}
