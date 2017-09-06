#include "job.h"
#include "job_p.h"

using namespace Business;

DEFINE_PIMPL(Job)

Job::Job(const QString& title, const QString& place)
  : _pimpl(new Job_p(this, title, place))
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

QString Job::place() const
{
  return d()->place();
}

void Job::setPlace(const QString& place)
{
  d()->setPlace(place);
}
