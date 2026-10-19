# Project 01: Command-Line Task Manager

Your goal is to build a terminal application that lets a user manage a list of tasks. Treat this like a small software engineering assignment: define requirements, design the program, implement it, test it, and then add persistence.

Since you already have programming experience, the focus isn't on learning what a loop is. It's on learning how to structure a C++ program, work with its standard library, handle invalid input, and write reliable code.

## Functional Requirements

### 1. User Stories

1. Adding Tasks

As a user, I want to add tasks to my task manager in order to create a list of tasks to keep track of.

The user can easily add tasks that will be marked incomplete when created.

2. Complete Tasks

As a user, I want to mark tasks as complete in order to show what has been completed and no longer need attention to.

The user can easily mark a task as complete to continue on their task list.

3. Delete Tasks

As a user, I want to delete a task in order to remove tasks and clear up space in the task manager.

The user should be able to remove tasks once completed, or even when not completed if task is no longer relevant.

4. List Tasks

As a user, I want to list out all my tasks in order to see all tasks that are yet to be completed.

The user should be able to show all their tasks, completed or incompleted, so that they know what needs to be done if forgotten.

### 2. Functional Requirements

1. Add a task

The user enters a task name and description, which is added to the task list.
- Tasks should be labeled with an ID
- Tasks should have a description attached as well
- Tasks should start as incomplete

2. List all tasks

Display all tasks in a readable format, include ID, Name, Descriptipon
- Clear distinction between incomplete and complete
- Display message when there are no tasks.
- Keep output readable when descriptions have different lengths

3. Complete a Task

The user enters a task ID to mark the corresponding task as completed
- Completing tasks should only work for existing IDs
- Completing a task twice should produce a sensible message
- Completing a task must not remove it from the list

4. Delete a Task

The user enters a task ID to remove it
- Only the task with that ID should be deleted.
- Invalid IDs must not affect any task.
- Display a confirmation message after a successful deletion

5. Exit the application

The user can quit from the main menu at any time. The program should terminate cleanly without crashing or getting stuck in an input loop

### 3. User Interface

Keep the inerface entirely in the terminal. No need for a graphical interface, external libraries, or a database

Example:

```shell
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

Select an option:
```

### 4. Data Model

The general object will be a `Task` struct containing the following information:

- ID: int
- Name: string
- Description: string
- Completed: bool

Tasks can be stored in a `std::vector`

### 5. Input validation and edge cases
  
Test the following situations

Scenario	                                Expected behavior
User enters a valid menu option	          Perform the requested operation
User enters abc instead of a menu number	Show an error and continue
User enters an unsupported menu number	  Reject it and redisplay the menu
User adds an empty description	          Reject it
User enters a nonexistent task ID	        Show an appropriate message
User enters a negative ID	                Reject it or report that it doesn't exist
User lists an empty task list	            Display a friendly message
User deletes the last task	              Leave the list empty
User enters a description with spaces	    Store the entire description
User enters a very long description	      Handle it without crashing or corrupting the list

### 6. Stretch Goal

1. Add file persistence

The program shoudl save tasks to a file, such as `tasks.txt` and load them automatically when it starts

Hint: Use standard library's `std::ifstream` and `std::ofstream`

2. Use CMake to configure and build the project

### 7. Completion Checklist

[ ] Create and compile a C++ project using a repeatable build command.
[ ] Implement the task data structure and task container.
[ ] Implement add, list, complete, delete, and exit operations.
[ ] Use functions to separate responsibilities.
[ ] Handle invalid input without crashing or getting stuck.
[ ] Ensure IDs remain unique after deletions.
[ ] Test empty lists, invalid IDs, and descriptions with spaces.
[ ] Add file saving and loading.
[ ] Verify that task state survives closing and reopening the program.
[ ] Remove duplicated logic and make the code readable.
