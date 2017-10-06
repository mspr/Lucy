#include "personviewcreationmarker.h"
#include "personbuilderwizard.h"
#include "personview.h"
#include "familytreescene.h"
#include "business/person.h"
#include "business/gender.h"

#include <QGraphicsSceneHoverEvent>
#include <QDebug>

using namespace Business;

PersonViewCreationMarker::PersonViewCreationMarker(Business::Gender gender, PersonView* personView, QGraphicsScene* scene)
  : QGraphicsPixmapItem()
  , _personView(personView)
  , _setPixmapVisible(true)
{
  Q_ASSERT(_personView != nullptr);
  Q_ASSERT(scene != nullptr);

  const QSize pixmapSize = QSize(20, 20);

  if (gender == Gender::Masculine)
  {
    QPixmap masculineGenderPixmap(":/images/gender_masculine.png");
    setPixmap(masculineGenderPixmap.scaled(pixmapSize));
  }
  else
  {
    QPixmap feminineGenderPixmap(":/images/gender_feminine.png");
    setPixmap(feminineGenderPixmap.scaled(pixmapSize));
  }

  setAcceptHoverEvents(true);

  scene->addItem(this);
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
  {

    QGraphicsPixmapItem::paint(painter, option, widget);
  }
}
