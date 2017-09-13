#ifndef QUERYOPERATOR_H
#define QUERYOPERATOR_H

#include <QString>

class QueryOperator
{
  public:
    QueryOperator(const QString& text);

    QString toString() const;

  private:
    QString _text;
};

#endif // QUERYOPERATOR_H
