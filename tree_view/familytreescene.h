#ifndef FAMILYTREESCENE_H
#define FAMILYTREESCENE_H

#include <QGraphicsScene>
#include <QList>

class QGraphicsSceneMouseEvent;

class FamilyTreeScene : public QGraphicsScene
{
  Q_OBJECT

  public:
    FamilyTreeScene(const QRectF& sceneRect, QObject* parent = nullptr);

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*) override;
};

#endif // FAMILYTREESCENE_H
