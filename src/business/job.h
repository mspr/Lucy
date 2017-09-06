#ifndef JOB_H
#define JOB_H

#include "domainobject.h"

namespace Business
{
  class Job_p;

  class Job : public DomainObject
  {
    DECLARE_PIMPL(Job)

    public:
      Job(const QString& title, const QString& place);

      QString title() const;
      void setTitle(const QString& title);

      QString place() const;
      void setPlace(const QString& place);
  };

} // Business

#endif // JOB_H
