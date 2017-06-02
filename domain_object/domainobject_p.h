#ifndef DOMAINOBJECT_P_H
#define DOMAINOBJECT_P_H

class DomainObject_p
{
  public:
    DomainObject_p();
    virtual ~DomainObject_p();

    void tryLoad();

  protected:
    virtual void load_impl() = 0;

  protected:
    int _id;
    bool _isLoaded;
};

#endif // DOMAINOBJECT_P_H
