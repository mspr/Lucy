#include "familytreescenevisibilityfilter.h"
#include "tree_view/familytreescene.h"
#include "tree_view/familytreenodeview.h"
#include "business/person.h"

using namespace Business;

FamilyTreeSceneVisibilityFilter::FamilyTreeSceneVisibilityFilter(QObject* parent)
  : FamilyTreeSceneAbstractFilter("Show only involved persons", parent)
{
}

void FamilyTreeSceneVisibilityFilter::filter_impl(FamilyTreeScene* scene, const QList<int>& personIds)
{
  const QList<FamilyTreeNodeView*> nodes = scene->nodes();
  for (int i=0; i<nodes.count(); ++i)
  {
    FamilyTreeNodeView* node = nodes.at(i);
    Person* person = node->person();
    Q_ASSERT(person != nullptr);

    if (!personIds.contains(person->id()))
      node->hide();
  }
}
