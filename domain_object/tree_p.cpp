#include "tree_p.h"
#include "person.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Tree_p::Tree_p(const int id)
  : DomainObject_p(id)
  , _reference(nullptr)
{
}

Tree_p::Tree_p(const QString& name, Person* reference)
  : DomainObject_p()
  , _name(name)
  , _reference(reference)
{
  Q_ASSERT(reference != nullptr);
}

void Tree_p::load_impl(QSqlQuery& query)
{
    while (query.next())
    {
        _name = query.value(0).toString();
        const int referenceId = query.value(0).toInt();
        _reference.reset(new Person(referenceId));
    }
}

QString Tree_p::databaseTableName() const
{
  return "Tree";
}

void Tree_p::insertIntoDatabase()
{
  Q_ASSERT(_reference != nullptr);

  QString queryStr = "INSERT INTO public.\"Tree\" (\"Name\", \"Reference\") VALUES (:treeName, :reference);";
  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":treeName", QVariant::fromValue(_name));
  query.bindValue(":reference", _reference->id());

  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _isLoaded = true;
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert Tree into database:" << sqlError.text();
  }
}

void Tree_p::updateInDatabase()
{

}

QString Tree_p::name() const
{
  return _name;
}

Person* Tree_p::reference() const
{
  return _reference.data();
}

void Tree_p::setName(const QString& name)
{
  _name = name;
  setDirty();
}
