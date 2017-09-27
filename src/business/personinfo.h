#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QString>

namespace Business
{
  class Birth;
  enum class Gender;

  struct PersonInfo
  {
    QString firstName;
    QString lastName;
    Gender gender;
    Birth* birth;
  };

} // Business

#endif // PERSONINFO_H
