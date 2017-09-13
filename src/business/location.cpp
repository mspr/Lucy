#include "location.h"
#include "location_p.h"

using namespace Business;

DEFINE_PIMPL(Location)

Location::Location(const QString& country, const QString& department, const QString& city)
  : _pimpl(new Location_p(this, country, department, city))
{
}

QString Location::country() const
{
  return d()->country();
}

void Location::setCountry(const QString& country)
{
  d()->setCountry(country);
}

QString Location::department() const
{
  return d()->department();
}

void Location::setDepartment(const QString& department)
{
  d()->setDepartment(department);
}

QString Location::city() const
{
  return d()->city();
}

void Location::setCity(const QString& city)
{
  d()->setCity(city);
}
