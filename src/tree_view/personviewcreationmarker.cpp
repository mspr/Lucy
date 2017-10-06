#include "personviewcreationmarker.h"
#include "personbuilderwizard.h"
#include "personview.h"
#include "familytreescene.h"
#include "business/person.h"

#include <QGraphicsSceneHoverEvent>
#include <QDebug>

using namespace Business;

PersonViewCreationMarker::PersonViewCreationMarker(const QPixmap& pixmap, PersonView* personView, QGraphicsItem* parent)
  : QGraphicsPixmapItem(pixmap, parent)
  , _personView(personView)
  , _setPixmapVisible(true)
{
  Q_ASSERT(_personView != nullptr);

  setAcceptHoverEvents(true);
}

void PersonViewCreationMarker::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
  _setPixmapVisible = true;

  QGraphicsPixmapItem::hoverEnterEvent(e);
}

void PersonViewCreationMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
  _setPixmapVisible = false;

  QGraphicsPixmapItem::hoverLeaveEvent(e);
}

void PersonViewCreationMarker::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  qDebug() << "mousePressEvent " << e->scenePos();

  FamilyTreeScene* scene = dynamic_cast<FamilyTreeScene*>(this->scene());
  Q_ASSERT(scene != nullptr);

  PersonBuilderWizard personBuilderWizard(_personView);
  if (personBuilderWizard.exec())
  {
  }

  QGraphicsPixmapItem::mousePressEvent(e);
}

QRectF PersonViewCreationMarker::boundingRect() const
{
  return QGraphicsPixmapItem::boundingRect();
//  const QRectF boundingRect = QGraphicsPixmapItem::boundingRect();
//  return QRectF(0, 0, boundingRect.width() + 50, boundingRect.height() + 50);
}

QPainterPath PersonViewCreationMarker::shape() const
{
  QPainterPath path;
  const QRectF boundingRect = this->boundingRect();
  path.addRect(0, 0, boundingRect.width() + 50, boundingRect.height() + 50);
//  QRegion region;
//  path.addRegion(QRegion(pixmap().mask());
  return path;
}

void PersonViewCreationMarker::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  if (_setPixmapVisible)
    QGraphicsPixmapItem::paint(painter, option, widget);
}
