#include "treecreationdialog.h"
#include "ui_treecreationdialog.h"

TreeCreationDialog::TreeCreationDialog(QWidget* parent)
  : QDialog(parent),
    _ui(new Ui::TreeCreationDialog)
{
  _ui->setupUi(this);
}

TreeCreationDialog::~TreeCreationDialog()
{
  delete _ui;
}
