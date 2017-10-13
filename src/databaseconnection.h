#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QSqlDatabase>

class DatabaseConnection
{
  public:
    static DatabaseConnection* getInstance();
    static void kill();

    bool open();
    bool isOpen() const;

  private:
    DatabaseConnection();
    ~DatabaseConnection();

  private:
    static DatabaseConnection* _databaseManager;
    QSqlDatabase _database;
};

#endif // DATABASECONNECTION_H
