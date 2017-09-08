#ifndef BIRTH_P_H
#define BIRTH_P_H

#include "domainobject_p.h"
#include <QDate>

namespace Business
{
  class Birth;
  class Location;

  class Birth_p : public DomainObject_p
  {
    DECLARE_FACADE(Birth)

    public:
      Birth_p(Birth* facade, const QDate& date, Location* location);

      QDate date() const;
      void setDate(const QDate& date);

      Location* location() const;
      void setLocation(Location* location);

      virtual void updateInDatabase() override;
      virtual void insertIntoDatabase() override;

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QString databaseTableName() const override;

    private:
      QDate _date;
      Location* _location;
  };

} // Business

#endif // BIRTH_P_H
