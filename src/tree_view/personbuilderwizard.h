#ifndef PERSONBUILDERWIZARD_H
#define PERSONBUILDERWIZARD_H

#include <QWizard>

namespace Ui { class PersonBuilderWizard; }
namespace Business { class Person; }

class PersonBuilderWizard : public QWizard
{
  Q_OBJECT

  public:
    explicit PersonBuilderWizard(QWidget* parent = nullptr);
    ~PersonBuilderWizard();

    Business::Person* person() const;

  public slots:
    virtual int exec() override;
    virtual void open() override;

  protected:
    virtual void done(int result) override;

  private:
    Ui::PersonBuilderWizard* _ui;
    Business::Person* _person;
};

#endif // PERSONBUILDERWIZARD_H
