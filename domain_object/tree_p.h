#ifndef TREE_P_H
#define TREE_P_H

#include "domainobject_p.h"

class Person;

class Tree_p : public DomainObject_p
{
  public:
    Tree_p(const int id);
    Tree_p();

    void setName(const QString& name);
    void setReference(Person* person);

    QString name() const;

    virtual void insertIntoDatabase();
    virtual void updateInDatabase();

  protected:
    virtual void load_impl(QSqlQuery& query) override;
    virtual QString databaseTableName() const override;

  private:
    int _rootId;
    Person* _reference;
    QString _name;

};

#endif // TREE_P_H
