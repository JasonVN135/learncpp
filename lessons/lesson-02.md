# 2.1 - Introduction to functions

## Questions

1. In a function definition, what are the curly braces and statements in-between called?
  - Function Body
2. What does the following program print?
```cpp
#include <iostream> // for std::cout

void doB()
{
    std::cout << "In doB()\n";
}

void doA()
{
    std::cout << "In doA()\n";

    doB();
}

// Definition of function main()
int main()
{
    std::cout << "Starting main()\n";

    doA();
    doB();

    std::cout << "Ending main()\n";

    return 0;
}
```

```shell
Starting main()
In doA()
In doB()
In doB()
Ending main()
```

## Notes

**Function**: A reusable sequence of statements designed to do a particular job.
- Executing code must have the function `main()`
- Putting all code inside main becomes increasingly hard to manage

**User-Defined Functions**: Functions that you write yourself
**Function Call**: Tells the CPU to interrupt the current fucntion and execute another function
- CPU "puts a bookmark" at the current point of execution
- Executes the function named in the function call
- Returns to the point it bookmarked and resumes execution

**Caller**: The function initiating the function call
**Callee**: The function being called
**Invocation**: A function call, secondary name
**Invoker**: The callee

### An example of a user-defined function

```cpp
returnType functionName() // This is the function header (tells the compiler about the existence of the function)
{
    // This is the function body (tells the compiler what the function does)
}
```

**Function Header**: Tells the compiler about the existence of a function, function's name, and some other information
**Function Body**: The curly braces and statements in-between
- Where the statements that determine what your function does will go

To call a function, we use the function's name followed by a set of parentheses (e.g. `functionName()`) with no whitespace.

```cpp
#include <iostream> // for std::cout

// Definition of user-defined function doPrint()
// doPrint() is the called function in this example
void doPrint()
{
    std::cout << "In doPrint()\n";
}

// Definition of user-defined function main()
int main()
{
    std::cout << "Starting main()\n";
    doPrint();                        // Interrupt main() by making a function call to doPrint().  main() is the caller.
    std::cout << "Ending main()\n";   // This statement is executed after doPrint() ends

    return 0;
}
```

### Calling Functions more than once

Functions can be called more than once.

```cpp
#include <iostream> // for std::cout

void doPrint()
{
    std::cout << "In doPrint()\n";
}

// Definition of function main()
int main()
{
    std::cout << "Starting main()\n";
    doPrint(); // doPrint() called for the first time
    doPrint(); // doPrint() called for the second time
    std::cout << "Ending main()\n";

    return 0;
}
```

Output:

```shell
Starting main()
In doPrint()
In doPrint()
Ending main()
```

### Functions can call functions that call other functions

```cpp
#include <iostream> // for std::cout

void doB()
{
    std::cout << "In doB()\n";
}


void doA()
{
    std::cout << "Starting doA()\n";

    doB();

    std::cout << "Ending doA()\n";
}

// Definition of function main()
int main()
{
    std::cout << "Starting main()\n";

    doA();

    std::cout << "Ending main()\n";

    return 0;
}
```

```shell
Starting main()
Starting doA()
In doB()
Ending doA()
Ending main()
```

### Nested functions are not supported

**Nested Function**: A function whose definition is placed inside another function
- In C++, nested functions are not supported

```cpp
#include <iostream>

int main()
{
    void foo() // Illegal: this function is nested inside function main()
    {
        std::cout << "foo!\n";
    }

    foo(); // function call to foo()

    return 0;
}
```

```cpp
#include <iostream>

void foo() // no longer inside of main()
{
    std::cout << "foo!\n";
}

int main()
{
    foo();

    return 0;
}
```

# 2.2 Function return values (value-returning functions)

## Questions

1. Determine what the program will output, or whether the program will generate a compiler error

```cpp
#include <iostream>

int return7()
{
    return 7;
}

int return9()
{
    return 9;
}

int main()
{
    std::cout << return7() + return9() << '\n';

    return 0;
}
```

```shell
16
```

```cpp
#include <iostream>

int return7()
{
    return 7;

    int return9()
    {
        return 9;
    }
}

int main()
{
    std::cout << return7() + return9() << '\n';

    return 0;
}
```

```shell
Error
```

```cpp
#include <iostream>

int return7()
{
    return 7;
}

int return9()
{
    return 9;
}

int main()
{
    return7();
    return9();

    return 0;
}
```

```shell
nothing
```

```cpp
#include <iostream>

int getNumbers()
{
    return 5;
    return 7;
}

int main()
{
    std::cout << getNumbers() << '\n';
    std::cout << getNumbers() << '\n';

    return 0;
}
```

```shell
5
5
```

```cpp
#include <iostream>

int return 5()
{
    return 5;
}

int main()
{
    std::cout << return 5() << '\n';

    return 0;
}
```

```shell
Error
```

2. What does "DRY" stand for, why is it a useful practice to follow?
- Don't repeat yourself. It helps eliminate tedious code fixes and repetitiveness.

## Notes

```cpp
#include <iostream>

int main()
{
	// get a value from the user
	std::cout << "Enter an integer: ";
	int num{};
	std::cin >> num;

	// print the value doubled
	std::cout << num << " doubled is: " << num * 2 << '\n';

	return 0;
}
```

The program is composed of 2 conceptual parts.
- Get a value from the user
- Tell the user what double that value is

The same program in multiple functions:

```cpp
// This program doesn't work
#include <iostream>

void getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;
}

int main()
{
	getValueFromUser(); // Ask user for input

	int num{}; // How do we get the value from getValueFromUser() and use it to initialize this variable?

	std::cout << num << " doubled is: " << num * 2 << '\n';

	return 0;
}
```

The value that is entered is lost in `getValueFromUser` when it terminates and control returns to `main`

