#ifndef QUERYLISTMODEL_H
#define QUERYLISTMODEL_H

#include <QAbstractListModel>

class Query;

class QueryListModel : public QAbstractListModel
{
  Q_OBJECT

  public:
    QueryListModel(QObject* parent = nullptr);

    void createNewQuery(const QString& queryName);

    virtual int columnCount(const QModelIndex& parent) const override;
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

  signals:
    void queryExecuted(const QList<int>& personIds);

  public slots:
    void setCurrentTree(int treeId);
    void executeSelectedQuery(const QModelIndex& index);

  private:
    int _currentTreeId;
    QList<Query*> _queries;
};

#endif // QUERYLISTMODEL_H
