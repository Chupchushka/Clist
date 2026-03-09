#include "task.h"

Task::Task(int task_id, std::string task_content, bool task_completion){
    id = task_id;
    content = task_content;
    completion = task_completion;
}
