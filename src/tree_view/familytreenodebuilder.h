#ifndef FAMILYTREENODEBUILDER_H
#define FAMILYTREENODEBUILDER_H

#include <QDialog>
#include "domain_object/person.h"

namespace Ui { class FamilyTreeNodeBuilder; }

class FamilyTreeNodeBuilder : public QDialog
{
  Q_OBJECT

  public:
    explicit FamilyTreeNodeBuilder(QWidget* parent = nullptr);
    ~FamilyTreeNodeBuilder();

    Person* person() const;

  private:
    Ui::FamilyTreeNodeBuilder* _ui;
};

#endif // FAMILYTREENODEBUILDER_H
