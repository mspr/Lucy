#ifndef TESTQUERYLISTMODEL_H
#define TESTQUERYLISTMODEL_H

#include <QObject>

class TestQueryListModel : public QObject
{
  Q_OBJECT

  private slots:
    void columnCount();
    void rowCount_empty_model();
};

#endif // TESTQUERYLISTMODEL_H
