#ifndef PERSONIDENTIFICATIONWIZARDPAGE_H
#define PERSONIDENTIFICATIONWIZARDPAGE_H

#include <QWizardPage>

namespace Ui { class PersonIdentificationWizardPage; }

class PersonIdentificationWizardPage : public QWizardPage
{
  Q_OBJECT

  public:
    explicit PersonIdentificationWizardPage(QWidget* parent);
    ~PersonIdentificationWizardPage();

  private:
    Ui::PersonIdentificationWizardPage* _ui;
};

#endif // PERSONIDENTIFICATIONWIZARDPAGE_H
