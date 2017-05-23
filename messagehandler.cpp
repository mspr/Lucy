#include "messagehandler.h"
#include "outputwindow.h"

using namespace Output;

OutputWindow* MessageHandler::s_outputWindow = nullptr;

MessageHandler::MessageHandler()
{
}

/*static*/ void MessageHandler::registerOutputWindow(OutputWindow* outputWindow)
{
  Q_ASSERT_X(outputWindow != nullptr, "registerOutputWindow()", "nullptr");
  s_outputWindow = outputWindow;
}

/*static*/ void MessageHandler::handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  printToConsole(type, context, msg);

  tryRedirectToOutputWindow(type, context, msg);
}

/*static*/ void MessageHandler::printToConsole(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  QByteArray localMsg = msg.toLocal8Bit();
  switch (type)
  {
    case QtDebugMsg:
      fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    break;
#if QT_VERSION >= 0x050500
    case QtInfoMsg:
      fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    break;
#endif
    case QtWarningMsg:
      fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    abort();
  }
}

/*static*/ void MessageHandler::tryRedirectToOutputWindow(QtMsgType type, const QMessageLogContext& /*context*/, const QString& msg)
{
  if (s_outputWindow != nullptr)
    s_outputWindow->showMessage(type, msg);
}
