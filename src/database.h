#pragma once
#include <shared_mutex>
#include <sqlite3.h>
#include <string>
#include <vector>

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
  void editTask(std::string id, std::string column_name, std::string new_content);

  int getColumnSize(std::string column_name);

  std::vector<std::string> getColumn(std::string column_name);
  std::vector<bool> getIntColumn(std::string column_name);
};
