#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include "domain_object/tree.h"
#include <QGraphicsScene>
#include <QList>

class QGraphicsSceneMouseEvent;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, QObject* parent = nullptr);

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;

  private:
    void ExtendTreeFromNode(QGraphicsItem* previousNode, Qt::MouseButton button);

  private:
    QHash<QGraphicsItem*, int> _levelByTreeNode;
    QHash<QGraphicsItem*, double> _inclinationByTreeNode;
};

#endif // FAMILYTREESCENE_H
