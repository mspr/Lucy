#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree_view/familytreeview.h"
#include "tree_view/familytreescene.h"
#include "output/outputwindow.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "treecreationdialog.h"

#include <QFileDialog>

using namespace Output;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  _treeTabWidget = new QTabWidget();
  setCentralWidget(_treeTabWidget);

  OutputWindow* outputWindow = new OutputWindow(this);
  addDockWidget(Qt::BottomDockWidgetArea, outputWindow);
}

void MainWindow::newProject()
{

}

void MainWindow::openProject()
{
  // TODO Close current project if necessary

  const QString projectFileName = QFileDialog::getOpenFileName(this,
                                                               tr("Open Project"),
                                                               "",
                                                               tr("Project Files (*.lcy)"));

  ProjectManager::getInstance()->openProject(projectFileName);

  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  const QList<Tree*>& trees = currentProject->trees();

  for (int i=0; i<trees.count(); ++i)
  {
    FamilyTreeView* familyTreeView = new FamilyTreeView();
    FamilyTreeScene* familyTreeScene = new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), familyTreeView);
    familyTreeView->setScene(familyTreeScene);
    familyTreeView->setSceneRect(QRectF(-1000, -1000, 2000, 2000));

    _treeTabWidget->addTab(familyTreeView, trees.at(i)->name());
  }
}

void MainWindow::saveProject()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  currentProject->commit();
}

void MainWindow::quit()
{
  qApp->quit();
}

void MainWindow::createTree()
{
  TreeCreationDialog treeCreationDialog(this);
  if (treeCreationDialog.exec())
  {
  }
}

MainWindow::~MainWindow()
{
  delete _ui;
}
