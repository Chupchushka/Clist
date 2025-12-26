#pragma once
#include <sqlite3.h>

class Database {
private:
  const char *dir = "../build/database/database.db";
  sqlite3 *DB;

public:
  void createDatabase();
};
