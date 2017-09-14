#include "clausetabledelegate.h"
#include "queryfields.h"
#include <QComboBox>

ClauseTableDelegate::ClauseTableDelegate(QueryFields* fields, QObject* parent)
  : QStyledItemDelegate(parent)
  , _fields(fields)
{
  Q_ASSERT(_fields != nullptr);
}

void ClauseTableDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

}

QSize ClauseTableDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  return QSize();
}

QWidget* ClauseTableDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  if (index.column() != 1)
    return QStyledItemDelegate::createEditor(parent, option, index);

  QComboBox* fieldComboBox = new QComboBox(parent);
  fieldComboBox->addItems(_fields->fieldNames());
//  connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));

  return fieldComboBox;
}

void ClauseTableDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
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

void ClauseTableDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  QComboBox* fieldComboBox = qobject_cast<QComboBox*>(editor);
  if (fieldComboBox != nullptr)
      model->setData(index, fieldComboBox->currentText(), Qt::EditRole);
  else
      QStyledItemDelegate::setModelData(editor, model, index);
}
