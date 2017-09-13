#include "familytreenodebuilder.h"
#include "ui_familytreenodebuilder.h"
#include "business/birth.h"
#include "business/gender.h"

using namespace Business;

FamilyTreeNodeBuilder::FamilyTreeNodeBuilder(QWidget* parent)
  : QDialog(parent)
  , _ui(new Ui::FamilyTreeNodeBuilder)
{
  _ui->setupUi(this);
}

FamilyTreeNodeBuilder::~FamilyTreeNodeBuilder()
{
  delete _ui;
}

Person* FamilyTreeNodeBuilder::person() const
{
  const QString firstName = _ui->firstNameLineEdit->text();
  const QString lastName = _ui->lastNameLineEdit->text();
  const Gender gender = _ui->feminineGenderPushButton->isChecked() ? Gender::Feminine : Gender::Masculine;

  const QDate birthDate = _ui->birthDateEdit->date();
  Birth* birth = new Birth(birthDate);

  return new Person(gender, firstName, lastName, birth);
}
