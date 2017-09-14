#include "queryoperators.h"
#include "queryoperator.h"

QueryOperators::QueryOperators()
{
  QueryOperator* opGreaterThan = new QueryOperator(">");
  _operators.append(opGreaterThan);
  QueryOperator* opEqual = new QueryOperator("=");
  _operators.append(opEqual);
  QueryOperator* opDifferent = new QueryOperator("<>");
  _operators.append(opDifferent);

  QList<QueryOperator*> operatorsForInt;
  operatorsForInt.append(opGreaterThan);
  operatorsForInt.append(opEqual);
  operatorsForInt.append(opDifferent);

  _operatorsByType.insert(QMetaType::Int, operatorsForInt);
}

QueryOperators::~QueryOperators()
{
  qDeleteAll(_operators);
  _operators.clear();
  _operatorsByType.clear();
}

QList<QueryOperator*> QueryOperators::operatorsByType(QMetaType::Type type) const
{
  return _operatorsByType.value(type);
}