### Return Values

When writing user-defined functions, you get to determine whether your function will return a value back or not.

2 things are required:
- **Return Type**: Function has to indicate what type of value will be returned
  - `void`: No value will be returned
  - `int`: An integer will be returned
  - Only determines what *type* of value will be returned
- **Return Statement**: Inside the function that will return a value, indicates the specific value being returned
  - Consists of the `return` keyword, followed by a **return expression** with a semicolon.

When the return statement is executed:
- The return expression is evaluated to produce a value.
- The value produced by the return expression is copied back to the caller. This copy is called the **return value** of the function.
- The function exits, and control returns to the caller.

Updated function:

```cpp
#include <iostream>

int getValueFromUser() // this function now returns an integer value
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input; // return the value the user entered back to the caller
}

int main()
{
	int num { getValueFromUser() }; // initialize num with the return value of getValueFromUser()

	std::cout << num << " doubled is: " << num * 2 << '\n';

	return 0;
}
```

### Revisiting main()

`main()` returns an integer value\
2 Requirements for `main()`:\
- `main()` is required to return an `int`
- Explicit function calls to `main()` are disallowed

Global variables are initialized prior to the execution of `main`.
- If the initializer for such variable invokes a function, that function will execute prior to `main`

### Status Codes

Return value from `main()` is called a **status code** or **exit code** or **return code**.
- Used to signal whether your program was successful or not.
- `0`: Program ran normally
- Non-zero is often used to indicate some kind of failure

C++ standard library also defines exit codes
- `0` and `EXIT_SUCCESS` both mean the program executed successfully
- `EXIT_FAILURE` means the program did not execute successfully

### A value-returning function that does not return a value will produce undefined behavior

**value=returning function**: A function that returns a value
- return type is anything but `void`
- Must return a value of that type, using a return statement
  - Otherwise undefined behavior will result

Modern compilers should generate a warning if undefined behavior is present

### Function main will implicitly return 0 if no return statement is provided

The only exception to the rule that a value-returning function must reutnr a value via a return statement is for `main()`
- `main()` will implicitly return `0` if no return statement is provided.
- Best practice is to explicitly return a value from `main`
  - For intent and consistency

### Functions can only return a single value

A value-returning function can only return a single value back to the caller each time
- The value provided does not need to be a iteral

### The function author can decide what the return value means

Some functions use return values as status codes, others for a calculated or selected value, others nothing.
- Good idea to document your function with a comment

```cpp
// Function asks user to enter a value
// Return value is the integer entered by the user from the keyboard
int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input; // return the value the user entered back to the caller
}
```

### Reusing functions

```cpp
#include <iostream>

int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

int main()
{
    int x{ getValueFromUser() }; // first call to getValueFromUser
    int y{ getValueFromUser() }; // second call to getValueFromUser

    std::cout << x << " + " << y << " = " << x + y << '\n';

    return 0;
}
```

Best Practice: Don't repeat yourself

# 2.3 Void functions (non-value returning functions)

## Questions

1. Inspect the following programs and state what they output, or whether they will not compile

```cpp
#include <iostream>

void printA()
{
    std::cout << "A\n";
}

void printB()
{
    std::cout << "B\n";
}

int main()
{
    printA();
    printB();

    return 0;
}
```

```shell
A
B
```

```cpp
#include <iostream>

void printA()
{
    std::cout << "A\n";
}

int main()
{
    std::cout << printA() << '\n';

    return 0;
}
```

```shell
Compile Error
```

## Notes

### Void return values

To tell the compiler that a function does not return a value, a return type of **void** is used.

```cpp
#include <iostream>

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';

    // This function does not return a value so no return statement is needed
}

int main()
{
    printHi(); // okay: function printHi() is called, no value is returned

    return 0;
}
```

**Void Function**: Also called **Non-value Returning Function**, a function that does not return a value.

### Void functions don't need a return statement

A void function will automatically return to the caller at the end of the function.\
A return statement can be used in a void function
- This will cause the function to return to the caller at the point where the return statement is executed
- Putting an empty return statement at the end of a void function is redundant

```cpp
#include <iostream>

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';

    return; // tell compiler to return to the caller -- this is redundant since the return will happen at the end of the function anyway!
} // function will return to caller here

int main()
{
    printHi();

    return 0;
}
```

### Void functions can't be used in expression that require a value

```cpp
#include <iostream>

int main()
{
    std::cout << 5; // ok: 5 is a literal value that we're sending to the console to be printed
    std::cout << ;  // compile error: no value provided

    return 0;
}
```

```cpp
#include <iostream>

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';
}

int main()
{
    printHi(); // okay: function printHi() is called, no value is returned

    std::cout << printHi(); // compile error

    return 0;
}
```

The second function call won't compile, as the function is a void return type, no value is passed for `std::cout` to print.

### Returning a value from a void function is a compile error

Trying to return a value from a non-value returning function will result in a compilation error.

```cpp
void printHi() // This function is non-value returning
{
    std::cout << "In printHi()" << '\n';

    return 5; // compile error: we're trying to return a value
}
```

# 2.4 - Introduction to function parameters and arguments

## Questions

1. What's wrong with this program fragment?

```cpp
#include <iostream>

void multiply(int x, int y)
{
    return x * y;
}

int main()
{
    std::cout << multiply(4, 5) << '\n';

    return 0;
}
```
- multiply has the wrong return type

2. What two things are wrong with this program fragment?

```cpp
#include <iostream>

int multiply(int x, int y)
{
    int product { x * y };
}

int main()
{
    std::cout << multiply(4) << '\n';

    return 0;
}
```
- multiply takes 2 parameters, but the function call only has 1 argument.
- The product in the function is created but never returned, creating undefined behavior.

