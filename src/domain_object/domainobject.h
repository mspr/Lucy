#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H

#include <QScopedPointer>
#include <QUuid>

namespace Business { class DomainObject_p; }

#define DECLARE_PIMPL(T)                                \
  public:                                               \
    T(const int id);                                    \
    ~T();                                               \
                                                        \
    T##_p* d() const;                                   \
    virtual DomainObject_p* getD() const override;      \
                                                        \
  private:                                              \
    QScopedPointer<T##_p> _pimpl;

#define DEFINE_PIMPL(T)                                 \
  T::T(const int id) : _pimpl(new T##_p(this, id)) {};  \
  T::~T() {}                                            \
  T##_p* T::d() const                                   \
  {                                                     \
    _pimpl.data()->tryLoad();                           \
    return _pimpl.data();                               \
  }                                                     \
                                                        \
  DomainObject_p* T::getD() const                       \
  {                                                     \
    return d();                                         \
  }

namespace Business
{
  class DomainObject
  {
    public:
      DomainObject();
      virtual ~DomainObject();

      QUuid droid() const;
      int id() const;

      virtual DomainObject_p* getD() const = 0;
  };

} // Business

#endif // DOMAINOBJECT_H
