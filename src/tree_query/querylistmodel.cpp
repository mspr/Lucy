#include "querylistmodel.h"
#include "query.h"

QueryListModel::QueryListModel(QObject* parent)
  : QAbstractListModel(parent)
{
}

int QueryListModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 1;
}

int QueryListModel::rowCount(const QModelIndex& /*parent*/) const
{
  return _queries.count();
}

QVariant QueryListModel::data(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole)
    return _queries.at(index.row())->name();

  return QVariant();
}