3. What value does the following program print?

```cpp
#include <iostream>

int add(int x, int y, int z)
{
    return x + y + z;
}

int multiply(int x, int y)
{
    return x * y;
}

int main()
{
    std::cout << multiply(add(1, 2, 3), 4) << '\n';

    return 0;
}
```

```shell
24
```

4. Write a function called doubleNumber() that takes one integer parameter. The function should return double the value of the parameter.

```cpp
int doubleNumber(int num)
{
  return 2 * num;
}
```

5. Write a complete program that reads an integer from the user, doubles it using the doubleNumber() function you wrote in the previous quiz question, and then prints the doubled value out to the console.

```cpp
#include <iostream>

int readNumber()
{
  int num{0};
  std::cout << "Enter a number to double: ";
  std::cin >> num;
  return num; 
}

int doubleNumber(int num)
{
  return 2 * num;
}

int main()
{

  int num{readNumber()};
  std::cout << "Double your number is: " << doubleNumber(num) << "\n";
  return 0;
}
```

## Notes

### Function parameters and arguments

**Function Parameter**: A variable used in the header of a function. Work almost identically to variables defined inside the function, but are initialized with a value provided by the caller of the function.

```cpp
// This function takes no parameters
// It does not rely on the caller for anything
void doPrint()
{
    std::cout << "In doPrint()\n";
}

// This function takes one integer parameter named x
// The caller will supply the value of x
void printValue(int x)
{
    std::cout << x << '\n';
}

// This function has two integer parameters, one named x, and one named y
// The caller will supply the value of both x and y
int add(int x, int y)
{
    return x + y;
}
```

**Argument**: A value that is passed *from* the caller *to* the function when a function call is made.

```cpp
doPrint(); // this call has no arguments
printValue(6); // 6 is the argument passed to function printValue()
add(2, 3); // 2 and 3 are the arguments passed to function add()
```

### How parameters and arguments work together.

**Pass by Value**: When a function is called, all of the parameters of the function are created as variables, and the value of each of the arguments is **copied** into the matching parameter (using copy initialization)
**Value Parameters**: Function parameters that utilize pass by value

```cpp
#include <iostream>

// This function has two integer parameters, one named x, and one named y
// The values of x and y are passed in by the caller
void printValues(int x, int y)
{
    std::cout << x << '\n';
    std::cout << y << '\n';
}

int main()
{
    printValues(6, 7); // This function call has two arguments, 6 and 7

    return 0;
}
```

The function is called with 2 arguments
- Parameter `x` is created and initialized with the value `6`
- Parameter `y` is created and initialized with the value `7`

### Using return values as arguments

```cpp
#include <iostream>

int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

void printDouble(int value)
{
	std::cout << value << " doubled is: " << value * 2 << '\n';
}

int main()
{
	printDouble(getValueFromUser());

	return 0;
}
```

We're using the return value of `getValueFromUser()` directly as an argument to function `printDouble()`.
- This "compact syntax" may be a bit hard to read for some.

### How parameters and return values work together

We can create functions that take data as input, do some calculations with it, and return the value to the caller

```cpp
#include <iostream>

// add() takes two integers as parameters, and returns the result of their sum
// The values of x and y are determined by the function that calls add()
int add(int x, int y)
{
    return x + y;
}

// main takes no parameters
int main()
{
    std::cout << add(4, 5) << '\n'; // Arguments 4 and 5 are passed to function add()
    return 0;
}
```

### Unreferenced parameters and unnamed parameters

**Unreferenced Parameters**: Functions that have parameters that are not used in the body of the function

```cpp
void doSomething(int count) // warning: unreferenced parameter count
{
    // This function used to do something with count but it is not used any longer
}

int main()
{
    doSomething(4);

    return 0;
}
```

The compiler will probably warn that variable `count` has been defined but not used

**Unnamed Parameter**: A parameter without a name
- The name of a function parameter is optional
- In cases where a function parameter needs to exist but is not used in the body, you can simply omit the name
- Recommended to use a comment to document what the unnamed parameter was

```cpp
void doSomething(int /*count*/)
{
}
```

Case for using an unnamed parameter:
- If we update a function that doesn't need the parameter anymore, removing the parameter will cause every call to the function to break.
- Leaving the parameter will cause a warning still.
- To avoid both of these problems, using an unnamed parameter will be a solution for both.

# 2.5 - Introduction to Local Scope

## Questions

1. What does the following program print?

```cpp
#include <iostream>

void doIt(int x)
{
    int y{ 4 };
    std::cout << "doIt: x = " << x << " y = " << y << '\n';

    x = 3;
    std::cout << "doIt: x = " << x << " y = " << y << '\n';
}

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << "main: x = " << x << " y = " << y << '\n';

    doIt(x);

    std::cout << "main: x = " << x << " y = " << y << '\n';

    return 0;
}
```

```shell
main: x = 1 y = 2
doIt: x = 1 y = 4
doIt: x = 3 y = 4
main: x = 1 y = 2
```

## Notes

### Local Variables

**Local variables**: Variables defined inside the body of a function
- Function parameters are also generally considered to be local variables

```cpp
int add(int x, int y) // function parameters x and y are local variables
{
    int z{ x + y }; // z is a local variable

    return z;
}
```

### Local variable lifetime

Function parameters are created and initialized when the function is entered
- Variables within the function ody are created and initialized at the point of definition

Local variables are destroyed in the opposite order of creation at the end of the set of braces in which it is defined.

```cpp
int add(int x, int y)
{
    int z{ x + y };

    return z;
} // z, y, and x destroyed here
```

An object's **lifetime** is defined to be the time between its creation and destruction.
- Variable destruction happen when the program is running, not at compile time
- Lifetime is a runtime property.

### What happens when an object is destroyed?

