#ifndef TREECREATIONDIALOG_H
#define TREECREATIONDIALOG_H

#include <QDialog>

namespace Ui { class TreeCreationDialog; }

class TreeCreationDialog : public QDialog
{
  Q_OBJECT

  public:
    explicit TreeCreationDialog(QWidget* parent = nullptr);
    ~TreeCreationDialog();

  private:
    Ui::TreeCreationDialog* _ui;
};

#endif // TREECREATIONDIALOG_H
