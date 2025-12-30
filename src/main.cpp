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

  int choice = ui.createMenuBar();
  std::cout << choice;

  endwin();
  return 0;
}
