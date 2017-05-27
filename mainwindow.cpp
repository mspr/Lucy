#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tree_view/familytreeview.h"
#include "tree_view/familytreescene.h"
#include "output/outputwindow.h"

using namespace Output;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  _familyTreeView = new FamilyTreeView();
  setCentralWidget(_familyTreeView);

  _familyTreeScene.reset(new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), _familyTreeView));
  _familyTreeView->setScene(_familyTreeScene.data());
  _familyTreeView->setSceneRect(QRectF(-1000, -1000, 2000, 2000));

  OutputWindow* outputWindow = new OutputWindow(this);
  addDockWidget(Qt::BottomDockWidgetArea, outputWindow);
}

void MainWindow::newProject()
{

}

void MainWindow::openProject()
{

}

void MainWindow::saveProject()
{

}

MainWindow::~MainWindow()
{
  delete _ui;
}
