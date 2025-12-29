#include "database.h"
#include <ncurses.h>
#include <string>

int main() {
  // Screen setup
  initscr();
  cbreak();
  noecho();

  // Get max y & x
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  // Setup menu Window
  WINDOW *menuWin = newwin(6, xMax - 12, yMax - 8, 5);
  box(menuWin, 0, 0);
  refresh();
  wrefresh(menuWin);

  keypad(menuWin, true);

  std::string choices[3] = {"Edit", "Mark complete", "Delete"};
  int choice;
  int highlight = 0;
  int size = sizeof(choices) / sizeof(choices[0]);

  while (1) {

    // Prints the list and highlights the chose options
    for (int i = 0; i < size; i++) {
      if (i == highlight) {
        wattron(menuWin, A_REVERSE);
      }
      mvwprintw(menuWin, i + 1, 1, choices[i].c_str());
      wattroff(menuWin, A_REVERSE);
    }

    choice = wgetch(menuWin);

    // Change highlight option depend the key pressed
    switch (choice) {
    case KEY_UP:
      highlight--;
      break;
    case KEY_DOWN:
      highlight++;
      break;
    default:
      break;
    }

    if (choice == 10) {
      // Logic when chosing the option
      break;
    }
  }

  endwin();
  return 0;
}
