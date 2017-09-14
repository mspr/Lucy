#include "clausetablemodel.h"

ClauseTableModel::ClauseTableModel(QObject* parent)
  : QAbstractTableModel(parent)
{

}

int ClauseTableModel::rowCount(const QModelIndex& parent) const
{
  return 1;
}

int ClauseTableModel::columnCount(const QModelIndex& parent) const
{
  return 1;
}

QVariant ClauseTableModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}
