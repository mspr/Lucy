#ifndef QUERYCLAUSE_H
#define QUERYCLAUSE_H

#include <QObject>
#include <QVariant>

class QueryField;
class QueryOperator;

class QueryClause : public QObject
{
  public:
    QueryClause(QObject* parent = nullptr);

    QueryField* field() const;
    QueryOperator* queryOperator() const;
    QVariant value() const;

  private:
    QueryField* _field;
    QueryOperator* _operator;
    QVariant _value;
};

#endif // QUERYCLAUSE_H
