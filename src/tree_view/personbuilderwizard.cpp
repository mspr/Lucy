#include "personbuilderwizard.h"
#include "ui_personbuilderwizard.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "business/tree.h"
#include "business/person.h"
#include "business/location.h"
#include "business/birth.h"

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
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());
  Tree* currentTree = currentProject->currentTree();
  Q_ASSERT(currentTree != nullptr);

  const QString firstName = _ui->firstNameLineEdit->text();
  const QString lastName = _ui->lastNameLineEdit->text();

  const QDate birthDate = _ui->dateEdit->date();
  const QString birthCountry = _ui->countryLineEdit->text();
  const QString birthDepartment = _ui->departmentLineEdit->text();
  const QString birthCity = _ui->cityLineEdit->text();
  Location* birthLocation = new Location(birthCountry, birthDepartment, birthCity);
  Birth* birth = new Birth(birthDate, birthLocation);

  _person = new Person(firstName, lastName, birth);

  currentTree->addPerson(_person);
//  currentProject->add(birthLocation);
//  currentProject->add(birth);
  currentProject->add(_person);

  QWizard::done(result);
}
