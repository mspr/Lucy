#ifndef PERSONDELETECOMMAND_H
#define PERSONDELETECOMMAND_H

#include <QUndoCommand>
#include "business/personinfo.h"

namespace Business { class Person; }
namespace Business { class Tree; }
namespace Business { enum class DatabaseStatus; }

class PersonDeleteCommand : public QUndoCommand
{
  public:
    PersonDeleteCommand(Business::Person* person, QUndoCommand* parent = nullptr);

    virtual void redo() override;
    virtual void undo() override;

  private:
    Business::Person* _person;
    Business::DatabaseStatus _status;
    Business::PersonInfo _personInfo;
    Business::Tree* _tree;
};

#endif // PERSONDELETECOMMAND_H
