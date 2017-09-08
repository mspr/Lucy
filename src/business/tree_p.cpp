#include "tree_p.h"
#include "person.h"
#include "person_p.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

using namespace Business;

DEFINE_FACADE(Tree)

Tree_p::Tree_p(Tree* facade, const int id)
  : DomainObject_p(id)
  , _facade(facade)
  , _reference(nullptr)
{
  Q_ASSERT(_facade != nullptr);
}

Tree_p::Tree_p(Tree* facade, const QString& name)
  : DomainObject_p()
  , _facade(facade)
  , _name(name)
  , _reference(nullptr)
{
}

Tree_p::~Tree_p()
{
  qDeleteAll(_persons);
  _persons.clear();
}

void Tree_p::load_impl(QSqlQuery& query)
{
  _name = query.value(1).toString();

  QString queryStr = "SELECT * FROM public.\"TreePerson\" WHERE \"TreeId\" = :id";
  QSqlQuery selectTreePersonQuery;
  selectTreePersonQuery.prepare(queryStr);
  selectTreePersonQuery.bindValue(":id", QVariant::fromValue(_id));
  if (selectTreePersonQuery.exec())
  {
    while (selectTreePersonQuery.next())
    {
      const bool isReference = selectTreePersonQuery.value(3).toBool();
      if (isReference)
      {
        const int personId = selectTreePersonQuery.value(2).toInt();
        Person* person = new Person(personId);
        addPerson(person);

        _reference = person;
      }
    }
  }
  else
  {
    const QSqlError sqlError = selectTreePersonQuery.lastError();
    qCritical() << "Fail to select data from " << databaseTableName() << " table from database:" << sqlError.text();
  }
}

QString Tree_p::databaseTableName() const
{
  return "Tree";
}

QSqlQuery Tree_p::prepareInsertIntoDatabaseQuery()
{
  Q_ASSERT(_reference != nullptr);

  QString queryStr = "INSERT INTO public.\"Tree\" (\"Name\") VALUES (:treeName);";
  QSqlQuery query;
  query.prepare(queryStr);
  query.bindValue(":treeName", QVariant::fromValue(_name));

  return query;

//  if (query.exec())
//  {
//    _id = query.lastInsertId().toInt();

//    // Insert persons recursively from the reference
//    _reference->getD()->insertIntoDatabase();

//    for (int i=0; i<_persons.count(); ++i)
//    {
//      Person* person = _persons.at(i);
//      const int personId = person->id();
//      Q_ASSERT(personId != -1);

//      const bool isReference = (person == _reference);

//      QString queryStr = "INSERT INTO public.\"TreePerson\" (\"TreeId\", \"PersonId\", \"IsReference\") VALUES (:treeId, :personId, :isReference);";
//      QSqlQuery query;
//      query.prepare(queryStr);
//      query.bindValue(":treeId", QVariant::fromValue(_id));
//      query.bindValue(":personId", QVariant::fromValue(personId));
//      query.bindValue(":isReference", QVariant::fromValue(isReference));
//      if (!query.exec())
//      {
//        const QSqlError sqlError = query.lastError();
//        qCritical() << "Fail to insert Tree into database:" << sqlError.text();
//      }
//    }

//    _isLoaded = true;
//  }
//  else
//  {
//    const QSqlError sqlError = query.lastError();
//    qCritical() << "Fail to insert Tree into database:" << sqlError.text();
//  }
}

void Tree_p::updateInDatabase()
{

}

QString Tree_p::name() const
{
  return _name;
}

QList<Person*> Tree_p::persons() const
{
  return _persons;
}

Person* Tree_p::reference() const
{
  return _reference;
}

void Tree_p::setName(const QString& name)
{
  _name = name;
  setDirty();
}

void Tree_p::addPerson(Person* person)
{
  Q_ASSERT(person != nullptr);
  Q_ASSERT(!_persons.contains(person));

  person->setTree(facade());
  _persons.append(person);
}

void Tree_p::setReference(Person* person)
{
  Q_ASSERT(person != nullptr);
  Q_ASSERT(_persons.contains(person));

  _reference = person;
}
