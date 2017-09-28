#ifndef DOMAINOBJECT_H
#define DOMAINOBJECT_H

#include <QObject>

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
  enum class DatabaseStatus;

  class DomainObject : public QObject
  {
    public:
      DomainObject(QObject* parent = nullptr);
      virtual ~DomainObject();

      QUuid droid() const;
      int id() const;

      DatabaseStatus status() const;
      bool isDirty() const;
      bool isNew() const;
      bool isDeleted() const;

      virtual DomainObject_p* getD() const = 0;
  };

} // Business

#endif // DOMAINOBJECT_H
