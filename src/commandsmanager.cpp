#include "commandsmanager.h"

#include <QUndoStack>

CommandsManager* CommandsManager::_commandsManager = nullptr;

/*static*/ CommandsManager* CommandsManager::getInstance()
{
  if (_commandsManager == nullptr)
    _commandsManager = new CommandsManager();

  return _commandsManager;
}

/*static*/ void CommandsManager::kill()
{
  if (_commandsManager != nullptr)
  {
    delete _commandsManager;
    _commandsManager = nullptr;
  }
}

CommandsManager::CommandsManager()
  : QObject()
  , _undoStack(new QUndoStack(this))
{
}

void CommandsManager::addCommand(QUndoCommand* command)
{
  Q_ASSERT(command != nullptr);
  _undoStack->push(command);
}
