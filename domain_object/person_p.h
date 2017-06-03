#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QString>

class Person_p : public DomainObject_p
{
  public:
    Person_p(const int id);

  protected:
    virtual void load_impl() override;

  private:
    QString _name;
};

#endif // PERSON_P_H
