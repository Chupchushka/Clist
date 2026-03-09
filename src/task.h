#pragma once
#include <string.h>
#include <iostream>

class Task{
    private:
    public:
        int id;
        std::string content;
        bool completion;

    Task(int task_id, std::string task_content, bool completion);
};
