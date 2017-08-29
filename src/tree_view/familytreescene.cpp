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

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, Tree* tree, QObject* parent)
  : QGraphicsScene(sceneRect, parent)
{
  Q_ASSERT(tree != nullptr);

  FamilyTreeNodeView* referenceNode = createReferenceNode(tree->reference(), QPointF(0, 0));
  Q_ASSERT(referenceNode != nullptr);

  extendTreeFromNodeRecursively(referenceNode);
}

void FamilyTreeScene::extendTreeFromNodeRecursively(FamilyTreeNodeView* node)
{
  Q_ASSERT(node != nullptr);
  Person* person = node->person();
  Q_ASSERT(person != nullptr);

  Person* father = person->father();
  if (father != nullptr)
  {
    FamilyTreeNodeView* fatherNode = extendTreeFromNode(node, father, Qt::LeftButton);
    Q_ASSERT(fatherNode != nullptr);
    extendTreeFromNodeRecursively(fatherNode);
  }

  Person* mother = person->mother();
  if (mother != nullptr)
  {
    FamilyTreeNodeView* motherNode = extendTreeFromNode(node, mother, Qt::RightButton);
    Q_ASSERT(motherNode != nullptr);
    extendTreeFromNodeRecursively(motherNode);
  }
}

FamilyTreeNodeView* FamilyTreeScene::extendTreeFromNode(FamilyTreeNodeView* node, Person* person, Qt::MouseButton button)
{
  Q_ASSERT(node != nullptr);
  Q_ASSERT(person != nullptr);
  Q_ASSERT(_levelByTreeNode.contains(node));
  Q_ASSERT(_inclinationByTreeNode.contains(node));

  const int radius = 200;

  const int previousNodeLevel = _levelByTreeNode.value(node);
  const int newTreeLevel = previousNodeLevel + 1;
  Q_ASSERT(newTreeLevel > 0);

  const QPointF previousNodeRectCenter = node->boundingRect().center();
  const QPointF previousNodeCenterScenePos = node->scenePos() + previousNodeRectCenter;

  double inclination = 5*M_PI/12 * 1.0/newTreeLevel;

  double angle = _inclinationByTreeNode.value(node);

  if (button == Qt::LeftButton)
    inclination *= -1;
  else if (button == Qt::RightButton)
    inclination *= 1;

  angle += inclination;

  const double x = previousNodeCenterScenePos.x() + radius*sin(angle);
  const double y = previousNodeCenterScenePos.y() - radius*cos(angle);
  const QPointF scenePos = QPointF(x, y);

  qDebug() << previousNodeCenterScenePos << " >> " << scenePos;

  FamilyTreeNodeView* newNode = createNode(person, scenePos);
  Q_ASSERT(newNode != nullptr);

  _levelByTreeNode.insert(newNode, newTreeLevel);
  _inclinationByTreeNode.insert(newNode, angle);

  return newNode;
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

      Tree* currentTree = ProjectManager::getInstance()->currentProject()->currentTree();
      Q_ASSERT(currentTree != nullptr);

      FamilyTreeNodeBuilder familyTreeNodeBuilder;
      if (familyTreeNodeBuilder.exec())
      {
        Person* person = familyTreeNodeBuilder.person();

        const Qt::MouseButton button = e->button();

        if (button == Qt::LeftButton)
          node->person()->setFather(person);
        else if (button == Qt::RightButton)
          node->person()->setMother(person);

        currentTree->addPerson(person);

        extendTreeFromNode(node, person, button);
      }
    }
  }
  else if (e->button() == Qt::RightButton)
  {
  }
}
