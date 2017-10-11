#include "treebuilderview.h"
#include "ui_treebuilderview.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "business/tree.h"
#include "business/birth.h"
#include "business/gender.h"
#include "project/projectmanager.h"
#include "project/project.h"

using namespace Business;

TreeBuilderView::TreeBuilderView(QWidget* parent)
  : QDialog(parent)
  , _ui(new Ui::TreeBuilderView)
{
  _ui->setupUi(this);

  _ui->treeNameLineEdit->setProperty("mandatoryField", true);
  _ui->firstNameLineEdit->setProperty("mandatoryField", true);
  _ui->lastNameLideEdit->setProperty("mandatoryField", true);

  clearValidationMarkers();
}

void TreeBuilderView::clearValidationMarkers()
{
  _ui->treeNameValidationMarker->hide();
  _ui->firstNameValidationMarker->hide();
  _ui->lastNameValidationMarker->hide();
}

TreeBuilderView::~TreeBuilderView()
{
  delete _ui;
}

int TreeBuilderView::exec()
{
  const int result = QDialog::exec();
  if (result)
  {
    QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
    Q_ASSERT(!currentProject.isNull());

    const QString treeName = _ui->treeNameLineEdit->text();
    Tree* tree = new Tree(treeName);

    PersonInfo personInfo;
    personInfo.firstName = _ui->firstNameLineEdit->text();
    personInfo.lastName = _ui->lastNameLideEdit->text();
    personInfo.gender = Gender::Masculine;
    const QDate birthDate = _ui->birthDateEdit->date();
    personInfo.birth = new Birth(birthDate);
    Person* person = new Person(personInfo);

    tree->add(person);
    tree->setReference(person);

    currentProject->add(tree);
    currentProject->setCurrentTree(tree);
  }

  return result;
}

void TreeBuilderView::accept()
{
  bool valid = true;

  clearValidationMarkers();

  if (_ui->treeNameLineEdit->text().isEmpty())
  {
    _ui->treeNameValidationMarker->show();
    valid = false;
  }

  if (_ui->firstNameLineEdit->text().isEmpty())
  {
    _ui->firstNameValidationMarker->show();
    valid = false;
  }

  if (_ui->lastNameLideEdit->text().isEmpty())
  {
    _ui->lastNameValidationMarker->show();
    valid = false;
  }

  if (valid)
    QDialog::accept();
}
