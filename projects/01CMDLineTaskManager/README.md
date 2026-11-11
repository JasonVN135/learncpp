# Command Line Task Manager

The goal of this project is to build a terminal application that can be used to track tasks that must be completed. We must define requirements, design the program, implement it, test it, and then add persistence.

## 1. Functional Requirements

1. Add a task

The user enters a task description, which is added to the task list
- Descriptions cannot be empty or consist only of whitespace
- Each task receives a unique ID
- New tasks start with an incomplete status

2. List all tasks

Display all tasks in a readable format, including their ID, description, and status
- Clearly distinguish completed from incompleted tasks
- Display a helpful message when there are no tasks
- Keep the output readable when descriptions have different lengths

3. Complete a task

The user enters a task DI to mark the corresponding task as completed
- Only an existing ID can be modified
- Completing a task twice should produce a sensible message
- Completing a task must not remove it from the list

4. Delete a task

The user enters a task ID to remove it
- Only the task with that ID should be deleted
- Invalid IDs must not affect any task
- Display a confirmation message after a successful deletion

5. Exit the application

The user can quit from the main menu at any time. The program should terminate cleanly without crashing or getting stuck in an input loop. 

Data also must persist, meaning when relaunching the application, previous tasks that remained should still be present.

## 2. User Interface

The interface will exist entirely in the terminal. Not need for graphical user interfaces, extended libraries, or databases.

Data can be kept in a text file or csv.

Example:

```
=============================
       TASK MANAGER
=============================
1. Add task
2. List tasks
3. Complete task
4. Delete task
5. Exit

Select an option: 2

ID   STATUS       DESCRIPTION
1    [ ]          Learn C++ classes
2    [x]          Set up compiler
3    [ ]          Build task manager
```


## 3. Completion Checklist


[x] Create and compile a C++ project using a repeatable build command.
[x] Implement the task data structure and task container.
[x] Implement add, list, complete, delete, and exit operations.
[x] Use functions to separate responsibilities.
[x] Handle invalid input without crashing or getting stuck.
[x] Ensure IDs remain unique after deletions.
[ ] Test empty lists, invalid IDs, and descriptions with spaces.
[x] Add file saving and loading.
[ ] Verify that task state survives closing and reopening the program.
[x] Remove duplicated logic and make the code readable.

