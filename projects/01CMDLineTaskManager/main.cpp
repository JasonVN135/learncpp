#include <fstream>
#include <iostream>
#include <filesystem>
#include "task.h"
#include "task_manager.h"
#include "file_manager.h"
#include "user_interface.h"


int main()
{

    // Create file if it does not exist yet
    if (!std::filesystem::exists(FILE_PATH))
    {
        std::ofstream tmp(FILE_PATH);
        tmp << 0;
        tmp.close();
    }

    // Load the task file
    TaskManager manager {readTaskFile()};

    // Display Program
    displayTitle();

    int choice {0};
    
    // While the user doesn't quit
    while (choice != 4)
    {
        displayOptions();

        // The choice the user selects (-1 if invalid)
        choice = getInputOption();

        if (choice == -1)
        {
            std::cout << "Invalid input, enter a valid option.\n\n";
            continue;
        }


            switch (choice)
            {
                case 1: // Add Task
                    break;
                case 2: // View Tasks
                    viewTasksMenu(manager);
                    break;
                case 3: // Complete Task
                    break;
                case 4: // Delete Task
                    break;
                case 5: // Quit Program
                    break;
                default: // Invalid Command
                    break;
            }
        
    } // User has quit, ending program

    Task task;
    // Save Tasks

    return 0;
}
