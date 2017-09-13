#include "personviewcreationmarker.h"
#include "personbuilderwizard.h"
#include "familytreenodeview.h"
#include "familytreescene.h"
#include "business/person.h"

using namespace Business;

PersonViewCreationMarker::PersonViewCreationMarker(const QPixmap& pixmap, FamilyTreeNodeView* personView, QGraphicsItem* parent)
  : QGraphicsPixmapItem(pixmap, parent)
  , _personView(personView)
{
  Q_ASSERT(_personView != nullptr);
}

void PersonViewCreationMarker::hoverEnterEvent(QGraphicsSceneHoverEvent* e)
{
  QGraphicsPixmapItem::hoverEnterEvent(e);
}

void PersonViewCreationMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent* e)
{
  QGraphicsPixmapItem::hoverLeaveEvent(e);
}

void PersonViewCreationMarker::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
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
