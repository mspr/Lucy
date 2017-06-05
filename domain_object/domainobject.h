#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H

#include <QScopedPointer>
#include <QUuid>

class DomainObject_p;

#define DECLARE_PIMPL(T)                                \
  public:                                               \
    T(const int id);                                    \
    ~T();                                               \
                                                        \
    int id() const;                                     \
                                                        \
    T##_p* d() const;                                   \
    virtual DomainObject_p* getD() const override;      \
                                                        \
  private:                                              \
    QScopedPointer<T##_p> _pimpl;

#define DEFINE_PIMPL(T)                           \
  T::T(const int id) : _pimpl(new T##_p(id)) {};  \
  T::~T() {}                                      \
  int T::id() const                               \
  {                                               \
    return _pimpl.data()->id();                   \
  }                                               \
  T##_p* T::d() const                             \
  {                                               \
    _pimpl.data()->tryLoad();                     \
    return _pimpl.data();                         \
  }                                               \
                                                  \
  DomainObject_p* T::getD() const                 \
  {                                               \
    return d();                                   \
  }

class DomainObject
{
  public:
    DomainObject();
    virtual ~DomainObject();

    QUuid droid() const;

    virtual DomainObject_p* getD() const = 0;
};

#endif // DOMAINOBJECT_H
