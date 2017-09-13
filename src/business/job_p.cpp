#include "job_p.h"
#include "location.h"
#include "location_p.h"

#include <QSqlQuery>
#include <QVariant>

using namespace Business;

DEFINE_FACADE(Job)

Job_p::Job_p(Job* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
  , _location(nullptr)
{
  Q_ASSERT(_facade != nullptr);
}

Job_p::Job_p(Job* facade, const QString& title, Location* location)
  : DomainObject_p()
  , _facade(facade)
  , _title(title)
  , _location(location)
{
  Q_ASSERT(_facade != nullptr);
}

Job_p::~Job_p()
{
  if (_location != nullptr)
  {
    delete _location;
    _location = nullptr;
  }
}

QString Job_p::title() const
{
  return _title;
}

void Job_p::setTitle(const QString& title)
{
  _title = title;
}

Location* Job_p::location() const
{
  return _location;
}

void Job_p::setLocation(Location* location)
{
  Q_ASSERT(location != nullptr);
  _location = location;
}

QSqlQuery Job_p::prepareUpdateInDatabaseQuery()
{
  QString queryStr = "UPDATE public.\"Job\" SET \"Title\" = :title, \"Location\" = :location WHERE Id = :id;";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":title", QVariant::fromValue(_title));
  query.bindValue(":location", QVariant::fromValue(_location->id()));
  query.bindValue(":id", QVariant::fromValue(_id));

  return query;
}

void Job_p::load_impl(QSqlQuery& query)
{
  Q_ASSERT(_location == nullptr);

  _title = query.value(1).toString();

  const int locationId = query.value(2).toInt();
  _location = new Location(locationId);
}

QSqlQuery Job_p::prepareInsertIntoDatabaseQuery()
{
  QString queryStr = "INSERT INTO public.\"Job\" (\"Title\", \"Location\") VALUES (:title, :location);";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":title", QVariant::fromValue(_title));

  if (_location != nullptr)
  {
    _location->d()->insertIntoDatabase();
    query.bindValue(":location", QVariant::fromValue(_location->id()));
  }

  return query;
}

QString Job_p::databaseTableName() const
{
  return "Job";
}
