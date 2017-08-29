#include "familytreenodebuilder.h"
#include "ui_familytreenodebuilder.h"

FamilyTreeNodeBuilder::FamilyTreeNodeBuilder(QWidget* parent)
  : QDialog(parent)
  , m_ui(new Ui::FamilyTreeNodeBuilder)
{
  m_ui->setupUi(this);
}

FamilyTreeNodeBuilder::~FamilyTreeNodeBuilder()
{
  delete m_ui;
}

Person* FamilyTreeNodeBuilder::person() const
{
  const QString firstName = m_ui->firstNameLineEdit->text();
  const QString lastName = m_ui->lastNameLineEdit->text();
  const QDate birthDate = m_ui->birthDateEdit->date();

  return new Person(firstName, lastName, birthDate);
}
