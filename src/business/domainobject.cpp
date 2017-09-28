#include "domainobject.h"
#include "domainobject_p.h"

using namespace Business;

DomainObject::DomainObject(QObject* parent)
  : QObject(parent)
{
}

DomainObject::~DomainObject()
{
}

QUuid DomainObject::droid() const
{
  return getD()->droid();
}

int DomainObject::id() const
{
  return getD()->id();
}

DatabaseStatus DomainObject::status() const
{
  return getD()->status();
}

bool DomainObject::isDirty() const
{
  return getD()->isDirty();
}

bool DomainObject::isNew() const
{
  return getD()->isNew();
}

bool DomainObject::isDeleted() const
{
  return getD()->isDeleted();
}
