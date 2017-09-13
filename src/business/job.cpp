#include "job.h"
#include "job_p.h"

using namespace Business;

DEFINE_PIMPL(Job)

Job::Job(const QString& title, Location* location)
  : _pimpl(new Job_p(this, title, location))
{
}

QString Job::title() const
{
  return d()->title();
}

void Job::setTitle(const QString& title)
{
  d()->setTitle(title);
}

Location* Job::location() const
{
  return d()->location();
}

void Job::setLocation(Location* location)
{
  d()->setLocation(location);
}
