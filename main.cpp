#include "mainwindow.h"
#include "messagehandler.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  qInstallMessageHandler(MessageHandler::handleMessage);

  MainWindow w;
  w.show();

  return a.exec();
}
