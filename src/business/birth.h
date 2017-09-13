#ifndef BIRTH_H
#define BIRTH_H

#include "domainobject.h"
#include <QDate>

namespace Business
{
  class Birth_p;
  class Location;

  class Birth : public DomainObject
  {
    DECLARE_PIMPL(Birth)

    public:
      Birth(const QDate& date, Location* location = nullptr);

      QDate date() const;
      void setDate(const QDate& date);

      Location* location() const;
      void setLocation(Location* location);
  };

} // Business

#endif // BIRTH_H
