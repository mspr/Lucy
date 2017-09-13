#include "queryoperators.h"

QHash<QMetaType::Type, QList<QueryOperator>> QueryOperators::_operatorsByType = QueryOperators::initializeOperatorsByType();

/*static*/ QHash<QMetaType::Type, QList<QueryOperator>> QueryOperators::initializeOperatorsByType()
{
  QHash<QMetaType::Type, QList<QueryOperator>> operatorsByType;

  QueryOperator opGreaterThan(">");
  QueryOperator opEqual("=");
  QueryOperator opDifferent("<>");

  QList<QueryOperator> operatorsForInt;
  operatorsForInt.append(opGreaterThan);
  operatorsForInt.append(opEqual);
  operatorsForInt.append(opDifferent);

  operatorsByType.insert(QMetaType::Int, operatorsForInt);

  return operatorsByType;
}

/*static*/ QList<QueryOperator> QueryOperators::operatorsByType(QMetaType::Type type)
{
  return _operatorsByType.value(type);
}
