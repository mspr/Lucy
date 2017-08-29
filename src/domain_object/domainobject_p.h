#ifndef DOMAINOBJECT_P_H
#define DOMAINOBJECT_P_H

#include <QObject>
#include <QString>
#include <QUuid>

class QSqlQuery;

#define DECLARE_FACADE(T)                                 \
  public:                                                 \
    T##_p(T* facade, const int id);                       \
    T##_p(T* facade);                                     \
    virtual ~T##_p();                                     \
                                                          \
    T* facade() const;                                    \
                                                          \
  private:                                                \
    T* _facade;

#define DEFINE_FACADE(T)                                \
  T##_p::T##_p(T* facade) : _facade(facade)             \
  {                                                     \
    Q_ASSERT(facade != nullptr);                        \
  }                                                     \
                                                        \
  T* T##_p::facade() const                              \
  {                                                     \
    return _facade;                                     \
  }                                                     \

class DomainObject_p : public QObject
{
  Q_OBJECT

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

  signals:
    void dirty();

  protected:
    virtual void load_impl(QSqlQuery& query) = 0;
    virtual QString databaseTableName() const = 0;

    void setDirty();

  protected:
    int _id;
    QUuid _droid;
    bool _isLoaded;
    bool _isDirty;
};

#endif // DOMAINOBJECT_P_H
