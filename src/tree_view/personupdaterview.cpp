#include "personupdaterview.h"
#include "ui_personupdaterview.h"
#include "domain_object/person.h"

using namespace Business;

PersonUpdaterView::PersonUpdaterView(Person* person, QWidget* parent)
  : QDialog(parent)
  , _ui(new Ui::PersonUpdaterView)
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  _ui->setupUi(this);
}

PersonUpdaterView::~PersonUpdaterView()
{
  delete _ui;
}

void PersonUpdaterView::open()
{
  QDialog::open();
}

int PersonUpdaterView::exec()
{
  _ui->firstNameLineEdit->setText(_person->firstName());
  _ui->lastNameLineEdit->setText(_person->lastName());
  _ui->birthDateEdit->setDate(_person->birthDate());

  return QDialog::exec();
}

void PersonUpdaterView::accept()
{
  _person->setFirstName(_ui->firstNameLineEdit->text());
  _person->setLastName(_ui->lastNameLineEdit->text());
  _person->setBirthDate(_ui->birthDateEdit->date());

  QDialog::accept();
}
