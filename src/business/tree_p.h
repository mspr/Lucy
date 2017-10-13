#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

namespace Business
{
  class Tree;
  class Person;

  class Tree_p : public DomainObject_p
  {
    Q_OBJECT

    DECLARE_FACADE(Tree)

    public:
      Tree_p(Tree* facade, const QString& name);

      QString name() const;
      void setName(const QString& name);

      QList<Person*> persons() const;
      void add(Person* person);
      void remove(Person* person);

      Person* reference() const;
      void setReference(Person* person);
      bool isReference(Person* person) const;

      int countGenerations() const;

    signals:
      void personRemoved(Person* person);
      void personAdded(Person* person);

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QSqlQuery prepareInsertIntoDatabaseQuery() override;
      virtual void onInsertIntoDatabaseSucceeded() override;
      virtual QSqlQuery prepareUpdateInDatabaseQuery() override;
      virtual QString databaseTableName() const override;

    private:
      void setupConnections();
      int countGenerationsRecursively(Person* person) const;

    private:
      QString _name;
      QList<Person*> _persons;
      Person* _reference;
  };

} // Business

#endif // TREE_P_H
