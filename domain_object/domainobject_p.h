#ifndef DOMAINOBJECT_P_H
#define DOMAINOBJECT_P_H

class DomainObject_p
{
  public:
    DomainObject_p();
    DomainObject_p(const int id);
    virtual ~DomainObject_p();

    void tryLoad();

  protected:
    virtual void load_impl() = 0;

  protected:
    enum class State
    {
      New,
      Deleted,
      Dirty,
      Unchanged
    };

  protected:
    int _id;
    State _state;
    bool _isLoaded;
};

#endif // DOMAINOBJECT_P_H
