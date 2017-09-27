#ifndef PERSONCREATECOMMAND_H
#define PERSONCREATECOMMAND_H

#include <QUndoCommand>

namespace Business { class Person; }
namespace Business { struct PersonInfo; }
class PersonView;

class PersonCreateCommand : public QUndoCommand
{
  public:
    PersonCreateCommand(const Business::PersonInfo& personInfo, PersonView* personView);

    virtual void redo() override;
    virtual void undo() override;

  private:
    const Business::PersonInfo& _personInfo;
    Business::Person* _person;
    PersonView* _personView;
};

#endif // PERSONCREATECOMMAND_H
