#ifndef FAMILYTREESCENEFILTERS_H
#define FAMILYTREESCENEFILTERS_H

#include <QObject>

class FamilyTreeScene;
class FamilyTreeSceneAbstractFilter;

class FamilyTreeSceneFilters : public QObject
{
  Q_OBJECT

  public:
    FamilyTreeSceneFilters(FamilyTreeScene* scene, QObject* parent = nullptr);

  public slots:
    void onQueryExecuted(const QList<int>& personIds);
    void setCurrentFilter(int index);

  private:
    FamilyTreeScene* _scene;
    QList<FamilyTreeSceneAbstractFilter*> _filters;
    FamilyTreeSceneAbstractFilter* _currentFilter;
};

#endif // FAMILYTREESCENEFILTERS_H
