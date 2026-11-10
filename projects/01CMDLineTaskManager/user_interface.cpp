#include "user_interface.h"

void displayTitle()
{
    std::cout << "====================\n";
    std::cout << "    Task Manager    \n";
    std::cout << "====================\n\n";
}

void displayOptions()
{
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Complete Task\n";
    std::cout << "4. Delete Task\n";
    std::cout << "5. Quit\n\n";
}


int getInputOption()
{
    std::string userInput {};

    std::cin >> userInput;

    try {
        int choice {0};
        choice = std::stoi(userInput);

        if (choice <= 0 || choice >= 5) {
            return -1;
        }
        return choice;

    } catch (...) {
        return -1;
    }

}


void addTaskMenu(TaskManager& manager)
{

    std::string name {};

    std::cout << "Name: ";
    std::getline(std::cin >> std::ws, name);

    while (name.size() <= 0)
    {
        std::cout << "Enter a valid name for your task: ";
        std::getline(std::cin >> std::ws, name);
    }

    std::string description {};
    std::cout << "Description: ";
    std::getline(std::cin >> std::ws, description);

    while (description.size() <= 0)
    {
        std::cout << "Enter a valid description for your task: ";
        std::getline(std::cin >> std::ws, description);
    }

    addTask(manager, name, description);

    std::cout << "Task \'" << name << "\' has successfully been added.\n";
}

void viewTasksMenu(TaskManager& manager)
{
    viewTasks(manager);
}

void completeTaskMenu(TaskManager& manager)
{
    std::string userInput {};
    std::cout << "Task ID to Complete: ";
    std::getline(std::cin >> std::ws, userInput);

    try {
        int taskId {std::stoi(userInput)};
        bool success {completeTask(manager, taskId)};

        if (success) {
            std::cout << "Task Completed\n";
        }
        else {
            std::cout << "Unable to find Task " << taskId << "\n";
        }
    }
    catch (...) {
        std::cout << "Task ID must be an Integer.\n";
    }
}

void deleteTaskMenu(TaskManager& manager)
{
    std::string userInput {};
    std::cout << "Task ID to Delete: ";
    std::getline(std::cin >> std::ws, userInput);

    try {
        int taskId {std::stoi(userInput)};
        bool success {deleteTask(manager, taskId)};

        if (success) {
            std::cout << "Task Deleted\n";
        }
        else {
            std::cout << "Unable to find Task " << taskId << "\n";
        }
    }
    catch (...) {
        std::cout << "Task ID must be an Integer.\n";
    }
}
