#include "ipersonviewmodel.h"
#include <QtGlobal>

IPersonViewModel::IPersonViewModel(Business::Person* person)
  : _person(person)
{
  Q_ASSERT(_person != nullptr);
}
