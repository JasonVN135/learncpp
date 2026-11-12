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

    std::cout << "Enter Option: ";

    std::getline(std::cin >> std::ws, userInput);

    std::cout << "\n";

    try {
        int choice {0};
        choice = std::stoi(userInput);

        if (choice <= 0 || choice >= 6) {
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
    std::getline(std::cin, name);

    // Retrieve a valid name
    while (true)
    {
        if (name.find_first_not_of(' ') == std::string::npos)
        {
            std::cout << "Enter a valid name for your task: ";
        }
        else if (name.find(',') != std::string::npos)
        {
            std::cout << "Name cannot contain a comma: ";
        }
        else
        {
            break; // Exit out of loop
        }
        std::getline(std::cin, name);
    }

    std::string description {};
    std::cout << "Description: ";
    std::getline(std::cin, description);

    // Retrieve a valid description
    while (true)
    {
        if (description.find_first_not_of(' ') == std::string::npos)
        {
            std::cout << "Enter a valid description for your task: ";
        }
        else if (description.find(',') != std::string::npos)
        {
            std::cout << "Description cannot contain a comma: ";
        }
        else
        {
            break; // Exit out of loop
        }
        std::getline(std::cin, description);
    }

    addTask(manager, name, description);
    std::cout << "Task \'" << name << "\' has successfully been added\n";
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
        std::cout << "Task ID must be an Integer\n";
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
        std::cout << "Task ID must be an Integer\n";
    }
}
