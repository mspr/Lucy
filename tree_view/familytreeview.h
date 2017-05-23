#ifndef FAMILYTREEVIEW_H
#define FAMILYTREEVIEW_H

#include <QGraphicsView>

class FamilyTreeView : public QGraphicsView
{
  public:
    FamilyTreeView(QWidget* parent = nullptr);

  protected:
    virtual void keyPressEvent(QKeyEvent*) override;
    virtual void keyReleaseEvent(QKeyEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;
    virtual void wheelEvent(QWheelEvent*) override;

  private:
    QPointF _lastPos;
};

#endif // FAMILYTREEVIEW_H
