#include "domainobject_p.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

using namespace Business;

DomainObject_p::DomainObject_p(const int id)
  : _id(id)
  , _droid(QUuid::createUuid())
  , _isLoaded(false)
  , _isDirty(false)
{
}

DomainObject_p::DomainObject_p()
  : _id(-1)
  , _droid(QUuid::createUuid())
  , _isLoaded(false)
  , _isDirty(false)
{
}

DomainObject_p::~DomainObject_p()
{
}

QUuid DomainObject_p::droid() const
{
  return _droid;
}

int DomainObject_p::id() const
{
  return _id;
}

void DomainObject_p::tryLoad()
{
  if (!_isLoaded && _id != -1)
  {
    QString queryStr = "SELECT * FROM public.\"" + databaseTableName() + "\" WHERE \"Id\" = :id";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":id", QVariant::fromValue(_id));

    if (query.exec())
    {
      if (query.next())
      {
        load_impl(query);

        _isLoaded = true;
      }
      else
      {
        throw std::invalid_argument("Impossible to load data from database.");
      }
    }
    else
    {
      const QSqlError sqlError = query.lastError();
      qCritical() << "Fail to select data from " << databaseTableName() << " table from database:" << sqlError.text();
    }
  }
}

void DomainObject_p::insertIntoDatabase()
{
  QSqlQuery query = prepareInsertIntoDatabaseQuery();
  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _isLoaded = true;
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert " << databaseTableName() + " into database:" << sqlError.text();
  }
}

void DomainObject_p::deleteFromDatabase()
{
  QString queryStr = "DELETE FROM public.\"" + databaseTableName() + "\" WHERE \"Id\" = :id";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":id", QVariant::fromValue(_id));

  if (!query.exec())
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to delete " << databaseTableName() << " " << _id << " from database :" << sqlError.text();
  }
}

void DomainObject_p::setDirty()
{
  _isDirty = true;
  emit dirty();
}
