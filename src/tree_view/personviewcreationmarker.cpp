#include "personviewcreationmarker.h"
#include "personbuilderwizard.h"
#include "personview.h"
#include "familytreescene.h"
#include "business/person.h"
#include "business/gender.h"

#include <QGraphicsSceneHoverEvent>
#include <QPainter>

using namespace Business;

PersonViewCreationMarker::PersonViewCreationMarker(Business::Gender gender, const QRectF& boundingRect,
                                                   PersonView* personView, QGraphicsScene* scene)
  : QGraphicsPixmapItem()
  , _gender(gender)
  , _boundingRect(boundingRect)
  , _personView(personView)
  , _setPixmapVisible(false)
{
  Q_ASSERT(_personView != nullptr);
  Q_ASSERT(scene != nullptr);

  const QSize pixmapSize = QSize(20, 20);

  if (_gender == Gender::Masculine)
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
  FamilyTreeScene* scene = dynamic_cast<FamilyTreeScene*>(this->scene());
  Q_ASSERT(scene != nullptr);

  PersonBuilderWizard personBuilderWizard(_personView, _gender);
  if (personBuilderWizard.exec())
  {
  }

  QGraphicsPixmapItem::mousePressEvent(e);
}

QRectF PersonViewCreationMarker::boundingRect() const
{
  return _boundingRect;
}

QPainterPath PersonViewCreationMarker::shape() const
{
  QPainterPath path;
  path.addRect(_boundingRect);
  return path;
}

void PersonViewCreationMarker::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
  if (_setPixmapVisible)
  {
    const qreal posX = _boundingRect.x() + _boundingRect.width()/2 - pixmap().width()/2;
    const qreal posY = _boundingRect.y() + _boundingRect.height()/2 - pixmap().height()/2;
    const QRect rect(posX, posY, pixmap().width(), pixmap().height());
    painter->drawPixmap(rect, pixmap());
  }
}
