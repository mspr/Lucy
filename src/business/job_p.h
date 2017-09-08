#ifndef JOB_P_H
#define JOB_P_H

#include "domainobject_p.h"

namespace Business
{
  class Job;
  class Location;

  class Job_p : public DomainObject_p
  {
    DECLARE_FACADE(Job)

    public:
      Job_p(Job* facade, const QString& title, Location* location);

      QString title() const;
      void setTitle(const QString& title);

      Location* location() const;
      void setLocation(Location* location);

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QSqlQuery prepareInsertIntoDatabaseQuery() override;
      virtual QSqlQuery prepareUpdateInDatabaseQuery() override;
      virtual QString databaseTableName() const override;

    private:
      QString _title;
      Location* _location;
  };

} // Business

#endif // JOB_P_H
