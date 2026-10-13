# 3.1 - Syntax and semantic errors

## Notes

Generally two types of errors: Syntax errors and semantic errors (logic errors)

### Syntax Errors

**Syntax Errors**: Ocurs when you write a statement that is not valid according to the grammar of the C++ language
- Missing semicolons
- Mismatched parentheses or braces

**Semantic errors**: An error in meaning. When a statement is syntactically valid, but either violates other rules of the language, or doesn't do what the programmer intended
- Some caught by the compiler
- Undeclared variables
- Type mismatches

Some semantic errors only occur at runtime, causing the program to crash
- Ex: Division by zero
- Will produce the wrong value or behavior

# 3.2 - Debugging Process

## Notes

### A general approach to debugging

1. Find the root cause of the problem
2. Ensure you understand why the issue is occurring
3. Determine how you'll fix the issue
4. Repair the issue causing the problem
5. Retest to ensure the problem has been fixed
6. Retest to ensure no new problems have emerged

# 3.3 - A strategy for debugging

## Notes

### Finding problems via code inspection

We can approxmiate where the issue is likely to be based on the nature of the error and the way the program is structured.

As programs get more complex, finding issues by code inspection becomes more complex:
1. More code to look at
2. Code itself tends to be more complex
3. Code's behavior may not give you many clues as to where things are going wrong.
4. Bugs can be caused by making bad assumptions

### Finding problems by running the program

Can watch the behavior of the program as it runs, and try to diagnose the issue from that
1. Figure out how to reproduce the problem
2. Run the program and gather information to narrow down where the problem is
3. Repeat the prior step until you find the problem

### Reproducing the problem

**Reproducing the problem**: Making the problem appear in a consistent manner
- Sometimes, the problem may only occur on certain computers, or in particular circumstances
- Generating a set of reproduction steps can be helpful

**Reproduction steps**: A list of clear and precise steps that can be followed to cause an issue to recur with a high level of predictability

# 3.4 - Basic Debugging Tactics

## Notes

### Debugging Tactic #1: Commenting out your code

If your program is exhibiting erroneous behavior, one way to reduce the amount of code you have to search through is to cmmen some code out and see if the issue persists.
- If the issue remains unchanged, the commented out code probably wasn't the problem

### Debugging tactic #2: Validating your code flow

A program may be called too many or too few times\
It can be helpful to place statements at the top of your functions to print the function's name.

When printing info for debugging, use `std::cerr`.
- `std::cout` might be buffered.
- `std::cerr` is unbuffered, anything you send to it will output immediately
  - Helps make clear that the information being output is for an error case rather than normal case

When adding temporary debug statements, it can be helpful to not indent them.
- Easier to find for removal later.

```cpp
#include <iostream>

int getValue()
{
std::cerr << "getValue() called\n";
	return 4;
}

int main()
{
std::cerr << "main() called\n";
    std::cout << getValue << '\n';

    return 0;
}
```

### Debugging tactic #3: Printing values

With some bugs, the program may be calculating or passing the wrong value
- We can also output the value of variables (including parameters) or expressions to ensure that they are correct

```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void printResult(int z)
{
	std::cout << "The answer is: " << z << '\n';
}

int getUserInput()
{
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getUserInput() };
std::cerr << "main::x = " << x << '\n';
	int y{ getUserInput() };
std::cerr << "main::y = " << y << '\n';

	int z{ add(x, 5) };
std::cerr << "main::z = " << z << '\n';
	printResult(z);

	return 0;
}
```

### Why using printing statements to debug isn't great

1. Debug statements clutter your code
2. Debug statements clutter the output of your program
3. Debug statements require modificaton of your code to both add and to remove, which can introduce new bugs
4. Debug statements must be removed after you're done with them, which makes them non-reusable

# 3.5 - More debugging tactics

## Notes

### Conditionalizing your debugging code

One way to make debugging easier to disable and enable debugging throughtout your program is to make your debugging statements conditional using preprocessor directives

```cpp
#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}
```

This allows us to reuse previously added debug statements and then just disable them when we're done with them
- Addresses the issue with having to remove debug statements and the risk in doing so
- The cost of even more code clutter
- If you make a typo (Mispell DEBUG) or forget to include the header into a code file, some or all of the debugging for that file may not be enabled

