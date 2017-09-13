#include "querylistmodel.h"

QueryListModel::QueryListModel(QObject* parent)
  : QAbstractListModel(parent)
{
}

int QueryListModel::columnCount(const QModelIndex& parent) const
{
  return 1;
}

int QueryListModel::rowCount(const QModelIndex& parent) const
{
  return 1;
}

QVariant QueryListModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}
