#include "file_manager.h"

TaskManager readTaskFile()
{
    std::ifstream inf{FILE_PATH};

    TaskManager taskManager;
    
    // If file doesn't exist, exit
    if (!inf)
    {
        std::cerr << "Unable to read file: " << FILE_PATH << "\n";
        return taskManager;
    }

    std::string strInput{};
    int taskIdx {-1};

    while (inf >> strInput)
    {
        // Read the first line which should contain the index of tasks
        if (taskIdx == -1)
        {
            taskIdx = strInput.at(0) - '0';
        }
        else
        // Read and parse each line to create the tasks
        {
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
                        task.id = parsed.at(0) - '0';
                        break;
                    case 1:
                        task.name = parsed;
                        break;
                    case 2:
                        task.description = parsed;
                        break;
                    case 3:
                        task.completed = true;
                        break;
                }
                index++;
            }
            taskManager.tasks.push_back(task);
        }
    }
    return taskManager;

}
