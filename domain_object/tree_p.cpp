#include "tree_p.h"

#include <QSqlQuery>
#include <QVariant>

Tree_p::Tree_p(const int id)
  : DomainObject_p(id)
{
}

void Tree_p::load_impl(QSqlQuery& query)
{
    while (query.next())
    {
        _name = query.value(0).toString();
        _rootId = query.value(1).toInt();
    }
}

QString Tree_p::databaseTableName() const
{
  return "Tree";
}

void Tree_p::insertIntoDatabase()
{

}

void Tree_p::updateInDatabase()
{

}

QString Tree_p::name() const
{
  return _name;
}

void Tree_p::setName(const QString& name)
{
  _name = name;
}
