#include "queryoperators.h"
#include "queryoperator.h"

QueryOperators::QueryOperators()
{
  QueryOperator* opGreaterThan = new QueryOperator(">", this);
  _operators.append(opGreaterThan);
  QueryOperator* opEqual = new QueryOperator("=", this);
  _operators.append(opEqual);
  QueryOperator* opDifferent = new QueryOperator("<>", this);
  _operators.append(opDifferent);

  QList<QueryOperator*> operatorsForInt;
  operatorsForInt.append(opGreaterThan);
  operatorsForInt.append(opEqual);
  operatorsForInt.append(opDifferent);

  _operatorsByType.insert(QMetaType::Int, operatorsForInt);
}

QList<QueryOperator*> QueryOperators::operatorsByType(QMetaType::Type type) const
{
  return _operatorsByType.value(type);
}
