#ifndef PERSONBUILDERWIZARD_H
#define PERSONBUILDERWIZARD_H

#include <QWizard>
#include "business/gender.h"

namespace Business { class Tree; }
namespace Business { class Person; }
class PersonView;

class PersonBuilderWizard : public QWizard
{
  Q_OBJECT

  public:
    explicit PersonBuilderWizard(Business::Tree* tree,
                                 Business::Gender gender = Business::Gender::Unidentified,
                                 Business::Person* child = nullptr,
                                 QWidget* parent = nullptr);
    ~PersonBuilderWizard();

  public slots:
    virtual int exec() override;
    virtual void open() override;

  protected:
    virtual void done(int result) override;

  private:
    Business::Tree* _tree;
    Business::Person* _child;
};

#endif // PERSONBUILDERWIZARD_H