### Using a logger

**Log**: A sequential record of events that have happened, usually time-stamped\
**Logging**: Process of generating a log so they can be reviewed later
- Most applications and operating systems write log files that can be used to help diagnose issues that occur.
- Can be easily sent to other people for diagnosis

C++ contains an output stream named `std::clog`
- By default `std::clog` writes to the standard error stream (same as `std::cerr`)
- Better off using a third-party logging tool

### Using plog logger

```cpp
#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
	PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger

	PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console

	int x{ getUserInput() };
	std::cout << "You entered: " << x << '\n';

	return 0;
}
```

# 3.6 - Using an integrated debugger: Stepping

## Notes

**Program State**: All tracked information of the execution

All previous methods of debugging require altering code, which takes time and can introduce new bugs, clutter code, make existing code harder to understand.

### The Debugger

**Debugger**: A computer program that allows the programmer to control how another program executes and examines the program state while that program is running
- Can use a debugger to eexecute a program line by line
- Examine teh value of variables along the way

**Integrated Debugger**: A debugger that uses the same interface as the code editor, so you can debug using the same environment that you use to write your code

### Stepping

**Stepping**: The name for a set of related debugger features that let us execute our code statement by statement

### Step Into

**Step Into**: Executes the next statement in the normal execution path of the program
- then pauses execution of the program so we can examine the program's state
- If the statement being executed contains a function call, *step into* causes the program to jump to the top of the function being called

### Step Over

**Step Over**: Executes the next statement in the normal execution path of the program.
- Step over will execute an entire function without stopping and return control to you after the function has been executed

### Step Out

**Step Out**: Does not just execute the next line of code. Executes all remaining code in the function currently being executed.
- Then returns control to you when the function has returned

### A Step Too Far

It's very easy to accidentally step past the place you wanted to examine
- Usual thing to do is stop debugging and restart debugging again

### Step Back

Some debuggers (VS Enterprise Edition and rr) have introduced **step back** to rewind the last step.
- Isn't standardized yet and varies by debugger.

# 3.7 - Using an integrated debugger: Running and breakpoints

## Notes

### Run to cursor

**Run to Cursor**: Command executes the program until execution reaches the statement selected by the cursor.
- Returns control to you so you can debug starting at that point

### Continue

**Continue**: Simply continues running the program as per normal
- Until program terminates
- Until something triggers control to return back to you again

### Start

**Start**: Same as continue, just starting from the beginning of the program
- Can only be invoked when not already in a debug session

### Breakpoints

**Breakpoints**: A special marker that tells the debugger to stop execution of the program at the breakpoint when running in debug mode.

Could of advantages
- Will cause the debugger to return control to you every tim they are encountered
- Can set a breakpoint and it will persist until you remove it

Breakpoints placed on lines that are not in the path of execution will not cause the debugger to halt execution of the code

### Set next statement

**Set Next Statement**: Allows us to change the point of execution to some other statement.
- Can be used to jump the point of execution forwards and skip some code that would otherwise execute
- Or backwards and have something that already executed run again

### "Step back" vs jumping backwards via "Set next statement"

"Step back" rewinds the state of everything, as if you'd never gone past that point in the first place

"Set next statement" only changes the point of execution
- Any changes to variable values or other program state are not undone

# 3.8 - Using an integrated debugger: Watching variables

## Notes

### Watching variables

**Watching a variable**: The process of inspecting the value of a variable while the program is executing in debug mod

### The watch window

**Watch Window**: A window where you can add variables you would like to continually inspect
- These variables will be updated as you step through your program

### Setting a breakpoint on watched variables

Some debuggers will allow you to set a breakpoint on a watched variable rather than a line
- Cause the program to stop execution whenever the value of that variable changes

# 3.9 - Using an integrated debugger: The call stack

**Call Stack**: A list of all the active functions that have been called to get to the current point of execution
- Includes an entry for each function called
  - As well as which line of code will be returned to when the function returns
- A new function is called-> function is added to the top of the call stack
- When current function returns to the caller, it is removed from the call stack
  - Control returns to the function just below it.

