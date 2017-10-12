#ifndef PERSONBIRTHWIZARDPAGE_H
#define PERSONBIRTHWIZARDPAGE_H

#include <QWizardPage>

namespace Ui { class PersonBirthWizardPage; }

class PersonBirthWizardPage : public QWizardPage
{
  Q_OBJECT

  public:
    explicit PersonBirthWizardPage(QWidget* parent);
    ~PersonBirthWizardPage();

  private:
    Ui::PersonBirthWizardPage* _ui;
};

#endif // PERSONBIRTHWIZARDPAGE_H