Nothing, the destroyed object simply becomes invalid\
If the object is a class type object, prior to destruction, a special function called a destructor is invoked.
- In many cases, the destructor does nothing

Any use of an object after it has been destroyed will result in undefined behavior\
**Deallocated**: Memory will be freed up for reuse
- At some point after destruction

### Local scope (block scope)

**Scope**: An identifier's scope determines where the identifier can be seen and used within the source code.\
**In Scope**: An identifier can be seen and used\
**Out of Scope**: An identifier can not be seen and can not be used.\
- Scope is a compile time property, using an identifier when out of scope will result in a compile error.

**Local Scope**: (Block Scope), identifiers will be usable from the point of definition to the end of the innermost pair of curly braces containing the identifier
- For function parameters, at the end of the function.
- Ensures local variables cannot be used before the point of definition or after they are destroyed.
- Local variables defined in one function are also not in scope of other functions

```cpp
#include <iostream>

// x is not in scope anywhere in this function
void doSomething()
{
    std::cout << "Hello!\n";
}

int main()
{
    // x can not be used here because it's not in scope yet

    int x{ 0 }; // x enters scope here and can now be used within this function

    doSomething();

    return 0;
} // x goes out of scope here and can no longer be used
```

### "Out of scope" vs "going out of scope"

**Out of Scope**: For identifiers, anywhere it cannot be accessed within the code
**Going out of Scope**: Applied to objects rather than identifiers. An object goes out of scope at the end of the scope in which the object was instantiated.

```cpp
#include <iostream>

int add(int x, int y) // x and y are created and enter scope here
{
    // x and y are usable only within add()
    return x + y;
} // y and x go out of scope and are destroyed here

int main()
{
    int a{ 5 }; // a is created, initialized, and enters scope here
    int b{ 6 }; // b is created, initialized, and enters scope here

    // a and b are usable only within main()

    std::cout << add(a, b) << '\n'; // calls add(5, 6), where x=5 and y=6

    return 0;
} // b and a go out of scope and are destroyed here
```

### Functional separation

```cpp
#include <iostream>

int add(int x, int y) // add's x and y are created and enter scope here
{
    // add's x and y are visible/usable within this function only
    return x + y;
} // add's y and x go out of scope and are destroyed here

int main()
{
    int x{ 5 }; // main's x is created, initialized, and enters scope here
    int y{ 6 }; // main's y is created, initialized, and enters scope here

    // main's x and y are usable within this function only
    std::cout << add(x, y) << '\n'; // calls function add() with x=5 and y=6

    return 0;
} // main's y and x go out of scope and are destroyed here
```

This program compiles and runs identically, even though functions `main` and `add` both have variables named `x` and `y`.
- These variables are distinct, they just happen to share the same names.
- When inside `main`, `x` and `y` refer to main's locally scoped variables. Those can only be seen inside of `main`.
- When inside `add`, `x` and `y` refer to function parameters, which can only be seen inside `add`

### Where to define local variables

The best practice is that local variables inside the function body should be defined as close to their first use as reasonable.

```cpp
#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int x{};       // x defined here
	std::cin >> x; // and used here

	std::cout << "Enter another integer: ";
	int y{};       // y defined here
	std::cin >> y; // and used here

	int sum{ x + y }; // sum can be initialized with intended value
	std::cout << "The sum is: " << sum << '\n';

	return 0;
}
```

Older/more primitive compilers used to require all local variables be defined at the top of the function. But is suboptimal

### When to use function parameters vs Local variables

When a variable is needed within a function:
- Use a function parameter when the caller will pass in the initialization value for the variable as an argument
- Use a local variable otherwise.

### Introduction to temporary objects

**Temporary Object**: An unnamed object that is used to hold a value that is only needed for a short perriod of time
- Generated by the compiler when they are needed

```cpp
#include <iostream>

int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input; // return the value of input back to the caller
}

int main()
{
	std::cout << getValueFromUser() << '\n'; // where does the returned value get stored?

	return 0;
}
```

The return value is stored in a temporary object, this temporary object is then passed to std::cout to be printed.
- Temporary objects have no scope at all
- Destroyed at the end of the full expression in which they are created
- Always destroyed before the next statement executes

# 2.6 - Why functions are useful, and how to use them effectively

## Notes

### Why use functions

- **Organization**: Having all code live inside the `main()` function becomes increasingly compilcate
  - Functions are like mini-programs that we can write separately from the main program, without having to think about the rest of the program
  - Allows us to reduce a complicated program into smaller, more manageable chunks which reduces the overall complexity of our program
- **Reusability**: Once a function is written, it can be called multiple times from within the program
  - Avoids duplicated code and minimizes the probability of copy/paste errors
  - Functions can be shared with other programs, reducing the code that has to be written.
- **Testing**: Lesss code to test.
  - Functions are self-contained, once we've tested a function to ensure it works, we don't need to test it again unless we change it.
  - Reduces the amount of code we have to test at one time
  - Easier to find bugs or avoid them
- **Extensibility**: When we need to extend our program to handle a case it didn't handle bfore, functions allow us to make the change in one pace and have the change take effect every time.
- **Abstraction**: only need to know the name, inputs, outputs, and where it lives
  - Don't need to know how it works, or what other code it's dependent upont o use it
  - Lowers the amount of knowledge required to use other people's code

### Effectively using Functions

- Groups of statements that appear more than once in a program should generally be made into a function
- Code that has a well-defined set of inputs and outputs is a good candidate
- A function should generally perform one (and only one) task
- **Refactoring**: When a function becomes too long, too complicated, or hard to understand, it can be split into multiple sub-functions

# 2.7 - Forward declarations and definitions

## Questions

