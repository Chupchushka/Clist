#include "tui.h"
#include <ncurses.h>

int TUI::createMenuBar() {
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  menuWin = newwin(5, xMax - 12, yMax - 6, 5);

  box(menuWin, 0, 0);
  refresh();
  wrefresh(menuWin);
  keypad(menuWin, true);

  while (true) {
    // Prints the list and highlights the chosen options
    for (int i = 0; i < size; i++) {
      if (i == highlight) {
        wattron(menuWin, A_REVERSE);
      }
      mvwprintw(menuWin, i + 1, 1, choices[i].c_str());
      wattroff(menuWin, A_REVERSE);
    }

    choice = wgetch(menuWin);

    // Handling key presses
    switch (choice) {
    case KEY_UP:
      if (highlight == 0) {
        highlight = size - 1;
      } else {
        highlight--;
      }
      break;
    case KEY_DOWN:
      if (highlight == size - 1) {
        highlight = 0;
      } else {
        highlight++;
      }
      break;
    default:
      break;
    }

    // If enter was pressed return selected option
    if (choice == 10) {
      // Clear the window
      wclear(menuWin);
      wrefresh(menuWin);
      delwin(menuWin);

      return highlight;
    }
  }
}
