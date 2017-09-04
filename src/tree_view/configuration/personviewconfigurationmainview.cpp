#include "personviewconfigurationmainview.h"
#include "ui_personviewconfigurationmainview.h"

PersonViewConfigurationMainView::PersonViewConfigurationMainView(QWidget* parent)
  : QDialog(parent)
  , _ui(new Ui::PersonViewConfigurationMainView)
{
  _ui->setupUi(this);
}

PersonViewConfigurationMainView::~PersonViewConfigurationMainView()
{
  delete _ui;
}
