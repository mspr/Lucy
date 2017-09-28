#include "personview.h"
#include "familytreescene.h"
#include "business/person.h"
#include "business/birth.h"
#include "business/tree.h"

#include <QGraphicsScene>
#include <QPainter>

using namespace Business;

int PersonView::_width = 100;
int PersonView::_height = 50;
int PersonView::_margin = 5;

PersonView::PersonView(const QPointF& sceneCenterPos, Person* person, QGraphicsItem* parent)
  : QGraphicsItemGroup(parent)
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  QGraphicsSimpleTextItem* personFirstNameViewItem = new QGraphicsSimpleTextItem(_person->firstName(), this);
  addToGroup(personFirstNameViewItem);
  QGraphicsSimpleTextItem* personLastNameViewItem = new QGraphicsSimpleTextItem(_person->lastName(), this);
  personLastNameViewItem->setPos(0, 10);
  addToGroup(personLastNameViewItem);
  QGraphicsSimpleTextItem* personBirthDateViewItem = new QGraphicsSimpleTextItem(_person->birth()->date().toString(), this);
  personBirthDateViewItem->setPos(0, 20);
  addToGroup(personBirthDateViewItem);

  setSceneCenterPos(sceneCenterPos);
}

FamilyTreeScene* PersonView::treeScene() const
{
  return dynamic_cast<FamilyTreeScene*>(scene());
}

QPointF PersonView::sceneCenterPos() const
{
  return pos() + QPointF(_width/2, _height/2);
}

void PersonView::setSceneCenterPos(const QPointF& sceneCenterPos)
{
  setPos(sceneCenterPos.x() - _width/2, sceneCenterPos.y() - _height/2);
}

Person* PersonView::person() const
{
  return _person;
}

QRectF PersonView::boundingRect() const
{
  return QRectF(-_margin, -_margin, _width+2*_margin, _height+2*_margin);
}

QPainterPath PersonView::shape() const
{
  return QGraphicsItemGroup::shape();
}

void PersonView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QGraphicsItemGroup::paint(painter, option, widget);

  painter->drawRect(boundingRect());
}

void PersonView::keyPressEvent(QKeyEvent* e)
{
  QGraphicsItemGroup::keyPressEvent(e);

  if (e->key() == Qt::Key_Delete)
    _person->tree()->remove(_person);
}
