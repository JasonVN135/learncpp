#include <fstream>
#include <iostream>
<<<<<<< HEAD
#include <filesystem>
#include "task.h"
#include "task_manager.h"

const std::string FILE_PATH {"tasks.txt"};

int main()
{

    // Create file if it does not exist yet
    if (!std::filesystem::exists(FILE_PATH))
    {
        std::ofstream tmp(FILE_PATH);
        tmp.close();
    }

    // Load the task file
    std::ifstream inf{FILE_PATH};

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

=======
#include "task.h"

int main()
{
    Task task {};
    task.id = 1;
    task.name = "Do Stuff";
    task.description = "Remember to do stuff";
    task.completed = false;
    std::cout << "Hello World!\n";

    std::cout << task.id << " " << task.name << " " << task.description << " " << task.completed << "\n";
>>>>>>> 5e63883 (Started Project 1)
    return 0;
}
