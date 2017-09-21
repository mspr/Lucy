#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree_view/familytreeview.h"
#include "tree_view/familytreescene.h"
#include "output/outputwindow.h"
#include "recentprojectsview.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "treecreationdialog.h"
#include "business/tree.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QSettings>
#include <QDebug>

using namespace Output;
using namespace Business;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
  , _recentProjectsNumber(5)
  , _recentProjectsMenu(nullptr)
{
  _ui->setupUi(this);

  setupRecentProjectsMenu();

  RecentProjectsView* recentProjectsView = new RecentProjectsView(_recentProjectsMenu->actions(), this);
  addDockWidget(Qt::LeftDockWidgetArea, recentProjectsView);

  _treeTabWidget = new QTabWidget();
  setCentralWidget(_treeTabWidget);

  OutputWindow* outputWindow = new OutputWindow(this);
  addDockWidget(Qt::BottomDockWidgetArea, outputWindow);

  setupSignalSlotConnections();

  setWindowState(Qt::WindowMaximized);
}

void MainWindow::setupRecentProjectsMenu()
{
  Q_ASSERT(_recentProjectsMenu == nullptr);

  _recentProjectsMenu = new QMenu(_ui->menuBar);
  _recentProjectsMenu->setVisible(false);
  _ui->menuBar->addMenu(_recentProjectsMenu);

  for (int i=0; i<_recentProjectsNumber; ++i)
  {
    QAction* action = new QAction(_recentProjectsMenu);
    connect(action, &QAction::triggered, this, &MainWindow::openRecentProject);
    _recentProjectsMenu->addAction(action);
  }
}

void MainWindow::updateRecentProjectsMenu()
{
  Q_ASSERT(_recentProjectsMenu != nullptr);

  QSettings settings;
  const QStringList recentProjects = settings.value("recentProjects").toStringList();
  if (recentProjects.count() > 0)
  {
    const QList<QAction*> actions = _recentProjectsMenu->actions();
    for (int i=0; i<actions.count(); ++i)
    {
      QAction* action = actions.at(i);
      action->setText(recentProjects.at(i));
    }

    _recentProjectsMenu->setVisible(true);
  }
}

void MainWindow::setupSignalSlotConnections()
{
  connect(ProjectManager::getInstance(), ProjectManager::projectOpen, this, MainWindow::onProjectOpen);
}

void MainWindow::newProject()
{
  QInputDialog* dialog = new QInputDialog(this);
  dialog->setLabelText("Project name:");
  dialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

  if (!dialog->exec())
    return;

  const QString projectName = dialog->textValue();
  if (!projectName.isEmpty())
  {
    std::function<void()> action = [&] ()
    {
      ProjectManager::getInstance()->createNewProject(projectName);
    };

    askUserToSaveAndContinue(action);
  }
}

void MainWindow::openRecentProject()
{

}

void MainWindow::openProject()
{
  const QString projectFileName = QFileDialog::getOpenFileName(this,
                                                               tr("Open Project"),
                                                               "",
                                                               tr("Project Files (*.lcy)"));

  if (!projectFileName.isEmpty())
  {
    std::function<void()> action = [&] ()
    {
      ProjectManager::getInstance()->openProject(projectFileName);
    };

    askUserToSaveAndContinue(action);
  }
}

void MainWindow::askUserToSaveAndContinue(std::function<void ()> action)
{
  QWeakPointer<Project> currentProject = ProjectManager::getInstance()->currentProject().toWeakRef();
  if (!currentProject.isNull())
  {
    if (currentProject.data()->isDirty())
    {
      const int res = QMessageBox::warning(this,
                                           "Project open with changes",
                                           "A project is already open and has been modified. Do you want to save changes before closing it ?",
                                           QMessageBox::SaveAll,
                                           QMessageBox::Ignore,
                                           QMessageBox::Cancel);
      if (res & QMessageBox::SaveAll)
      {
        saveProject();
      }
      else if (res & QMessageBox::Ignore)
      {
      }
      else
      {
        return;
      }
    }
  }

  action();
}

void MainWindow::saveProject()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());
  currentProject->save();
}

void MainWindow::saveProjectAs()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());

  const QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Project"),
                                                        ".",
                                                        tr("Project Files (*.lcy)"));

  if (!fileName.isEmpty())
  {
    currentProject->setFileInfo(QFileInfo(fileName));
    currentProject->save();
  }
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

void MainWindow::onProjectOpen()
{
  _ui->actionCreateTree->setEnabled(true);

  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  connect(currentProject.data(), Project::treeAdded, this, MainWindow::onTreeAdded);
  connect(currentProject.data(), Project::dirty, this, MainWindow::onProjectDirty);
  connect(currentProject.data(), Project::upToDate, this, MainWindow::onProjectUpToDate);
  connect(currentProject.data(), Project::saved, this, MainWindow::onProjectSaved);
  connect(currentProject.data(), Project::destroyed, this, MainWindow::onProjectClosed);

  setWindowTitle(currentProject.data()->name() + "[*]");

  const QList<Tree*> trees = currentProject->trees();
  for (int i=0; i<trees.count(); ++i)
  {
    FamilyTreeView* familyTreeView = new FamilyTreeView(trees.at(i));
    _treeTabWidget->addTab(familyTreeView, trees.at(i)->name());
  }

  onProjectUpToDate();
}

void MainWindow::onProjectClosed()
{
  _treeTabWidget->clear();
}

void MainWindow::onTreeAdded(QUuid droid)
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Tree* treeAdded = currentProject->tree(droid);

  Q_ASSERT(treeAdded != nullptr);

  FamilyTreeView* familyTreeView = new FamilyTreeView(treeAdded);
  _treeTabWidget->addTab(familyTreeView, treeAdded->name());
}

void MainWindow::onProjectDirty()
{
  _ui->actionSave->setEnabled(true);
  _ui->actionSaveAs->setEnabled(true);
  setWindowModified(true);
}

void MainWindow::onProjectUpToDate()
{
  _ui->actionSave->setEnabled(false);
  _ui->actionSaveAs->setEnabled(false);
  setWindowModified(false);
}

void MainWindow::onProjectSaved()
{
  Project* project = dynamic_cast<Project*>(sender());
  Q_ASSERT(project != nullptr);

  const QString fileName = project->fileInfo().fileName();

  QSettings settings;
  QStringList recentProjects = settings.value("recentProjects").toStringList();
  recentProjects.removeAll(fileName);
  recentProjects.prepend(fileName);
  settings.setValue("recentProjects", recentProjects);
}

MainWindow::~MainWindow()
{
  delete _ui;
}
