#include "treecreationdialog.h"
#include "ui_treecreationdialog.h"
#include "domain_object/person.h"
#include "domain_object/tree.h"
#include "project/projectmanager.h"
#include "project/project.h"

TreeCreationDialog::TreeCreationDialog(QWidget* parent)
  : QDialog(parent),
    _ui(new Ui::TreeCreationDialog)
{
  _ui->setupUi(this);
}

TreeCreationDialog::~TreeCreationDialog()
{
  delete _ui;
}

int TreeCreationDialog::exec()
{
  const int result = QDialog::exec();
  if (result)
  {
    const QString treeName = _ui->treeNameLineEdit->text();
    const QString firstName = _ui->firstNameLineEdit->text();
    const QString lastName = _ui->lastNameLideEdit->text();
    const QDate birthDate = _ui->birthDateEdit->date();

    QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
    Q_ASSERT(!currentProject.isNull());

    Tree* tree = new Tree(treeName);
    Person* person = new Person(firstName, lastName, birthDate);
    tree->addPerson(person);
    tree->setReference(person);

    currentProject->add(tree);
    currentProject->setCurrentTree(tree);
  }

  return result;
}
