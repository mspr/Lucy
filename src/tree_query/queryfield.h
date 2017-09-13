#ifndef QUERYFIELD_H
#define QUERYFIELD_H

#include <QString>

class QueryField
{
  public:
    QueryField(const QString& name);

    QString name() const;

  private:
    QString _name;
};

#endif // QUERYFIELD_H
