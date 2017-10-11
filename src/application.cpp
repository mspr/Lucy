#include "application.h"

#include <QFile>
#include <QDebug>

Application::Application(int& argc, char** argv)
  : QApplication(argc, argv)
{
  const QString styleSheetFileName = ":/application.qss";
  if (!loadStyleSheet(styleSheetFileName))
    qWarning() << QString("Impossible to load style sheet file %1.").arg(styleSheetFileName);
}

bool Application::notify(QObject* receiver, QEvent* event)
{
  try
  {
    return QApplication::notify(receiver, event);
  }
  catch (std::exception& e)
  {
    qCritical() << "Exception handled: " << e.what();
    return false;
  }
}

bool Application::loadStyleSheet(const QString& fileName)
{
  bool ret = false;

  QFile file(fileName);
  if (file.open(QFile::ReadOnly))
  {
    QTextStream styleIn(&file);
    setStyleSheet(styleIn.readAll());
    file.close();
    ret = true;
  }

  return ret;
}
