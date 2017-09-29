#ifndef TREEBUILDERVIEW_H
#define TREEBUILDERVIEW_H

#include <QDialog>

namespace Ui { class TreeBuilderView; }

class TreeBuilderView : public QDialog
{
  Q_OBJECT

  public:
    explicit TreeBuilderView(QWidget* parent = nullptr);
    ~TreeBuilderView();

  public slots:
    virtual int exec() override;

  private:
    Ui::TreeBuilderView* _ui;
};

#endif // TREEBUILDERVIEW_H
