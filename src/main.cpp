#include "database.h"
#include "tui.h"
#include <ncurses.h>
#include <string>
#include <vector>

TUI ui;
Database db;

void makeAction(std::string choice){
    if (choice == "Edit"){
        std::cout << "LOG: Edit call" << std::endl;
    }
    else if (choice == "Mark complete"){
        std::cout << "LOG: Mark complete call" << std::endl;
    }
    else if (choice == "Delete"){
        std::cout << "LOG: Delete call" << std::endl;
    }
}

int main() {
  db.createDatabase();
  for (int i = 0; i <= 50; i++) {
    db.createTask("task number " + std::to_string(i));
  }

  // Screen setup
  initscr();
  cbreak();
  noecho();

  int highlighted_task_index;
  std::string choice;

  while (true)
  {
    std::vector<std::string> tasks = db.getColumn("task_content");

    highlighted_task_index = ui.renderMainWin(tasks);
    choice = ui.renderActionWin();
    makeAction(choice);
  }


  return 0;
}
