# 8.1 - Control Flow Introduction

## Notes

**Execution Path**: The specific sequence of statements that the CPU executes

**Straight-Line Proram**: Take the same path every time they are run

**Control Flow Statements**: Statements that allow the programmer to change the normal path of execution through the program

**Branching**: When a control flow statement causes point of execution to change to a non-sequential statmement

### Categories of flow control statements

- Conditional statement:
  - Causes a sequence of code to execute only if some condition is met
  - If, else, switch
- Jumps:
  - Tells the CPU to start executing the statements at some other location
  - goto, break, continue
- Function calls
  - Jump to some other location and back
  - function calls, return
- Loops
  - Repeatedly execute some sequence of code 0+ times, until some condition is met
  - while, do-while, for, ranged-for
- Halts
  - Terminates the program
  - std::exit(), std::abort()
- Exceptions
  - A special kind of flow control structure designed for error handling
  - try, throw, catch

# 8.2 - If statements and blocks

## Notes
 
**Conditional Statement**: A statement that specifies whether some associated statement(s) should be executed

### Quick If-Statement recap

```cpp
 if (condition)
    true_statement;
else
    false_statement;
```

If the `condition` is `true`, the `true_statement` executes, if the `condition` is `false` and the optional `else statement` exists, the `false statement` executes

### If or Else with multiple conditional statements

You can use a compound statement block to run multiple lines in each block

```cpp
#include <iostream>

namespace constants
{
    constexpr int minRideHeightCM { 140 };
}

int main()
{
    std::cout << "Enter your height (in cm): ";
    int x{};
    std::cin >> x;

    if (x >= constants::minRideHeightCM)
        std::cout << "You are tall enough to ride.\n";
    else
    { // note addition of block here
        std::cout << "You are not tall enough to ride.\n";
        std::cout << "Too bad!\n";
    }

    return 0;
}
```

### Implicit blocks

If the programmer does not declare a block in the statement portion, the compiler will implicitly declare one.

### To block or not to block single statements

Consider putting single statement assocaited with an `if` or `else` in blocks.
- Experienced C++ developers sometimes disregard this practice in favor of tighter vertical spacing

A reasonable middle-ground alternative is to put single-lines on thesame line as the `if` or `else`

```cpp
if (age >= minDrinkingAge) purchaseBeer();
else std::cout << "No drinky for you\n".
```

### If-else vs if-if

- Use if-else when you only want to execute the code after the first `true` condition
- Use if-if when you want to execute the code after all `true` conditions

```cpp
#include <iostream>

void ifelse(bool a, bool b, bool c)
{
    if (a)      // always evaluates
        std::cout << "a";
    else if (b) // only evaluates when prior if-statement condition is false
        std::cout << "b";
    else if (c) // only evaluates when prior if-statement condition is false
        std::cout << "c";
    std::cout << '\n';
}

void ifif(bool a, bool b, bool c)
{
    if (a) // always evaluates
        std::cout << "a";
    if (b) // always evaluates
        std::cout << "b";
    if (c) // always evaluates
        std::cout << "c";
    std::cout << '\n';
}

int main()
{
    ifelse(false, true, true);
    ifif(false, true, true);

    return 0;
}
```

# 8.3 - Common if statement problems

## Notes

### Nested if-statements and dangling else problem

Possible to nest if-statements within other if-statements

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";

    return 0;
}
```

Consider the following:

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if-statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if-statement
            std::cout << x << " is between 0 and 20\n";

    // which if statement does this else belong to?
    else
        std::cout << x << " is negative\n";

    return 0;
}
```

The above program introduces a source of potential ambiguity called **dangling else**
- Is the else statement matched up with the outer or inner if-statement

To avoid ambiguities when nesting if-statements, it is a good idea to explicitly enclose the inner if-statement within a block

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0)
    {
        if (x <= 20)
            std::cout << x << " is between 0 and 20\n";
        else // attached to inner if statement
            std::cout << x << " is greater than 20\n";
    }
    else // attached to outer if statement
        std::cout << x << " is negative\n";

    return 0;
}
```

### Flattening nested if statements

Nested if-statements can be flattened by either restructuring the logic or by using logical operators

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x < 0)
        std::cout << x << " is negative\n";
    else if (x <= 20) // only executes if x >= 0
        std::cout << x << " is between 0 and 20\n";
    else // only executes if x > 20
        std::cout << x << " is greater than 20\n";

    return 0;
}
```


### Null statements

**Null Statement**: An expression statement that consists of just a semicolon

```cpp
if (x > 10)
    ; // this is a null statement
```

Null statements do nothing, typically used when the language requires a statement to exist but the programm doesn't need one
- Null statements are typically plaed on their own lines

Null statements can unintentionally cause problems

```cpp
if (nuclearCodesActivated()); // note the semicolon at the end of this line
    blowUpTheWorld();
```

### Operator== vs Operator= inside the condition

`Operator==` tests equality, `Operator=` is for assignment

# 8.4 - Constexpr if statements

## Notes

Normally the conditional of an if-statement is evaluated at runtime

Consider the case where the conditional is a constant expression

```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	// reminder: low-precision floating point literals of the same type can be tested for equality
	if (gravity == 9.8) // constant expression, always true
		std::cout << "Gravity is normal.\n";   // will always be executed
	else
		std::cout << "We are not on Earth.\n"; // will never be executed

	return 0;
}
```

The else-statement will never be executed
- Evaluating a constexpr conditional at runtime is wasteful.
- Also wasteful to compile code into the executable that can never be executed

### Constexpr if statement C++17

**Constexpr if statement**: Requires the conditional to be a constant expression
- The conditional of a constexpr if-statement will be evaluated at compile time
If the constexpr conditional evaluates to `true`, the entire if-else will be replaced
- Same for when the conditional evaluates to `false`

```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
	else
		std::cout << "We are not on Earth.\n";

	return 0;
}
```

It will compile to this

