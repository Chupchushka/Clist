#include "database.h"
#include "task.h"
#include "tui.h"
#include <ncurses.h>
#include <string>
#include <vector>

TUI ui;
Database db;

void makeAction(std::string choice, int task_id) {
  if (choice == "Edit") {
    db.editTask(std::to_string(task_id), ui.renderEditWin());
    std::cout << "LOG: Edit call" << std::endl;
  } else if (choice == "Mark complete") {
    std::cout << "LOG: Mark complete call" << std::endl;
  } else if (choice == "Delete") {
    std::cout << "LOG: Delete call" << std::endl;
    db.deleteTask(std::to_string(task_id));
  }
}

int main() {
  db.createDatabase();
  for (int i = 0; i <= 50; i++) {
    db.createTask("task number " + std::to_string(i));
  }

  db.editTask(std::to_string(2), "privet");

  std::vector<Task> tasks;

  // Screen setup
  initscr();
  cbreak();
  noecho();

  int highlighted_task_index;
  std::string choice;

  while (true) {
    std::vector<std::string> tasks_content = db.getColumn("task_content");
    std::vector<std::string> tasks_id = db.getColumn("task_id");

    tasks.clear();

    for (int i = 0; i < tasks_content.size(); i++) {
      tasks.push_back(Task(std::stoi(tasks_id[i]), tasks_content[i]));
    }

    highlighted_task_index = ui.renderMainWin(tasks);

    if (highlighted_task_index == -1) {
      db.createTask("New task");
      ui.main_window_highlight = tasks.size();
    } else {
      choice = ui.renderActionWin();
      makeAction(choice, highlighted_task_index);
    }
  }

  return 0;
}
