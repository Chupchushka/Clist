#include "database.h"
#include "tui.h"
#include <ncurses.h>
#include <string>
#include <vector>

TUI ui;
Database db;

int main() {
  db.createDatabase();
  for (int i = 0; i <= 100; i++) {
    db.createTask("task number " + std::to_string(i));
  }

  // Screen setup
  initscr();
  cbreak();
  noecho();

  std::vector<std::string> tasks = db.getColumn("task_content");
  ui.renderMainWin(tasks);

  return 0;
}
