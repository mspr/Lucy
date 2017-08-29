#ifndef TESTINTERVAL_H
#define TESTINTERVAL_H

#include <QObject>

class TestProject : public QObject
{
  Q_OBJECT

  private slots:
    void setFileName();
};

#endif // TESTINTERVAL_H
