#ifndef QUERYBUILDERMAINMODEL_H
#define QUERYBUILDERMAINMODEL_H

#include <QObject>

class QueryFields;
class QueryListModel;
class ClauseTableModel;

class QueryBuilderMainModel : public QObject
{
  Q_OBJECT

  public:
    QueryBuilderMainModel(QObject* parent = nullptr);

    QueryFields* queryFields() const;
    QueryListModel* queryListModel() const;
    ClauseTableModel* clauseTableModel() const;

  signals:
    void queryExecuted(const QList<int>& personIds);

  private:
    QueryFields* _queryFields;
    QueryListModel* _queryListModel;
    ClauseTableModel* _clauseTableModel;
};

#endif // QUERYBUILDERMAINMODEL_H
