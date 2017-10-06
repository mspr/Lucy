#ifndef PERSONVIEWCREATIONMARKER_H
#define PERSONVIEWCREATIONMARKER_H

#include <QGraphicsPixmapItem>

class PersonView;

class PersonViewCreationMarker : public QGraphicsPixmapItem
{
  public:
    PersonViewCreationMarker(const QPixmap& pixmap, PersonView* personView, QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

  protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

  private:
    PersonView* _personView;
    bool _setPixmapVisible;
};

#endif // PERSONVIEWCREATIONMARKER_H
