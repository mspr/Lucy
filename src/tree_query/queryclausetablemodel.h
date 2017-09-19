#ifndef QUERYCLAUSETABLEMODEL_H
#define QUERYCLAUSETABLEMODEL_H

#include <QAbstractTableModel>

class QueryClause;

class QueryClauseTableModel : public QAbstractTableModel
{
  public:
    QueryClauseTableModel(QObject* parent = nullptr);

    void createNewClause();

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

  private:
    QList<QueryClause*> _clauses;
};

#endif // QUERYCLAUSETABLEMODEL_H
