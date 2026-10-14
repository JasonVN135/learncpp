#include <fstream>
#include <iostream>
#include <filesystem>
#include "task.h"


const std::string FILE_PATH {"tasks.txt"};

/**
 * @brief Displays the program's name on start up
 */
void displayManager()
{
    std::cout << "====================\n";
    std::cout << "    Task Manager    \n";
    std::cout << "====================\n\n";
}

/**
 * @brief Displays the options the user can perform in the program
 */
void displayOptions()
{
    std::cout << "1. Add Task\n";
    std::cout << "2. Complete Task\n";
    std::cout << "3. Remove Task\n";
    std::cout << "4. Quit\n\n";
}

/**
 * @brief Perform the necessary action given the user's input.
 * 
 * @return Return if the program should continue running or close
 */
bool handleAction(int option)
{
    switch (option)
    {
        case 1: // Add Task
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

/**
 * @brief Returns if the input the user entered is a valid input
 * 
 * @return the command as an `int` if valid, 0 if invalid
 */
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

    // Save Tasks
    std::cout << FILE_PATH << "\n";

    return 0;
}
