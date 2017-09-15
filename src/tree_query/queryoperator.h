#ifndef QUERYOPERATOR_H
#define QUERYOPERATOR_H

#include <QObject>

class QueryOperator : public QObject
{
  public:
    QueryOperator(const QString& text, const QString& sqlText, QObject* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

    QString sqlText() const;
    void setSqlText(const QString& sqlText);

  private:
    QString _text;
    QString _sqlText;
};

#endif // QUERYOPERATOR_H