1. What is function prototype?
  - A declaration to inform the compiler the existence of a function before it is defined, including the return type, function name, parameters, and escaping with a semicolon. 
2. What is forward declaration?
  - Allows us to tell the compiler about the existence of an identifier *before* actually defining the identifier
3. How do we declare a forward declaration for functions?
  - Use a Function Declaration/Prototype
4. Write the function declaration for this function (use the preferred form with names):

```cpp
int doMath(int first, int second, int third, int fourth)
{
     return first + second * third / fourth;
}
```
```cpp
int doMath(int first, int second, int third, int fourth);
```

5. For each of the following programs, state whether they fail to compile, fail to link, or compile and link successfully. If you are not sure, try compiling them!

```cpp
#include <iostream>
int add(int x, int y);

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```
fail to compile

```cpp
#include <iostream>
int add(int x, int y);

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```
fail to compile


```cpp
#include <iostream>
int add(int x, int y);

int main()
{
    std::cout << "3 + 4 = " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```
Fail to link


```cpp
#include <iostream>
int add(int x, int y, int z);

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}

int add(int z, int y, int x) // names don't match the declaration
{
    return x + y + z;
}
```
success

```cpp
#include <iostream>
int add(int, int, int); // no parameter names

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```
success

```cpp
#include <iostream>

int add(int x, int y);

int add(int x, int y, int z)
{
    return x + y + z;
}

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}
```
Compiles and links

## Notes

```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

This does not actually compile. The compiler compiles contents of code files sequentially
- When the compiler reaches `add(3, 4)`, it doesn't know what add is

Best Practice: When addressing compilation errors/warnings, resolve the first issue listed and then compile again

### Option 1: Reorder the function definition

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}
```

By the time `main` calls `add`, the compiler will already know what `add` is.\
In larger programs, it can be tedious trying to figure out which functions call which other functions\
If 2 functions call each other, it will be a problem.

### Option 2: Forward Declaration

**Forward Declaration**: Allows us to tell the compiler about the existence of an identifier *before* actually defining the identifier
- Tell the compiler about the existence of a function before we define the function's body

**Function Declaration Statement**: Used to write a forward declaration.
- Consists of the function's return type, name, and parameter types, terminated with a semicolon
- Names of parameters are optional
- Body is not included

Function Declaration:

```cpp
int add(int x, int y); // function declaration includes return type, name, parameters, and semicolon.  No function body!
```

The previous program with function declaration:

```cpp
#include <iostream>

int add(int x, int y); // forward declaration of add() (using a function declaration)

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
    return 0;
}

int add(int x, int y) // even though the body of add() isn't defined until here
{
    return x + y;
}
```

Function declaration do not need to specify the names of the parameters, you can also forward declar function like so:

```cpp
int add(int, int); // valid function declaration
```

It is preferred to still provide parameter names.

### Why Forward Declaration?

Forward declarations are used to tell the compiler about the existence of some functions that has been defined in a different code file
- If caller and callee are in 2 files, without forward declaration becomes difficult/impossible

Can be used to define our functions in an order-agnostic matter
- Allows defining functions in whatever order maximizes organization or reader understanding

Times when we have 2 functions call each other, reordering isn't possible

### Forgetting the function body

If forward declaration is made, the body doesn't exist, but the function is never called:
- The program will compile and run fine

If the function is called:
- The program will compile okay, but the linker will complain that it can't resolve the function call

```cpp
#include <iostream>

int add(int x, int y); // forward declaration of add()

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

// note: No definition for function add
```

This will result in compile errors

### Other types of forward declaration

Forward declaration can also be used with other identifiers in C++ such as variables and types.
- Variables and types have different syntax for forward declaration

### Declaration vs Defintiions

**Declaration**: Tells the compiler about the *existence* of an identifier and its associated type information

```cpp
int add(int x, int y); // tells the compiler about a function named "add" that takes two int parameters and returns an int.  No body!
int x;                 // tells the compiler about an integer variable named x
```

**Definition**: Declaration that actually implements (for functions + types) or instantiates the identifier

```cpp
// because this function has a body, it is an implementation of function add()
int add(int x, int y)
{
    int z{ x + y };   // instantiates variable z

    return z;
}

int x;                // instantiates variable x
```

In C++, all definitions are declarations, not all declarations are definitions.

### The One Definition Rule (ODR)

**One Definition Rule**: 3 Parts
1. Within a *file*, each function, variable, type, or template in a given sope can only have 1 definition.
  - Definitions occurring in different scopes do not violate this rule
2. Within a *program*, each function or variable in a given scope can only have one definition\
  - Programs can have more than one file
3. Types, templates, inline functions, and inline variables are allowed to have duplicate definitions in different files
  - So long as each definiition is identical

```cpp
int add(int x, int y)
{
     return x + y;
}

int add(int x, int y) // violation of ODR, we've already defined function add(int, int)
{
     return x + y;
}

int main()
{
    int x{};
    int x{ 5 }; // violation of ODR, we've already defined x
}
```

# 2.8 - Programs with multiple code files

## Questions

1. Split the following program into two files (main.cpp, and input.cpp). main.cpp should have the main function, and input.cpp should have the getInteger function.

```cpp
#include <iostream>

int getInteger()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getInteger() };
	int y{ getInteger() };

	std::cout << x << " + " << y << " is " << x + y << '\n';
	return 0;
}
```

```cpp
// main.cpp
#include <iostream>

int getInteger();

int main()
{
	int x{ getInteger() };
	int y{ getInteger() };

	std::cout << x << " + " << y << " is " << x + y << '\n';
	return 0;
}
```

```cpp
// input.cpp
#include <iostream>

int getInteger()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;
	return x;
}
```

## Notes

### Adding files to your project

When compiling with multiple files, you need to include all of the relvant code files on the compile line

