#ifndef FAMILYTREESCENEABSTRACTFILTER_H
#define FAMILYTREESCENEABSTRACTFILTER_H

#include <QObject>

class FamilyTreeScene;

class FamilyTreeSceneAbstractFilter : public QObject
{
  public:
    FamilyTreeSceneAbstractFilter(const QString& name, QObject* parent = nullptr);

    void filter(FamilyTreeScene* scene, const QList<int>& personIds);

  protected:
    virtual void filter_impl(FamilyTreeScene* scene, const QList<int>& personIds) = 0;

  protected:
    QString _name;
};

#endif // FAMILYTREESCENEABSTRACTFILTER_H
