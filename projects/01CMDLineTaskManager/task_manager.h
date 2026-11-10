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

/**
 * Create and add a task to the task manager.
 * 
 * @param taskManager The task manager to add a task in.
 * @param name The name of the task
 * @param description The description of the task
 */
void addTask(TaskManager& taskManager, std::string name, std::string description);

void viewTasks(TaskManager& taskManager);

bool completeTask(TaskManager& taskManager, int taskId);

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
 */
std::string getTaskAsText(Task& task);


#endif