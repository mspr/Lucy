#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QList>

class QueryClause;

class Query
{
  public:
    Query(const QString& name);

    QString name() const;
    void setName(const QString& name);

    QList<int> execute();

  private:
    QString _name;
    QList<QueryClause*> _clauses;
};

#endif // QUERY_H
