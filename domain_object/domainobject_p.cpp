#include "domainobject_p.h"

DomainObject_p::DomainObject_p()
  : _id(-1),
    _isLoaded(false)
{
}

DomainObject_p::~DomainObject_p()
{
}

void DomainObject_p::tryLoad()
{
  if (!_isLoaded)
  {
    load_impl();
    _isLoaded = true;
  }
}
