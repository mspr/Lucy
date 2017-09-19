#ifndef FAMILYTREESCENEVISIBILITYFILTER_H
#define FAMILYTREESCENEVISIBILITYFILTER_H

#include "familytreesceneabstractfilter.h"

class FamilyTreeSceneVisibilityFilter : public FamilyTreeSceneAbstractFilter
{
  public:
    FamilyTreeSceneVisibilityFilter(QObject* parent = nullptr);

  protected:
    virtual void filter_impl(FamilyTreeScene* scene, const QList<int>& personIds) override;
};

#endif // FAMILYTREESCENEVISIBILITYFILTER_H
