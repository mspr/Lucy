#include "tree.h"

#include <QSqlQuery>
#include <QVariant>

Tree::Tree(const int id)
  : _id(id)
{
  QString queryStr = "SELECT * FROM Tree WHERE Id = :id";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":id", QVariant::fromValue(id));

  if (query.exec())
  {
      while (query.next())
      {
          QString country = query.value(0).toString();
      }
  }
}
