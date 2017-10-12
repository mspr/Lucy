#include "personbirthwizardpage.h"
#include "ui_personbirthwizardpage.h"

PersonBirthWizardPage::PersonBirthWizardPage(QWidget* parent)
  : QWizardPage(parent)
  , _ui(new Ui::PersonBirthWizardPage)
{
  _ui->setupUi(this);

  registerField("birth", _ui->birthDateEdit);
}

PersonBirthWizardPage::~PersonBirthWizardPage()
{
  delete _ui;
}
