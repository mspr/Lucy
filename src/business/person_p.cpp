#include "person_p.h"
#include "person.h"
#include "tree.h"
#include "job.h"
#include "birth.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

using namespace Business;

DEFINE_FACADE(Person)

Person_p::Person_p(Person* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
  , _tree(nullptr)
  , _birth(nullptr)
  , _father(nullptr)
  , _mother(nullptr)
{
  Q_ASSERT(_facade != nullptr);
}

Person_p::Person_p(Person* facade, const QString& firstName, const QString& lastName, Birth* birth)
  : DomainObject_p()
  , _facade(facade)
  , _firstName(firstName)
  , _lastName(lastName)
  , _birth(birth)
  , _father(nullptr)
  , _mother(nullptr)
{
  Q_ASSERT(_facade != nullptr);
  Q_ASSERT(_birth != nullptr);
}

Person_p::~Person_p()
{
  if (_birth != nullptr)
  {
    delete _birth;
    _birth = nullptr;
  }
}

QString Person_p::firstName() const
{
  return _firstName;
}

void Person_p::setFirstName(const QString& firstName)
{
  _firstName = firstName;
  setDirty();
}

QString Person_p::lastName() const
{
  return _lastName;
}

void Person_p::setLastName(const QString& lastName)
{
  _lastName = lastName;
  setDirty();
}

Birth* Person_p::birth() const
{
  return _birth;
}

void Person_p::setBirth(Birth* birth)
{
  Q_ASSERT(birth != nullptr);
  _birth = birth;
//  setDirty();
}

Person* Person_p::father() const
{
  return _father;
}

void Person_p::setFather(Person* father)
{
  Q_ASSERT(father != nullptr);
  _father = father;
  //setDirty();
}

Person* Person_p::mother() const
{
  return _mother;
}

void Person_p::setMother(Person* mother)
{
  Q_ASSERT(mother != nullptr);
  _mother = mother;
  //setDirty();
}

Tree* Person_p::tree() const
{
  return _tree;
}

void Person_p::setTree(Tree* tree)
{
  Q_ASSERT(tree != nullptr);
  _tree = tree;
}

QList<Job*> Person_p::jobs() const
{
  return _jobs;
}

void Person_p::addJob(Job* job)
{
  Q_ASSERT(job != nullptr);
  Q_ASSERT(!_jobs.contains(job));
  _jobs.append(job);
  //setDirty();
}

void Person_p::load_impl(QSqlQuery& query)
{
  Q_ASSERT(_tree == nullptr);
  Q_ASSERT(_father == nullptr);
  Q_ASSERT(_mother == nullptr);

    _firstName = query.value(1).toString();
    _lastName = query.value(3).toString();
//    _birthDate = query.value(4).toDate();

    const int fatherId = query.value(5).toInt();
    if (fatherId != 0)
      _father = new Person(fatherId);

    const int motherId = query.value(6).toInt();
    if (motherId != 0)
      _mother = new Person(motherId);
}

QString Person_p::databaseTableName() const
{
  return "Person";
}

void Person_p::insertIntoDatabase()
{
  QString queryStr = "INSERT INTO public.\"Person\" (\"FirstName\", \"BirthDate\", \"LastName\", \"Father\", \"Mother\") VALUES (:firstName, :birthDate, :lastName, :father, :mother);";

  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":firstName", QVariant::fromValue(_firstName));
  query.bindValue(":lastName", QVariant::fromValue(_lastName));
//  query.bindValue(":birthDate", QVariant::fromValue(_birthDate));

  if (_father != nullptr)
  {
    _father->getD()->insertIntoDatabase();
    query.bindValue(":father", QVariant::fromValue(_father->id()));
  }

  if (_mother != nullptr)
  {
    _mother->getD()->insertIntoDatabase();
    query.bindValue(":mother", QVariant::fromValue(_mother->id()));
  }

  if (query.exec())
  {
    _id = query.lastInsertId().toInt();
    _isLoaded = true;
  }
  else
  {
    const QSqlError sqlError = query.lastError();
    qCritical() << "Fail to insert Person into database:" << sqlError.text();
  }
}

void Person_p::updateInDatabase()
{

}
