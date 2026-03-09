#include "database.h"
#include "task.h"
#include "tui.h"
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>
#include <vector>

TUI ui;
Database db;

void makeAction(std::string choice, Task task) {
  if (choice == "Edit") {
    db.editTask(std::to_string(task.id),"task_content", ui.renderEditWin());
  } else if (choice == "Mark complete") {
    db.editTask(std::to_string(task.id), "task_completion",
                std::to_string(!task.completion));
  } else if (choice == "Delete") {
    db.deleteTask(std::to_string(task.id));
    ui.main_window_highlight--;
  }
}

int main() {
  
  // Check if the terminal emulator support colors
  if (!has_colors()) {
    std::cerr << "Warning! Your terminal emulator doesn't support colors. It may cause some issues while rendering." << std::endl;
  }

  db.createDatabase();
  std::vector<Task> tasks;

  // Screen setup
  initscr();
  cbreak();
  noecho();
  start_color();

  int returned_id;
  std::string choice;

  while (true) {
    std::vector<std::string> tasks_content = db.getColumn("task_content");
    std::vector<std::string> tasks_id = db.getColumn("task_id");
    std::vector<bool> task_completion = db.getIntColumn("task_completion");

    tasks.clear();

    for (int i = 0; i < tasks_content.size(); i++) {
      tasks.push_back(Task(std::stoi(tasks_id[i]), tasks_content[i], task_completion[i]));
    }

    returned_id = ui.renderMainWin(tasks);

    // If a was pressed
    if (returned_id == -1) {
      db.createTask(ui.renderEditWin());
      ui.main_window_highlight = tasks.size();
    } else if (returned_id == -2) {
      endwin();
      break;
    }
    else {
      // Find the task that is highlighted & make action
      for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == returned_id) {
          choice = ui.renderActionWin();
          makeAction(choice, tasks[i]);
          break;
        }
      }
    }
  }
  return 0;
}
