#ifndef QUERYCLAUSE_H
#define QUERYCLAUSE_H

#include "queryfield.h"
#include "queryoperator.h"
#include <QVariant>

class QueryClause
{
  public:
    QueryClause();

  private:
    QUuid _selectedFieldDroid;
    QueryOperator _operator;
    QVariant _value;
};

#endif // QUERYCLAUSE_H