```cpp
int main()
{
	constexpr double gravity{ 9.8 };

	std::cout << "Gravity is normal.\n";

	return 0;
}
```

### Modern compilers and if statements with constexpr conditionals C++17

Modern compilers will generally treat non-constexpr if-statements that have constexpr conditionals as if they were constexpr if-statements
- They are not required to do so

A compiler that encounters a non-constexpr if-statement with a constexpr conditional may issue a warning advising you to use `if constexpr` instead

# 8.5 - Switch statement basics

## Notes

C++ Provides an alternative conditional statement called a switch-statement that is specialized

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

**Switch Statement**: An expression is evaluated to produce a value

One of the following occurs:
- If the expression's value is equal to the value after any of the case-labels, the statements after the matching case-label are executed
- If no matching value can be found and a default label exists, the statements after the default label are executed
- If no matching value can be found and there is no default label, the switch is skipped

### Starting a switch

Start a switch with the `switch` keyword, followed by parentheses with the conditional expression that we would like to evaluate inside

The condition in a switch must evaluate to an integral type or an enumerated type
- No floating point types, strings, and most other non-integral types

Following the conditional expression, we declare a block, inside the block we use labels to define all of the values we want to test for equality

### Case labels

**Case Label**: Declared using the `case` keyword and followed by a constant expression.
- Constant expression must either match the type of the condition or must be convertible to that type

If the value of the conditional expression equals the expression after a `case label` execution begins at the first statement after the `case label` and then continues sequentially

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 2
    {
    case 1:
        std::cout << "One";
        return;
    case 2: // which matches the case statement here
        std::cout << "Two"; // so execution starts here
        return; // and then we return to the caller
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

```shell
Two
```

There is no limit to the number of case labels, but all case labels must be unique

```cpp
switch (x)
{
case 54:
case 54:  // error: already used value 54!
case '6': // error: '6' converts to integer value 54, which is already used
}
```     

### The default label

**Default Label**: Declared using the `default` keyword. If the conditional expression doesn't match any case label and a default label exiss, execution begins at the first statement after the default label

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default: // which does not match to any case labels
        std::cout << "Unknown"; // so execution starts here
        return; // and then we return to the caller
    }
}

int main()
{
    printDigitName(5);
    std::cout << '\n';

    return 0;
}
```

There can only be only default label per switch statement

### No matching case label and no default case

If the value of the conditional statement doesn't match any of the case labels, and no default case has been provided, then no cases inside the switch are executed

### Taking a break

We used return-statements to stop execution of the statement after our labels, but this also exits the entire function

**Break Statement**: Using `break` keyword, tells the compiler that we are done executing statements within the switch and that execution should continue with the statement after the end of the switch block

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x evaluates to 3
    {
    case 1:
        std::cout << "One";
        break;
    case 2:
        std::cout << "Two";
        break;
    case 3:
        std::cout << "Three"; // execution starts here
        break; // jump to the end of the switch block
    default:
        std::cout << "Unknown";
        break;
    }

    // execution continues here
    std::cout << " Ah-Ah-Ah!";
}

int main()
{
    printDigitName(3);
    std::cout << '\n';

    return 0;
}
```

### Labels are conventionally not indented

A label does not define a nested scope
- The code following a label is conventionally not indented

Labels are simply not indented. This makes it easier to find each label, because the statements are only indented one level from the swtich block, it correctly implies that the statements are all part of the scope of the switch block

```cpp
// Preferred version
void printDigitName(int x)
{
    switch (x)
    {
    case 1: // not indented from switch statement
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}
```

### Switch vs If-Else

Switch statements are best used when there is a single expression we want to evaluate for equality against a small number of values

If-Else is significantly mroe flexible

# Switch fallthrough and scoping

## Questions

1. Write a function called calculate() that takes two integers and a char representing one of the following mathematical operations: +, -, *, /, or % (remainder). Use a switch statement to perform the appropriate mathematical operation on the integers, and return the result. If an invalid operator is passed into the function, the function should print an error message. For the division operator, do an integer division, and don’t worry about divide by zero.

Hint: “operator” is a keyword, variables can’t be named “operator”.

```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int x{0};
    std::cin >> x;
    return x;
}

char getSign()
{
    std::cout << "Enter a sign: ";
    char x{0};
    std::cin >> x;
    return x;
}

void calculate(int x, int y, char sign)
{

    int answer{0};

    switch (sign)
    {
        case '+':
            answer = x + y;
            break;
        case '-':
            answer = x - y;
            break;
        case '*':
            answer = x * y;
            break;
        case '/':
            answer = x / y;
            break;
        case '%':
            answer = x % y;
            break;
    }

    std::cout << "Answer: " << answer << "\n";
}

int main()
{

    int x{getNumber()};
    char sign(getSign());
    int y{getNumber()};

    calculate(x, y, sign);

    return 0;
}
```

## Notes

### Fallthrough

When a switch expression matches a case label or default label, execution begins at the first statement following the matching label
- Execution will continue sequentiallly until 1 of the following termination conditions happens
    - End of the switch block is reached
    - Another control flow statement (break or return)
    - Something else interrupts the normal flow (OS Shuts down, universe explode)

The presence of another case label is **Not** one of these terminating conditions


```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }

    return 0;
}
```

```shell
2
3
4
5
```

### The [[Fallthrough]] attribute

**Attributes**: Modern C++ feature that allows the programmer to provide the compiler with some additional data about the code
- Attributes are not statements, they can be used almost anywhere where they are contextually relevant

[[fallthrough]] attribute modifies a `null statement` to indicate that fallthrough is intentional

```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }

    return 0;
}
```

### Sequential case labels

You can use logical OR operator to combine multiple tests into a single statement

```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```

### Labels do not define a new scope

With `if statements`, you can only have a single statement after the if condition
- That statement is considered to be implicitly inside a block

Switch statements, the statements after labels are all scoped to teh switch block

