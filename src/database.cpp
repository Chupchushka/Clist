#include "database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

// Opens connection to the DB requiers sqlite3_close at the end
void Database::openDatabase() {
  int exit = sqlite3_open(dir, &DB);

  // Error checking
  if (exit) {
    std::cerr << "LOG: Error while opening database!" << std::endl;
  }
}

// Returns a string to use in sql statements
std::string Database::quotesql(const std::string &s) {
  return std::string("'") + s + std::string("'");
}

// Create the database and make initial table
void Database::createDatabase() {
  openDatabase();

  // Creating a basic table
  char *errMsg;
  char *sql = "CREATE TABLE IF NOT EXISTS tasks ("
              "task_id INTEGER PRIMARY KEY AUTOINCREMENT, "
              "task_content TEXT NOT NULL"
              ");";

  int exit = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "LOG: error while creating initial table!" << std::endl;
    sqlite3_free(errMsg);
  }

  sqlite3_close(DB);
}

// Insert task to the table
void Database::createTask(std::string task_content) {
  openDatabase();

  char *errMsg;
  std::string sql = "INSERT INTO tasks (task_content) VALUES (" +
                    quotesql(task_content) + ");";

  int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "LOG: ERROR while executing sql!" << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  sqlite3_close(DB);
}
