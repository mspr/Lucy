#include "persondeletecommand.h"
#include "business/person.h"
#include "business/person_p.h"
#include "business/tree.h"

using namespace Business;

PersonDeleteCommand::PersonDeleteCommand(Person* person)
  : QUndoCommand()
  , _person(person)
{
  Q_ASSERT(_person != nullptr);
  setText("Delete person " + _person->firstName() + " " + _person->lastName());
}

void PersonDeleteCommand::redo()
{
  _person->tree()->remove(_person);

  if (_person->isNew())
  {
    _person->deleteLater();
  }
  else
  {
    _person->d()->markAsDeleted();
  }
}

void PersonDeleteCommand::undo()
{

}
