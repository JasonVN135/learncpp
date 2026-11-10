#include "file_manager.h"

void readTaskFile(TaskManager& manager)
{
    std::ifstream inf{FILE_PATH};
    
    // If file doesn't exist, exit
    if (!inf)
    {
        std::cerr << "Unable to read file: " << FILE_PATH << "\n";
        return;
    }

    std::string strInput{};

    // Read the first line which should contain the index of tasks
    int taskIdx {0};
    std::getline(inf, strInput);
    if (!strInput.empty())
    {
        taskIdx = std::stoi(strInput);
    }
    manager.index = taskIdx;
    
    // Read each task
    while (std::getline(inf, strInput))
    {
        // Read and parse each line to create the tasks
        Task task{};
        // Parse the string by ','
        std::stringstream ss{strInput};
        std::string parsed{};
        int index = 0;
        while(getline(ss, parsed, ','))
        {
            switch (index)
            {
                case 0:
                    task.id = std::stoi(parsed);
                    break;
                case 1:
                    task.name = parsed;
                    break;
                case 2:
                    task.description = parsed;
                    break;
                case 3:
                    task.completed = std::stoi(parsed);
                    break;
            }
            index++;
        }
        manager.tasks.push_back(task);
        
    }\
}

void writeTaskToFile(TaskManager& manager)
{
    std::ofstream of{FILE_PATH};

    of << manager.index << "\n";

    for (Task& task : manager.tasks)
    {
        of << getTaskAsText(task) << "\n";
    }

    of.close();
}