#ifndef TASK_H
#define TASK_H

#include <string>

typedef struct
{
    int id;
    std::string name;
    std::string description;
    bool completed;
} Task;


#endif
