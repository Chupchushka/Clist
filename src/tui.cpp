#include "tui.h"
#include "task.h"
#include <ncurses.h>
#include <string>

#define ACALL -1

std::string TUI::renderActionWin() {
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  menuWin = newwin(5, xMax - 12, yMax - 6, 5);

  box(menuWin, 0, 0);
  refresh();
  wrefresh(menuWin);
  keypad(menuWin, true);

  // Keyboard input
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

      return choices[highlight];
    }
  }
}

std::string TUI::renderEditWin(){
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  editWin = newwin(5, xMax - 12, yMax - 6, 5);

  box(editWin, 0, 0);
  refresh();
  wrefresh(editWin);
  keypad(editWin, true);
  echo();

  mvwprintw(editWin, 2, 1, "New content: ");
  wrefresh(editWin);

  char buffer[256];
  mvwgetnstr(editWin, 2, 14, buffer, 255);
  
  // Cleaning window
  noecho();
  wclear(editWin);
  wrefresh(editWin);
  delwin(editWin);
  
  return std::string(buffer);
}

int TUI::renderMainWin(std::vector<Task> tasks) {
  // Get yMax & xMax
  getmaxyx(stdscr, yMax, xMax);

  // Window setup
  mainWin = newwin(yMax - 7, xMax - 6, 1, 3);
  box(mainWin, 0, 0);
  refresh();
  wrefresh(mainWin);
  keypad(mainWin, TRUE);

  // Calculate visible area (subtract 2 for top/bottom borders, 2 for padding)
  int visible_height = yMax - 7 - 4;
  int scroll_offset = 0;

  while (true) {
    // Clear window content (preserve border)
    for (int i = 1; i < yMax - 8; i++) {
      wmove(mainWin, i, 1);
      wclrtoeol(mainWin);
    }
    box(mainWin, 0, 0);

    // Adjust scroll offset to keep highlighted item visible
    if (main_window_highlight < scroll_offset) {
      scroll_offset = main_window_highlight;
    }
    if (main_window_highlight >= scroll_offset + visible_height) {
      scroll_offset = main_window_highlight - visible_height + 1;
    }

    // Print only visible tasks
    int visible_end =
        std::min(scroll_offset + visible_height, (int)tasks.size());
    for (int i = scroll_offset; i < visible_end; i++) {
      int row = i - scroll_offset + 2;

      if (i == main_window_highlight) {
        wattron(mainWin, A_REVERSE);
      }
      mvwprintw(mainWin, row, 3, tasks[i].content.c_str());
      wattroff(mainWin, A_REVERSE);
    }

    // Show scroll indicator
    if (tasks.size() > visible_height) {
      mvwprintw(mainWin, yMax - 8, xMax - 15, "[%d/%d]",
                main_window_highlight + 1, (int)tasks.size());
    }

    wrefresh(mainWin);
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
    case KEY_PPAGE: // Page Up
      main_window_highlight =
          std::max(0, main_window_highlight - visible_height);
      break;
    case KEY_NPAGE: // Page Down
      main_window_highlight = std::min((int)tasks.size() - 1,
                                       main_window_highlight + visible_height);
      break;
    case 'a':
      return ACALL;
      break;
    default:
      break;
    }

    // If enter key is pressed
    if (main_window_choice == 10) {
      wrefresh(mainWin);
      return tasks[main_window_highlight].id;
    }
  }
}
