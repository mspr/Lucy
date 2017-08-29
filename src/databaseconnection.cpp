#include "databaseconnection.h"

#include <QtSql/QSqlError>
#include <QDebug>

DatabaseConnection::DatabaseConnection()
{
  _database = QSqlDatabase::addDatabase("QPSQL");
  _database.setHostName("localhost");
  _database.setPort(5432);
  _database.setDatabaseName("lucy");
  _database.setUserName("postgres");
  _database.setPassword("postgres");

  if (!_database.open())
  {
    const QString errorMsg = _database.lastError().text();
    qCritical() << "Error when opening database " << errorMsg;
  }
}

DatabaseConnection::~DatabaseConnection()
{
  if (_database.isOpen())
    _database.close();
}
