#include "querylistmodel.h"
#include "query.h"

QueryListModel::QueryListModel(QObject* parent)
  : QAbstractListModel(parent)
  , _currentTreeId(-1)
{
}

void QueryListModel::setCurrentTree(int treeId)
{
  Q_ASSERT(treeId != -1);
  _currentTreeId = treeId;
}

void QueryListModel::executeSelectedQuery(const QModelIndex& index)
{
  Q_ASSERT(index.isValid());
  Query* query = _queries.at(index.row());
  const QList<int> personIds = query->execute();
  if (personIds.count() > 0)
    emit queryExecuted(personIds);
}

void QueryListModel::createNewQuery(const QString& queryName)
{
  beginInsertRows(QModelIndex(), _queries.count(), _queries.count());
  Query* query = new Query(queryName, this);
  _queries.append(query);
  endInsertRows();
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
