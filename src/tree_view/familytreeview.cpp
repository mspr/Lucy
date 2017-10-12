#include "familytreeview.h"
#include "familytreescene.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>

using namespace Business;

FamilyTreeView::FamilyTreeView(Tree* tree, QWidget* parent)
  : QGraphicsView(parent)
{
  Q_ASSERT(tree != nullptr);

  FamilyTreeScene* familyTreeScene = new FamilyTreeScene(QRectF(-10000, -10000, 20000, 20000), tree, this);
  Q_UNUSED(familyTreeScene);

  setMouseTracking(true);
}

Tree* FamilyTreeView::tree() const
{
  FamilyTreeScene* scene = dynamic_cast<FamilyTreeScene*>(this->scene());
  Q_ASSERT(scene != nullptr);

  return scene->tree();
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
