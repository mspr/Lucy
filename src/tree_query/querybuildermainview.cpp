#include "querybuildermainview.h"
#include "ui_querybuildermainview.h"
#include "querylistmodel.h"
#include "clausetablemodel.h"

QueryBuilderMainView::QueryBuilderMainView(QWidget* parent)
  : QDockWidget(parent)
  , _ui(new Ui::QueryBuilderMainView)
{
  _ui->setupUi(this);

  QueryListModel* queryListModel = new QueryListModel(this);
  _ui->queryListView->setModel(queryListModel);

  ClauseTableModel* clauseTableModel = new ClauseTableModel(this);
  _ui->clauseTableView->setModel(clauseTableModel);
}

QueryBuilderMainView::~QueryBuilderMainView()
{
  delete _ui;
}
