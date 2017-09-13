#ifndef QUERYCLAUSE_H
#define QUERYCLAUSE_H

#include <QVariant>

class QueryOperator;

class QueryClause
{
  public:
    QueryClause();

  private:
    QVariant _value;
    QHash<QMetaType::Type, QList<QueryOperator*>> operatorsByType;
};

#endif // QUERYCLAUSE_H
