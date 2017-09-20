#include "familytreescene.h"
#include "familytreenodeview.h"
#include "familytreenodebuilder.h"
#include "business/person.h"
#include "business/gender.h"
#include "business/tree.h"
#include "project/projectmanager.h"
#include "project/project.h"
#include "math.h"
#include "application.h"
#include "personupdaterview.h"
#include "personbuilderwizard.h"
#include "personviewcreationmarker.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

using namespace Business;

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, Tree* tree, QObject* parent)
  : QGraphicsScene(sceneRect, parent)
{
  Q_ASSERT(tree != nullptr);

  FamilyTreeNodeView* referenceNode = createReferenceNode(tree->reference(), QPointF(0, 0));
  _referenceNode = referenceNode;

  extendTreeFromNodeRecursively(referenceNode);

  adjustNodes();
}

void FamilyTreeScene::extendTreeFromNodeRecursively(FamilyTreeNodeView* node)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  Person* father = person->father();
  if (father != nullptr)
  {
    FamilyTreeNodeView* fatherNode = extendTreeFromNode(node, father);
    Q_ASSERT(fatherNode != nullptr);
    extendTreeFromNodeRecursively(fatherNode);
  }

  Person* mother = person->mother();
  if (mother != nullptr)
  {
    FamilyTreeNodeView* motherNode = extendTreeFromNode(node, mother);
    Q_ASSERT(motherNode != nullptr);
    extendTreeFromNodeRecursively(motherNode);
  }
}

FamilyTreeNodeView* FamilyTreeScene::extendTreeFromNode(FamilyTreeNodeView* node, Person* person)
{
  Q_ASSERT(node != nullptr);
  Q_ASSERT(person != nullptr);
  Q_ASSERT(_levelByTreeNode.contains(node));

  const QPointF previousNodeRectCenter = node->boundingRect().center();
  const QPointF previousNodeCenterScenePos = node->scenePos() + previousNodeRectCenter;

  double xOffset = (node == _referenceNode ? 500 : 100);
  if (person->gender() == Gender::Masculine)
    xOffset *= -1;

  const double x = previousNodeCenterScenePos.x() + xOffset;
  const double y = previousNodeCenterScenePos.y() - 100;
  const QPointF scenePos = QPointF(x, y);

  FamilyTreeNodeView* newNode = createNode(person, scenePos);
  Q_ASSERT(newNode != nullptr);

  const int previousNodeLevel = _levelByTreeNode.value(node);
  const int newTreeLevel = previousNodeLevel + 1;
  Q_ASSERT(newTreeLevel > 0);

  _levelByTreeNode.insert(newNode, newTreeLevel);

  return newNode;
}

void FamilyTreeScene::adjustNodes()
{
  _referenceNode->setPos(QPointF(0, 0));

  adjustNodesRecursively(_referenceNode);
}

void FamilyTreeScene::adjustNodesRecursively(FamilyTreeNodeView* node)
{
  Q_ASSERT(node != nullptr);

  const QPointF nodeCenterScenePos = node->scenePos();
  int xOffset = 200;
  const int yOffset = 100;

  if (node == _referenceNode)
  {
    const int oldGenerationsCount = countOldGenerations();
    xOffset = oldGenerationsCount * 200;
  }

  Person* mother = node->person()->mother();
  if (mother != nullptr)
  {
    FamilyTreeNodeView* motherView = getView(mother);
    motherView->setSceneCenterPos(nodeCenterScenePos + QPointF(xOffset, yOffset));
    adjustNodesRecursively(motherView);
  }

  Person* father = node->person()->father();
  if (father != nullptr)
  {
    FamilyTreeNodeView* fatherView = getView(father);
    fatherView->setSceneCenterPos(nodeCenterScenePos + QPointF(-xOffset, yOffset));
    adjustNodesRecursively(fatherView);
  }
}

QList<FamilyTreeNodeView*> FamilyTreeScene::nodes() const
{
  return _nodes;
}

FamilyTreeNodeView* FamilyTreeScene::getView(Person* person) const
{
  Q_ASSERT(person != nullptr);

  for (int i=0; i<_nodes.count(); ++i)
  {
    FamilyTreeNodeView* view = _nodes.at(i);
    if (view->person() == person)
      return view;
  }

  Q_ASSERT(false);

  return nullptr;
}

int FamilyTreeScene::countOldGenerations() const
{
  int generationsCount = 1;

  int remainingNodes = _nodes.count();
  while ((remainingNodes /= 2) > 1)
    ++generationsCount;

  return generationsCount;
}

FamilyTreeNodeView* FamilyTreeScene::createReferenceNode(Person* person, const QPointF& scenePos)
{
  FamilyTreeNodeView* node = createNode(person, scenePos);
  Q_ASSERT(node != nullptr);

  _levelByTreeNode.insert(node, 0);
  _inclinationByTreeNode.insert(node, 0);

  return node;
}

FamilyTreeNodeView* FamilyTreeScene::createNode(Person* person, const QPointF& scenePos)
{
  FamilyTreeNodeView* node = new FamilyTreeNodeView(scenePos, person);
  addItem(node);
  _nodes.append(node);

  const QRectF boundingRect = node->boundingRect();
  const QPointF sceneCenterPos = node->sceneCenterPos();

  PersonViewCreationMarker* fatherViewCreationMarker = new PersonViewCreationMarker(QPixmap(":/images/fatherGender.png"), node);
  fatherViewCreationMarker->setPos(sceneCenterPos - QPointF(boundingRect.width()/2, boundingRect.height()/2));
  addItem(fatherViewCreationMarker);

  PersonViewCreationMarker* motherViewCreationMarker = new PersonViewCreationMarker(QPixmap(":/images/motherGender.png"), node);
  motherViewCreationMarker->setPos(sceneCenterPos + QPointF(-boundingRect.width()/2, boundingRect.height()/2));
  addItem(motherViewCreationMarker);

  return node;
}

void FamilyTreeScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  if (e->button() == Qt::MiddleButton)
  {
    qDebug() << e->scenePos();
    return;
  }

  QGraphicsScene::mousePressEvent(e);
}

void FamilyTreeScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* e)
{
  FamilyTreeNodeView* node = nodeAtPos(e->scenePos());
  if (node != nullptr)
  {
    PersonUpdaterView personUpdaterView(node->person());
    personUpdaterView.exec();
  }

  QGraphicsScene::mouseDoubleClickEvent(e);
}

FamilyTreeNodeView* FamilyTreeScene::nodeAtPos(const QPointF& scenePos) const
{
  FamilyTreeNodeView* node = nullptr;

  QGraphicsItem* itemAtPos = itemAt(scenePos, QTransform());
  if (itemAtPos != nullptr)
    node = dynamic_cast<FamilyTreeNodeView*>(itemAtPos->parentItem());

  return node;
}
