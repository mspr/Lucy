#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree_view/familytreeview.h"
#include "tree_view/familytreescene.h"
#include "output/outputwindow.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "treecreationdialog.h"
#include "domain_object/tree.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QDebug>

using namespace Output;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);
  setWindowState(Qt::WindowMaximized);

  _treeTabWidget = new QTabWidget();
  setCentralWidget(_treeTabWidget);

  OutputWindow* outputWindow = new OutputWindow(this);
  addDockWidget(Qt::BottomDockWidgetArea, outputWindow);

  setupSignalSlotConnections();
}

void MainWindow::setupSignalSlotConnections()
{
  connect(ProjectManager::getInstance(), ProjectManager::projectOpen, this, MainWindow::onProjectOpen);
}

void MainWindow::newProject()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  if (!currentProject.isNull())
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
    }
  }
}

void MainWindow::openProject()
{
  // TODO Close current project if necessary

  const QString projectFileName = QFileDialog::getOpenFileName(this,
                                                               tr("Open Project"),
                                                               "",
                                                               tr("Project Files (*.lcy)"));

  if (!projectFileName.isEmpty())
  {
    ProjectManager::getInstance()->openProject(projectFileName);

    QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
    const QList<Tree*>& trees = currentProject->trees();

    for (int i=0; i<trees.count(); ++i)
    {
      FamilyTreeView* familyTreeView = new FamilyTreeView();
      FamilyTreeScene* familyTreeScene = new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), familyTreeView);
      Person* reference = trees.at(i)->reference();
      familyTreeScene->createNodeView(reference, QPointF(0, 0));
      familyTreeView->setScene(familyTreeScene);
      familyTreeView->setSceneRect(QRectF(-1000, -1000, 2000, 2000));

      _treeTabWidget->addTab(familyTreeView, trees.at(i)->name());
    }
  }
}

void MainWindow::saveProject()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());

  const QString fileName = currentProject->name() + ".lcy";
  QFile file(fileName);
  if (file.open(QIODevice::WriteOnly))
  {
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("project");
    xmlWriter.writeAttribute("name", currentProject->name());

    for (int i=0; i<currentProject->trees().count(); ++i)
    {
      Tree* tree = currentProject->trees().at(i);
      xmlWriter.writeStartElement("tree");
      xmlWriter.writeAttribute("id", QString::number(tree->id()));
      xmlWriter.writeEndElement();
    }

    xmlWriter.writeStartElement("current_tree");
    xmlWriter.writeAttribute("id", QString::number(currentProject->currentTree()->id()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();

    file.close();
  }
  else
  {
  }

  currentProject->commit();
}

void MainWindow::saveProjectAs()
{
  //  const filename = QFileDialog::getSaveFileName(this,
  //                                     tr("Save Xml"), ".",
  //                                     tr("Xml files (*.xml)"));


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
  _ui->actionSave->setEnabled(true);
  _ui->actionSaveAs->setEnabled(true);

  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  connect(currentProject.data(), Project::treeAdded, this, MainWindow::onTreeAdded);
  connect(currentProject.data(), Project::updated, this, MainWindow::onProjectUpdated);
  connect(currentProject.data(), Project::upToDate, this, MainWindow::onProjectUpToDate);

  setWindowTitle(currentProject.data()->name() + "[*]");
}

void MainWindow::onTreeAdded(QUuid droid)
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Tree* treeAdded = currentProject->tree(droid);

  Q_ASSERT(treeAdded != nullptr);

  FamilyTreeView* familyTreeView = new FamilyTreeView();
  FamilyTreeScene* familyTreeScene = new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), familyTreeView);
  familyTreeView->setScene(familyTreeScene);
  familyTreeView->setSceneRect(QRectF(-1000, -1000, 2000, 2000));

  _treeTabWidget->addTab(familyTreeView, treeAdded->name());
}

void MainWindow::onProjectUpdated()
{
  setWindowModified(true);
}

void MainWindow::onProjectUpToDate()
{
  setWindowModified(false);
}

MainWindow::~MainWindow()
{
  delete _ui;
}
