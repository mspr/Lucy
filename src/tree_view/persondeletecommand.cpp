#include "persondeletecommand.h"

PersonDeleteCommand::PersonDeleteCommand()
  : QUndoCommand()
{
}

void PersonDeleteCommand::redo()
{
//  scene->removeNode(_personView);

//  delete _personView;

//  const bool newPerson = _person->id() != -1;
//  if (newPerson)
//  {

//  }
//  else
//  {
////    _personInfo = _person->info();
////    delete _person;
//  }
}

void PersonDeleteCommand::undo()
{

}
