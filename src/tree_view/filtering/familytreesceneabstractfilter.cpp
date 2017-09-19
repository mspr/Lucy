#include "familytreesceneabstractfilter.h"

FamilyTreeSceneAbstractFilter::FamilyTreeSceneAbstractFilter(const QString& name, QObject* parent)
  : QObject(parent)
  , _name(name)
{
  Q_ASSERT(!_name.isEmpty());
}

void FamilyTreeSceneAbstractFilter::filter(FamilyTreeScene* scene, const QList<int>& personIds)
{
  Q_ASSERT(scene != nullptr);

  filter_impl(scene, personIds);
}
