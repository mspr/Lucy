#ifndef PERSONVIEWCREATIONMARKER_H
#define PERSONVIEWCREATIONMARKER_H

#include <QGraphicsPixmapItem>

class FamilyTreeNodeView;

class PersonViewCreationMarker : public QGraphicsPixmapItem
{
  public:
    PersonViewCreationMarker(const QPixmap& pixmap, FamilyTreeNodeView* personView, QGraphicsItem* parent = nullptr);

  protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

  private:
    FamilyTreeNodeView* _personView;
};

#endif // PERSONVIEWCREATIONMARKER_H
