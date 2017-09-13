#include "querybuildermainview.h"
#include "ui_querybuildermainview.h"
#include "querylistmodel.h"

QueryBuilderMainView::QueryBuilderMainView(QWidget* parent)
  : QDockWidget(parent)
  , _ui(new Ui::QueryBuilderMainView)
{
  _ui->setupUi(this);

  QueryListModel* queryListModel = new QueryListModel(this);
  _ui->queryListView->setModel(queryListModel);
}

QueryBuilderMainView::~QueryBuilderMainView()
{
  delete _ui;
}
