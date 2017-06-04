#include "domainobject_p.h"

DomainObject_p::DomainObject_p(const int id)
  : _id(id),
    _isLoaded(false)
{
}

DomainObject_p::DomainObject_p()
  : _state(State::New)
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
