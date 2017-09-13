#ifndef QUERYOPERATORS_H
#define QUERYOPERATORS_H

#include "queryoperator.h"
#include <QMetaType>
#include <QHash>

class QueryOperators
{
  public:
    static QList<QueryOperator> operatorsByType(QMetaType::Type);

  private:
    QueryOperators() = delete;

  private:
    static QHash<QMetaType::Type, QList<QueryOperator>> initializeOperatorsByType();

  private:
    static QHash<QMetaType::Type, QList<QueryOperator>> _operatorsByType;
};

#endif // QUERYOPERATORS_H
