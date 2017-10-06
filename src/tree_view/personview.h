#ifndef PERSONVIEW_H
#define PERSONVIEW_H

#include <QGraphicsItemGroup>

namespace Business { class Person; }
class FamilyTreeScene;
class PersonViewCreationMarker;

class PersonView : public QGraphicsItemGroup
{
  public:
    PersonView(const QPointF& scenePos, Business::Person* person, QGraphicsScene* scene);

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    Business::Person* person() const;

    FamilyTreeScene* treeScene() const;

    QPointF sceneCenterPos() const;
    void setSceneCenterPos(const QPointF& sceneCenterPos);

  protected:
    virtual void keyPressEvent(QKeyEvent*) override;

  private:
    void setupCreationMarkers();

  public:
    static int _width;
    static int _height;
    static int _margin;

  private:
    Business::Person* _person;
    PersonViewCreationMarker* _fatherMarker;
    PersonViewCreationMarker* _motherMarker;
};

#endif // PERSONVIEW_H