**Call Stack Window**: A debugger window that shows the current stack

# 3.10 - Finding issues before they become problems

## Notes

### Don't make errors

Things that can help avoid making errors:
- Follow best practices
- Don't program when tired or frustrated
- Understand where the common pitfalls are in a language
- Don't let your functions get too long
- Prefer using the standard lib to writing your own code
- Comment your code liberally
- Start with simple solutions, then layer in complexity incrementally
- Avoid clever/non-obvious solutions
- Optimize for readability and maintainability, not performance.

### Refactor your code

**Refactoring**: Process of making structural changes to your code without changing its behavior
- Goal is to make your program less complex by increasing its organization and modularity

A function that takes up one vertical screen worth of code is generally regarded as too long\
Goal is to maximize comprehension and maintainability

### Introduction to defensive programming

When users use the application in a way that you did not anticipate, errors can occur.

**Defensive Programming**: Practice whereby the programmer tries to anticipate all of the ways the software could be misused
- Either by end-users, or by other developers
- Can often be detected and then mitigated

### Finding errors fast

Next best thing is to catch errors you do make quickly
- Program a little bit at time, and then test your code and make sure it works.

### Introduction to testing functions

**Unit Testing**: A software testing method by which small units of source code are tested to determine whether they are correct

There are many 3rd party unit testing frameworks that can be used.

### Introduction to constraints

Constraint-based techniques involve the addition of some extra code to check that some set of assumptions or expectations are not violated
- 1 common method of constraint-based techniques is with *assert* and *static_assert*

### Shotgunning for general issues

**Static Analysis Tools**: Programs that analyze your source code to identify specific semantic isues
- Issues found byt hese tools may or may not be the cause of any particular problem you are having, but may help point out fragile areas of code or issues

The compiler will warn you if you try to use a variable that has not been initialized

# 3.x - Chapter 3 Summary

- **Syntax Error**: An error that occurs when you write a statement that is not valid according to the grammar of the C++ language
- **Semantic Error**: A statement is syntactically valid, but does not do what the programmer intended
- **Debugging**: The process of finding and removing errors from a program

5 step process to approach debugging:
1. Find the root cause
2. Understand the problem
3. Determine a fix
4. Repair the issue
5. Retest

**Static Analysis Tools**: Tools that analyze your code and look for semantic issues that may indicate problems with your code

Number of tactics we can use to help find issues:
- Commenting out code
- Using output statements to validate your code flow
- Printing values

- **Log File**: A file that records events that occur in a program
- **Logging**: Process of writing information to a log file
- **Refactoring**: Process of restructuring your code without changing how it behaves
- **Unit Testing**: A software testing method by which small units of source code are tested to determine whether they are correct
- **Defensive programming**: A technique whereby the programmer tries to anticipate all of teh ways the software could be misused.
- **Debugger**: A tool that allows the programmer to control how a program executes and examine the program state while the program is running
- **Integrated Debugger**: A debugger that integrates into the code editor
- **Stepping**: Name for a set of related debugging features that allow you to step through your code statement by statement
- **Step Into**: Execute the next statement in the normal execution path of the program
  - Then pauses execution
  - If the satmenet contains a function call, the program will jump to the top of the function being called
- **Step Over**: Executes the next statement in the normal execution path of the program
  - Then pauses execution
  - If the statemnet contains afunction call, execute the function and returns control to you after the function has been executed
- **Step Out**: Executes all remainng code in the function currently being executed
  - Then returns control to you when the function has returned
- **Run to cursor**: Executes the program until execution reaches the statement selectedby your mouse cursor
- **Continue**: Runs the program, util the proram terminates or a breakpoint is hit
- **Start**: Same as continue, just from the beginning of the program
- **Breakpoint**: A special marker that tells the debugger to stop execution of the program when the breakpoint is reached
- **Set next statement**: Command allows us to change the point of execution to some other statement
  - Used to jump the point of execution forwards and skp some code that would otherwise exeucte
  - Or backwards and have something that already executed run again
- **Call Stack**: A list of all the active functions that have been executed to get to the current point of execution