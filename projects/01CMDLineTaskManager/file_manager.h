#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "task.h"
#include "task_manager.h"

const std::string FILE_PATH {"tasks.txt"};

/**
 * Read from the task file and retrieve all tasks. Place all tasks in the TaskManager. Return if the action was successful.
 * 
 * @param manager The TaskManager to write tasks into
 * 
 * @return If the read was successful.
 * 
 */
bool readTaskFile(TaskManager& manager);


/**
 * With the task manager, write to the task file to record and save information.
 * 
 * @param manager The TaskManager to retrieve tasks from.
 */
void writeTaskToFile(TaskManager& manager);

#endif