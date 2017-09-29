#include "personbuilderwizard.h"
#include "ui_personbuilderwizard.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "business/tree.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/location.h"
#include "business/birth.h"
#include "business/gender.h"
#include "commands/personcreatecommand.h"
#include "commands/commandsmanager.h"

using namespace Business;

PersonBuilderWizard::PersonBuilderWizard(PersonView* personView, QWidget* parent)
  : QWizard(parent)
  , _ui(new Ui::PersonBuilderWizard)
  , _personView(personView)
{
  Q_ASSERT(_personView != nullptr);

  _ui->setupUi(this);
}

PersonBuilderWizard::~PersonBuilderWizard()
{
  delete _ui;
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

  PersonInfo personInfo;

  personInfo.firstName = _ui->firstNameLineEdit->text();
  personInfo.lastName = _ui->lastNameLineEdit->text();
  personInfo.gender = _ui->feminineGenderPushButton->isChecked() ? Gender::Feminine : Gender::Masculine;

  const QDate birthDate = _ui->dateEdit->date();
  const QString birthCountry = _ui->countryLineEdit->text();
  const QString birthDepartment = _ui->departmentLineEdit->text();
  const QString birthCity = _ui->cityLineEdit->text();
  Location* birthLocation = new Location(birthCountry, birthDepartment, birthCity);
  personInfo.birth = new Birth(birthDate, birthLocation);

  PersonCreateCommand* personCreateCommand = new PersonCreateCommand(personInfo, _personView);
  CommandsManager::getInstance()->addCommand(personCreateCommand);
  personCreateCommand->redo();

  QWizard::done(result);
}
