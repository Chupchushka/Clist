#pragma once
#include <iostream>
#include <ncurses.h>
#include <string.h>

class TUI {

private:
  int yMax, xMax;
  int choice;
  int highlight = 0;
  int size = sizeof(choices) / sizeof(choices[0]);

  WINDOW *menuWin;

public:
  std::string choices[3] = {"Edit", "Mark complete", "Delete"};
  int createMenuBar();
};
