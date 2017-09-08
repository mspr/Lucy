#include "birth_p.h"
#include "location.h"
#include "location_p.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

using namespace Business;

DEFINE_FACADE(Birth)

Birth_p::Birth_p(Birth* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
  , _location(nullptr)
{
  Q_ASSERT(_facade != nullptr);
}

Birth_p::Birth_p(Birth* facade, const QDate& date, Location* location)
  : DomainObject_p()
  , _facade(facade)
  , _date(date)
  , _location(location)
{
  Q_ASSERT(_facade != nullptr);
}

Birth_p::~Birth_p()
{
}

QDate Birth_p::date() const
{
  return _date;
}

void Birth_p::setDate(const QDate& date)
{
  _date = date;
}

Location* Birth_p::location() const
{
  return _location;
}

void Birth_p::setLocation(Location* location)
{
  Q_ASSERT(location != nullptr);
  _location = location;
}

void Birth_p::updateInDatabase()
{

}

void Birth_p::insertIntoDatabase()
{
  QString queryStr = "INSERT INTO public.\"Birth\" (\"BirthDate\", \"Location\") VALUES (:birthDate, :location);";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":birthDate", QVariant::fromValue(_date));

  if (_location != nullptr)
  {
    _location->d()->insertIntoDatabase();
    query.bindValue(":location", QVariant::fromValue(_location->id()));
  }

  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _isLoaded = true;
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert Birth into database:" << sqlError.text();
  }
}

void Birth_p::load_impl(QSqlQuery& query)
{
  Q_ASSERT(_location == nullptr);

  _date = query.value(1).toDate();

  const int locationId = query.value(2).toInt();
  _location = new Location(locationId);
}

QString Birth_p::databaseTableName() const
{
  return "Birth";
}
