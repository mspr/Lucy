#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H

#include <QSharedPointer>

#define DEFINE_PIMPL(T) \
  protected: \
    QSharedPointer<T> d() const \
    { \
      return _pimpl; \
    } \
  private: \
    QSharedPointer<T> _pimpl;

class DomainObject
{
  public:
    DomainObject();
};

#endif // DOMAINOBJECT_H
