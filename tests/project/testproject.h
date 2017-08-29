#ifndef TESTINTERVAL_H
#define TESTINTERVAL_H

#include <QObject>

class TestProject : public QObject
{
  Q_OBJECT

  public slots:
    void setFileName();
};

#endif // TESTINTERVAL_H
