#include "familytreescene.h"
#include "familytreenodeview.h"
#include "familytreenodebuilder.h"
#include "domain_object/person.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "domain_object/person.h"
#include "math.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, QObject* parent)
  : QGraphicsScene(sceneRect, parent)
{
}

void FamilyTreeScene::extendTreeFromNode(FamilyTreeNodeView* previousNode, Qt::MouseButton button)
{
  Q_ASSERT(previousNode != nullptr);
  Q_ASSERT(_levelByTreeNode.contains(previousNode));
  Q_ASSERT(_inclinationByTreeNode.contains(previousNode));

  const int radius = 200;

  const int previousNodeLevel = _levelByTreeNode.value(previousNode);
  const int newTreeLevel = previousNodeLevel + 1;
  Q_ASSERT(newTreeLevel > 0);

  const QPointF previousNodeRectCenter = previousNode->boundingRect().center();
  const QPointF previousNodeCenterScenePos = previousNode->scenePos() + previousNodeRectCenter;

  double inclination = 5*M_PI/12 * 1.0/newTreeLevel;

  double angle = _inclinationByTreeNode.value(previousNode);

  if (button == Qt::LeftButton)
    inclination *= -1;
  else if (button == Qt::RightButton)
    inclination *= 1;

  angle += inclination;

  const double x = previousNodeCenterScenePos.x() + radius*sin(angle);
  const double y = previousNodeCenterScenePos.y() - radius*cos(angle);
  const QPointF scenePos = QPointF(x, y);

  qDebug() << previousNodeCenterScenePos << " >> " << scenePos;

  FamilyTreeNodeBuilder familyTreeNodeBuilder;
  if (familyTreeNodeBuilder.exec())
  {
    Person* person = familyTreeNodeBuilder.person();
    FamilyTreeNodeView* node = createNode(person, scenePos);
    Q_ASSERT(node != nullptr);

    if (button == Qt::LeftButton)
      previousNode->person()->setFather(person);
    else if (button == Qt::RightButton)
      previousNode->person()->setMother(person);

    ProjectManager::getInstance()->currentProject()->add(person);

    _levelByTreeNode.insert(node, newTreeLevel);
    _inclinationByTreeNode.insert(node, angle);
  }
}

void FamilyTreeScene::createReferenceNode(Person* person, const QPointF& scenePos)
{
  QGraphicsItem* node = createNode(person, scenePos);
  Q_ASSERT(node != nullptr);

  _levelByTreeNode.insert(node, 0);
  _inclinationByTreeNode.insert(node, 0);
}

FamilyTreeNodeView* FamilyTreeScene::createNode(Person* person, const QPointF& scenePos)
{
  FamilyTreeNodeView* node = new FamilyTreeNodeView(scenePos, person);
  addItem(node);

  return node;
}

void FamilyTreeScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  if (e->button() == Qt::MiddleButton)
  {
    qDebug() << "FamilyTreeScene::mousePressEvent " << e->scenePos();
    return;
  }

  QGraphicsItem* itemAtPos = itemAt(e->scenePos(), QTransform());
  if (itemAtPos != nullptr)
  {
    // TODO Change press event filter to catch it from group item directly
    FamilyTreeNodeView* node = dynamic_cast<FamilyTreeNodeView*>(itemAtPos->parentItem());
    if (node != nullptr)
    {
      Q_ASSERT(_levelByTreeNode.contains(node));

//      double degrees = 3*M_PI/8.0;
//      degrees *= pow(0.9, _levelByTreeNode.value(node));

      extendTreeFromNode(node, e->button());
    }
  }
  else if (e->button() == Qt::RightButton)
  {
  }
}
