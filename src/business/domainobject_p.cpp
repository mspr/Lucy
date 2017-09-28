#include "domainobject_p.h"
#include "business/databasestatus.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

using namespace Business;

DomainObject_p::DomainObject_p(const int id)
  : _id(id)
  , _status(DatabaseStatus::New)
  , _droid(QUuid::createUuid())
{
}

DomainObject_p::DomainObject_p()
  : _id(-1)
  , _status(DatabaseStatus::New)
  , _droid(QUuid::createUuid())
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

DatabaseStatus DomainObject_p::status() const
{
  return _status;
}

bool DomainObject_p::isDirty() const
{
  return _status == DatabaseStatus::Dirty;
}

bool DomainObject_p::isNew() const
{
  return _status == DatabaseStatus::New;
}

bool DomainObject_p::isDeleted() const
{
  return _status == DatabaseStatus::Deleted;
}

void DomainObject_p::tryLoad()
{
  if (_status == DatabaseStatus::New && _id != -1)
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

        _status = DatabaseStatus::Loaded;
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

void DomainObject_p::setDirty()
{
  _status = DatabaseStatus::Dirty;
  emit dirty();
}

void DomainObject_p::markAsDeleted()
{
  Q_ASSERT(_status != DatabaseStatus::Deleted);
  Q_ASSERT(_status != DatabaseStatus::New);

  _status = DatabaseStatus::Deleted;
}

void DomainObject_p::commit()
{
  switch (_status)
  {
    case DatabaseStatus::New:
      insertIntoDatabase();
    break;
    case DatabaseStatus::Dirty:
      updateInDatabase();
    break;
    case DatabaseStatus::Deleted:
      deleteFromDatabase();
    break;
    case DatabaseStatus::Loaded:
    break;
  }
}

void DomainObject_p::insertIntoDatabase()
{
  Q_ASSERT(_id == -1);
  Q_ASSERT(_status == DatabaseStatus::New);

  QSqlQuery query = prepareInsertIntoDatabaseQuery();
  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _status = DatabaseStatus::Loaded;

    onInsertIntoDatabaseSucceeded();
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert " << databaseTableName() + " into database:" << sqlError.text();
  }
}

void DomainObject_p::onInsertIntoDatabaseSucceeded()
{
}

void DomainObject_p::updateInDatabase()
{
  Q_ASSERT(_id != -1);
  Q_ASSERT(_status == DatabaseStatus::Dirty);

  QSqlQuery query = prepareUpdateInDatabaseQuery();
  if (!query.exec())
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to update " << databaseTableName() + " in database:" << sqlError.text();
  }
}

void DomainObject_p::deleteFromDatabase()
{
  Q_ASSERT(_id != -1);
  Q_ASSERT(_status == DatabaseStatus::Deleted);

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
