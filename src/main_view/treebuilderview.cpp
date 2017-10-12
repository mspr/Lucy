#include "treebuilderview.h"
#include "ui_treebuilderview.h"
#include "tree_view/personbuilderwizard.h"
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
  _ui->treeNameValidationMarker->hide();

  _ui->treeNameLineEdit->setFocus();
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

    PersonBuilderWizard personBuilderWizard(tree);
    if (personBuilderWizard.exec() == QWizard::Accepted)
    {
      currentProject->add(tree);
      currentProject->setCurrentTree(tree);
    }
    else
    {
      tree->deleteLater();
    }
  }

  return result;
}

void TreeBuilderView::accept()
{
  _ui->treeNameValidationMarker->hide();

  if (_ui->treeNameLineEdit->text().isEmpty())
    _ui->treeNameValidationMarker->show();
  else
    QDialog::accept();
}
