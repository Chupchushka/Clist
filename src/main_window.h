#pragma once
#include <ncurses.h>
#include <string>
#include <vector>

class MainWindow {
private:
  int yMax, xMax;
  int choice;
  int highlight = 0;

  WINDOW *mainWin;

public:
  int renderMainWin(std::vector<std::string> tasks);
};
