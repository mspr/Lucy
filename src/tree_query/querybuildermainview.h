#ifndef QUERYBUILDERMAINVIEW_H
#define QUERYBUILDERMAINVIEW_H

#include <QDockWidget>

namespace Ui { class QueryBuilderMainView; }

class QueryBuilderMainView : public QDockWidget
{
  Q_OBJECT

  public:
    explicit QueryBuilderMainView(QWidget* parent = nullptr);
    ~QueryBuilderMainView();

  private:
    Ui::QueryBuilderMainView* _ui;
};

#endif // QUERYBUILDERMAINVIEW_H
