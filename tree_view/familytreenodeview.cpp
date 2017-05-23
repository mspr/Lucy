#include "familytreenodeview.h"

#include <QPen>
#include <QPainter>
#include <QDebug>

FamilyTreeNodeView::FamilyTreeNodeView(const QPointF& scenePos, const int radius, QGraphicsItem* parent)
  : QGraphicsEllipseItem(scenePos.x()-radius, scenePos.y()-radius, 2*radius, 2*radius, parent)
{
}

QRectF FamilyTreeNodeView::boundingRect() const
{
  return QGraphicsEllipseItem::boundingRect();
}

QPainterPath FamilyTreeNodeView::shape() const
{
  return QGraphicsEllipseItem::shape();
}

void FamilyTreeNodeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QGraphicsEllipseItem::paint(painter, option, widget);

//  QRectF rect = boundingRect();
//  QPen pen(Qt::NoPen);
//  QBrush brush(Qt::blue);
//  brush.setStyle(Qt::SolidPattern);

//  painter->setPen(pen);
//  painter->setBrush(brush);
//  painter->drawEllipse(rect);
}
