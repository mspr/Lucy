#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

class Person;

class Tree_p : public DomainObject_p
{
  public:
    Tree_p(const int id);
    Tree_p(const QString& name, Person* reference);

    QString name() const;
    Person* reference() const;

    void setName(const QString& name);

    virtual void insertIntoDatabase();
    virtual void updateInDatabase();

  protected:
    virtual void load_impl(QSqlQuery& query) override;
    virtual QString databaseTableName() const override;

  private:
    QString _name;
    QScopedPointer<Person> _reference;
};

#endif // TREE_P_H
