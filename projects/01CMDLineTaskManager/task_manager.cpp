#include <iostream>
#include "task_manager.h"



bool addTask(TaskManager& taskManager)
{
    return true;
}

bool completeTask(TaskManager& taskManager, int taskId)
{
    return true;
}

bool deleteTask(TaskManager& taskManager, int taskId)
{
    return true;
}


void displayManager()
{
    std::cout << "====================\n";
    std::cout << "    Task Manager    \n";
    std::cout << "====================\n\n";
}


void displayOptions()
{
    std::cout << "1. Add Task\n";
    std::cout << "2. Complete Task\n";
    std::cout << "3. Remove Task\n";
    std::cout << "4. Quit\n\n";
}

bool handleAction(int option)
{
    switch (option)
    {
        case 1: // Add Task
            handleAddTask();
            return true;
        case 2: // Complete Task
            return true;
        case 3: // Delete Task
            return true;
        case 4: // Quit Program
            return false;
        default: // Invalid Command
            return true;
    }
}


int getValidInput(std::string input)
{
    if (input.size() != 1)
    {
        return 0;
    }

    char ch {input.at(0)};
    if (ch < '1' || ch > '4')
    {
        return 0;
    }

    // Returns as an int if value is between '1' and '4'
    return ch - '0';
}

void handleAddTask()
{
    std::cout << "Task Name: ";
    std::string name {};
    while (name.size() <= 0)
    {
        std::getline(std::cin, name);
    }

    std::cout << "Task Description: ";
    std::string desc {};
    while (desc.size() <= 0)
    {
        std::getline(std::cin, desc);
    }
    
    
}