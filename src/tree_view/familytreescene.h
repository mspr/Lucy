#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include <QGraphicsScene>
#include <QList>

namespace Business { class Person; }
namespace Business { class Tree; }

class QGraphicsSceneMouseEvent;
class FamilyTreeNodeView;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, Business::Tree* tree, QObject* parent = nullptr);

    FamilyTreeNodeView* createReferenceNode(Business::Person* person, const QPointF& scenePos);
    FamilyTreeNodeView* createNode(Business::Person* person, const QPointF& scenePos);
    FamilyTreeNodeView* extendTreeFromNode(FamilyTreeNodeView* node, Business::Person* person);

    QList<FamilyTreeNodeView*> nodes() const;

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;

  private:
    void extendTreeFromNodeRecursively(FamilyTreeNodeView* node);

    FamilyTreeNodeView* nodeAtPos(const QPointF& scenePos) const;

    void adjustNodes();
    void adjustNodesRecursively(FamilyTreeNodeView* node);
    int countOldGenerations() const;
    FamilyTreeNodeView* getView(Business::Person* person) const;

  private:
    QHash<QGraphicsItem*, int> _levelByTreeNode;
    QHash<QGraphicsItem*, double> _inclinationByTreeNode;
    QList<FamilyTreeNodeView*> _nodes;
    FamilyTreeNodeView* _referenceNode;
};

#endif // FAMILYTREESCENE_H
