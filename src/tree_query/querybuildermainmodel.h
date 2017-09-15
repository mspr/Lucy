#ifndef QUERYBUILDERMAINMODEL_H
#define QUERYBUILDERMAINMODEL_H

#include <QObject>

class QueryFields;
class QueryListModel;
class QueryClauseTableModel;

class QueryBuilderMainModel : public QObject
{
  Q_OBJECT

  public:
    QueryBuilderMainModel(QObject* parent = nullptr);

    QueryFields* queryFields() const;
    QueryListModel* queryListModel() const;
    QueryClauseTableModel* clauseTableModel() const;

  signals:
    void queryExecuted(const QList<int>& personIds);

  private:
    QueryFields* _queryFields;
    QueryListModel* _queryListModel;
    QueryClauseTableModel* _clauseTableModel;
};

#endif // QUERYBUILDERMAINMODEL_H
