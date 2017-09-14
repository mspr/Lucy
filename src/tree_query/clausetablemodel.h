#ifndef CLAUSETABLEMODEL_H
#define CLAUSETABLEMODEL_H

#include <QAbstractTableModel>
#include "queryclause.h"

class ClauseTableModel : public QAbstractTableModel
{
  public:
    ClauseTableModel(QObject* parent = nullptr);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

  private:
    QList<QueryClause> _clauses;
};

#endif // CLAUSETABLEMODEL_H
