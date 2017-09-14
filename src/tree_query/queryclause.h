#ifndef QUERYCLAUSE_H
#define QUERYCLAUSE_H

#include <QVariant>
#include <QUuid>

class QueryField;
class QueryOperator;

class QueryClause
{
  public:
    QueryClause();

    QueryField* field() const;
    QueryOperator* queryOperator() const;
    QVariant value() const;

  private:
    QueryField* _field;
    QueryOperator* _operator;
    QVariant _value;
};

#endif // QUERYCLAUSE_H
