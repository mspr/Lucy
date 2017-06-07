#include "familytreescene.h"
#include "familytreenodeview.h"
#include "domain_object/person.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, QObject* parent)
  : QGraphicsScene(sceneRect, parent)
{
}

void FamilyTreeScene::ExtendTreeFromNode(QGraphicsItem* previousNode, Qt::MouseButton button)
{
  Q_ASSERT(previousNode != nullptr);
  Q_ASSERT(_levelByTreeNode.contains(previousNode));
  Q_ASSERT(_inclinationByTreeNode.contains(previousNode));

  const int radius = 200;

  const int previousNodeLevel = _levelByTreeNode.value(previousNode);
  const int newTreeLevel = previousNodeLevel + 1;
  Q_ASSERT(newTreeLevel > 0);

  double angle = _inclinationByTreeNode.value(previousNode);

  const QPointF previousNodeScenePos = previousNode->boundingRect().center();

  double inclination = 5*M_PI/12 * 1.0/newTreeLevel;
  if (button == Qt::LeftButton)
    inclination *= -1;
  else if (button == Qt::RightButton)
    inclination *= 1;

  angle += inclination;

  qDebug() << "create node from pos " << previousNodeScenePos << " with inclination " << angle;

  double x = previousNodeScenePos.x() + radius*sin(angle);
  double y = previousNodeScenePos.y() - radius*cos(angle);

  FamilyTreeNodeView* newTreeNode = new FamilyTreeNodeView(QPointF(x, y), 10);
  addItem(newTreeNode);

  _levelByTreeNode.insert(newTreeNode, newTreeLevel);
  _inclinationByTreeNode.insert(newTreeNode, angle);
}

void FamilyTreeScene::createNodeView(Person* person, const QPointF& scenePos)
{
  Q_ASSERT(person != nullptr);

  QGraphicsItemGroup* personViewItem = new QGraphicsItemGroup();
  personViewItem->setPos(scenePos);
  addItem(personViewItem);

  QGraphicsSimpleTextItem* personFirstNameViewItem = new QGraphicsSimpleTextItem(person->firstName(), personViewItem);
  personViewItem->addToGroup(personFirstNameViewItem);
  QGraphicsSimpleTextItem* personLastNameViewItem = new QGraphicsSimpleTextItem(person->lastName(), personViewItem);
  personViewItem->addToGroup(personLastNameViewItem);
  QGraphicsSimpleTextItem* personBirthDateViewItem = new QGraphicsSimpleTextItem(person->birthDate().toString(), personViewItem);
  personViewItem->addToGroup(personBirthDateViewItem);
}

void FamilyTreeScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  qDebug() << "FamilyTreeScene::mousePressEvent " << e->scenePos();

  static double degrees = 3*M_PI/8.0;
  degrees *= 0.9;

  QGraphicsItem* itemAtPos = itemAt(e->scenePos(), QTransform());
  if (itemAtPos != nullptr)
  {
    ExtendTreeFromNode(itemAtPos, e->button());
  }
  else if (e->button() == Qt::RightButton)
  {

//    FamilyTreeNodeView* treeNode = new FamilyTreeNodeView(e->scenePos(), 50);
//    qDebug() << "tree node view scene pos " << treeNode->scenePos();
//    qDebug() << "tree node view pos " << treeNode->pos();
//    qDebug() << "tree node view rect " << treeNode->boundingRect();
//    addItem(treeNode);

//    _levelByTreeNode.insert(treeNode, 0);
//    _inclinationByTreeNode.insert(treeNode, 0.0);

//    QGraphicsTextItem* graphicsTextItem = new QGraphicsTextItem("Coucou c'est moi", treeNode);
//    qDebug() << "tree text view scene pos " << graphicsTextItem->scenePos();
//    qDebug() << "tree text view pos " << graphicsTextItem->pos();
    //graphicsTextItem->setPos(QPointF(5.0, 5.0));
    //addItem(graphicsTextItem);
  }
}
