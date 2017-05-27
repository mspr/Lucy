#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>

class DatabaseConnection
{
  public:
    DatabaseConnection();
    ~DatabaseConnection();

  private:
    QSqlDatabase _database;
};

#endif // DATABASECONNECTION_H