```cpp
switch (1)
{
case 1: // does not create an implicit block
    foo(); // this is part of the switch scope, not an implicit block to case 1
    break; // this is part of the switch scope, not an implicit block to case 1
default:
    std::cout << "default case\n";
    break;
}
```

### Variable declaration and initialization inside case statements

You can declare or define variables inside the switch, both before and after the case labels, but not initialize

A variable declared or defined in one case can be used in a later case, even if the case in which the variable is defined is never executed

```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```

Initialization of variables does require the definition to execute
- Initialization of variables is disallowed in any case that is not the last case

```cpp
switch (1)
{
case 1:
{ // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
}

default:
    std::cout << "default case\n";
    break;
}
```

# 8.7 - Goto Statements

## Notes

Unconditional jump causes execution to jump to another spot in the code
- "Unconditional" means the jump always happens

**Goto Statements**: Unconditional jump, the spot it jumps to is identified through use of a **statement label**
- Statement labels are conventionally not indeented

```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
    return 0;
}
```

### Statement labels have function scope

**Function Scope**: The label is visible throughout the function even before its point of declaration.
- Goto statement and its corresponding `statement label` must appear in the same function

Goto statement can also jump forward

```cpp
#include <iostream>

void printCats(bool skip)
{
    if (skip)
        goto end; // jump forward; statement label 'end' is visible here due to it having function scope

    std::cout << "cats\n";
end:
    ; // statement labels must be associated with a statement
}

int main()
{
    printCats(true);  // jumps over the print statement and doesn't print anything
    printCats(false); // prints "cats"

    return 0;
}
```

The statement labels must be associated with a statement
- We had to use a null statement so we had a statement to label
- We were able to jump to the statement labeled by `end` even though we hadn't declared `end` yet due to statement labels havign function scope

You can only jump within the bounds of a single function

If you jump forward you can't jump forward over the initialization of any variable that is still in scope at the location being jumped to 

```cpp
int main()
{
    goto skip;   // error: this jump is illegal because...
    int x { 5 }; // this initialized variable is still in scope at statement label 'skip'
skip:
    x += 3;      // what would this even evaluate to if x wasn't initialized?
    return 0;
}
```

### Avoid using Goto

Goto is shunned in C++
- Allows a programmer to jump around the code arbitrarily

**Spaghetti Code**: Code that has a path of execution that resembles a bowl of spaghetti

# 8.8  - Introduction to loops and while loops

## Questions

1. In the above program, why is variable inner declared inside the while block instead of immediately following the declaration of outer?
- We want inner to reset every outer loop iteration, that way it returns to 1. If we set it right after outer, then inner never gets reset back to 1 and only the first line will go through.

2. Write a program that prints out the letters a through z along with their ASCII codes. Use a loop variable of type char.

```cpp
#include <iostream>


int main()
{

    char letter{'a'};
    while (letter <= 'z')
    {
        std::cout << letter << " " << static_cast<int>(letter) << "\n";
        ++letter;
    }
    return 0;
}
```

3. Invert the nested loops example so it prints the following:

```shell
5 4 3 2 1
4 3 2 1
3 2 1
2 1
1
```

```cpp
#include <iostream>

int main()
{
    int outer{5};
    while (outer >= 1)
    {
        int inner{outer};
        while (inner >= 1)
        {
            std::cout << inner << " ";
            --inner;
        }
        std::cout << "\n";
        --outer;
    }
}
```

4. Now make the numbers print like this:

```shell
        1
      2 1
    3 2 1
  4 3 2 1
5 4 3 2 1
```

```cpp
#include <iostream>

int main()
{
    int outer{1};
    while (outer <= 5)
    {
        int inner{5};
        while (inner >= 1)
        {
            if (inner <= outer)
            {
                std::cout << inner << " ";
            }
            else {
                std::cout << "  ";
            }
            --inner;
        }
        std::cout << "\n";
        ++outer;
    }
}
```

## Notes

### Introduction to loops

You want to print all the numbers between 1 and 10, without loops you do this:

```cpp
#include <iostream>

int main()
{
    std::cout << "1 2 3 4 5 6 7 8 9 10";
    std::cout << " done!\n";
    return 0;
}
```

This is doable, it becomes increasingly less so if you want to print more numbers

### While statements

**While Statements**: the simplest loop. Declared using the `while` keyword. When a while-statement is executed, the expression *condition* is evaluated
- If the condition evaluates to `true` the assoicated `statement` executes
- Once the statement has finished executing, control returns to the top of the while-statement and the process is repeated

The while-statement will keep looping as long as the condition continues to evaluate to `true`

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10)
    {
        std::cout << count << ' ';
        ++count;
    }

    std::cout << "done!\n";

    return 0;
}
```

### While-statements that evaluate to false initially

If the condition initially evaluates to `false`, the associated statement will not execute at all

```cpp
#include <iostream>

int main()
{
    int count{ 15 };
    while (count <= 10)
    {
        std::cout << count << ' ';
        ++count;
    }

    std::cout << "done!\n";

    return 0;
}
```

### Infinite Loops

If the expression is always `true`, the while loop will execute forever creating an infinite loop.

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10) // this condition will never be false
    {
        std::cout << count << ' '; // so this line will repeatedly execute
    }

    std::cout << '\n'; // this line will never execute

    return 0; // this line will never execute
}
```

### Intentional Infinite Loops

```cpp
while (true)
{
  // this loop will execute forever
}
```
The only way to exit an infinite loop is through a return-statement, a break-statement, an exit-statement, a goto-statement, anexception, or the user killing the program

```cpp
#include <iostream>

int main()
{

    while (true) // infinite loop
    {
        std::cout << "Loop again (y/n)? ";
        char c{};
        std::cin >> c;

        if (c == 'n')
            return 0;
    }

    return 0;
}
```

Best Practice: Favor `while(true)` for intentional infinite loops

