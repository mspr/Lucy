#ifndef PERSONBUILDERWIZARD_H
#define PERSONBUILDERWIZARD_H

#include <QWizard>

namespace Ui { class PersonBuilderWizard; }
class PersonView;

class PersonBuilderWizard : public QWizard
{
  Q_OBJECT

  public:
    explicit PersonBuilderWizard(PersonView* personView, QWidget* parent = nullptr);
    ~PersonBuilderWizard();

  public slots:
    virtual int exec() override;
    virtual void open() override;

  protected:
    virtual void done(int result) override;

  private:
    Ui::PersonBuilderWizard* _ui;
    PersonView* _personView;
};

#endif // PERSONBUILDERWIZARD_H
