#include "databaseconnection.h"

#include <QtSql/QSqlError>
#include <QDebug>

DatabaseConnection* DatabaseConnection::_databaseManager = nullptr;

/*static*/ DatabaseConnection* DatabaseConnection::getInstance()
{
  if (_databaseManager == nullptr)
    _databaseManager = new DatabaseConnection();

  return _databaseManager;
}

/*static*/ void DatabaseConnection::kill()
{
  if (_databaseManager != nullptr)
  {
    delete _databaseManager;
    _databaseManager = nullptr;
  }
}

DatabaseConnection::DatabaseConnection()
{
  _database = QSqlDatabase::addDatabase("QPSQL");
  _database.setHostName("localhost");
  _database.setPort(5432);
  _database.setDatabaseName("lucy");
  _database.setUserName("postgres");
  _database.setPassword("postgres");
}

bool DatabaseConnection::open()
{
  const bool success = _database.open();
  if (!success)
  {
    const QString errorMsg = _database.lastError().text();
    qCritical() << "Error when opening database " << errorMsg;
  }

  return success;
}

bool DatabaseConnection::isOpen() const
{
  return _database.isOpen();
}

DatabaseConnection::~DatabaseConnection()
{
  if (_database.isOpen())
    _database.close();
}
