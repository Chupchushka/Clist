#include "database.h"
#include "tui.h"
#include <ncurses.h>
#include <string>

TUI ui;
Database db;

int main() {
  db.createDatabase();
  db.createTask("Task1");
  db.createTask("Task2");
  db.createTask("Task3");
  db.createTask("Task4");

  // Screen setup
  initscr();
  cbreak();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *tasksWin = newwin(yMax - 7, xMax - 6, 1, 3);
  box(tasksWin, 0, 0);
  refresh();
  wrefresh(tasksWin);

  ui.createMenuBar();

  getch();

  endwin();
  db.getColumn("task_id");
  return 0;
}
