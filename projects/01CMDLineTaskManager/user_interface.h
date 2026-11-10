#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <fstream>
#include <iostream>
#include <string>
#include "task_manager.h"

/**
 * Display the header for the task mananger.
 */
void displayTitle();


/**
 * Display the options the users can enter to perform actions relating to tasks.
 */
void displayOptions();


/**
 * Return the user's choice for input. Return -1 if the input is out of range or can't be converted into an integer.
 * 
 * @return The user's option as an integer.
 * 
 */
int getInputOption();


/**
 * Gather inputs to add a new task to the TaskManager.
 * 
 * @param manager The TaskManager instance.
 */
void addTaskMenu(TaskManager& manager);

/** 
 * View all tasks with the TaskManager. 
 * 
 * @param manager The TaskManager instance.
 */
void viewTasksMenu(TaskManager& manager);

/**
 * Complete a task with the TaskManager. 
 * 
 * @param manager The TaskManager instance.
 */
void completeTaskMenu(TaskManager& manager);

/**
 * Delete a task with the TaskManager.
 * 
 * @param manager The TaskManager instance.
 */
void deleteTaskMenu(TaskManager& manager);

#endif