#ifndef PERSONBUILDERWIZARD_H
#define PERSONBUILDERWIZARD_H

#include <QWizard>

namespace Business { enum class Gender; }
class PersonView;

class PersonBuilderWizard : public QWizard
{
  Q_OBJECT

  public:
    explicit PersonBuilderWizard(PersonView* personView, Business::Gender gender, QWidget* parent = nullptr);
    ~PersonBuilderWizard();

  public slots:
    virtual int exec() override;
    virtual void open() override;

  protected:
    virtual void done(int result) override;

  private:
    Business::Gender _gender;
    PersonView* _personView;
};

#endif // PERSONBUILDERWIZARD_H
