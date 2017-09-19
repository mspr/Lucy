#include "querybuildermainview.h"
#include "ui_querybuildermainview.h"
#include "querybuildermainmodel.h"
#include "querylistmodel.h"
#include "querylistdelegate.h"
#include "queryclausetablemodel.h"
#include "queryclausetabledelegate.h"

QueryBuilderMainView::QueryBuilderMainView(QWidget* parent)
  : QDockWidget(parent)
  , _ui(new Ui::QueryBuilderMainView)
  , _model(new QueryBuilderMainModel(this))
{
  _ui->setupUi(this);

  QueryListDelegate* queryListDelegate = new QueryListDelegate(this);
  _ui->queryListView->setModel(_model->queryListModel());
  _ui->queryListView->setItemDelegate(queryListDelegate);

  QueryClauseTableDelegate* clauseTableDelegate = new QueryClauseTableDelegate(_model->queryFields(), this);
  _ui->clauseTableView->setModel(_model->clauseTableModel());
  _ui->clauseTableView->setItemDelegate(clauseTableDelegate);
}

QueryBuilderMainView::~QueryBuilderMainView()
{
  delete _ui;
}

void QueryBuilderMainView::createNewQuery()
{
  _model->queryListModel()->createNewQuery();
}

void QueryBuilderMainView::createNewClause()
{
  _model->clauseTableModel()->createNewClause();
}

void QueryBuilderMainView::onExecuteQuery()
{

}
