#ifndef LOCATION_H
#define LOCATION_H

#include "domainobject.h"

namespace Business
{
  class Location_p;

  class Location : public DomainObject
  {
    DECLARE_PIMPL(Location)

    public:
      Location(const QString& country, const QString& department, const QString& city);

      QString country() const;
      void setCountry(const QString& country);

      QString department() const;
      void setDepartment(const QString& department);

      QString city() const;
      void setCity(const QString& city);
  };

} // Business

#endif // LOCATION_H
