#ifndef PERSONDELETECOMMAND_H
#define PERSONDELETECOMMAND_H

#include <QUndoCommand>

class PersonDeleteCommand : public QUndoCommand
{
  public:
    PersonDeleteCommand();

    virtual void redo() override;
    virtual void undo() override;
};

#endif // PERSONDELETECOMMAND_H