### Unintentional infinite loops

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10) // this is an infinite loop
        ;               // whose body is a null statement

    { // this is no longer associated with the while loop
        std::cout << count << ' ';
        ++count;
    }

    std::cout << "done!\n";

    return 0;
}
```

Because the loop condition evaluates to `true`, the loop body executes
- The loop body is a null-statement, doing nothing
- Count never increments, causing an infinite loop

A semicolon after the condition is always a mistake

### Loop variables and naming

**Loop Variable**: A variable that is used to control ohw many times a loop executes

`while (count <= 10)`, count is a loop variable

Loop variables are often given simple names, with `i`, `j`, `k`

**Counter**: The most common type of loop variable, counts how mayntimes a loop has executed

### Integral loop variables should be signed

```cpp
#include <iostream>

int main()
{
    unsigned int count{ 10 }; // note: unsigned

    // count from 10 down to 0
    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "blastoff!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }

    std::cout << '\n';

    return 0;
}
```

When count does reach 0, it will print blastoff, then decrement. But because it is unsigned, it wraps around back to the max number of integer. Since count is still >= 0, this will continue on forever

Best practice: Integral loop variables should generally be a signed integral type

### Doing something every N interations

**Iterations**: Each time a loop is executed

We often want to do something every 2nd, 3rd, or 4th iteration, such as print a newline.
- Can be done with the remainder operator

```cpp
#include <iostream>

// Iterate through every number between 1 and 50
int main()
{
    int count{ 1 };
    while (count <= 50)
    {
        // print the number (pad numbers under 10 with a leading 0 for formatting purposes)
        if (count < 10)
        {
            std::cout << '0';
        }

        std::cout << count << ' ';

        // if the loop variable is divisible by 10, print a newline
        if (count % 10 == 0)
        {
            std::cout << '\n';
        }

        // increment the loop counter
        ++count;
    }

    return 0;
}
```

```shell
01 02 03 04 05 06 07 08 09 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
```

### Nested Loops

Also possible to nest loops inside other loops

```cpp
#include <iostream>

void printUpto(int outer)
{
    // loop between 1 and outer
    // note: inner will be created and destroyed at the end of the block
    int inner{ 1 };
    while (inner <= outer)
    {
        std::cout << inner << ' ';
        ++inner;
    }
} // inner destroyed here

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // This function prints numbers between 1 and outer
        printUpto(outer);

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }

    return 0;
}
```

```shell
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```

# 8.9 - Do While Statement

## Notes

Consider the case where we want to show the user a menu and ask them to make a selection
- If the user chooses an invalide selection, ask them again
- The menu should go inside the loop

```cpp
#include <iostream>

