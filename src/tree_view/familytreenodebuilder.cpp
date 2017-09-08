#include "familytreenodebuilder.h"
#include "ui_familytreenodebuilder.h"
#include "business/birth.h"

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

  const QDate birthDate = _ui->birthDateEdit->date();
  Birth* birth = new Birth(birthDate);

  return new Person(firstName, lastName, birth);
}
