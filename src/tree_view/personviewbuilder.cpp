#include "personviewbuilder.h"
#include "ui_personviewbuilder.h"
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
  const QString firstName = _ui->firstNameLineEdit->text();
  const QString lastName = _ui->lastNameLineEdit->text();
  const Gender gender = _ui->feminineGenderPushButton->isChecked() ? Gender::Feminine : Gender::Masculine;

  const QDate birthDate = _ui->birthDateEdit->date();
  Birth* birth = new Birth(birthDate);

  return new Person(gender, firstName, lastName, birth);
}
