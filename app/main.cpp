#include "application.h"
#include "main_view/mainwindow.h"
#include "messagehandler.h"
#include "databaseconnection.h"
#include "project/projectmanager.h"
#include "commands/commandsmanager.h"

int main(int argc, char* argv[])
{
  Application a(argc, argv);

  qInstallMessageHandler(MessageHandler::handleMessage);

  DatabaseConnection::getInstance()->open();

  MainWindow w;
  w.show();

  const int res = a.exec();

  CommandsManager::kill();
  ProjectManager::kill();
  DatabaseConnection::kill();

  return res;
}
