#ifndef JOB_P_H
#define JOB_P_H

#include "domainobject_p.h"

namespace Business
{
  class Job;

  class Job_p : public DomainObject_p
  {
    DECLARE_FACADE(Job)

    public:
      Job_p(Job* facade, const QString& title, const QString& place);

      QString title() const;
      void setTitle(const QString& title);

      QString place() const;
      void setPlace(const QString& place);

      virtual void updateInDatabase() override;
      virtual void insertIntoDatabase() override;

    protected:
      virtual void load_impl(QSqlQuery& query) override;
      virtual QString databaseTableName() const override;

    private:
      QString _title;
      QString _place;
  };

} // Business

#endif // JOB_P_H
