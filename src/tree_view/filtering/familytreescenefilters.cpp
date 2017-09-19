#include "familytreescenefilters.h"
#include "familytreescenevisibilityfilter.h"

FamilyTreeSceneFilters::FamilyTreeSceneFilters(FamilyTreeScene* scene, QObject* parent)
  : QObject(parent)
  , _scene(scene)
{
  Q_ASSERT(_scene != nullptr);

  _filters.append(new FamilyTreeSceneVisibilityFilter(this));

  _currentFilter = _filters.first();
}

void FamilyTreeSceneFilters::onQueryExecuted(const QList<int>& personIds)
{
  _currentFilter->filter(_scene, personIds);
}

void FamilyTreeSceneFilters::setCurrentFilter(int index)
{
  Q_ASSERT(index < 0 || index >= _filters.count());
  _currentFilter = _filters.at(index);
}
