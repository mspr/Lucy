#include "ipersonview.h"
#include <QtGlobal>

IPersonView::IPersonView()
  : _model(nullptr)
{
}

void IPersonView::setModel(IPersonViewModel* model)
{
  Q_ASSERT(model != nullptr);
  _model = model;
}

IPersonViewModel* IPersonView::model() const
{
  return _model;
}
