#ifndef QUERYFIELDS_H
#define QUERYFIELDS_H

#include "queryfield.h"
#include <QList>

class QueryFields
{
  public:
    static QList<QueryField> fields();

  private:
    QueryFields() = delete;

  private:
    static QList<QueryField> initializeFields();

  private:
    static QList<QueryField> _fields;
};

#endif // QUERYFIELDS_H
