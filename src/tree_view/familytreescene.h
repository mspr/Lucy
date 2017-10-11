#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include <QGraphicsScene>
#include <QList>

namespace Business { class Person; }
namespace Business { class Tree; }

class QGraphicsSceneMouseEvent;
class PersonView;
class FamilyTreeView;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, Business::Tree* tree, FamilyTreeView* view);

    PersonView* createReferenceNode(Business::Person* person, const QPointF& scenePos);
    PersonView* createNode(Business::Person* person, const QPointF& scenePos);
    PersonView* createNode(PersonView* node, Business::Person* person);

    PersonView* getView(Business::Person* person) const;
    QList<PersonView*> nodes() const;

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;

  private:
    void createNodeRecursively(PersonView* node);

    PersonView* nodeAtPos(const QPointF& scenePos) const;

    void adjustNodes();
    void adjustNodesRecursively(PersonView* node, int generationsCount);

  private slots:
    void onPersonAdded(Business::Person* person);
    void onPersonRemoved(Business::Person* person);

  private:
    Business::Tree* _tree;
    QHash<QGraphicsItem*, int> _levelByTreeNode;
    QList<PersonView*> _nodes;
    PersonView* _referenceNode;
};

#endif // FAMILYTREESCENE_H
