#include "familytreescene.h"
#include "personview.h"
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
#include "familytreeview.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

using namespace Business;

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, Tree* tree, FamilyTreeView* view)
  : QGraphicsScene(sceneRect, view)
  , _tree(tree)
{
  Q_ASSERT(view != nullptr);
  Q_ASSERT(_tree != nullptr);

  setBackgroundBrush(QBrush(QColor(247, 248, 255)));

  view->setScene(this);
  view->setSceneRect(sceneRect);

  PersonView* referenceNode = createReferenceNode(tree->reference(), QPointF(0, 0));
  _referenceNode = referenceNode;
  Q_ASSERT(_referenceNode != nullptr);

  createNodeRecursively(referenceNode);

  adjustNodes();

  connect(tree->d(), Tree_p::personAdded, this, FamilyTreeScene::onPersonAdded);
  connect(tree->d(), Tree_p::personRemoved, this, FamilyTreeScene::onPersonRemoved);
}

void FamilyTreeScene::createNodeRecursively(PersonView* node)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  if (person->hasFather())
  {
    PersonView* fatherNode = createNode(node, person->father());
    createNodeRecursively(fatherNode);
  }

  if (person->hasMother())
  {
    PersonView* motherNode = createNode(node, person->mother());
    createNodeRecursively(motherNode);
  }
}

PersonView* FamilyTreeScene::createNode(PersonView* node, Person* person)
{
  Q_ASSERT(node != nullptr);
  Q_ASSERT(_levelByTreeNode.contains(node));

  PersonView* newNode = createNode(person, QPointF(0, 0));
  Q_ASSERT(newNode != nullptr);

  const int newTreeLevel = _levelByTreeNode.value(node) + 1;
  _levelByTreeNode.insert(newNode, newTreeLevel);

  return newNode;
}

void FamilyTreeScene::adjustNodes()
{
  Q_ASSERT(views().count() == 1);
  QGraphicsView* view = views().first();
  const QRect viewportRect = view->viewport()->rect();
  const QRectF visibleSceneRect = views().first()->mapToScene(viewportRect).boundingRect();

  _referenceNode->setSceneCenterPos(QPointF(0, visibleSceneRect.height()/2));

  const int generationsCount = _tree->countGenerations();

  adjustNodesRecursively(_referenceNode, generationsCount);

  view->fitInView(itemsBoundingRect(), Qt::KeepAspectRatio);
}

void FamilyTreeScene::adjustNodesRecursively(PersonView* node, int generationsCount)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  if (person->hasParents())
  {
    Q_ASSERT(_levelByTreeNode.contains(node));
    const int nodeLevel = _levelByTreeNode.value(node);
    const int factor = generationsCount - nodeLevel;
    Q_ASSERT(factor > 0);

    const QPointF nodeCenterScenePos = node->sceneCenterPos();
    const int xOffset = 100 * pow(2, factor - 1);
    const int yOffset = 100;

    if (person->hasMother())
    {
      PersonView* motherView = getView(person->mother());
      motherView->setSceneCenterPos(nodeCenterScenePos - QPointF(-xOffset, yOffset));
      adjustNodesRecursively(motherView, generationsCount);
    }

    if (person->hasFather())
    {
      PersonView* fatherView = getView(person->father());
      fatherView->setSceneCenterPos(nodeCenterScenePos - QPointF(xOffset, yOffset));
      adjustNodesRecursively(fatherView, generationsCount);
    }
  }
}

Tree* FamilyTreeScene::tree() const
{
  return _tree;
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

PersonView* FamilyTreeScene::createReferenceNode(Person* person, const QPointF& scenePos)
{
  PersonView* node = createNode(person, scenePos);
  Q_ASSERT(node != nullptr);

  _levelByTreeNode.insert(node, 1);

  return node;
}

PersonView* FamilyTreeScene::createNode(Person* person, const QPointF& scenePos)
{
  Q_ASSERT(person != nullptr);

  PersonView* node = new PersonView(scenePos, person, this);
  _nodes.append(node);

  return node;
}

void FamilyTreeScene::onPersonAdded(Person* person)
{
  Q_ASSERT(person != nullptr);

  Person* child = person->child();
  Q_ASSERT(child != nullptr);
  PersonView* childNode = getView(child);

  createNode(childNode, person);

  adjustNodes();
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

QList<PersonView*> FamilyTreeScene::nodes() const
{
  return _nodes;
}
