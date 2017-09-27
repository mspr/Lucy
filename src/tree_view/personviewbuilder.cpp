#include "personviewbuilder.h"
#include "ui_personviewbuilder.h"
#include "business/personinfo.h"
#include "business/birth.h"
#include "business/gender.h"

using namespace Business;

PersonViewBuilder::PersonViewBuilder(QWidget* parent)
  : QDialog(parent)
  , _ui(new Ui::PersonViewBuilder)
{
  _ui->setupUi(this);
}

PersonViewBuilder::~PersonViewBuilder()
{
  delete _ui;
}

Person* PersonViewBuilder::person() const
{
  PersonInfo personInfo;

  personInfo.firstName = _ui->firstNameLineEdit->text();
  personInfo.lastName = _ui->lastNameLineEdit->text();
  personInfo.gender = _ui->feminineGenderPushButton->isChecked() ? Gender::Feminine : Gender::Masculine;

  const QDate birthDate = _ui->birthDateEdit->date();
  personInfo.birth = new Birth(birthDate);

  return new Person(personInfo);
}
