#include <fstream>
#include <iostream>
#include <filesystem>
#include "task.h"
#include "task_manager.h"
#include "file_manager.h"

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
    displayManager();

    bool running {true};
    
    // While the user doesn't quit
    while (running)
    {
        displayOptions();

        // Retrieve user option
        std::string input;
        std::getline(std::cin, input);

        int inputResult {getValidInput(input)};

        if (!inputResult)
        {
            std::cout << "Invalid input, enter a valid option.\n\n";
            continue;
        }
        
        // Handle user option
        running = handleAction(inputResult);

    } // User has quit, ending program

    Task task;
    // Save Tasks
    std::cout << FILE_PATH << "\n";

    return 0;
}
