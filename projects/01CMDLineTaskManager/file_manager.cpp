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

    // Read the first line which should contain the index of tasks
    int taskIdx {-1};
    inf >> strInput;
    if (strInput.empty())
    {
        taskIdx = std::stoi(strInput);
    }

    while (inf >> strInput)
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
                    task.completed = true;
                    break;
            }
            index++;
        }
        taskManager.tasks.push_back(task);
        
    }
    return taskManager;

}
