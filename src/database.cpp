#include "database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

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

void Database::deleteTask(std::string id) {
  openDatabase();
  char *errMsg;
  std::string sql = "DELETE FROM tasks WHERE task_id=" + id + ";";

  int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "LOG: ERROR while executing sql!" << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  sqlite3_close(DB);
}

int Database::getColumnSize(std::string column_name) {

    openDatabase();
    sqlite3_stmt *stmt;
    std::string sql = "SELECT COUNT(" + column_name + ") FROM tasks";

    int count = 0;

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return count;
}

std::vector<std::string> Database::getColumn(std::string column_name) {
  openDatabase();

  std::string sql = "SELECT " + column_name + " FROM tasks;";

  std::vector<std::string> values;

  // prepare the sql statement
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

  // Error checking
  if (rc != SQLITE_OK) {
    std::cerr << "LOG: prepare failed: " << sqlite3_errmsg(DB) << std::endl;
  } else {
    bool done = false;

    while (!done) {
      switch (sqlite3_step(stmt)) {

       // Case if sql prepared the next row
      case SQLITE_ROW: {
        // Get the n column text
            values.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        break;
      }
      // Case if sql is finished
      case SQLITE_DONE:
        sqlite3_finalize(stmt);
        done = true;
        break;
      }
    }
    sqlite3_close(DB);
    return values;
  }
}
