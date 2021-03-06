#ifndef PERSONUPDATERVIEW_H
#define PERSONUPDATERVIEW_H

#include <QDialog>

namespace Ui { class PersonUpdaterView; }
namespace Business { class Person; }

class PersonUpdaterView : public QDialog
{
  Q_OBJECT

  public:
    explicit PersonUpdaterView(Business::Person* person, QWidget* parent = nullptr);
    ~PersonUpdaterView();

  public slots:
    virtual void open() override;
    virtual int exec() override;
    virtual void accept() override;

  private:
    Ui::PersonUpdaterView* _ui;
    Business::Person* _person;
};

#endif // PERSONUPDATERVIEW_H
