#include "personbuilderwizard.h"
#include "ui_personbuilderwizard.h"
#include "business/person.h"

using namespace Business;

PersonBuilderWizard::PersonBuilderWizard(QWidget* parent)
  : QWizard(parent)
  , _ui(new Ui::PersonBuilderWizard)
  , _person(nullptr)
{
  _ui->setupUi(this);
}

PersonBuilderWizard::~PersonBuilderWizard()
{
  delete _ui;
}

Person* PersonBuilderWizard::person() const
{
//  Person* person = _person;
//  _person = nullptr;

  return _person;
}

int PersonBuilderWizard::exec()
{
  return QWizard::exec();
}

void PersonBuilderWizard::open()
{
  QWizard::open();
}

void PersonBuilderWizard::done(int result)
{
  if (_person != nullptr)
    delete _person;

  const QString firstName = _ui->firstNameLineEdit->text();
  const QString lastName = _ui->lastNameLineEdit->text();
  const QDate birthDate = _ui->dateEdit->date();

  _person = new Person(firstName, lastName, birthDate);

  QWizard::done(result);
}
