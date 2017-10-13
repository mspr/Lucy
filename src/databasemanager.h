#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>

class DatabaseManager
{
  public:
    static DatabaseManager* getInstance();
    static void kill();

    bool open();
    bool isOpen() const;

  private:
    DatabaseManager();
    ~DatabaseManager();

  private:
    static DatabaseManager* _databaseManager;
    QSqlDatabase _database;
};

#endif // DATABASEMANAGER_H
