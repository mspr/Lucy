#ifndef FAMILYTREENODEBUILDER_H
#define FAMILYTREENODEBUILDER_H

#include <QDialog>
#include "business/person.h"

namespace Ui { class FamilyTreeNodeBuilder; }

class FamilyTreeNodeBuilder : public QDialog
{
  Q_OBJECT

  public:
    explicit FamilyTreeNodeBuilder(QWidget* parent = nullptr);
    ~FamilyTreeNodeBuilder();

    Business::Person* person() const;

  private:
    Ui::FamilyTreeNodeBuilder* _ui;
};

#endif // FAMILYTREENODEBUILDER_H
