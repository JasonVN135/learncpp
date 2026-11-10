#include <iostream>
#include "task_manager.h"


void addTask(TaskManager& taskManager, std::string name, std::string description)
{
    Task task {taskManager.index, name, description, false};
    taskManager.tasks.push_back(task);
}

void viewTasks(TaskManager& taskManager)
{
    for (Task task : taskManager.tasks)
    {
        displayTask(task);
    }
}

bool completeTask(TaskManager& taskManager, int taskId)
{
    return true;
}

bool deleteTask(TaskManager& taskManager, int taskId)
{
    return true;
}

void displayTask(Task& task)
{

    std::string completedSign {"[ ]"};

    if (task.completed)
    {
        completedSign = "[x]";
    }

    std::cout << task.id << " " << task.name << " " << completedSign << "\n";
}

std::string getTaskAsText(Task& task)
{
    std::string idStr {"" + task.id};
    std::string completed = (task.completed) ? "1" : "0";

    std::string taskStr {"" + idStr + "," + task.name + "," + task.description + "," + completed};

    return taskStr;
}