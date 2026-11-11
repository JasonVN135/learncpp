# Task Manager Test Cases

## Software Requirements

1. C++20 or higher.

## Shared Preconditions

### SP-01: Empty Task List

The following setup must be completed before executing any test case that references SP-01.

1. Ensure `tasks.txt` is empty or doesn't exist.
2. Run the command `./main`

### SP-02: Task list with existing tasks

The following setup must be completed before executing any test case that references SP-02.

1. Complete SP-01
1. Type `1` then press `Enter`
2. Type `Laundry` then press `Enter`
3. Type `Fold today's laundry` then press `Enter`
4. Type `1` then press `Enter`
5. Type `Dishes` then press `Enter`
6. Type `Rinse and dry dishes` then press `Enter`
7. Type `1` then press `Enter`
8. Type `Vacuum` then press `Enter`
9. Type `Vacuum the carpets` then press `Enter`

### SP-03: Task list with completed tasks

The following setup must be completed before executing any test case that references SP-03.

1. Complete SP-02 
2. Type `3` then press `Enter`
3. Type `0` then press `Enter`

### SP-04: Tasks with deleted entry

The following setup must be completed before executing any test case that references SP-04.

1. Complete SP-03
2. Type `4` then press `Enter`
3. Type `1` then press `Enter`

## Test Cases

### TC Template

**Status:** The status

**Description:** The description

**Preconditions:**
- A condition that must be met

**Steps:**:
1. Step to perform

**Expected Results:**
- What to expect

**Actual Results:**
-  What you got

### TC-01: Open the program with no `tasks.txt` file

**Status:** Complete

**Description:** The user must be able to open the program without a tasks.txt file.

**Preconditions:**
- User is in the current project directory.
- `tasks.txt` file can not be present in the directory.

**Steps:**:
1. Run the command `make`
2. Run the command `./main`
3. Observe Results
4. Press `Ctrl + C` to force close the program

**Expected Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

**Actual Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

### TC-02: Open the program with an empty `tasks.txt` file

**Status:** Complete

**Description:** The user must be able to open the program with an empty tasks.txt file.

**Preconditions:**
- User is in the current project directory.
- `tasks.txt` must exist but be empty.

**Steps:**:
1. Run the command `make`
2. Run the command `./main`
3. Observe Results
4. Press `Ctrl + C` to force close the program

**Expected Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

**Actual Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

### TC-03: Open the program with a `tasks.txt` file that holds a single number

**Status:** Incomplete

**Description:** The user must be able to open the program with a tasks.txt file with a single number.

**Preconditions:**
- User is in the current project directory.
- `tasks.txt` has the following text:

```
0
```

**Steps:**:
1. Run the command `make`
2. Run the command `./main`
3. Observe Results
4. Press `Ctrl + C` to force close the program

**Expected Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

**Actual Results:**
- The terminal prints out the following:

```
====================
    Task Manager    
====================

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 
```

### TC-04: Incorrectly formatted tasks.txt file.

**Status:** Incomplete

**Description:** The program should gracefully fail if the `tasks.txt` file is improperly edited and not formatted correctly.

**Preconditions:**
- User is in the current project directory.
- `tasks.txt` has the following text:

```
1
,Laundry,Fold the laundry,0
```

**Steps:**:
1. Run the command `make`
2. Run the command `./main`
3. Observe Results

**Expected Results:**
- The terminal prints out the following:

```
Unable to open `tasks.txt`
```

**Actual Results:**
- The terminal prints out the following:

```
terminate called after throwing an instance of 'std::invalid_argument'
  what():  stoi
Aborted
```

### TC-05: Add a task

**Status:** Incomplete

**Description:** The user can add a task with a name and description.

**Preconditions:**
- SP-01 completed

**Steps:**:
1. Run the command `./main`
2. Type `1` then press `Enter`
3. Type `Laundry` then press `Enter`
4. Type `Fold today's laundry` then press `Enter`

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 1

Name: Laundry
Description: Fold today's laundry
Task 'Laundry' has successfully been added.
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-06: Add a task with no Name

**Status:** Incomplete

**Description:** The user will not be able to add a task unless the task has a name. The user will be reprompted to enter a name.

**Preconditions:**
- SP-01 completed

**Steps:**:
1. Run the command `./main`
2. Type `1` then press `Enter`
3. Type nothing and press `Enter`
4. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 1

Name: 
Enter a valid name for your task: 
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-07: Add a task with no Description

**Status:** Incomplete

**Description:** The user will not be able to add a task unless the task has a description. The user will be reprompted to enter a description.

**Preconditions:**
- SP-01 completed

**Steps:**:
1. Run the command `./main`
2. Type `1` then press `Enter`
3. Type `Laundry` then press `Enter`
4. Type nothing and press `Enter`
5. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 1

Name: Laundry
Description: 
Enter a valid description for your task: 
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-07: Add a task with a comma in the name

**Status:** Incomplete

**Description:** The user will not be able to add a task with a comma in the name. The user will be reprompted to type a new name.

**Preconditions:**
- SP-01 completed

**Steps:**:
1. Run the command `./main`
2. Type `1` then press `Enter`
3. Type `Laundry, fold, and hang` then press `Enter`
4. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 1

Name: Laundry, fold, and hang
Name cannot contain a comma: 
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-08: Add a task with a comma in the description

**Status:** Incomplete

**Description:** The user will not be able to add a task with a comma in the description. The user will be reprompted to type a new description.

**Preconditions:**
- SP-01 completed

