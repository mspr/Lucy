#include "querylistdelegate.h"
#include <QLineEdit>

QueryListDelegate::QueryListDelegate(QObject* parent)
  : QStyledItemDelegate(parent)
{
}

QWidget* QueryListDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  if (index.column() != 1)
    return QStyledItemDelegate::createEditor(parent, option, index);

  return new QLineEdit(parent);
}

void QueryListDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  QLineEdit* queryNameLineEdit = qobject_cast<QLineEdit*>(editor);
  if (queryNameLineEdit != nullptr)
  {
    const QString currentText = index.data(Qt::EditRole).toString();
    queryNameLineEdit->setText(currentText);
  }
  else
  {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void QueryListDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QLineEdit* queryNameLineEdit = qobject_cast<QLineEdit*>(editor);
  if (queryNameLineEdit != nullptr)
    model->setData(index, queryNameLineEdit->text(), Qt::EditRole);
  else
    QStyledItemDelegate::setModelData(editor, model, index);
}
