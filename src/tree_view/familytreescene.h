#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include "domain_object/tree.h"
#include <QGraphicsScene>
#include <QList>

class QGraphicsSceneMouseEvent;
class FamilyTreeNodeView;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, Tree* tree, QObject* parent = nullptr);

    FamilyTreeNodeView* createReferenceNode(Person* person, const QPointF& scenePos);
    FamilyTreeNodeView* createNode(Person* person, const QPointF& scenePos);

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;

  private:
    void extendTreeFromNodeRecursively(FamilyTreeNodeView* node);
    FamilyTreeNodeView* extendTreeFromNode(FamilyTreeNodeView* node, Person* person, Qt::MouseButton button);

    FamilyTreeNodeView* nodeAtPos(const QPointF& scenePos) const;

  private:
    QHash<QGraphicsItem*, int> _levelByTreeNode;
    QHash<QGraphicsItem*, double> _inclinationByTreeNode;
};

#endif // FAMILYTREESCENE_H