**Steps:**:
1. Run the command `./main`
2. Type `1` then press `Enter`
3. Type `Laundry` then press `Enter`
4. Type `Do laundry, then fold, and finally hang` then press `Enter`
5. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 1

Name: Laundry
Description: Do laundry, then fold, and finally hang
Description cannot contain a comma: 
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-09: View tasks

**Status:** Incomplete

**Description:** The user can view all tasks.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `2` and press `Enter
2. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 2

ID  Status Name                 Description
0   [ ]    Laundry              Fold today's Laundry
1   [ ]    Dishes               Rinse and dry dishes
2   [ ]    Vacuum               Vacuum the carpet
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-10: Complete incomplete task

**Status:** Incomplete

**Description:** The user can complete a task.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `3` and press `Enter`
2. Type `0` and press `Enter`
3. Type `2` and press `Enter`
4. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 3

Task ID to Complete: 0
Task Completed

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 2

ID  Status Name                 Description
0   [x]    Laundry              Fold today's Laundry
1   [ ]    Dishes               Rinse and dry dishes
2   [ ]    Vacuum               Vacuum the carpet
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-11: Complete completed task

**Status:** Incomplete

**Description:** The user will be alerted when they attempt to complete an already complete task.

**Preconditions:**
- SP-03 completed

**Steps:**:
1. Type `3` and press `Enter`
2. Type `0` and press `Enter`
3. Type `2` and press `Enter`
4. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 3

Task ID to Complete: 0
The task has already been completed

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

Enter Option: 2

ID  Status Name                 Description
0   [x]    Laundry              Fold today's Laundry
1   [ ]    Dishes               Rinse and dry dishes
2   [ ]    Vacuum               Vacuum the carpet
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-12: ID does not exist for completion

**Status:** Incomplete

**Description:** The user can not try to complete an ID that does not exist in the manager.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `3` and press `Enter`
2. Type `9` and press `Enter`
3. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 3

Task ID to Complete: 9
Unable to find Task 9
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-13: Invalid characters for completion ID

**Status:** Incomplete

**Description:** The user cannot enter invalid characters for completion when requested for the Task ID.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `3` and press `Enter`
2. Type `apple` and press `Enter`
3. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 3

Task ID to Complete: apple
Task ID must be an Integer
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-14: Delete task

**Status:** Incomplete

**Description:** The user can delete a task from the task list.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `4` and press `Enter`
2. Type `0` and press `Enter`
3. Type `2` and press `Enter`
4. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 4

Task ID to Delete: 0
Task Deleted

1. Add Task
2. View Tasks
3. Complete Task
4. Delete Task
5. Quit

ID  Status Name                 Description
1   [ ]    Dishes               Rinse and dry dishes
2   [ ]    Vacuum               Vacuum the carpet
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-15: ID does not exist for completion

**Status:** Incomplete

**Description:** The user can not try to delete an ID that does not exist in the manager.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `4` and press `Enter`
2. Type `9` and press `Enter`
3. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 4

Task ID to Delete: 9
Unable to find Task 9
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-16: Invalid characters for deleting ID

**Status:** Incomplete

**Description:** The user cannot enter invalid characters for deletion when requested for the Task ID.

**Preconditions:**
- SP-02 completed

**Steps:**:
1. Type `4` and press `Enter`
2. Type `apple` and press `Enter`
3. Observe results

**Expected Results:**
- The terminal prints out the following:

```
Enter Option: 3

Task ID to Delete: apple
Task ID must be an Integer
```

**Actual Results:**
- The terminal prints out the following:

```

```

### TC-17: Successful quit with no tasks

**Status:** Incomplete

**Description:** The user can quit the program at the home interface without having tasks.

**Preconditions:**
- SP-01 completed

**Steps:**
1. Type `5` and press `Enter`
2. Observe `tasks.txt` file.

**Expected Results:**

Terminal:
```
Enter Option: 5

Closing Task Manager
```

`tasks.txt`:
```
0
```

**Actual Results:**

### TC-18: Successful quit with tasks

**Status:** Incomplete

**Description:** The user can quit the program at the home interface with tasks still present.

**Preconditions:**
- SP-02 completed

**Steps:**
1. Type `5` and press `Enter`
2. Observe `tasks.txt` file.

**Expected Results:**

Terminal:
```
Enter Option: 5

Closing Task Manager
```

`tasks.txt`:
```
3
0,Laundry,Fold today's laundry,0
1,Dishes,Rinse and dry dishes,0
2,Vacuum,Vacuum the carpets,0
```

**Actual Results:**

### TC-19: Successful quit with tasks that are completed.

**Status:** Incomplete

**Description:** The user can quit the program at the home interface with tasks still present and some completed.

**Preconditions:**
- SP-03 completed

**Steps:**
1. Type `5` and press `Enter`
2. Observe `tasks.txt` file.

**Expected Results:**

Terminal:
```
Enter Option: 5

Closing Task Manager
```

`tasks.txt`:
```
3
0,Laundry,Fold today's laundry,1
1,Dishes,Rinse and dry dishes,0
2,Vacuum,Vacuum the carpets,0
```

**Actual Results:**

### TC-19: Successful quit with tasks that are deleted.

**Status:** Incomplete

**Description:** The user can quit the program at the home interface with tasks still present and some deleted.

**Preconditions:**
- SP-04 completed

**Steps:**
1. Type `5` and press `Enter`
2. Observe `tasks.txt` file.

**Expected Results:**

Terminal:
```
Enter Option: 5

Closing Task Manager
```

`tasks.txt`:
```
3
0,Laundry,Fold today's laundry,1
2,Vacuum,Vacuum the carpets,0
```

**Actual Results:**
