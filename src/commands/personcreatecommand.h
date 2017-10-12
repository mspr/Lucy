#ifndef PERSONCREATECOMMAND_H
#define PERSONCREATECOMMAND_H

#include <QUndoCommand>

namespace Business { class Person; }
namespace Business { struct PersonInfo; }
class PersonView;

class PersonCreateCommand : public QUndoCommand
{
  public:
    PersonCreateCommand(const Business::PersonInfo& personInfo, PersonView* childView);

    virtual void redo() override;
    virtual void undo() override;

  private:
    const Business::PersonInfo& _personInfo;
    Business::Person* _person;
    PersonView* _childView;
};

#endif // PERSONCREATECOMMAND_H