```shell
g++ main.cpp add.cpp -o main
```

### Multi-file example

add.cpp:
```cpp
int add(int x, int y)
{
    return x + y;
}
```

main.cpp
```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // compile error
    return 0;
}
```

This will not work, an error will occur

```shell
main.cpp(5) : error C3861: 'add': identifier not found
```

The compiler doesn't know what the add identifier is. Even though the compiler may have seen the definition of `add()` previously, it doesn't remember.

This is intentional for a few reasons:
1. It allows the source files of the project to be compiled in any order
2. When we change a source file, only that source file needs to be recompiled
3. It reduces the possibility of naming conflicts between identifiers in different files

Solution, place an identifier in `main.cpp`
```cpp
#include <iostream>

int add(int x, int y);

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // compile error
    return 0;
}
```

Because the compiler compiles each ocde file indeividually, each code file that uses `std::cout` and `std::cin` needs to have `#include <iostream>`


# 2.9 - Naming collisions and an introduction to namespace

## Notes

*Naming collision/conflict**: Two identical identifiers are introduced into the same program in a way that the compiler or linker can't tell them apart, the compiler or linker will produce an error
- If in the same file -> compile error
- If in separate files -> linker error

### Example of Naming collision

```cpp
//a.cpp
#include <iostream>

void myFcn(int x)
{
    std::cout << x;
}
```

```cpp
//main.cpp
#include <iostream>

void myFcn(int x)
{s
    std::cout << 2 * x;
}

int main()
{
    return 0;
}
```

Compiling will be fine, but linking executes and discovers conflicting definitions and abort an error

Most naming collisisons occurs in 2 cases:
1. 2+ identical naming functions are introduced into separate files belonging to the same program. Result in a linker error.
2. 2+ identically named functions (or global variables) are introduced into the same file. Result in a compiler error

### Scope regions

**Scope Region**: An area of source code where all declared identifiers are considered distinct from names declared in other scopes
- Within a given scope region, all identifiers must be unique

### Namespace

**Namespace**: Provides another type of scope region (**Namespace Scope**) that allows you to declare/define names inside of it for the purpose of disambiguation.
- A name declared within a scope region is distinct from any identical name declared in another space
- A namespace may only contain declarations and definitions. Executable statements are only allowed as part of a definition (e.g. of a function)

### Global Namespace

**Global Namespace (Global Scope)**: Any name that is not defined inside a class, function, or a namespace is part of this namespace.

### The std namespace

cout and cin were originally part of the global namespace.
- Identifier in the standard library could potentially conflict with any name you picked for your own identifier.

`std::cout` and `std::cin` are really `cout` and `cin` with the `std` namespace.

We can create our own function or variable with the name `cout` and `cin` without conflict.

### Explicit namespace qualifier std::

The most straight forward way to tell the compiler we want to use `cout` from `std` is using the `std::` prefix

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello world!"; // when we say cout, we mean the cout defined in the std namespace
    return 0;
}
```

`::`: The **scope resolution operator**.
- Left side is the namespace
- If nothing on the left, assumed to be the global namespace.

### Using namespace std (and why to avoid it)

```cpp
#include <iostream>

using namespace std; // this is a using-directive that allows us to access names in the std namespace with no namespace prefix

int main()
{
    cout << "Hello world!";
    return 0;
}
```

**Using directive**: Allows us to acess the names in a namespace without using a prefix.
- Can be bad practice due to compile errors and conflicts

### Curly braces and indented code

In certain cases, identifiers defined outside curly braces may still be part of the scope defined by the curly braces rather than the surrounding scope

```cpp
#include <iostream> // imports the declaration of std::cout into the global scope

void foo(int x) // foo is defined in the global scope, x is defined within scope of foo()
{ // braces used to delineate nested scope region for function foo()
    std::cout << x << '\n';
} // x goes out of scope here

int main()
{ // braces used to delineate nested scope region for function main()
    foo(5);

    int x { 6 }; // x is defined within the scope of main()
    std::cout << x << '\n';

    return 0;
} // x goes out of scope here
// foo and main (and std::cout) go out of scope here (the end of the file)
```

# 2.10 Introduction to the Preprocessor

## Notes

Each code (.cpp) file goes through a **preprocessing** phase.\
A program called the **prepreocessor** makes various changes to the text of the code file.
- Doesn't actually modify the code files
- Changes happen either temporarily in-memory or using temporary files
- Strips comments
- Ensures each code file ends in a newline

1 very important role: Processes `#includ3` directives

**Translation Unit**: The result of a preprocessor finish processing a code file.
- The transition unit is what is then compiled by the compiler

### Preprocessor directives

Preprocessor scans through the code file (top to bottom), looking for preprocessor directives\
**Preprocessor directives**: Instructions that start witha `#` and end with a newline.
- Tells the preprocessor to perform certain text manipulation tasls

### #include

When you `#include` a file, the preprocessor replaces the #include directive with the contents of the include file.
- The contents are then preprocessed, then the rest of the file is preprocessed

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```

When the preprocessor runs, it replaces `#include <iostream>` with the contents of the file named `iostream` and then preprocess the included content and the rest of the file.

### Macro defines

**Macro**: A rule that defines how input text is converted into replacement output text.
- `#define` directive can be used to create a macro

2 basic types of macros: *object-like macros* and *function-like macros*

**Function-like Macros**: Act like functions
- Generally considered unsafe, and almost anything they can do can be done by a normal function

**Object-like Macros**: Defined in 1 of 2 ways:
```cpp
#define IDENTIFIER
#define IDENTIFIER substitution_text
```

Macro names are typically all uppercase, separated by underscores

### Object-like macros with substitution text

An association is made between the macro identifier and *substitution_text*. All further occurrences of the macro identifier are replaced by the *substitution_text*

