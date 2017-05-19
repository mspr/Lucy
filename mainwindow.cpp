#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "familytreeview.h"
#include "familytreescene.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);

  _familyTreeView = new FamilyTreeView();
  setCentralWidget(_familyTreeView);

  _familyTreeScene.reset(new FamilyTreeScene(_familyTreeView));
}

MainWindow::~MainWindow()
{
  delete _ui;
}
