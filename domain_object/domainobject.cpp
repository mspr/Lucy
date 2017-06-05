#include "domainobject.h"
#include "domainobject_p.h"

DomainObject::DomainObject()
{
}

DomainObject::~DomainObject()
{
}

QUuid DomainObject::droid() const
{
  return getD()->droid();
}
