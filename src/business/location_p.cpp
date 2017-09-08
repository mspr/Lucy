#include "location_p.h"

#include <QSqlQuery>
#include <QVariant>

using namespace Business;

DEFINE_FACADE(Location)

Location_p::Location_p(Location* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
{
  Q_ASSERT(_facade != nullptr);
}

Location_p::Location_p(Location* facade, const QString& country, const QString& department, const QString& city)
  : DomainObject_p()
  , _facade(facade)
  , _country(country)
  , _department(department)
  , _city(city)
{
  Q_ASSERT(_facade != nullptr);
}

Location_p::~Location_p()
{
}

QString Location_p::country() const
{
  return _country;
}

void Location_p::setCountry(const QString& country)
{
  _country = country;
}

QString Location_p::department() const
{
  return _department;
}

void Location_p::setDepartment(const QString& department)
{
  _department = department;
}

QString Location_p::city() const
{
  return _city;
}

void Location_p::setCity(const QString& city)
{
  _city = city;
}

void Location_p::updateInDatabase()
{

}

void Location_p::load_impl(QSqlQuery& query)
{
  _country = query.value(1).toString();
  _department = query.value(2).toString();
  _city = query.value(3).toString();
}

QSqlQuery Location_p::prepareInsertIntoDatabaseQuery()
{
  QString queryStr = "INSERT INTO public.\"Location\" (\"Country\", \"Department\", \"City\") VALUES (:country, :department, :city);";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":country", QVariant::fromValue(_country));
  query.bindValue(":department", QVariant::fromValue(_department));
  query.bindValue(":city", QVariant::fromValue(_city));

  return query;
}

QString Location_p::databaseTableName() const
{
  return "Location";
}
