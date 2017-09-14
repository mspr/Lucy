#ifndef QUERYFIELDS_H
#define QUERYFIELDS_H

#include <QObject>

class QueryField;

class QueryFields : public QObject
{
  public:
    QueryFields(QObject* parent = nullptr);
    ~QueryFields();

    QList<QueryField*> fields() const;
    QueryField* field(const QUuid& droid) const;
    QList<QString> fieldNames() const;

  private:
    QList<QueryField*> _fields;
};

#endif // QUERYFIELDS_H
