#ifndef QUERYBUILDERMAINMODEL_H
#define QUERYBUILDERMAINMODEL_H

#include <QObject>

class QueryFields;
class QueryListModel;
class ClauseTableModel;

class QueryBuilderMainModel : QObject
{
  public:
    QueryBuilderMainModel(QObject* parent = nullptr);

    QueryFields* queryFields() const;
    QueryListModel* queryListModel() const;
    ClauseTableModel* clauseTableModel() const;

  private:
    QueryFields* _queryFields;
    QueryListModel* _queryListModel;
    ClauseTableModel* _clauseTableModel;
};

#endif // QUERYBUILDERMAINMODEL_H
