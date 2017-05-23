#include "familytreescene.h"
#include "familytreenodeview.h"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

FamilyTreeScene::FamilyTreeScene(const QRectF& sceneRect, QObject* parent)
  : QGraphicsScene(sceneRect, parent)
{
}

void FamilyTreeScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  qDebug() << "FamilyTreeScene::mousePressEvent " << e->scenePos();

  if (e->button() == Qt::RightButton)
  {
    FamilyTreeNodeView* treeNode = new FamilyTreeNodeView(e->scenePos(), 5);
    addItem(treeNode);
  }
}
