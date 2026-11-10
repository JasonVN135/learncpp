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

}

void viewTasksMenu(TaskManager& manager)
{
    viewTasks(manager);
}

void completeTaskMenu(TaskManager& manager)
{
    
}

void deleteTaskMenu(TaskManager& manager)
{
    
}
