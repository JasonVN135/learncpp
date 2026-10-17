#ifndef TASK_H
#define TASK_H

#include <string_view>

typedef struct
{
    int id;
    std::string_view name;
    std::string_view description;
    bool completed;
} Task;


#endif
