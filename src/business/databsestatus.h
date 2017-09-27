#ifndef DATABASESTATUS_H
#define DATABASESTATUS_H

namespace Business
{
  enum class DatabaseStatus
  {
    New,
    Loaded,
    Dirty,
    Deleted
  };
}

#endif // DATABASESTATUS_H
