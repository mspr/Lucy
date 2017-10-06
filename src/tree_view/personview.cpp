#include "personview.h"
#include "familytreescene.h"
#include "business/person.h"
#include "business/gender.h"
#include "business/birth.h"
#include "business/tree.h"
#include "commands/persondeletecommand.h"
#include "commands/persondeletecascadecommand.h"
#include "commands/commandsmanager.h"
#include "personviewcreationmarker.h"

#include <QPainter>
#include <QDebug>

using namespace Business;

int PersonView::_width = 100;
int PersonView::_height = 50;
int PersonView::_margin = 5;

PersonView::PersonView(const QPointF& sceneCenterPos, Person* person, QGraphicsScene* scene)
  : QGraphicsItemGroup()
  , _person(person)
{
  Q_ASSERT(_person != nullptr);

  setupComponents();

  scene->addItem(this);

  setupCreationMarkers();

  setSceneCenterPos(sceneCenterPos);
}

void PersonView::setupComponents()
{
  QGraphicsSimpleTextItem* personFirstNameViewItem = new QGraphicsSimpleTextItem(_person->firstName(), this);
  addToGroup(personFirstNameViewItem);
  QGraphicsSimpleTextItem* personLastNameViewItem = new QGraphicsSimpleTextItem(_person->lastName(), this);
  personLastNameViewItem->setPos(0, 10);
  addToGroup(personLastNameViewItem);
  QGraphicsSimpleTextItem* personBirthDateViewItem = new QGraphicsSimpleTextItem(_person->birth()->date().toString(), this);
  personBirthDateViewItem->setPos(0, 20);
  addToGroup(personBirthDateViewItem);
}

void PersonView::setupCreationMarkers()
{
  const QRectF boundingRect(0, 0, _width/2 + _margin, _height/2 + _margin);
  _fatherMarker = new PersonViewCreationMarker(Gender::Masculine, boundingRect, this, scene());
  _motherMarker = new PersonViewCreationMarker(Gender::Feminine, boundingRect, this, scene());
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

  const QRectF boundingRect = this->boundingRect();

  Q_ASSERT(_fatherMarker != nullptr);
  const QPointF fatherViewSceneCenterPos = sceneCenterPos - QPointF(boundingRect.width()/2 + _margin,
                                                                    boundingRect.height()/2 + _margin + _fatherMarker->boundingRect().height());
  _fatherMarker->setPos(fatherViewSceneCenterPos);

  Q_ASSERT(_motherMarker != nullptr);
  const QPointF motherViewSceneCenterPos = sceneCenterPos - QPointF(0,
                                                                    boundingRect.height()/2 + _margin + _motherMarker->boundingRect().height());
  _motherMarker->setPos(motherViewSceneCenterPos);
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
  {
    if (_person->hasParents())
    {
      PersonDeleteCommand* personDeleteCommand = new PersonDeleteCommand(_person);
      CommandsManager::getInstance()->addCommand(personDeleteCommand);
      personDeleteCommand->redo();
    }
    else
    {
      PersonDeleteCascadeCommand* personDeleteCascadeCommand = new PersonDeleteCascadeCommand(_person);
      CommandsManager::getInstance()->addCommand(personDeleteCascadeCommand);
      personDeleteCascadeCommand->redo();
    }
  }
}
