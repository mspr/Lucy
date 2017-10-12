#include "personcreatecommand.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "business/tree.h"
#include "business/person.h"
#include "business/person_p.h"
#include "business/personinfo.h"
#include "tree_view/personview.h"
#include "tree_view/familytreescene.h"

using namespace Business;

PersonCreateCommand::PersonCreateCommand(const PersonInfo& personInfo, Person* child)
  : QUndoCommand("Create person " + personInfo.firstName + " " + personInfo.lastName)
  , _personInfo(personInfo)
  , _person(nullptr)
  , _child(child)
{
  Q_ASSERT(_child != nullptr);
}

void PersonCreateCommand::redo()
{
  Q_ASSERT(_person == nullptr);

  _person = new Person(_personInfo);

  Q_ASSERT(_child != nullptr);
  _child->setParent(_person);

  Tree* tree = _child->tree();
  Q_ASSERT(tree != nullptr);
  tree->add(_person);
}

void PersonCreateCommand::undo()
{
  Q_ASSERT(_person != nullptr);

  _person->tree()->remove(_person);

  _person->d()->removeChild();

  _person->deleteLater();
  _person = nullptr;
}
