#ifndef QUERYOPERATORS_H
#define QUERYOPERATORS_H

#include <QObject>
#include <QHash>

class QueryOperator;

class QueryOperators : public QObject
{
  public:
    QueryOperators();

    QList<QueryOperator*> operatorsByType(QMetaType::Type) const;

  private:
    QList<QueryOperator*> _operators;
    QHash<QMetaType::Type, QList<QueryOperator*>> _operatorsByType;
};

#endif // QUERYOPERATORS_H
