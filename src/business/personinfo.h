#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QString>

namespace Business
{
  class Birth;
  enum class Gender;

  struct PersonInfo
  {
    PersonInfo()
    {
    }

    PersonInfo(const QString& firstName, const QString& lastName, Gender gender, Birth* birth)
      : firstName(firstName)
      , lastName(lastName)
      , gender(gender)
      , birth(birth)
    {
    }

    QString firstName;
    QString lastName;
    Gender gender;
    Birth* birth;
  };

} // Business

#endif // PERSONINFO_H
