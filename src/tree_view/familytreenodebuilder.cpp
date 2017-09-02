#include "familytreenodebuilder.h"
#include "ui_familytreenodebuilder.h"

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

  return new Person(firstName, lastName, birthDate);
}
