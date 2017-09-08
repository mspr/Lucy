#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

namespace Business
{
  class Tree;
  class Person;

  class Tree_p : public DomainObject_p
  {
    DECLARE_FACADE(Tree)

    public:
      Tree_p(Tree* facade, const QString& name);

      QString name() const;
      void setName(const QString& name);

      QList<Person*> persons() const;
      void addPerson(Person* person);

      Person* reference() const;
      void setReference(Person* person);

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QSqlQuery prepareInsertIntoDatabaseQuery() override;
      virtual QSqlQuery prepareUpdateInDatabaseQuery() override;
      virtual QString databaseTableName() const override;

    private:
      QString _name;
      QList<Person*> _persons;
      Person* _reference;
  };

} // Business

#endif // TREE_P_H
