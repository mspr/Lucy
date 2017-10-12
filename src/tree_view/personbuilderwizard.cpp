#include "personbuilderwizard.h"
#include "personidentificationwizardpage.h"
#include "personbirthwizardpage.h"
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

PersonBuilderWizard::PersonBuilderWizard(PersonView* childView, Gender gender, QWidget* parent)
  : QWizard(parent)
  , _gender(gender)
  , _childView(childView)
{
  Q_ASSERT(_childView != nullptr);

  addPage(new PersonIdentificationWizardPage(this));
  addPage(new PersonBirthWizardPage(this));
}

PersonBuilderWizard::~PersonBuilderWizard()
{
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

  personInfo.firstName = field("firstName").toString();
  personInfo.lastName = field("lastName").toString();
  personInfo.gender = _gender;

  const QDate birthDate = field("birth").toDate();
//  const QString birthCountry = _ui->countryLineEdit->text();
//  const QString birthDepartment = _ui->departmentLineEdit->text();
//  const QString birthCity = _ui->cityLineEdit->text();
//  Location* birthLocation = new Location(birthCountry, birthDepartment, birthCity);
  personInfo.birth = new Birth(birthDate, nullptr);

  PersonCreateCommand* personCreateCommand = new PersonCreateCommand(personInfo, _childView);
  CommandsManager::getInstance()->addCommand(personCreateCommand);

  QWizard::done(result);
}
