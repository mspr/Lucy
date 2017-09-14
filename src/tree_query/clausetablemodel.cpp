#include "clausetablemodel.h"
#include "queryclause.h"
#include "queryfield.h"
#include "queryoperator.h"

ClauseTableModel::ClauseTableModel(QObject* parent)
  : QAbstractTableModel(parent)
{
}

int ClauseTableModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _clauses.count();
}

int ClauseTableModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 3;
}

QVariant ClauseTableModel::data(const QModelIndex& index, int role) const
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
