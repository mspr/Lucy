#include "persondeletecommand.h"
#include "business/person.h"
#include "business/person_p.h"
#include "business/tree.h"
#include "business/databasestatus.h"

using namespace Business;

PersonDeleteCommand::PersonDeleteCommand(Person* person)
  : QUndoCommand()
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  _tree = _person->tree();
  _status = _person->status();

  setText("Delete person " + _person->firstName() + " " + _person->lastName());
}

void PersonDeleteCommand::redo()
{
  _tree->remove(_person);

  if (_status == DatabaseStatus::New)
  {
    _personInfo = _person->info();
    _person->deleteLater();
  }
  else
  {
    _person->d()->markAsDeleted();
  }
}

void PersonDeleteCommand::undo()
{
  if (_status == DatabaseStatus::New)
  {
    _person = new Person(_personInfo);
  }
  else
  {
    _person->revertStatus();
  }

  _tree->add(_person);
}
