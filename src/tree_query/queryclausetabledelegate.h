#ifndef QUERYCLAUSETABLEDELEGATE_H
#define QUERYCLAUSETABLEDELEGATE_H

#include <QStyledItemDelegate>

class QueryFields;

class QueryClauseTableDelegate : public QStyledItemDelegate
{
  public:
    QueryClauseTableDelegate(QueryFields* fields, QObject* parent = nullptr);

    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

  private:
    QueryFields* _fields;
};

#endif // QUERYCLAUSETABLEDELEGATE_H
