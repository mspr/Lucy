#include "application.h"
#include "main_view/mainwindow.h"
#include "messagehandler.h"
#include "databasemanager.h"
#include "project/projectmanager.h"
#include "commands/commandsmanager.h"

int main(int argc, char* argv[])
{
  Application a(argc, argv);

  qInstallMessageHandler(MessageHandler::handleMessage);

  DatabaseManager::getInstance()->open();

  MainWindow w;
  w.show();

  const int res = a.exec();

  CommandsManager::kill();
  ProjectManager::kill();
  DatabaseManager::kill();

  return res;
}
