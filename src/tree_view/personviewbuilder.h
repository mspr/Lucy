#ifndef PERSONVIEWBUILDER_H
#define PERSONVIEWBUILDER_H

#include <QDialog>
#include "business/person.h"

namespace Ui { class PersonViewBuilder; }

class PersonViewBuilder : public QDialog
{
  Q_OBJECT

  public:
    explicit PersonViewBuilder(QWidget* parent = nullptr);
    ~PersonViewBuilder();

    Business::Person* person() const;

  private:
    Ui::PersonViewBuilder* _ui;
};

#endif // PERSONVIEWBUILDER_H
