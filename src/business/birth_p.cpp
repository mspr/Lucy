#include "birth_p.h"

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
  Q_ASSERT(_location != nullptr);
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

}

void Birth_p::load_impl(QSqlQuery& /*query*/)
{

}

QString Birth_p::databaseTableName() const
{
  return "Birth";
}
