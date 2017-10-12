#include "personidentificationwizardpage.h"
#include "ui_personidentificationwizardpage.h"

PersonIdentificationWizardPage::PersonIdentificationWizardPage(QWidget* parent)
  : QWizardPage(parent)
  , _ui(new Ui::PersonIdentificationWizardPage)
{
  _ui->setupUi(this);

  registerField("firstName*", _ui->firstNameLineEdit);
  registerField("lastName*", _ui->lastNameLineEdit);

  _ui->firstNameLineEdit->setProperty("mandatoryField", true);
  _ui->lastNameLineEdit->setProperty("mandatoryField", true);
}

PersonIdentificationWizardPage::~PersonIdentificationWizardPage()
{
  delete _ui;
}
