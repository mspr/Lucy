#ifndef FAMILYTREENODEVIEW_H
#define FAMILYTREENODEVIEW_H

#include <QGraphicsItemGroup>

class Person;

class FamilyTreeNodeView : public QGraphicsItemGroup
{
  public:
    FamilyTreeNodeView(const QPointF& scenePos, Person* person, QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    Person* person() const;

  public:
    static int _width;
    static int _height;
    static int _margin;

  private:
    Person* _person;
};

#endif // FAMILYTREENODEVIEW_H
