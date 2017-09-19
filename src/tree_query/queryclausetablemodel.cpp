#include "queryclausetablemodel.h"
#include "queryclause.h"
#include "queryfield.h"
#include "queryoperator.h"

QueryClauseTableModel::QueryClauseTableModel(QObject* parent)
  : QAbstractTableModel(parent)
{
}

void QueryClauseTableModel::createNewClause()
{
  beginInsertRows(QModelIndex(), _clauses.count(), _clauses.count());
  QueryClause* clause = new QueryClause(this);
  _clauses.append(clause);
  endInsertRows();
}

int QueryClauseTableModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _clauses.count();
}

int QueryClauseTableModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 3;
}

QVariant QueryClauseTableModel::data(const QModelIndex& index, int role) const
{
  switch(index.column())
  {
    case 0:
      switch (role)
      {
        case Qt::DisplayRole:
          return _clauses.at(index.row())->field()->name();
        break;
        case Qt::EditRole:
          return _clauses.at(index.row())->field()->name();
        break;
      }
    break;
    case 1:
      return _clauses.at(index.row())->queryOperator()->text();
    break;
    case 2:
      return _clauses.at(index.row())->value();
    break;
  }

  return QVariant();
}
