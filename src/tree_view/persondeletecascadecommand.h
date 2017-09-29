#ifndef PERSONDELETECASCADECOMMAND_H
#define PERSONDELETECASCADECOMMAND_H

#include <QUndoCommand>

namespace Business { class Person; }

class PersonDeleteCascadeCommand : public QUndoCommand
{
  public:
    PersonDeleteCascadeCommand(Business::Person* person);

    virtual void redo() override;
    virtual void undo() override;

  private:
    void stackPersonsRecursively(Business::Person* person, QStack<Business::Person*>& stack);

  private:
    Business::Person* _person;
};

#endif // PERSONDELETECASCADECOMMAND_H
