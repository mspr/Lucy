#include "queryclausetabledelegate.h"
#include "queryfields.h"
#include <QComboBox>

QueryClauseTableDelegate::QueryClauseTableDelegate(QueryFields* fields, QObject* parent)
  : QStyledItemDelegate(parent)
  , _fields(fields)
{
  Q_ASSERT(_fields != nullptr);
}

void QueryClauseTableDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QStyledItemDelegate::paint(painter, option, index);
}

QSize QueryClauseTableDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* QueryClauseTableDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  if (index.column() != 1)
    return QStyledItemDelegate::createEditor(parent, option, index);

  QComboBox* fieldComboBox = new QComboBox(parent);
  fieldComboBox->addItems(_fields->fieldNames());
//  connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));

  return fieldComboBox;
}

void QueryClauseTableDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
  QComboBox* fieldComboBox = qobject_cast<QComboBox*>(editor);
  if (fieldComboBox != nullptr)
  {
     const QString currentText = index.data(Qt::EditRole).toString();
     const int row = fieldComboBox->findText(currentText);
     if (row >= 0)
         fieldComboBox->setCurrentIndex(row);
  }
  else
  {
      QStyledItemDelegate::setEditorData(editor, index);
  }
}

void QueryClauseTableDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QComboBox* fieldComboBox = qobject_cast<QComboBox*>(editor);
  if (fieldComboBox != nullptr)
      model->setData(index, fieldComboBox->currentText(), Qt::EditRole);
  else
      QStyledItemDelegate::setModelData(editor, model, index);
}
