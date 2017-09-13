#ifndef QUERYLISTMODEL_H
#define QUERYLISTMODEL_H

#include <QAbstractListModel>

class QueryListModel : public QAbstractListModel
{
  public:
    QueryListModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent) const override;
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;
};

#endif // QUERYLISTMODEL_H
