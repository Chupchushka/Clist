#pragma once
#include <sqlite3.h>
#include <string>

class Database {
private:
  const char *dir = "../build/database/database.db";
  sqlite3 *DB;

public:
  void createDatabase();
  void createTask(std::string task_content);
  void openDatabase();
  std::string quotesql(const std::string &s);
};
