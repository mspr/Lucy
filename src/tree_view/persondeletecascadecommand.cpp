#include "persondeletecascadecommand.h"
#include "business/person.h"
#include "persondeletecommand.h"

using namespace Business;

PersonDeleteCascadeCommand::PersonDeleteCascadeCommand(Person* person)
  : QUndoCommand()
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  createDeleteCommandsRecursively(_person);
}

void PersonDeleteCascadeCommand::createDeleteCommandsRecursively(Person* person)
{
  Q_ASSERT(person != nullptr);

  PersonDeleteCommand* deleteCommand = new PersonDeleteCommand(person, this);
  Q_UNUSED(deleteCommand);

  Person* father = _person->father();
  if (father != nullptr)
    createDeleteCommandsRecursively(father);

  Person* mother = _person->mother();
  if (mother != nullptr)
    createDeleteCommandsRecursively(mother);
}

void PersonDeleteCascadeCommand::redo()
{
  QUndoCommand::redo();
}

void PersonDeleteCascadeCommand::undo()
{
  QUndoCommand::undo();
}
