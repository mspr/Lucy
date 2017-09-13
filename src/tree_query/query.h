#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QList>

class Clause;

class Query
{
  public:
    Query(const QString& name);

    QString name() const;
    void setName(const QString& name);

  private:
    QString _name;
    QList<Clause*> _clauses;
};

#endif // QUERY_H
