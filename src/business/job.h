#ifndef JOB_H
#define JOB_H

#include "domainobject.h"

namespace Business
{
  class Job_p;
  class Location;

  class Job : public DomainObject
  {
    DECLARE_PIMPL(Job)

    public:
      Job(const QString& title, Location* location = nullptr);

      QString title() const;
      void setTitle(const QString& title);

      Location* location() const;
      void setLocation(Location* location);
  };

} // Business

#endif // JOB_H