int main()
{
    // selection must be declared outside while-loop, so we can use it later
    int selection {}; // value initialized to 0

    while (selection < 1 || selection > 4)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```

This only works because our initial value of `0` is not in the valid set.
- What if `0` was a valid choice, we had to pick a different initializer to represent "invalid"
- Or we have to use a new variable to represent invalid

```cpp
#include <iostream>

int main()
{
    int selection {};
    bool invalid { true }; // new variable just to gate the loop

    while (invalid)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";

        std::cin >> selection;
        invalid = (selection < 1 || selection > 4);
    }

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```

### Do While Statements

**Do While Statement**: A looping construct that works just like a while loop, except the statement always executes at least once

```shell
do
    statement; // can be a single statement or a compound statement
while (condition);
```

```cpp
#include <iostream>

int main()
{
    // selection must be declared outside of the do-while-loop, so we can use it later
    int selection {};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection < 1 || selection > 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```

We can avoid both magic numbers and additional variables

`selection` must be declared outside fothe do while block
- If declared inside, it would be destroyed when the do block terminates

Do while loops aren't commonly used
- Having a condition at the bottom of the loop obscures the loop condition

Best Practice: Favor while loops over do-while when given an equal choice

# 8.10 - For statements

## Questions

1. Write a for-loop that prints every even number from 0 to 20.

```cpp
#include <iostream>

int main()
{
    for (int i = 0; i <= 20; ++i)
    {
        std::cout << i << "\n";
    }
    return 0;
}
```

2. Write a function named sumTo() that takes an integer parameter named value, and returns the sum of all the numbers from 1 to value.

For example, sumTo(5) should return 15, which is 1 + 2 + 3 + 4 + 5.

Hint: Use a non-loop variable to accumulate the sum as you iterate from 1 to the input value, much like the pow() example above uses the total variable to accumulate the return value each iteration.

```cpp
int sumTo(int num)
{
    int total{0};
    for (int i = 1; i <= num; ++i)
    {
        total += i;
    }
    return total;
}
```

3. What's wrong with the following for loop?

```cpp
// Print all numbers from 9 to 0
for (unsigned int i{ 9 }; i >= 0; --i)
    std::cout << i<< ' ';
```

After it prints 0 and it decrements, because it is an unsigned int, `i` will wrap around back to the max number. Since the number is >= 0 still, it will continue to run infinitely

4. 

## Notes

**For Statement** (**For Loop**): Preferred when we have an obvious loop variable because it lets us easily and concisely define, initialize, test, and change the value of loop variables

```shell
for (init-statement; condition; end-expression)
   statement;
```

Same thing as

```shell
{ // note the block here
    init-statement; // used to define variables used in the loop
    while (condition)
    {
        statement; 
        end-expression; // used to modify the loop variable prior to reassessment of the condition
    }
} // variables defined inside the loop go out of scope here
```

### Evaluation of for-statement

A for statement is evaluated in 3 parts
1. init-statement is executed.
   - Happens once when the loop is initiated
   - Typically used for variable definition and initialization
   - "Loop scope", form of block scope where these variables exists from the point of definition through the end of the loop statement
2. With each loop iteration, the condition is evaluated.
    - If evaluated to `true`, the statement is executed
    - If `false`, the loop terminates and execution continues with the next statement beyond the loop
3. After the statement is executed, the end expression is evaluated
    - The expression is used to increment or decreemnt the loop variables defined in the init-statement

The order of execution:
1. Init-statement
2. Condition
3. Loop Body
4. End-Expression

```cpp
#include <iostream>

int main()
{
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

### The perils of `operator!=` in for loop conditions

```cpp
#include <iostream>

int main()
{
    for (int i { 0 }; i < 10; ++i) // uses <, still terminates
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

    for (int i { 0 }; i != 10; ++i) // uses !=, infinite loop
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

     return 0;
}
```

Using `i <10` is better as it will terminate even if `i` jumps over the value `10`, where the `i != 10` will not.

### Off-by-one errors

**Off-By-One Errors**: Occur when the loop iterates 1 too many or 1 too few times to produce the desired results

```cpp
#include <iostream>

int main()
{
    // oops, we used operator< instead of operator<=
    for (int i{ 1 }; i < 5; ++i)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

We were suppose to print `1 2 3 4 5`, but we printed `1 2 3 4` instead.

### Omitted Expressions

It is possible to write for loops that omit any or all of the statements or expressions

```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }

    std::cout << '\n';

    return 0;
}
```

There are cases where not definition a loop variable or not incrementing it in the end-expression is desired

This is an infinite loop:

```cpp
for (;;)
    statement;
```

C++ will define the omitted condition-expression in a for-loop to be treated as `true`

### For-loops with multiple counters

Sometimes for loops need to work with multiple variables

Programmers can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end expression

```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```

```shell
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0
```

Best Practice: Defining multiple variables and using the comma operator is acceptable inside a for statement

### Nested for-loops

For loops can be nested inside other loops

```cpp
#include <iostream>

int main()
{
	for (char c{ 'a' }; c <= 'e'; ++c) // outer loop on letters
	{
		std::cout << c; // print our letter first

		for (int i{ 0 }; i < 3; ++i) // inner loop on all numbers
			std::cout << i;

		std::cout << '\n';
	}

	return 0;
}
```

```shell
a012
b012
c012
d012
e012
```

### Variables used only inside a loop should be defined inside the loop

Creating a variable has no cost, it is the initializatino that has a cost.
- There is no cost difference between initialization and assignment

Defining a variable outside theloop is likely to have 2 consequences
- Makes the program more complex, as we have to read more code to see where the variable is used
- It may actually be slower because the compiler may not be able to optimize a variable with a larger scope as effectively

### Conclusion

For statements are the most comonly used loop in C++ because they place all of the necessary information about loop variables, loop condition, and loop variable modifiers at the top of the loops

Excel when you have a counter variable

# 8.11 - Break and Continue

## Notes

### Break

**Break Statement**: Causes a while loop, do-while loop, for loop, or switch statement to end, with execution continuing with the next statement after the loop or switch being broken out of

### Breaking a switch

In a switch statement, a `break` is typically used at the end of each case to signify the case is finished

### Breaking a loop

`Break` statements can be used to end the loop early.
- Execution continues with the next statement after the end of the loop
- 
A `break` is also a common way to get out of an intentional infinite loop

### Break vs Return

A `break` terminates the switch or loop, and the execution continues at the first statement beyond the switch or loop

A `return` statement terminates the entire function that the loop is within, and execution continues at point where the function was called

### Continue

**Continue Statement**: Provides a convenient way to end the current iteration of a loop without terminating the entire loop

```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue; // go to next iteration

        // If the number is not divisible by 4, keep going
        std::cout << count << '\n';

        // The continue statement jumps to here
    }

    return 0;
}
```

```shell
1
2
3
5
6
7
9
```

A `continue` statement works by causing the current point of execution to jump to the bottom of the current loop

### The debate over use of break and continue

`break` and `continue` can help make loops more readable by keeping the number of nested blocks down and reducing the need for complicated looping logic

Best Practice; Use break and continue when they simplify your loop logic

### The debate over use of early return

**Early Return**: A return statement that is not the last statement in a function

Best Practice: Use early returns when they simplify your function's logic

# 8.12 - Halts (exiting your program early)

## Notes

**Halt**: A flow control statement that terminates the program.
- Halts are implemented as functions, our halt statements will be function calls

### The std::exit() function

`std::exit()` is a function that causes the program to terminate normally

**Normal Termination**: The program has exited in an expected way.
- Does not imply anything about whether the program was successful or not

If the user typed an invalid filename, your program returns a non-zero `status code`, but it will have a `normal termination`

`std::exit()` Performs a number of cleanup functions
- Objects with static storage duration are destoryed
- Other miscellaneous file cleanup is done
- Contorl is returned back to the OS

### Calling std::exit() explicitly

`std::exit()` can be called explicitly to halt the program before it would normally terminate
- Include the `cstdlib` header

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::cout << 1 << '\n';
    cleanup();

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

`std::exit()` can be called from any function to terminate the program at the point

### std::exit() does not clean up local variables

`std::exit()` does not clean up any local variables.
- Can be dangerous if your program relies on any local variables cleaning themselves up

### std::atexit

C++ offers the `std::atexit()` function, which allowsyou to specify a function that will automatically be called on program termiantion via `std::exit()`

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

```shell
1
cleanup!
```

When we pass `cleanup` function as an argument, we use `cleanup` not `cleanup()`

Benefit is that we only have to call it once.
- We don't have ot remember to call anything before calling `std::exit()`

`std::exit()` is implicitly called when `main()` terminates
- This will invoke any functions registered by `std::atexit()`

The function being registered cannot take parameters and have no return value

You can register multiple cleanup functions.
- They will be called in reverse order of registration
- The last one registered will be called first

### std::abort and std::terminate

**Abnormal Termination**: The program had some kind of unusual runtime error and the program couldn't continue to run
- Divide by 0

`std::abort()` causes abnormal termination
- Does not do any cleanup

`std::termnate()`: Used in conjunction with `exceptions`
- Can be called explicitly
- More often called implicitly when an exception isn't handled
- By default, `std::terminate()` calls `std::abort()`

### When should you use a halt?

Only use a halt if there is no safe or reasonable way to return normally from the main function
- If you haven't disabled exceptions, prefer using exceptions for handling errors safely

# 8.13 - Introduction to Random Number Generation

## Notes

Computers aren't designed to take advantage of physical variabes
- Modern computers live in a controllecd electrical world where everything is binary
- No in between

Computers are designed to produce results that are as predictable as possible

Computers are generally incapable of generating truly random numbers
- Modern programs typically *simulate* randomness using an algorithm

### Algorithms and state

**Algorithm**: A finite sequence of instructions that can be followed to solve some problem or produce some useful result
- Algorithms are typically implemented as reusable functions

**Stateful**: Algorithm is considered stateful if it retains some information across calls\
**Stateless**: Algorithm is stateless if it doesn't store any information\
**State**: Refers to the current values held in stateful variables

**Deterministic**: That for a given input, it will always produce the same output sequence

### Pseudo-Random Number Generators (PRNG)

A **Pseudo-Random Number Generator**: Alogirthm that generates a sequence of numbers whose properties simulate a sequence of random numbers

```cpp
#include <iostream>

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    // Generate the next number

    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    s_state = 8253729 * s_state + 2396403; // first we modify the state
    return s_state % 32768; // then we use the new state to generate the next number in the sequence
}

