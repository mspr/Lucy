#include "treebuilderview.h"
#include "ui_treebuilderview.h"
#include "business/person.h"
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
    const QString firstName = _ui->firstNameLineEdit->text();
    const QString lastName = _ui->lastNameLideEdit->text();

    const QDate birthDate = _ui->birthDateEdit->date();
    Birth* birth = new Birth(birthDate);

    Tree* tree = new Tree(treeName);
    Person* person = new Person(Gender::Masculine, firstName, lastName, birth);
    tree->addPerson(person);
    tree->setReference(person);

    currentProject->add(tree);
    currentProject->add(person);
//    currentProject->add(birth);
    currentProject->setCurrentTree(tree);
  }

  return result;
}
