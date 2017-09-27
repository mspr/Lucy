#ifndef PERSONVIEW_H
#define PERSONVIEW_H

#include <QGraphicsItemGroup>

namespace Business { class Person; }
class FamilyTreeScene;

class PersonView : public QGraphicsItemGroup
{
  public:
    PersonView(const QPointF& scenePos, Business::Person* person, QGraphicsItem* parent = nullptr);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    Business::Person* person() const;

    FamilyTreeScene* treeScene() const;

    QPointF sceneCenterPos() const;
    void setSceneCenterPos(const QPointF& sceneCenterPos);

  public:
    static int _width;
    static int _height;
    static int _margin;

  private:
    Business::Person* _person;
};

#endif // PERSONVIEW_H
