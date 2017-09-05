#include "domainobject.h"
#include "domainobject_p.h"

using namespace Business;

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

int DomainObject::id() const
{
  return getD()->id();
}
