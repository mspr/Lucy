#ifndef PERSONIDENTIFICATIONWIZARDPAGE_H
#define PERSONIDENTIFICATIONWIZARDPAGE_H

#include <QWizardPage>

namespace Ui { class PersonIdentificationWizardPage; }
namespace Business { enum class Gender; }

class PersonIdentificationWizardPage : public QWizardPage
{
  Q_OBJECT

  public:
    explicit PersonIdentificationWizardPage(Business::Gender gender, QWidget* parent);
    ~PersonIdentificationWizardPage();

  private:
    Ui::PersonIdentificationWizardPage* _ui;
};

#endif // PERSONIDENTIFICATIONWIZARDPAGE_H
