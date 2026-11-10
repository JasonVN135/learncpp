
#include "task_manager.h"


void addTask(TaskManager& taskManager, std::string name, std::string description)
{
    int idx = taskManager.index;
    Task task {idx, name, description, false};
    taskManager.tasks.push_back(task);
    taskManager.index++;
}

void viewTasks(TaskManager& taskManager)
{
    for (Task& task : taskManager.tasks)
    {
        displayTask(task);
    }
}

bool completeTask(TaskManager& taskManager, int taskId)
{

    for (Task& task : taskManager.tasks)
    {
        if (task.id == taskId)
        {
            task.completed = true;
            return true;
        }
    }
    return false;
}

bool deleteTask(TaskManager& taskManager, int taskId)
{
    for (std::size_t i {0}; i < taskManager.tasks.size(); i++)
    {
        Task& task {taskManager.tasks.at(i)};
        if (task.id == taskId) {
            taskManager.tasks.erase(taskManager.tasks.begin() + i);
            return true;
        }
    }
    return false;
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
    std::string completed = (task.completed) ? "1" : "0";

    std::string taskStr {std::to_string(task.id) + "," + task.name + "," + task.description + "," + completed};
    return taskStr;
}