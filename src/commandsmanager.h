#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <QObject>

class QUndoStack;
class QUndoCommand;

class CommandsManager : public QObject
{
  public:
    static CommandsManager* getInstance();
    static void kill();

    void addCommand(QUndoCommand* command);

  private:
    CommandsManager();

  private:
    static CommandsManager* _commandsManager;
    QUndoStack* _undoStack;
};

#endif // COMMANDSMANAGER_H
