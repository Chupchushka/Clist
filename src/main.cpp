#include "database.h"

int main() {
  Database Db_service;
  Db_service.createDatabase();
  Db_service.createTask("Test");
  Db_service.createTask("Test2");
  Db_service.createTask("Test3");

  Db_service.deleteTask("1");
  return 0;
}
