#ifndef IPERSONVIEWMODEL_H
#define IPERSONVIEWMODEL_H

namespace Business { class Person; }

class IPersonViewModel
{
  public:
    IPersonViewModel(Business::Person* person);

  private:
    Business::Person* _person;
};

#endif // IPERSONVIEWMODEL_H
