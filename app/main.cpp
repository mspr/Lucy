#include "application.h"
#include "main_view/mainwindow.h"
#include "messagehandler.h"
#include "databaseconnection.h"
#include "project/projectmanager.h"

int main(int argc, char* argv[])
{
  Application a(argc, argv);

  qInstallMessageHandler(MessageHandler::handleMessage);

  DatabaseConnection dbConnection;

  MainWindow w;
  w.show();

  const int res = a.exec();

  ProjectManager::kill();

  return res;
}
