#include "database.h"
#include <iostream>
#include <sqlite3.h>

void Database::createDatabase() {
  int exit = sqlite3_open(dir, &DB);

  // Error checking
  if (exit) {
    std::cout << "LOG: Error while creating database!" << std::endl;
  } else {
    std::cerr << "LOG: database created succesfull!" << std::endl;
  }

  // Creating a basic table
  char *errMsg;
  char *sql = "CREATE TABLE IF NOT EXISTS tasks ("
              "task_id INTEGER PRIMARY KEY AUTOINCREMENT, "
              "task_name TEXT NOT NULL"
              ");";

  exit = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "LOG: error while creating initial table!" << std::endl;
    sqlite3_free(errMsg);
  }

  sqlite3_close(DB);
}
