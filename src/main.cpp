#include "database.h"
#include "tui.h"
#include <ncurses.h>
#include <string>

TUI ui;

int main() {
  // Screen setup
  initscr();
  cbreak();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *tasksWin = newwin(yMax - 6, xMax - 6, 1, 3);
  box(tasksWin, 0, 0);
  refresh();
  wrefresh(tasksWin);

  ui.createMenuBar();

  getch();

  endwin();
  return 0;
}
