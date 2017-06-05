#ifndef DOMAINOBJECT_P_H
#define DOMAINOBJECT_P_H

#include <QString>
#include <QUuid>

class QSqlQuery;

class DomainObject_p
{
  public:
    DomainObject_p();
    DomainObject_p(const int id);
    virtual ~DomainObject_p();

    void tryLoad();

    QUuid droid() const;
    int id() const;

    virtual void deleteFromDatabase();
    virtual void updateInDatabase() = 0;
    virtual void insertIntoDatabase() = 0;

  protected:
    virtual void load_impl(QSqlQuery& query) = 0;
    virtual QString databaseTableName() const = 0;

  protected:
    int _id;
    QUuid _droid;
    bool _isLoaded;
};

#endif // DOMAINOBJECT_P_H
