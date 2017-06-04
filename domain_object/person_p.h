#ifndef PERSON_P_H
#define PERSON_P_H

#include "domainobject_p.h"

#include <QString>
#include <QDate>

class Person_p : public DomainObject_p
{
  public:
    Person_p(const int id);

    void setFirstName(const QString& firstName);
    void setLastName(const QString& lastName);
    void setBirthDate(const QDate& birthDate);

  protected:
    virtual void load_impl() override;

  private:
    QString _firstName;
    QString _lastName;
    QDate _birthDate;
};

#endif // PERSON_P_H
