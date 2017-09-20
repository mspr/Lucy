#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include <QGraphicsScene>
#include <QList>

namespace Business { class Person; }
namespace Business { class Tree; }

class QGraphicsSceneMouseEvent;
class PersonView;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, Business::Tree* tree, QObject* parent = nullptr);

    PersonView* createReferenceNode(Business::Person* person, const QPointF& scenePos);
    PersonView* createNode(Business::Person* person, const QPointF& scenePos);
    PersonView* extendTreeFromNode(PersonView* node, Business::Person* person);

    QList<PersonView*> nodes() const;

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;

  private:
    void extendTreeFromNodeRecursively(PersonView* node);

    PersonView* nodeAtPos(const QPointF& scenePos) const;

    void adjustNodes();
    void adjustNodesRecursively(PersonView* node);
    int countOldGenerations() const;
    PersonView* getView(Business::Person* person) const;

  private:
    QHash<QGraphicsItem*, int> _levelByTreeNode;
    QList<PersonView*> _nodes;
    PersonView* _referenceNode;
};

#endif // FAMILYTREESCENE_H
