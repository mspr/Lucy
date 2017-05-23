#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QtMsgHandler>

namespace Output { class OutputWindow; }

class MessageHandler
{
  public:
    MessageHandler();

    static void registerOutputWindow(Output::OutputWindow* outputWindow);
    static void handleMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

  private:
    static void printToConsole(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static void tryRedirectToOutputWindow(QtMsgType type, const QMessageLogContext& context, const QString& msg);

  private:
    static Output::OutputWindow* s_outputWindow;
};

#endif // MESSAGEHANDLER_H
