#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "task.h"
#include "task_manager.h"

const std::string FILE_PATH {"tasks.txt"};

TaskManager readTaskFile();

#endif