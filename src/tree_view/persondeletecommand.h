#ifndef PERSONDELETECOMMAND_H
#define PERSONDELETECOMMAND_H

#include <QUndoCommand>

namespace Business { class Person; }

class PersonDeleteCommand : public QUndoCommand
{
  public:
    PersonDeleteCommand(Business::Person* person);

    virtual void redo() override;
    virtual void undo() override;

  private:
    Business::Person* _person;
};

#endif // PERSONDELETECOMMAND_H
