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
{
  Q_ASSERT(_personView != nullptr);
}

void PersonViewCreationMarker::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
  qDebug() << "hoverEnterEvent " << e->scenePos();

  QGraphicsPixmapItem::hoverEnterEvent(e);
}

void PersonViewCreationMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
  qDebug() << "hoverLeaveEvent " << e->scenePos();

  QGraphicsPixmapItem::hoverLeaveEvent(e);
}

void PersonViewCreationMarker::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
  qDebug() << "mousePressEvent " << e->scenePos();

  FamilyTreeScene* scene = dynamic_cast<FamilyTreeScene*>(this->scene());
  Q_ASSERT(scene != nullptr);

  PersonBuilderWizard personBuilderWizard;
  if (personBuilderWizard.exec())
  {
    Person* person = personBuilderWizard.person();

    _personView->person()->setParent(person);

    scene->extendTreeFromNode(_personView, person);
//    scene->adjustNodes();
  }

  QGraphicsPixmapItem::mousePressEvent(e);
}
