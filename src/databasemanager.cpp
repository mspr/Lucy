#include "databasemanager.h"

#include <QtSql/QSqlError>
#include <QDebug>

DatabaseManager* DatabaseManager::_databaseManager = nullptr;

/*static*/ DatabaseManager* DatabaseManager::getInstance()
{
  if (_databaseManager == nullptr)
    _databaseManager = new DatabaseManager();

  return _databaseManager;
}

/*static*/ void DatabaseManager::kill()
{
  if (_databaseManager != nullptr)
  {
    delete _databaseManager;
    _databaseManager = nullptr;
  }
}

DatabaseManager::DatabaseManager()
{
  _database = QSqlDatabase::addDatabase("QPSQL");
  _database.setHostName("localhost");
  _database.setPort(5432);
  _database.setDatabaseName("lucy");
  _database.setUserName("postgres");
  _database.setPassword("postgres");
}

bool DatabaseManager::open()
{
  const bool success = _database.open();
  if (!success)
  {
    const QString errorMsg = _database.lastError().text();
    qCritical() << "Error when opening database " << errorMsg;
  }

  return success;
}

bool DatabaseManager::isOpen() const
{
  return _database.isOpen();
}

DatabaseManager::~DatabaseManager()
{
  if (_database.isOpen())
    _database.close();
}
