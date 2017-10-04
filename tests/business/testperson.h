#ifndef TESTPERSON_H
#define TESTPERSON_H

#include <QObject>

class TestPerson : public QObject
{
  Q_OBJECT

  private slots:
    void createPerson();
    void setTree();
    void setFather();
    void setMother();
};

#endif // TESTPERSON_H
