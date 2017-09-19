#ifndef QUERYLISTDELEGATE_H
#define QUERYLISTDELEGATE_H

#include <QStyledItemDelegate>

class QueryListDelegate : public QStyledItemDelegate
{
  public:
    QueryListDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // QUERYLISTDELEGATE_H
