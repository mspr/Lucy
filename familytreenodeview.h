#ifndef FAMILYTREENODEVIEW_H
#define FAMILYTREENODEVIEW_H

#include <QGraphicsEllipseItem>

class FamilyTreeNodeView : public QGraphicsEllipseItem
{
  public:
    FamilyTreeNodeView(const QPointF& scenePos, const int radius, QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // FAMILYTREENODEVIEW_H
