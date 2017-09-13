#ifndef LOCATION_P_H
#define LOCATION_P_H

#include "domainobject_p.h"

namespace Business
{
  class Location;

  class Location_p : public DomainObject_p
  {
    DECLARE_FACADE(Location)

    public:
      Location_p(Location* facade, const QString& country, const QString& department, const QString& city);

      QString country() const;
      void setCountry(const QString& country);

      QString department() const;
      void setDepartment(const QString& department);

      QString city() const;
      void setCity(const QString& city);

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QSqlQuery prepareInsertIntoDatabaseQuery() override;
      virtual QSqlQuery prepareUpdateInDatabaseQuery() override;
      virtual QString databaseTableName() const override;

    private:
      QString _country;
      QString _department;
      QString _city;
  };

} // Business

#endif // LOCATION_P_H
