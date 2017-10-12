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

PersonCreateCommand::PersonCreateCommand(const PersonInfo& personInfo, PersonView* childView)
  : QUndoCommand("Create person " + personInfo.firstName + " " + personInfo.lastName)
  , _personInfo(personInfo)
  , _person(nullptr)
  , _childView(childView)
{
  Q_ASSERT(_childView != nullptr);
}

void PersonCreateCommand::redo()
{
  Q_ASSERT(_person == nullptr);

  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());
  Tree* currentTree = currentProject->currentTree();
  Q_ASSERT(currentTree != nullptr);

  _person = new Person(_personInfo);

  Person* child = _childView->person();
  Q_ASSERT(child != nullptr);
  child->setParent(_person);

  currentTree->add(_person);
}

void PersonCreateCommand::undo()
{
  Q_ASSERT(_person != nullptr);

  _person->tree()->remove(_person);

  _person->d()->removeChild();

  _person->deleteLater();
  _person = nullptr;
}
