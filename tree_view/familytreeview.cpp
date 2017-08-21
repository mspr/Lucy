#include "familytreeview.h"
#include "familytreescene.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>

FamilyTreeView::FamilyTreeView(Tree* tree, QWidget* parent)
  : QGraphicsView(parent)
{
  Q_ASSERT(tree != nullptr);

  FamilyTreeScene* familyTreeScene = new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), this);
  setScene(familyTreeScene);
  familyTreeScene->createReferenceNode(tree->reference(), QPointF(0, 0));
  setSceneRect(QRectF(-1000, -1000, 2000, 2000));

  setMouseTracking(true);
}

void FamilyTreeView::mousePressEvent(QMouseEvent* e)
{
  QGraphicsView::mousePressEvent(e);

  if (QApplication::keyboardModifiers() & Qt::ControlModifier)
  {
    setCursor(Qt::ClosedHandCursor);
    _lastPos = mapToScene(e->pos());
  }
}

void FamilyTreeView::mouseReleaseEvent(QMouseEvent* e)
{
  if (QApplication::keyboardModifiers() & Qt::ControlModifier)
    setCursor(Qt::OpenHandCursor);

  QGraphicsView::mouseReleaseEvent(e);
}

void FamilyTreeView::mouseMoveEvent(QMouseEvent* e)
{
  QGraphicsView::mouseMoveEvent(e);

  if (QApplication::keyboardModifiers() & Qt::ControlModifier &&
      QApplication::mouseButtons() & Qt::LeftButton)
  {
    QPointF dP = mapToScene(e->pos()) - _lastPos;
    centerOn(mapToScene(viewport()->rect().center()) - dP);
    _lastPos = mapToScene(e->pos());
  }
}

void FamilyTreeView::keyPressEvent(QKeyEvent* e)
{
  QGraphicsView::keyPressEvent(e);

  if (e->key() == Qt::Key_Control)
    setCursor(Qt::OpenHandCursor);
}

void FamilyTreeView::keyReleaseEvent(QKeyEvent* e)
{
  unsetCursor();

  QGraphicsView::keyReleaseEvent(e);
}

void FamilyTreeView::wheelEvent(QWheelEvent* e)
{
  QGraphicsView::wheelEvent(e);

  qreal factor = 1.5;

  if (e->delta() > 0)
    scale(factor, factor);
  else
    scale(1/factor, 1/factor);
}
