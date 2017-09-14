#include "clausetablemodel.h"
#include "queryclause.h"
#include "queryfield.h"

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
  switch (role)
  {
    case Qt::DisplayRole:
    break;
    case Qt::EditRole:
      return _clauses.at(index.row())->field()->name();
    break;
  }

  return QVariant();
}
