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

  setupConnections();
}

Tree_p::Tree_p(Tree* facade, const QString& name)
  : DomainObject_p()
  , _facade(facade)
  , _name(name)
  , _reference(nullptr)
{
  Q_ASSERT(!_name.isEmpty());
  setupConnections();
}

void Tree_p::setupConnections()
{
  qRegisterMetaType<Person*>("Person*");

  connect(this, Tree_p::personRemoved, this, DomainObject_p::dirty);
}

Tree_p::~Tree_p()
{
}

QString Tree_p::name() const
{
  return _name;
}

void Tree_p::setName(const QString& name)
{
  Q_ASSERT(!name.isEmpty());
  _name = name;
  setDirty();
}

QList<Person*> Tree_p::persons() const
{
  return _persons;
}

void Tree_p::add(Person* person)
{
  Q_ASSERT(person != nullptr);
  Q_ASSERT(!_persons.contains(person));

  person->setTree(facade());
  _persons.append(person);

  connect(person->getD(), Person_p::dirty, this, Tree_p::dirty);

  emit personAdded(person);

  if (!person->isNew())
    setDirty();
}

void Tree_p::remove(Person* person)
{
  Q_ASSERT(person != nullptr);
  Q_ASSERT(_persons.removeOne(person));

  emit personRemoved(person);
}

Person* Tree_p::reference() const
{
  return _reference;
}

void Tree_p::setReference(Person* person)
{
  Q_ASSERT(person != nullptr);
  Q_ASSERT(_persons.contains(person));

  _reference = person;
}

int Tree_p::countGenerations() const
{
  int count = 0;

  if (_reference != nullptr)
    count = countGenerationsRecursively(_reference);

  return count;
}

int Tree_p::countGenerationsRecursively(Person* person) const
{
  Q_ASSERT(person != nullptr);

  int count = 1;

  if (person->hasFather() && person->hasMother())
  {
    count += qMax(countGenerationsRecursively(person->father()),
                  countGenerationsRecursively(person->mother()));
  }
  else if (person->hasFather())
    count += countGenerationsRecursively(person->father());
  else if (person->hasMother())
    count += countGenerationsRecursively(person->mother());

  return count;
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
        add(person);

        setReference(person);
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
}

void Tree_p::onInsertIntoDatabaseSucceeded()
{
  // Insert persons recursively from the reference
  _reference->getD()->commit();

  for (int i=0; i<_persons.count(); ++i)
  {
    Person* person = _persons.at(i);
    const int personId = person->id();
    Q_ASSERT(personId != -1);

    const bool isReference = (person == _reference);

    QString queryStr = "INSERT INTO public.\"TreePerson\" (\"TreeId\", \"PersonId\", \"IsReference\") VALUES (:treeId, :personId, :isReference);";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":treeId", QVariant::fromValue(_id));
    query.bindValue(":personId", QVariant::fromValue(personId));
    query.bindValue(":isReference", QVariant::fromValue(isReference));
    if (!query.exec())
    {
      const QSqlError sqlError = query.lastError();
      qCritical() << "Fail to insert Tree into database:" << sqlError.text();
    }
  }
}

QSqlQuery Tree_p::prepareUpdateInDatabaseQuery()
{
  return QSqlQuery("");
}
