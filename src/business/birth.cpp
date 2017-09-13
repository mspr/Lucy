#include "birth.h"
#include "birth_p.h"

using namespace Business;

DEFINE_PIMPL(Birth)

Birth::Birth(const QDate& date, Location* location)
  : _pimpl(new Birth_p(this, date, location))
{
}

QDate Birth::date() const
{
  return d()->date();
}

void Birth::setDate(const QDate& date)
{
  d()->setDate(date);
}

Location* Birth::location() const
{
  return d()->location();
}

void Birth::setLocation(Location* location)
{
  d()->setLocation(location);
}
