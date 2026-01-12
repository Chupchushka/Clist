#include "database.h"
#include "main_window.h"
#include "tui.h"
#include <ncurses.h>
#include <string>
#include <vector>

TUI ui;
Database db;
MainWindow mv;

int main() {
  db.createDatabase();
  db.createTask("Task1");
  db.createTask("Task2");
  db.createTask("Task3");
  db.createTask("Task4");
  db.createTask("Task5");
  db.createTask("Task6");
  db.createTask("Task7");
  db.createTask("Task8");
  db.createTask("Task9");
  db.createTask("Task10");
  db.createTask("Task11");
  db.createTask("Task12");
  db.createTask("Task13");
  db.createTask("Task14");

  // Screen setup
  initscr();
  cbreak();
  noecho();

  std::vector<std::string> tasks = db.getColumn("task_content");
  mv.renderMainWin(tasks);

  return 0;
}
