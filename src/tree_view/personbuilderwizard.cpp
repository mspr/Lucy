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
#include "commands/personcreatecommand.h"
#include "commands/commandsmanager.h"

using namespace Business;

PersonBuilderWizard::PersonBuilderWizard(Tree* tree, Gender gender, Person* child, QWidget* parent)
  : QWizard(parent)
  , _tree(tree)
  , _child(child)
{
  Q_ASSERT(_tree != nullptr);

  if (_child == nullptr)
    setWindowTitle("Create Reference");
  else
    setWindowTitle("Create Person");

  addPage(new PersonIdentificationWizardPage(gender, this));
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
  if (result == QWizard::Accepted)
  {
    PersonInfo personInfo;

    personInfo.firstName = field("firstName").toString();
    personInfo.lastName = field("lastName").toString();
    personInfo.gender = field("feminineGender").toBool() ? Gender::Feminine : Gender::Masculine;

    const QDate birthDate = field("birth").toDate();
  //  const QString birthCountry = _ui->countryLineEdit->text();
  //  const QString birthDepartment = _ui->departmentLineEdit->text();
  //  const QString birthCity = _ui->cityLineEdit->text();
  //  Location* birthLocation = new Location(birthCountry, birthDepartment, birthCity);
    personInfo.birth = new Birth(birthDate, nullptr);

    if (_child != nullptr)
    {
      PersonCreateCommand* personCreateCommand = new PersonCreateCommand(personInfo, _child);
      CommandsManager::getInstance()->addCommand(personCreateCommand);
    }
    else
    {
      Person* person = new Person(personInfo);
      _tree->add(person);
      _tree->setReference(person);
    }
  }

  QWizard::done(result);
}
