#ifndef TESTQUERYLISTMODEL_H
#define TESTQUERYLISTMODEL_H

#include <QObject>

class TestQueryListModel : public QObject
{
  Q_OBJECT

  private slots:
    void createModel();
    void createNewQuery();
};

#endif // TESTQUERYLISTMODEL_H
