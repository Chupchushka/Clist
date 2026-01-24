#include "tui.h"
#include <ncurses.h>

int TUI::renderActionWin() {
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

int TUI::renderMainWin(std::vector<std::string> tasks) {
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  mainWin = newwin(yMax - 7, xMax - 6, 1, 3);
  box(mainWin, 0, 0);
  refresh();
  wrefresh(mainWin);
  keypad(mainWin, TRUE);

  while (true) {
    // Prints the list and highlights the chosen options
    for (int i = 0; i < tasks.size(); i++) {
      if (i == main_window_highlight) {
        wattron(mainWin, A_REVERSE);
      }
      mvwprintw(mainWin, i + 2, 3, tasks[i].c_str());
      wattroff(mainWin, A_REVERSE);
    }

    main_window_choice = wgetch(mainWin);

    // Handling key presses
    switch (main_window_choice) {

    case KEY_UP:
      if (main_window_highlight == 0) {
        main_window_highlight = tasks.size() - 1;
      } else {
        main_window_highlight--;
      }
      break;

    case KEY_DOWN:
      if (main_window_highlight == tasks.size() - 1) {
        main_window_highlight = 0;
      } else {
        main_window_highlight++;
      }
      break;

    default:
      break;
    }

    // If enter key is pressed
    if (main_window_choice == 10) {
      wrefresh(mainWin);
      renderActionWin();
      return main_window_highlight;
    }
  }
}
