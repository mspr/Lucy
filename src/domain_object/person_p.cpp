#include "person_p.h"
#include "person.h"
#include "tree.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

DEFINE_FACADE(Person)

Person_p::Person_p(Person* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
  , _tree(nullptr)
  , _father(nullptr)
  , _mother(nullptr)
{
    Q_ASSERT(_facade != nullptr);
}

Person_p::Person_p(Person* facade, const QString& firstName, const QString& lastName, const QDate& birthDate)
  : DomainObject_p()
  , _facade(facade)
  , _firstName(firstName)
  , _lastName(lastName)
  , _birthDate(birthDate)
  , _father(nullptr)
  , _mother(nullptr)
{
}

Person_p::~Person_p()
{
}

QString Person_p::firstName() const
{
  return _firstName;
}

QString Person_p::lastName() const
{
  return _lastName;
}

QDate Person_p::birthDate() const
{
  return _birthDate;
}

Person* Person_p::father() const
{
  return _father;
}

Person* Person_p::mother() const
{
  return _mother;
}

Tree* Person_p::tree() const
{
  return _tree;
}

void Person_p::load_impl(QSqlQuery& query)
{
  Q_ASSERT(_tree == nullptr);
  Q_ASSERT(_father == nullptr);
  Q_ASSERT(_mother == nullptr);

    _firstName = query.value(1).toString();
    _lastName = query.value(3).toString();
    _birthDate = query.value(4).toDate();

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
  query.bindValue(":birthDate", QVariant::fromValue(_birthDate));

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

void Person_p::setTree(Tree* tree)
{
  Q_ASSERT(tree != nullptr);
  _tree = tree;
}

void Person_p::setFirstName(const QString& firstName)
{
  _firstName = firstName;
  setDirty();
}

void Person_p::setLastName(const QString& lastName)
{
  _lastName = lastName;
  setDirty();
}

void Person_p::setBirthDate(const QDate& birthDate)
{
  _birthDate = birthDate;
  setDirty();
}

void Person_p::setFather(Person* father)
{
  Q_ASSERT(father != nullptr);
  _father = father;
}

void Person_p::setMother(Person* mother)
{
  Q_ASSERT(mother != nullptr);
  _mother = mother;
}
