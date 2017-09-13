#ifndef QUERYOPERATOR_H
#define QUERYOPERATOR_H

#include <QString>

class QueryOperator
{
  public:
    QueryOperator();
    QueryOperator(const QString& text);

    QString text() const;
    void setText(const QString& text);

  private:
    QString _text;
};

#endif // QUERYOPERATOR_H
