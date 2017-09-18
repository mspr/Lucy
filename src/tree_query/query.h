#ifndef QUERY_H
#define QUERY_H

#include <QObject>
#include <QList>

class QueryClause;

class Query : public QObject
{
  public:
    Query(const QString& name, QObject* parent = nullptr);

    QString name() const;
    void setName(const QString& name);

    QList<int> execute();

  private:
    QString _name;
    QList<QueryClause*> _clauses;
};

#endif // QUERY_H
