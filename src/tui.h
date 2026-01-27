#pragma once
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "task.h"

class TUI {

private:
  int yMax, xMax;
  // Action window variables
  int choice;
  int highlight = 0;
  int size = sizeof(choices) / sizeof(choices[0]);

  // Main window variables
  int main_window_choice;
  int main_window_highlight = 0;

  WINDOW *mainWin;
  WINDOW *menuWin;

public:
  std::string choices[3] = {"Edit", "Mark complete", "Delete"};

  std::string renderActionWin();
  int renderMainWin(std::vector<Task> tasks);
};
