#include "personidentificationwizardpage.h"
#include "ui_personidentificationwizardpage.h"
#include "business/gender.h"

using namespace Business;

PersonIdentificationWizardPage::PersonIdentificationWizardPage(Gender gender, QWidget* parent)
  : QWizardPage(parent)
  , _ui(new Ui::PersonIdentificationWizardPage)
{
  _ui->setupUi(this);

  if (gender == Gender::Feminine)
    _ui->feminineGenderButton->setChecked(true);
  else
    _ui->masculineGenderButton->setChecked(true);

  _ui->genderWidget->setVisible(gender == Gender::Unidentified);

  registerField("firstName*", _ui->firstNameLineEdit);
  registerField("lastName*", _ui->lastNameLineEdit);
  registerField("feminineGender", _ui->feminineGenderButton);

  _ui->firstNameLineEdit->setProperty("mandatoryField", true);
  _ui->lastNameLineEdit->setProperty("mandatoryField", true);
}

PersonIdentificationWizardPage::~PersonIdentificationWizardPage()
{
  delete _ui;
}
