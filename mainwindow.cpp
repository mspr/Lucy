#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "familytreeview.h"
#include "familytreescene.h"
#include "output/outputwindow.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>

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

//  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

////  QSqlDatabase db;
//  db.setHostName("localhost");
//  db.setPort(5432);
//  db.setDatabaseName("lucy");
//  db.setUserName("postgres");
//  db.setPassword("postgres");
//  bool check = db.open();
//  if (!check)
//  {
//    QString errorMsg = db.lastError().text();
//    qDebug() << "error when opening db " << errorMsg;
//  }

//  db.close();
}

MainWindow::~MainWindow()
{
  delete _ui;
}
