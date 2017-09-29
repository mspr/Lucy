#include "familytreescene.h"
#include "personview.h"
#include "personviewbuilder.h"
#include "business/person.h"
#include "business/gender.h"
#include "business/tree.h"
#include "business/tree_p.h"
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

  PersonView* referenceNode = createReferenceNode(tree->reference(), QPointF(0, 0));
  _referenceNode = referenceNode;

  extendTreeFromNodeRecursively(referenceNode);

  adjustNodes();

  connect(tree->d(), Tree_p::personAdded, this, FamilyTreeScene::onPersonAdded);
  connect(tree->d(), Tree_p::personRemoved, this, FamilyTreeScene::onPersonRemoved);
}

void FamilyTreeScene::extendTreeFromNodeRecursively(PersonView* node)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  if (person->hasFather())
  {
    PersonView* fatherNode = extendTreeFromNode(node, person->father());
    Q_ASSERT(fatherNode != nullptr);
    extendTreeFromNodeRecursively(fatherNode);
  }

  if (person->hasMother())
  {
    PersonView* motherNode = extendTreeFromNode(node, person->mother());
    Q_ASSERT(motherNode != nullptr);
    extendTreeFromNodeRecursively(motherNode);
  }
}

PersonView* FamilyTreeScene::extendTreeFromNode(PersonView* node, Person* person)
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

  PersonView* newNode = createNode(person, scenePos);
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

void FamilyTreeScene::adjustNodesRecursively(PersonView* node)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  const QPointF nodeCenterScenePos = node->scenePos();
  int xOffset = 200;
  const int yOffset = 100;

  if (node == _referenceNode)
  {
    const int oldGenerationsCount = countOldGenerations();
    xOffset = oldGenerationsCount * 200;
  }

  if (person->hasMother())
  {
    PersonView* motherView = getView(person->mother());
    motherView->setSceneCenterPos(nodeCenterScenePos + QPointF(xOffset, yOffset));
    adjustNodesRecursively(motherView);
  }

  if (person->hasFather())
  {
    PersonView* fatherView = getView(person->father());
    fatherView->setSceneCenterPos(nodeCenterScenePos + QPointF(-xOffset, yOffset));
    adjustNodesRecursively(fatherView);
  }
}

QList<PersonView*> FamilyTreeScene::nodes() const
{
  return _nodes;
}

PersonView* FamilyTreeScene::getView(Person* person) const
{
  Q_ASSERT(person != nullptr);

  for (int i=0; i<_nodes.count(); ++i)
  {
    PersonView* view = _nodes.at(i);
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

PersonView* FamilyTreeScene::createReferenceNode(Person* person, const QPointF& scenePos)
{
  PersonView* node = createNode(person, scenePos);
  Q_ASSERT(node != nullptr);

  _levelByTreeNode.insert(node, 0);

  return node;
}

PersonView* FamilyTreeScene::createNode(Person* person, const QPointF& scenePos)
{
  Q_ASSERT(person != nullptr);

  PersonView* node = new PersonView(scenePos, person);
  addItem(node);
  _nodes.append(node);

  const QRectF boundingRect = node->boundingRect();
  qDebug() << "boundingRect " << boundingRect;
  const QPointF sceneCenterPos = node->sceneCenterPos();
  qDebug() << "sceneCenterPos " << sceneCenterPos;
  const QSize pixmapSize = QSize(20, 20);

  const QPointF fatherViewSceneCenterPos = sceneCenterPos - QPointF(boundingRect.width()/2, boundingRect.height()/2);
  qDebug() << "fatherViewSceneCenterPos " << fatherViewSceneCenterPos;
  QPixmap masculineGenderPixmap(":/images/gender_masculine.png");
  PersonViewCreationMarker* fatherViewCreationMarker = new PersonViewCreationMarker(masculineGenderPixmap.scaled(pixmapSize), node);
  fatherViewCreationMarker->setPos(fatherViewSceneCenterPos);
  addItem(fatherViewCreationMarker);

  const QPointF motherViewSceneCenterPos = sceneCenterPos + QPointF(boundingRect.width()/2, -boundingRect.height()/2);
  qDebug() << "motherViewSceneCenterPos " << motherViewSceneCenterPos;
  QPixmap feminineGenderPixmap(":/images/gender_feminine.png");
  PersonViewCreationMarker* motherViewCreationMarker = new PersonViewCreationMarker(feminineGenderPixmap.scaled(pixmapSize), node);
  motherViewCreationMarker->setPos(motherViewSceneCenterPos);
  addItem(motherViewCreationMarker);

  return node;
}

void FamilyTreeScene::onPersonAdded(Person* person)
{
  Q_ASSERT(person != nullptr);

  Person* child = person->child();
  Q_ASSERT(child != nullptr);
  PersonView* childNode = getView(child);

  extendTreeFromNode(childNode, person);
}

void FamilyTreeScene::onPersonRemoved(Person* person)
{
  Q_ASSERT(person != nullptr);

  PersonView* personView = getView(person);
  removeItem(personView);

  delete personView;
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
  PersonView* node = nodeAtPos(e->scenePos());
  if (node != nullptr)
  {
    PersonUpdaterView personUpdaterView(node->person());
    personUpdaterView.exec();
  }

  QGraphicsScene::mouseDoubleClickEvent(e);
}

PersonView* FamilyTreeScene::nodeAtPos(const QPointF& scenePos) const
{
  PersonView* node = nullptr;

  QGraphicsItem* itemAtPos = itemAt(scenePos, QTransform());
  if (itemAtPos != nullptr)
    node = dynamic_cast<PersonView*>(itemAtPos->parentItem());

  return node;
}