int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << LCG16() << '\t';

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }

    return 0;
}
```

```shell
4339	838	25337	15372	6783	2642	6021	19992	14859	26462	
25105	13860	28567	6762	17053	29744	15139	9078	14633	2108	
7343	642	17845	29256	5179	14222	26689	12884	8647	17050	
8397	18528	17747	9126	28505	13420	32479	23218	21477	30328	
20075	26558	20081	3716	13303	19146	24317	31888	12163	982	
1417	16540	16655	4834	16917	23208	26779	30702	5281	19124	
9767	13050	32045	4288	31155	17414	31673	11468	25407	11026	
4165	7896	25291	26654	15057	26340	30807	31530	31581	1264	
9187	25654	20969	30972	25967	9026	15989	17160	15611	14414	
16641	25364	10887	9050	22925	22816	11795	25702	2073	9516	
```

Each number appears to be pretty random with respect to the previous one.

The state is initially set to `0`. Then to produce the next number in the sequence, the current state is modified by applying some mathematical operations

This particular algorithm isn't very good as a random number generator
- Each result alterantes between even and odd

Most PRNGs work similarly to LCG16, they just typically use more state variables and more complex mathematical operations

### Seeding a PRNG

The sequence of "Random Numbers" is not random at all.
- Given some initial state, a PRNG will generate the same sequence of numbers each time

In order to generate different output sequences, the initial state of a PRNG needs to be varied

**Random Seed**: Used to set the initial state of a PRNG\
**Seeded**: When the initial state of a PRNG has been set using a seed

The seed value is typically provided by the program using the PRNG

```cpp
#include <iostream>

unsigned int g_state{ 0 };

void seedPRNG(unsigned int seed)
{
    g_state = seed;
}

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    g_state = 8253729 * g_state + 2396403; // first we modify the state
    return g_state % 32768; // then we use the new state to generate the next number in the sequence
}

