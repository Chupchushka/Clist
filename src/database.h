#pragma once
#include <sqlite3.h>
#include <string>

class Database {
private:
  const char *dir = "../build/database/database.db";
  sqlite3 *DB;

public:
  std::string quotesql(const std::string &s);
  void openDatabase();
  void createDatabase();
  void createTask(std::string task_content);
  void deleteTask(std::string id);
  void getColumn(std::string column_name);
};
