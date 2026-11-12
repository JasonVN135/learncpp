#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <format>
#include <vector>
#include <iostream>
#include <string>
#include "task.h"

typedef struct
{
    std::vector<Task> tasks;
    int index;
} TaskManager;


/**
 * Create and add a task to the task manager.
 * 
 * @param taskManager The TaskManager to add a task in.
 * @param name The name of the task
 * @param description The description of the task
 */
void addTask(TaskManager& taskManager, std::string name, std::string description);

/**
 * View all tasks.
 * 
 * @param taskManager The TaskManager to read tasks from
 */
void viewTasks(TaskManager& taskManager);

/**
 * Complete a selected task.
 * 
 * @param taskManager The TaskManager to get the task from
 * @param taskId The Id of the task to complete.
 * 
 * @return If the task was successfully completed
 */
int completeTask(TaskManager& taskManager, int taskId);

/**
 * Delete a selected task.
 * 
 * @param taskManager The TaskManager to get the task from
 * @param taskId The Id of the task to delete.
 * 
 * @return If the task was successfully deleted
 */
bool deleteTask(TaskManager& taskManager, int taskId);

/** 
 * Output the task for the menu.
 * 
 * @param task The task to display
*/
void displayTask(Task& task);

/**
 * Return the task in a format to be stored in a text document.
 * 
 * @param task The task to write
 * 
 * @return The task in a formatted string.
 */
std::string getTaskAsText(Task& task);


#endif