```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```

The preprocessor converts the above into the following:
```cpp
// The contents of iostream are inserted here

int main()
{
    std::cout << "My name is: " << "Alex" << '\n';

    return 0;
}
```

This is a way to assign names to literals. There are better methods in C++ now. Object-like macros with substitution text are mostly legacy code.


### Object-like macros without substitution text

```cpp
#define USE_YEN
```

Most further occurrences of the identifier is removed and replaced by nothing.
- May seem useless, but not what it's used for
- Generally acceptable to use

### Conditional compilation

**Conditional Compilation**: Directives allow you to specify under what conditions something will or won't compile

**#ifdef**: Allows the preprocessor to check whether an identifier has been previously defined via #define.
- If so the code between `#ifdef` and matching `#endif` is compiled. If not, code is ignored.

```cpp
#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif

    return 0;
}
```

In place of `#ifdef PRINT_BOB` and `#ifndef PRINT_BOB` there is:
- `#if defined(PRINT_BOB)` and `#if !defined(PRINT_BOB)`

### #if 0

**#if 0**: Used to exclude a block of code from being compiled (as if it were inside a comment block)

```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    std::cout << "Steve\n";
#endif // until this point

    return 0;
}
```

You can reenable a block of code from `#if 0` by turning it into `#if 1`

### Macro substitution within other preprocessor commands

Mecro substitution does not occur when a macro identifier is used within another preprocessor command.

### Scope of #define

Directives are resolved before compilation, from top to bottom on a file-by-file basis.
- The preprocessor ignores C++ concepts of function scope.

```cpp
#include <iostream>

void foo()
{
#define MY_NAME "Alex"
}

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n';

	return 0;
}
```

`MY_NAME` will still be replaced\
Best to still define the identifiers outside of functions

Once the preprocessor has finished, all defined identifiers from the file are discarded.
- Directives are only valid from the point of definition to the end of the file

```cpp
// function.cpp
#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}
```

```cpp
// main.cpp
void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();

    return 0;
}
```

```shell
Not printing!
```

Even though PRINT was defined in `main.cpp`, it doesn't impact any of the code in `function.cpp`.


# 2.11 - Header Files

## Notes

### Header Files

**Header Files**: Uses the `.h` extension or `.hpp`, used to propagate a bunch of related forward declarations into a code file.

### Using Standard Library header files

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```

`std::cout` has been forward declared in the `iostream` header file
- We requested the preprocessor copy all of the content from the file `iostream` into the file doing the `#include`

### Using header files to propagate forward declarations

We had two files

```cpp
// add.cpp
int add(int x, int y)
{
    return x + y;
}
```

```cpp
// main.cpp
#include <iostream>

int add(int x, int y); // forward declaration using function prototype

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

Header files consists of 2 parts:
1. A **header guard**
2. The actual content of the header file, should be forward declarations for all of the identifiers we want other files to be able to see

Complete header file:
```h
// add.h
// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
```

For the header file to be used, we need to include the header file with quotes

```cpp
// main.cpp
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

```cpp
// add.cpp
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.

int add(int x, int y)
{
    return x + y;
}
```

### How include definitions in a header file results in a violation of the one-definition rule

For now, avoid putting function or variable definitions in header files.
- Generally result in a violation of the ODR

### Source files should include their paired header

In C++, it is bbest practice for code files to #include their paired header file.
- Allows the compiler to catch certain kinds of errors at compile time instead of link time

### Do not #include .cpp files

Reasons:
- Cause naming collisions between source fiels
- Large projects, hard to avoid ODR issues
- Any changes to a .cpp file will cause both the .cpp file and any other .cpp file that includes it to recompile
- Non-conventional

### Angled brackets vs double quotes

Using angled brackets tells the preprocessor we didn't write the header file.
- Preprocessor will look for the header only in the directories specified by the `include directories`
  - Configured as part of the project/IDE settings/compiler settings.

Using double quotes tells the preprocessor we wrote the header file
- Will first search for the header file in the current directory
  - If not found, it then searches `include directories`

### Why doesn't iostream have a .h extension

`iostream.h` is a different header file than iostream.
- `iostream.h` was originally global namespaced
- When everything got moved to the std namespace, they created `iostream` to avoid breaking all of the old code that used `iostream.h`

### Including header files from other directories

Bad way: Relative paths
- Requires you to reflect your directory structure in your code

```cpp
#include "headers/myHeader.h"
#include "../moreHeaders/myOtherHeader.h"
```

Better method: Tell your compiler or IDE that you have a bunch of header files in some other location
- Tell it to look there if it can't find it in the current directory
- In g++, use `-I` to include alternate directory

```shell
g++ -o main -I./source/includes main.cpp
```

- No space after `I`. For full path, remove `.`

### Headers may include other headers

Headers should `#include` other header file containing declaration that it needs

```h
// Foo.h
#include <string_view> // required to use std::string_view

std::string_view getApplicationName(); // std::string_view used here
```

### Transitive includes

**Transitive Includes**: Additional header files that are included when a the .cpp file includes a header file.
- Generally should not rely on the content of headers that are included transitively.

### The order of inclusion for header files

If everything is written properly, the order of inclusion shouldn't matter.

Best Practice: Order #include as follows
- The paired header file for this code file (e.g. `add.cpp` should `#include "add.h"`)
- Other hedaers from the same project (e.g. `#include "mymath.h"`)
- 3rd party library headers (e.g. `#include <boost/tuple/tuple.hpp>`)
- Standard librray headers (e.g. `#include <iostream>`)

Header for each group sorted alphabetically unless otherwise instructured

# 2.12 - Header Guards

## Questions

Add header guards to this header file:

```cpp
// add.h
int add(int x, int y);
```

