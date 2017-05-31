#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H

#include <QSharedPointer>

#define DECLARE_PIMPL(T) \
  protected: \
    QSharedPointer<T##_p> d() const; \
  private: \
    QSharedPointer<T##_p> _pimpl;

#define DEFINE_PIMPL(T) \
  QSharedPointer<T##_p> T::d() const \
  { \
    _pimpl.data()->tryLoad(); \
    return _pimpl; \
  } \

class DomainObject
{
  public:
    DomainObject();
};

#endif // DOMAINOBJECT_H
