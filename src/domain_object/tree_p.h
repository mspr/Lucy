#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

class Tree;
class Person;

class Tree_p : public DomainObject_p
{
  DECLARE_FACADE(Tree)

  public:
    Tree_p(Tree* facade, const QString& name);

    QString name() const;
    QList<Person*> persons() const;
    Person* reference() const;

    void setName(const QString& name);
    void addPerson(Person* person);
    void setReference(Person* person);

    virtual void insertIntoDatabase();
    virtual void updateInDatabase();

  protected:
    virtual void load_impl(QSqlQuery& query) override;
    virtual QString databaseTableName() const override;

  private:
    QString _name;
    QList<Person*> _persons;
    Person* _reference;
};

#endif // TREE_P_H
