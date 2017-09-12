#ifndef PERSONVIEWCREATIONMARKER_H
#define PERSONVIEWCREATIONMARKER_H

#include <QGraphicsPixmapItem>

class PersonViewCreationMarker : public QGraphicsPixmapItem
{
  public:
    PersonViewCreationMarker(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);
};

#endif // PERSONVIEWCREATIONMARKER_H
