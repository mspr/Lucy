#ifndef QUERYCLAUSE_H
#define QUERYCLAUSE_H

#include "queryoperator.h"
#include <QVariant>

class QueryClause
{
  public:
    QueryClause();

  private:
    QueryOperator _operator;
    QVariant _value;
};

#endif // QUERYCLAUSE_H
