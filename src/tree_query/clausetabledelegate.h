#ifndef CLAUSETABLEDELEGATE_H
#define CLAUSETABLEDELEGATE_H

#include <QStyledItemDelegate>

class ClauseTableDelegate : public QStyledItemDelegate
{
  public:
    ClauseTableDelegate(QObject* parent = nullptr);

    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // CLAUSETABLEDELEGATE_H
