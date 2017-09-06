#include "job_p.h"

using namespace Business;

DEFINE_FACADE(Job)

Job_p::Job_p(Job* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
{
  Q_ASSERT(_facade != nullptr);
}

Job_p::Job_p(Job* facade, const QString& title, const QString& place)
  : DomainObject_p()
  , _facade(facade)
  , _title(title)
  , _place(place)
{
  Q_ASSERT(_facade != nullptr);
}

Job_p::~Job_p()
{
}

QString Job_p::title() const
{
  return _title;
}

void Job_p::setTitle(const QString& title)
{
  _title = title;
}

QString Job_p::place() const
{
  return _place;
}

void Job_p::setPlace(const QString& place)
{
  _place = place;
}

void Job_p::updateInDatabase()
{

}

void Job_p::insertIntoDatabase()
{

}

void Job_p::load_impl(QSqlQuery& /*query*/)
{

}

QString Job_p::databaseTableName() const
{
  return "Job";
}