void print10()
{
    // Print 10 random numbers
    for (int count{ 1 }; count <= 10; ++count)
    {
        std::cout << LCG16() << '\t';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x {};
    std::cout << "Enter a seed value: ";
    std::cin >> x;

    seedPRNG(x); // seed our PRNG
    print10();   // generate 10 random values

    return 0;
}
```

### Seed quality and underseeding

If we want the program to produce different randomized numbers each time it is run, we need some way to vary the seed each time
- We can't use PRNG to generate a random seed

The theoretical naximum number of unique sequences that a PRNG can generate is determined by the number of bits in the PRNG states
- PRNG with 128 bits can generate 2^128 unique sequences

The number of unqiue output sequences a PRNG can `actually` generate is limited by the number of unique seed values the program using the PRNG can provide

**Underseeded**: If a PRNG is not provided with enough bits of quality seed data
- May begin to produce randomized results whose quality is compromised in some way

Underseeded PRNG may exhibit any of the following issues:
- Random sequence generated by consecutive runs may have a high correlation to each other
- The generation of the Nth random number, some values will never be able to generate
  - Mersenne Twister that is underseeded will never generate the values 7 or 13 as its first output
- Someone may be able to guess the seed based on the initial random value produced

Developers who aren't familiar with proper seeding practices will often try to initialize a PRNG using a single 32 bit or 64 bit value

### Many different kinds of PRNG algorithms

Many PRNGs are now considered relatively poor by modern standards, there's no reason to use a PRNG that doesn't perform well when its just as easy to use one that does

### Randomization inC++

Accessible via the `<random>` header

There are 6 PRNG families available for use

- minstd_rand and minstd_rand0 - Should not use
- mt19937 and mt19937_64 - Maybe use
- randlux24 and ranlux48 - Should not use
- knuth_b - Should not use
- default_random_engine - No
- rand() - No

As of C++20, the Mersenne Twister algorithm is the only PRNG that ships with C++ that has both becent perofrmance and quality

### So we should use Mersenne Twister?

Probably, for most applications

It is worth nothing that by modern PRNG standards, Mersenne Twister is a bit outdated
- Its results can be predicted after seeing 624 generated numbers
- Non-suitable for any application that requires non-predictability

If you are developing an application that requires the highest quality random results, the fastest results, or one where non-predictability is important, you'll need a 3rd party library
- Xoshio family and Wyrand for non-cryptogrpahic PRNG
- Chacha family for cryptographic (non-predictable) PRNG

# 8.14 - Generating random numbers using Mersenne Twister

## Notes

### Generating random numbers in C++ using Mersenne Twister

Mersenne Twister PRNG is the most popular PRNG across all programming languages
- Generally produces quality results and has decent performance
  - mt19937 - Generate 32 bit unsigned integers
  - mt19937 - Generate 64 bit unsigned integers

```cpp
#include <iostream>
#include <random> // for std::mt19937

int main()
{
	std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t'; // generate a random number

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

### Rolling a dice using Mersenne Twister

The number generated with 32 bit is between 0 and 4,294,967,295.
- We don't always want numbers in that range
- What if we want to simulate a 6 sided dice
- What if we want to simulate a range of 7-11 damage


**Random Number Distribution**: Converts the output of a PRNG into some other distribution numbers

**Uniform Distribution**: A random number distribution that produces outputs between 2 numbers with equal probbabily

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution

int main()
{
	std::mt19937 mt{};

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

### The above program isn't as random as it seems

major flaw with the program.

If you run the program multiple times, you will note that it prints the same numbers every time

It is being initialized with the same seed every time the program is run
- The seed is the same, the random numbers being generated are also the same
- To make our entire sequence randomized differently each run, we need to pick a seed that's not a fixed number

We need to pick something that changes each time the program is run

Two commonly used methods
- Use the system clock
- Use the system's random device

### Seeding with the system clock

C and C++ has a long history of PRNGs being seeded using the current time `std::time()`

C++ has a chrono library containing various clocks that we use can to generate a seed value

```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

We included <chrono>, giving access to the clock
- We're using the current time from the clock as a seed value for our Mesenne twister

If the program is run several times in quick succession, the seeds generated for each run won't be that different

### Seeding with the random device

The random library contains a type called `std::random_device`
- Will ask the OS for a pseudo random number

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

One potential problem with `std::random_device`
- It isn't required to be non-deterministic
- It could, on some systems, produce the same sequence every time the program is run

Best Practice: Use `std::random_device` to seed your PRNGs

### Only seed a PRNG once

Many PRNGs can be reseeded after the initial seeding
- This essentially re-initializes the stateof the random number generator, causing it to generate results starting from the new seed state
- Reseeding should be avoided unless you have a specific reason to do so

### Mersenne Twister and underseeding issues

The internal state of a Mersenne Twiswter requires (2493 bytes) which is 624 32-bit values or 312 64 bit-values


We're essentially initializing 624 integers using a single integer, which is significantly underseeding the Mersenne Twister PRNG.
- Underseeding PRNG can generate results that are suboptimal for applications that need the highest quality results

How to fix?
- `std::seed_seq` (seed sequence), ideally we want our seed data to be as many bits as the state of our PRNG, or our PRNG will beunderseeded
  - `std::seed_seq` is a type that was designed to help with this
  - Pass it as many randomized values as we have, and then it will generate as many additional unbiased seed values as needed
  - The more random data we can rpovide `std::seed_seq`, the better job it will do for us

```cpp
#include <iostream>
#include <random>

int main()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

### Warming up a PRNG

When a PRNG is given a poor quality seed, the initial results of the PRNG may not be high quality
- Some PRNGs benefit from being "warmed up"
  - The first N results renerated are discarded
- Allows the internal state of the PRNG to be mixed up such that the subsequent results should be of higher quality
- A few hundred to a few thousand initial results are discarded

The `seed_seq` initialization used by `std::mt19937` perofrms a warm up, so we don't need to explicitly warm up `std::mt19937` objects

### Debugging programs that use random numbers

Can be difficult because it may exhibit different behaviors each run

Helpful to ensure your program executes the same way each time, that way you can run the program as many times as needed

It's useful to seed your PRNG with a specific fixed value, that causes the erroneous behavior to occur

# 8.15 - Global Random Numbers (Random.h)

What happens if we want to use a random number generator in multiple functions or files

Could create a static local `std::mt19937` variable in each function that needs it
- Overkill to have every funciton that uses a random number generator define and seed its own local generator

Want a single PRNG object that we can share and access anywhere

Create a global number generator object

Simple, header-only solution with #include

```cpp
// Random.h
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```

# 8.x - Chapter 8 summary and quiz

## Review

**Execution Path**: The specific sequence of statements that the CPU executes in a program
**Straight Line Program**: Takes the same path every time it is run
**Control Flow Statement**: Allow the programmer to change the normal path of execution
**Branch**: When a control flow statement causes the program to begin executing some non-sequential instruction sequence
**Conditional Statement**: A statement that specifies whether some associated statement(s) should be executed or not
**If Statement**: Allow us to execute an associated statement based on whether some condition is `true`
**Else Statements**: Execute if the associated condition is `false`
**Dangling Else**: Occurs when it is ambiguous which `if statement` an `else statement` is connected to
**Null Statement**: A statement that consists of just a semicolon, it does nothing
**Switch Statement**: Provide a cleaner and faster method for selecting between a number of matching items
**Case Labels**: Used to identify the values for the evaluated condition to match
**Default Label**: Executed if no matching case label can be found
**Fallthrough**: When execution flows from a statement underneath a label into statements underneath a subsequent label
**Goto statement**: Allow the program to jumpt o somewhere else in the code, either forward or backwards, generally be avoided
**Spaghetti Code**: Occurs when a program has a path of execution that resembles a bowl of spaghetti
**While Loops**: Allow the program to loop as long as a given condition evaluates to `true`
**Infinite Loop**: A loop that has a condition that always evaluates to `true`
**Loop Variable**: An integer variable used to count how many times a loop has executed
**Iteration**: Each execution of a loop
**Do While Loop**: Similar to while loops, but the condition is evaluated after the loop executes instead of before
**For Loop**: Ideal when you need to loop a specific number of times
**Off-by-one Error**: Occurs when the loop iterates 1 too many or 1 too few times
**Break Statements**: Allow us to break out of a switch,while, do while, or for loop
**Continue Statement**: Allow us to move immediately to the next loop iteration
**Halts**: allow us to terminate our program
**Normal Termination**: The program has exited in an expected way
**Std::exit()**: Automatically called at the end of main, or called explicitly to terminate the program
**Abnormal Termination**: Occurs when the program encountered some kind of unexpected error and had to be shut down
**std::abort**: Caled for an abnormal termination
**Algorithm**: Finite sequence of instructions that can be followed to solve some problem or produce some usefl result
**Stateful**: If it retains some information across calls
**Stateless**: Does not store any information
**State**: refers to the current values held in stateful variables
**Deterministic**: If for a given input, it will always produce the same output sequence
**Pseudo-Random Number Generator**: Algorithm that generates a sequence of numbers whose properties simulate a sequence of random numbers
**Random Seed**: Can be provided to initialize the state of the PRNG
**Seeded**: When a PRNG has been initialized with a seed
**Underseeded**: The size of the seed value can be smaller than the size of the state of the PRNG, when this happens the PRNG is underseeded
**Period**: The length of the sequence before a PRNG begins to repeat itself
**Random Number Distribution**: Converts the output of a PRNG into some other distribution of numbers
**Uniform Distributon**: A random number distribution that produces outputs between 2 numbers X and Y with equal probability

## Quiz

1. Take the program below and modify it so that the ball falls for as many seconds as needed until it reaches the ground. Update the program to use all covered best practices (namespaces, constexpr, etc…).

```cpp
#include <iostream>

// Gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns the current ball height after "seconds" seconds
double calculateBallHeight(double towerHeight, int seconds)
{
	const double gravity { 9.8 };

	// Using formula: s = (u * t) + (a * t^2) / 2
	// here u (initial velocity) = 0, so (u * t) = 0
	const double fallDistance { gravity * (seconds * seconds) / 2.0 };
	const double ballHeight { towerHeight - fallDistance };

	// If the ball would be under the ground, place it on the ground
	if (ballHeight < 0.0)
		return 0.0;

	return ballHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
void calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	calculateAndPrintBallHeight(towerHeight, 0);
	calculateAndPrintBallHeight(towerHeight, 1);
	calculateAndPrintBallHeight(towerHeight, 2);
	calculateAndPrintBallHeight(towerHeight, 3);
	calculateAndPrintBallHeight(towerHeight, 4);
	calculateAndPrintBallHeight(towerHeight, 5);

	return 0;
}
```

```cpp
#include <iostream>

namespace Constants
{
	constexpr double gravity { 9.8 };
}

// Gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns the current ball height after "seconds" seconds
// note: this function could be constexpr, but we haven't covered constexpr functions yet
double calculateBallHeight(double towerHeight, int seconds)
{
	// Using formula: s = (u * t) + (a * t^2) / 2
	// here u (initial velocity) = 0, so (u * t) = 0
	const double fallDistance { Constants::gravity * (seconds * seconds) / 2.0 };
	const double ballHeight { towerHeight - fallDistance };

	if (ballHeight < 0.0)
		return 0.0;

	return ballHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
double calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);

	return ballHeight;
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	int seconds { 0 };
	while (calculateAndPrintBallHeight(towerHeight, seconds) > 0.0)
	{
		++seconds;
	}

	return 0;
}
```

2. A prime number is a natural number greater than 1 that is evenly divisible (with no remainder) only by 1 and itself.

Complete the following program by writing the isPrime() function using a for-loop. When successful, the program will print “Success!”.

```cpp
// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
#include <iostream>

bool isPrime(int x)
{
    return false;
    // write this function using a for loop
}

int main()
{
    assert(!isPrime(0)); // terminate program if isPrime(0) is true
    assert(!isPrime(1));
    assert(isPrime(2));  // terminate program if isPrime(2) is false
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}
```

```cpp
// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
#include <iostream>

// Non-optimized version
bool isPrime(int x)
{
    if (x <= 1) // if x is negative, 0, or 1 then the number is not prime
        return false;

    for (int test{ 2 }; test < x; ++test)
    {
        if (x % test == 0) // if x is evenly divisible
            return false;  // then this number isn't prime
    }

    return true; // if we didn't find any divisors, then x must be prime
}

int main()
{
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

    std::cout << "Success!\n";

    return 0;
}
```

3. Implement a game of Hi-Lo. First, your program should pick a random integer between 1 and 100. The user is given 7 tries to guess the number.

If the user does not guess the correct number, the program should tell them whether they guessed too high or too low. If the user guesses the right number, the program should tell them they won. If they run out of guesses, the program should tell them they lost, and what the correct number is. At the end of the game, the user should be asked if they want to play again. If the user doesn’t enter ‘y’ or ‘n’, ask them again.

```cpp
// Random.h
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```

```cpp
#include <cassert> // for assert
#include <iostream>
#include "random.h"

namespace Constants
{
    int attempts{7};
    int minValue{1};
    int maxValue{100};
}

int getGuess(int attempt)
{
    std::cout << "Guess #" << attempt << ": ";
    int guess{0};
    std::cin >> guess;
    return guess;
}

bool isGuessCorrectAndPrint(int answer, int guess)
{
    if (guess > answer)
    {
        std::cout << "Your guess is too high.\n";
        return false;
    }
    else if (guess < answer)
    {
        std::cout << "Your guess is too low.\n";
        return false;
    }
    else
    {
        std::cout << "Correct! You win!\n";
        return true;
    }
}

bool playAgain()
{
    char playAgain{};

    do {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> playAgain;

        if (playAgain == 'n')
        {
            break;
        }
    } while ((playAgain != 'y' && playAgain != 'n'));

    return playAgain == 'y' ? true : false;
}

int main()
{

    while (true)
    {
        std::cout << "Let's play a game. I'm thinking of a number between " << Constants::minValue << " and " << Constants::maxValue << " . You have " << Constants::attempts << " tries to guess what it is.\n";

        int answer = Random::get(Constants::minValue, Constants::maxValue);

        bool isCorrect{false};
        int attempt{1};

        while (!isCorrect && attempt <= Constants::attempts)
        {
            int guess{getGuess(attempt)};
            isCorrect = isGuessCorrectAndPrint(answer, guess);
            guess++;
        }

        if (!isCorrect)
        {
            std::cout << "Sorry, you lose. The correct number was " << answer << ".";
        }

        if (!playAgain())
        {
            break;
        }
    }

    std::cout << "Thank you for playing.\n";
    
    return 0;
}
```