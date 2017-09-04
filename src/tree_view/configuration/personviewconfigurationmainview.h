#ifndef PERSONVIEWCONFIGURATIONMAINVIEW_H
#define PERSONVIEWCONFIGURATIONMAINVIEW_H

#include <QDialog>

namespace Ui { class PersonViewConfigurationMainView; }

class PersonViewConfigurationMainView : public QDialog
{
  Q_OBJECT

  public:
    explicit PersonViewConfigurationMainView(QWidget* parent = nullptr);
    ~PersonViewConfigurationMainView();

  private:
    Ui::PersonViewConfigurationMainView* _ui;
};

#endif // PERSONVIEWCONFIGURATIONMAINVIEW_H
