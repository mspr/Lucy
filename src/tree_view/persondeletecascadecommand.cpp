#include "persondeletecascadecommand.h"
#include "business/person.h"
#include "persondeletecommand.h"

#include <QStack>

using namespace Business;

PersonDeleteCascadeCommand::PersonDeleteCascadeCommand(Person* person)
  : QUndoCommand()
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  QStack<Person*> stack;
  stackPersonsRecursively(_person, stack);

  while (!stack.isEmpty())
  {
    Person* person = stack.pop();
    PersonDeleteCommand* deleteCommand = new PersonDeleteCommand(person, this);
    Q_UNUSED(deleteCommand);
  }
}

void PersonDeleteCascadeCommand::stackPersonsRecursively(Person* person, QStack<Person*>& stack)
{
  Q_ASSERT(person != nullptr);

  stack.push(person);

  if (person->hasFather())
    stackPersonsRecursively(person->father(), stack);

  if (person->hasMother())
    stackPersonsRecursively(person->mother(), stack);
}

void PersonDeleteCascadeCommand::redo()
{
  QUndoCommand::redo();
}

void PersonDeleteCascadeCommand::undo()
{
  QUndoCommand::undo();
}
