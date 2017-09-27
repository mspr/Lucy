#include "personcreatecommand.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "business/tree.h"
#include "business/person.h"
#include "business/personinfo.h"
#include "personview.h"
#include "familytreescene.h"

using namespace Business;

PersonCreateCommand::PersonCreateCommand(const PersonInfo& personInfo, PersonView* personView)
  : QUndoCommand("Create person " + personInfo.firstName + " " + personInfo.lastName)
  , _personInfo(personInfo)
  , _person(nullptr)
  , _personView(personView)
{
  Q_ASSERT(_personView != nullptr);
}

void PersonCreateCommand::redo()
{
  QSharedPointer<Project> currentProject = ProjectManager::getInstance()->currentProject();
  Q_ASSERT(!currentProject.isNull());
  Tree* currentTree = currentProject->currentTree();
  Q_ASSERT(currentTree != nullptr);

  _person = new Person(_personInfo);

  currentTree->addPerson(_person);
//  currentProject->add(birthLocation);
//  currentProject->add(birth);
  currentProject->add(_person);

  _personView->person()->setParent(_person);

  _personView->treeScene()->extendTreeFromNode(_personView, _person);
//    scene->adjustNodes();
}

void PersonCreateCommand::undo()
{
  Q_ASSERT(_person != nullptr);

  // Remove node from scene

  // Remove person from project

  delete _person;
  _person = nullptr;
}
