#pragma once
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <vector>
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

  WINDOW *mainWin;
  WINDOW *menuWin;

  void printVisibleTasks(int scroll_offset, int visible_end, std::vector<Task> tasks);

public:
  std::string choices[3] = {"Edit", "Mark complete", "Delete"};
  std::string renderActionWin();
  int renderMainWin(std::vector<Task> tasks);
  int main_window_highlight = 0;
};
