#include "main_window.h"
#include <ncurses.h>
#include <string>
#include <vector>

int MainWindow::renderMainWin(std::vector<std::string> tasks) {
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  WINDOW *mainWin = newwin(yMax - 7, xMax - 6, 1, 3);
  box(mainWin, 0, 0);
  refresh();
  wrefresh(mainWin);
  keypad(mainWin, TRUE);

  while (true) {

    // Prints the list and highlights the chosen options
    for (int i = 0; i < tasks.size(); i++) {
      if (i == highlight) {
        wattron(mainWin, A_REVERSE);
      }
      mvwprintw(mainWin, i + 2, 3, tasks[i].c_str());
      wattroff(mainWin, A_REVERSE);
    }

    choice = wgetch(mainWin);

    // Handling key presses
    switch (choice) {

    case KEY_UP:
      if (highlight == 0) {
        highlight = tasks.size() - 1;
      } else {
        highlight--;
      }
      break;

    case KEY_DOWN:
      if (highlight == tasks.size() - 1) {
        highlight = 0;
      } else {
        highlight++;
      }
      break;

    default:
      break;
    }

    // If enter key is pressed
    if (choice == 10) {
      wrefresh(mainWin);
      return highlight;
    }
  }
}
