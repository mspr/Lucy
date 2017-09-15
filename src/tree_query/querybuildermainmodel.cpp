#include "querybuildermainmodel.h"
#include "querylistmodel.h"
#include "clausetablemodel.h"
#include "queryfields.h"

QueryBuilderMainModel::QueryBuilderMainModel(QObject* parent)
  : QObject(parent)
  , _queryFields(new QueryFields(this))
{
  _queryListModel = new QueryListModel(this);
  connect(_queryListModel, QueryListModel::queryExecuted, this, QueryBuilderMainModel::queryExecuted);

  _clauseTableModel = new ClauseTableModel(this);
}

QueryFields* QueryBuilderMainModel::queryFields() const
{
  return _queryFields;
}

QueryListModel* QueryBuilderMainModel::queryListModel() const
{
  return _queryListModel;
}

ClauseTableModel* QueryBuilderMainModel::clauseTableModel() const
{
  return _clauseTableModel;
}
