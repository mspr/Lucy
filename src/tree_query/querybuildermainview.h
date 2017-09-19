#ifndef QUERYBUILDERMAINVIEW_H
#define QUERYBUILDERMAINVIEW_H

#include <QDockWidget>

namespace Ui { class QueryBuilderMainView; }

class QueryBuilderMainModel;

class QueryBuilderMainView : public QDockWidget
{
  Q_OBJECT

  public:
    explicit QueryBuilderMainView(QWidget* parent = nullptr);
    ~QueryBuilderMainView();

  private slots:
    void createNewClause();
    void onExecuteQuery();

  private:
    Ui::QueryBuilderMainView* _ui;
    QueryBuilderMainModel* _model;
};

#endif // QUERYBUILDERMAINVIEW_H