```cpp
#ifndef ADD_H
#define ADD_H

int add(int x, int y);

#endif
```

## Notes

### The duplicate definition problem

With header files, there can easily be issues of multiple functions being defined

```h
// square.h
int getSquareSides()
{
    return 4;
}

```h
// wave.h
#include "square.h"
```

```cpp
// main.cpp

#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```

This will not compile as the function `getSquareSides()` appears twice

### Header Guards

**Header Guards (Include Guards**: Conditional compilation directives that take the following form:

```cpp
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```

The preprocessor will check whether `SOME_UNIQUE_NAME_HERE` has been previously defined in this translation unit.
- If this is the first time, `SOME_UNIQUE_NAME_HERE` will not be defined and it will then define it and include the contents
- If it already has been defined, the contents of the header will be ignored.

All header files should have a header guard.
- By convention, set the name to the full filename of the header file, all caps, using underscores for spaces or punctuation.

```cpp
// square.h
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

#endif
```

### Header guards do not preven a header from being included once into different code files

A header file is defined in a cpp file until the end of the file.
- This prevents the header from being included into the cpp a second time. (It's purpose)

Once the cpp file is finished, the header is no longer considered defined. When the preprocessor runs a new cpp file, the header file is not defined.

Best practice is to only put the forward declaration in the header files and definition in a cpp file.

### #pragma once

Modern compilers support a simple, alternate form with `#pragma` preprocessor directive

```cpp
#pragma once

// your code here
```

**#pragma once**: Servers the same purpose of header guards.
- 1 Known case where this fails:
  - If a header file is copied so that it exists in multiple places in the system.
  - If both copies of the header get included, the header guards will successfully de-dupe the identical headers, but #pragma once won't

Because `#pragma once` is not defined by the C++ standard, it is possible some compilers may not implement it.

Both methods are accepted

# 2.x - Chapter 2 Summary and Quiz

## Review

- **Function**: A reusable sequence of statements design to do a particular job
- **User-Defined Functions**: Functions you write yourself
- **Function Call**: Expression that tells the CPU to execute a function
- **Caller**: The function initiating the function call
- **Callee**: The function that is called
- **Function Body**: Curly braces and statements in a function definition
- **Value-Returning Function**: Functions that returns a value
- **Return Type**: The type of value that the function will return
- **Return Statement**: Determines the specific return value that is returned to the caller
- **Return By Vaue**: A return value is copied from the function back to the caller
- **Status Code**: The return value from the function *main*
- **DRY**: Don't Repeat Yourself
- **void**: Functions with this return type do not return a value to the caller
- **Void Function**: Functions that do not return a value
- **Early Return**: A return statement that is not the last statement in a function
- **Function Parameters**: A variable used in a function where the value is provided by the caller of the function
- **Argument**: An value passed by the caller to be used as function parameters
- **Pass By Value**: When an argument is copied into the parameter
- **Local Variables**: Function parameters and variables defined inside the function body.
- **Lifetime**: The time in which a variable exists
- **Runtime**: Start and end of a program running
- **Scope**: Variable's scope determines where it can be seen and used
- **In Scope**: A variable can be seen and used
- **Out of Scope**: A variable can not be seen or used
- **Compile-Time**: Enforced at compile time
- **Whitespace**: Characters used for formatting purposes. Spaces, tabs, newlines
- **Format declaration**: Tell the compiler about the existence of an identifier before actually defining the identifier.
- **Function prototype**: Includes the function's return type name, and parameters, but no function body, followed by a semicolon
- **Definition**: Actual implemenation of an identifier.
- **Declaration**: A statement that tells the compiler about the existence of the identifier.
- **Pure Declaration**: Declarations that are not also definitions (Function Prototypes)
- **Naming Collision**: When 2 identifiers are introduced into the same program in a way that the compiler or linker can't tell them apart.
- **Namespace**: Guarantees that all identifiers within the namespace are unique
- **Preprocessor**: Process that runs on the code before it is compiled
- **Directives**: Special instructions to the preprocessor, starting with `#` and ending with a newline
- **Macro**: A rule that defines how input text is converted to a replacement output text
- **Header Files**: Files designed to propagate declarations to code files.
- **Header Guards**: Prevent the contents of a header from being included more than once into a given code file.

## Quiz

1. Write a single-file program (named main.cpp) that reads two separate integers from the user, adds them together, and then outputs the answer. The program should use three functions:

- A function named “readNumber” should be used to get (and return) a single integer from the user.
- A function named “writeAnswer” should be used to output the answer. This function should take a single parameter and have no return value.
- A main() function should be used to glue the above functions together.

```cpp
// main.cpp
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The answer is " << x << '\n';
}

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x + y); // using operator+ to pass the sum of x and y to writeAnswer()
    return 0;
}
```

```shell
g++ -o main main.cpp
```

2. Modify the program you wrote in exercise #1 so that readNumber() and writeAnswer() live in a separate file called “io.cpp”. Use a forward declaration to access them from main().

```cpp
// io.cpp
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The answer is " << x << '\n';
}
```

```cpp
// main.cpp
int readNumber();
void writeAnswer(int x);

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x+y);
    return 0;
}
```

```shell
g++ -o main main.cpp io.cpp
```

3. Modify the program you wrote in #2 so that it uses a header file (named io.h) to access the functions instead of using forward declarations directly in your code (.cpp) files. Make sure your header file uses header guards.

```cpp
// io.h
#ifndef IO_H
#define IO_H

int readNumber();
void writeAnswer(int x);

#endif
```

```cpp
// io.cpp
#include "io.h"
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The answer is " << x << '\n';
}
```

```cpp
// main.cpp
#include "io.h"

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x+y);
    return 0;
}
```

```shell
g++ -o main main.cpp io.cpp
```