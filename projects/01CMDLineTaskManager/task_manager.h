#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include "task.h"

typedef struct
{
    std::vector<Task> tasks;
    int index;
} TaskManager;


// Task Functions


bool addTask(TaskManager& taskManager);

bool completeTask(TaskManager& taskManager, int taskId);

bool deleteTask(TaskManager& taskManager, int taskId);


// Display Functions

/**
 * @brief Displays the program's name on start up
 */
void displayManager();


/**
 * @brief Displays the options the user can perform in the program
 */
void displayOptions();

// Handle Inputs

/**
 * @brief Perform the necessary action given the user's input.
 * 
 * @param option The option the user enters
 * @return Return if the program should continue running or close
 */
bool handleAction(int option);


/**
 * @brief Returns if the input the user entered is a valid input
 * 
 * @return the command as an `int` if valid, 0 if invalid
 */
int getValidInput(std::string input);


/**
 * 
 */
void handleAddTask();


/**
 * 
 */
void handleCompleteTask();


/**
 * 
 */
void handleDeleteTask();


#endif