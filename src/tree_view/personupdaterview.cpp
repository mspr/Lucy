#include "personupdaterview.h"
#include "ui_personupdaterview.h"
#include "business/person.h"
#include "business/birth.h"

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
  _ui->birthDateEdit->setDate(_person->birth()->date());

  return QDialog::exec();
}

void PersonUpdaterView::accept()
{
  _person->setFirstName(_ui->firstNameLineEdit->text());
  _person->setLastName(_ui->lastNameLineEdit->text());
  _person->birth()->setDate(_ui->birthDateEdit->date());

  QDialog::accept();
}
