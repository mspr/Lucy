#include "familytreenodeview.h"
#include "business/person.h"
#include "business/birth.h"

#include <QGraphicsScene>
#include <QPainter>

using namespace Business;

int FamilyTreeNodeView::_width = 100;
int FamilyTreeNodeView::_height = 50;
int FamilyTreeNodeView::_margin = 5;

FamilyTreeNodeView::FamilyTreeNodeView(const QPointF& sceneCenterPos, Person* person, QGraphicsItem* parent)
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

void FamilyTreeNodeView::setSceneCenterPos(const QPointF& sceneCenterPos)
{
  setPos(sceneCenterPos.x() - _width/2, sceneCenterPos.y() - _height/2);
}

Person* FamilyTreeNodeView::person() const
{
  return _person;
}

QRectF FamilyTreeNodeView::boundingRect() const
{
  return QRectF(-_margin, -_margin, _width+2*_margin, _height+2*_margin);
}

QPainterPath FamilyTreeNodeView::shape() const
{
  return QGraphicsItemGroup::shape();
}

void FamilyTreeNodeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QGraphicsItemGroup::paint(painter, option, widget);

  painter->drawRect(boundingRect());
}
