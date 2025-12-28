#include "database.h"

int main() {
  Database Db_service;
  Db_service.createDatabase();
  Db_service.createTask("test");
  return 0;
}
