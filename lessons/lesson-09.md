# 9.1 - Introduction to testing your code

## Questions

1. When should you start testing your code?
- As soon as you've written a non-trivial function

## Notes

**Scope Creep**: You added som enew capabilities that were originally not planned for

**Software Testing**: The process of determining whether or not the software actulaly works as expected


### Test your programs in small pieces

Write your program in small, well defined units (funtions or classes), compile often, and test your code as you go

### informal Testing

After writing a unit of code, you can write some code to test the unit that was just added, and then erase the test once the test passes

```cpp
#include <iostream>

// We want to test the following function
// For simplicity, we'll ignore that 'y' is sometimes counted as a vowel
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int main()
{
    // So here's our temporary tests to validate it works
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0

    return 0;
}
```

### Preserving your tests

You may want to test the same code again later.
- It can make more sense to presever your tests so they can be run again in the future

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Not called from anywhere right now
// But here if you want to retest things later
void testVowel()
{
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0
}

int main()
{
    return 0;
}
```

### Automating your test functions

One problem above it that it relies on you to manually verify the results when you run it.

We can write a function that contains both the tests AND expected answers and compares them so we don't have to

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// returns the number of the test that failed, or 0 if all tests passed
int testVowel()
{
    if (!isLowerVowel('a')) return 1;
    if (isLowerVowel('q')) return 2;

    return 0;
}

int main()
{
    int result { testVowel() };
    if (result != 0)
        std::cout << "testVowel() test " << result << " failed.\n";
    else
        std::cout << "testVowel() tests passed.\n";

    return 0;
}
```

A better method is to use `assert` which will cause the program to abort with an error message if any test fails

```cpp
#include <cassert> // for assert
#include <cstdlib> // for std::abort
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Program will halt on any failed test case
int testVowel()
{
#ifdef NDEBUG
    // If NDEBUG is defined, asserts are compiled out.
    // Since this function requires asserts to not be compiled out, we'll terminate the program if this function is called when NDEBUG is defined.
    std::cerr << "Tests run with NDEBUG defined (asserts compiled out)";
    std::abort();
#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('b'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('y'));
    assert(!isLowerVowel('z'));

    return 0;
}

int main()
{
    testVowel();

    // If we reached here, all tests must have passed
    std::cout << "All tests succeeded\n";

    return 0;
}
```

### Unit Testing Frameworks

**Unit Testing Frameworks**: Designed to help simpilfy the process of writing, maintaining, and executing unit tests

### Integration Testing

**Integration Test**: Once units have been tested in isolation, they can be integrated into the program and retested to make sure they were integrated properly

# 9.2 - Code Coverage

## Questions

1. What is branch coverage?
- The percentage of branches that have been executed

2. How many tests would the following function need to minimally validate that it works?

```cpp
bool isLowerVowel(char c, bool yIsVowel)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    case 'y':
        return yIsVowel;
    default:
        return false;
    }
}
```
- 4

## Notes

### Code Coverage

**Code Coverage**: Used to describe howmuch of the source code of a program is executed while testing

### Statement Coverage

**Statement Coverage**: The percentage of statemets in your code that have been exercised by your testing routine

### Branch Coverage

**Branch Coverage**: The percentage of branches that have been executed, each possible branch counted separated
- `if statement` has 2 branches
- `switch` has many branches

```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```

`foo(1, 0)` gives 100% statement coverage but only 50% branch coverage. Also need to call `foo(0, 1)` to get 100% branch coverage

Aim for 100% branch coverage of your code

### Loop Coverage

**Loop Coverage**: if you have a loop in your code, you should ensure it works properly when it iterates 0, 1, and 2 times
- If it works correctly for the 2 iteration case, it should work correctly for all iterations greater than 2

```cpp
#include <iostream>

void spam(int timesToPrint)
{
    for (int count{ 0 }; count < timesToPrint; ++count)
         std::cout << "Spam! ";
}
```

You should call it three times
- `spam(0)` to test the 0 iteration case
- `spam(1)` to test the 1 iteration case
- `spam(2)` to test the 2 iteration case

### Testing different categories of input

When writing functions that accept parameters, or accepting user input, consider what happens with different categories of input

Testing a function to produce the square root of an integer
- should test with a 4, or a 0, or a negative number

For testing integers
- Consider how your function handles negative values, zeros, and positive values
- Check for overflow if relevant

For testing floating point numbers
- Consider how your function handles avlues that have precision issues
- Good `double` type values to test with are `0.1` and `-0.1`

For strings
- Consider how your function handles an empty string, an alphanumeric string, strings that have whitespace (leading, trailing, and inner), and strings that are all whitespace

For pointers
- Don't forget to test `nullptr` as well

# 9.3 - Common semantic errors in C++

## Notes

`syntax errors`: Occur when you write code that is not valid according to the grammar of the C++ language

`semantic errors`: Occur when you write code that doesn't do what you intended

### Conditional logic errors

**Condition Logic Error**: Occurs when the programmer incorrectly codes the logic of a conditional statement or loop condition

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (x >= 5) // oops, we used operator>= instead of operator>
        std::cout << x << " is greater than 5\n";

    return 0;
}
```

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    // oops, we used operator> instead of operator<
    for (int count{ 1 }; count > x; ++count)
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

### Infinite Loops

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

We forgot to increment `count`, so the loop condition will never be false

```cpp
#include <iostream>

int main()
{
    for (unsigned int count{ 5 }; count >= 0; --count)
    {
        if (count == 0)
            std::cout << "blastoff! ";
        else
          std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```
The program will never terminate because count can never be negative

### Off-by-one error

**Off-by-one Error**: An error that occurs when a loop executes 1 too many or too few times

```cpp
#include <iostream>

int main()
{
    for (int count{ 1 }; count < 5; ++count)
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

Need it to print `1 2 3 4 5` but it won't

### Incorrect Operator Precedence

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y) // oops: operator precedence issue
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```

`logical NOT` has higher precedence than `operator>`. This is not what is intended by the user

### Precision issues with floating point types

The following floating point variable doesn't have enough precision to store the entire number

```cpp
#include <iostream>

int main()
{
    float f{ 0.123456789f };
    std::cout << f << '\n';

    return 0;
}
```

The number is rounded slightly

```shell
0.123457
```

The more arithmetic you do with a floating point number, the more it will accumulate small rounding errors

### Integer devision

Because both operands are integers, we do integer divison

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 3 };

    std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // integer division

    return 0;
}
```

```shell
5 divided by 3 is: 1
```

### Accidental Null Statements

`null statements`, statements that do nothing

```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y');     // accidental null statement here
        blowUpWorld(); // so this will always execute since it's not part of the if-statement

    return 0;
}
```

Because of the accidental `null statement`, we blow up the world regardless of the user choice.

### Not using a compound statement when one is required

```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y')
        std::cout << "Okay, here we go...\n";
        blowUpWorld(); // Will always execute.  Should be inside compound statement.

    return 0;
}
```

A dangling else also falls in this category

### Using assignment instead of equality inside a condition

We may intend to use equality but accidentally use assignment instead

```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c = 'y') // uses assignment operator instead of equality operator
        blowUpWorld();

    return 0;
}
```

### Forgetting to use the function call operator when callng a function

```cpp
#include <iostream>

int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
```

# 9.4 - Detecting and handling errors

## Notes

Most errors occur due to faulty assumptions made by the programmer and/or  lack of proper error detection/handling

3 Key places where assumption errors typically occur:
- When a function returns, the programmer may have assumed the called functino was successful when it was not
- When a program receives input, the programmer may assume the input was in the correct format and semantically valid when it as not
- When a function has been called, the programmer may have assumed the arguments would be semantically valid when they were not

Many new programmers write code and then only test the happy path

**Happy Path**: Only the cases where there are no errors\
**Sad Path**: Things can and will go wrong

**Defensive Programming**: The practice of trying to anticipate all of the ways software can be misused, either by end-users, or by developers

### Handling errors in functions

Functions may fail for any number of reasons
- There is no best way to handle an error
- Depends on the nature of the problem and whether the program can be fixed or not

4 general strategies that can be sued:
- Handle the error within the function
- Pass the error back to the caller to deal with
- Halt the program
- Throw an exception

### Handling the error within the function

Best strategy is to recover from the error in the same function in which the error occurred, so that the error can be contained and corrected without impacting any code outside the function
- Retry until successful
- Cancel the operation being executed

```cpp
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
    else
        std::cout << "Error: Could not divide by zero\n";
}
```

### Passing errors back to the caller

The error can't reasonably be handled in the function that detects the error

Sometimes, the best option can be to pass the error back to the caller in hopes that the caller will be able to deal with it.

If the function has a `void` return type, it can be changed to return a `bool` that indicates success or failure

```cpp
bool printIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: could not divide by zero\n";
        return false;
    }

    std::cout << x / y;

    return true;
}
```

If the function returns a normal value, we can use a return value that wouldn't otherwise be possible to occur normally to indicate an error

```cpp
// The reciprocal of x is 1/x
double reciprocal(double x)
{
    return 1.0 / x;
}
```

We can return `0.0` to indicate an error case

```cpp
// The reciprocal of x is 1/x, returns 0.0 if x=0
constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace

double reciprocal(double x)
{
    if (x == 0.0)
       return error_no_reciprocal;

    return 1.0 / x;
}
```

**Sentinel Value**: A value that has some special meaning in the context of a function or algorithm

If the full range of return values can be produced by the funciton, then using a sentinel value to indicate an error is problematic

### Fatal errors

**Non-Recoverable Errors**: (**Fatal Error**) Error so bad that the program can not continue to operate properly
- Best thing to do is terminate the program

If in `main()`, return a non-zero value

If deep into subfunctions, best to use a `halt statement` such as `std::exit()`

```cpp
double doIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);
    }
    return x / y;
}
```

### Exceptions

Because returning an error from a function back to the caller is complicated, C++ offers an entirely separate way to pass errors back to the caller: `Exceptions`

When an error occurs, an exception is `thrown`.
- If the current function does not "catch" the error, the caller of the function has a chance to catch the error
- If the caller doesn't catch the error, the caller's caller has a chance to catch the error
- The error progressively moves up the call stack until it is either caught and handled, or until `main()` fails to handle the error

### When to use `std::cout` vs `std::cerr` vs logging


**Interactive Applications**: Those that the user will interact with after running\
**Non-Interactive Applications**: Applications that do not require user interaction to operate.
- The output of these programs may be used as input for another application

Within non-interactive applications, there are 2 types:
- **Tools**: Typically launched in order to produce some immediate results
- **Services**: Non-interactive applications that typically run silently in the background to perform some ongoing function

Rules of thumb:
- `std::cout` for all conventional, user-facing  text
- Interactive Program: `std::cout` for normal user-facing error messages ("Your input was invalid")
  - `std::cerr` or logfile for status and diagnostic information
    - Technical warnings and errors, percentage completion of long tasks, etc.
- Non-interactive program, use `std::cerr` for error output only
  - Allows errors to be displayed or parsed separately from normal output
- For any application type that is transactional in nature, use a logfile to produce a transactional log of events that can be reviewed later
  - Can include outputting to the logfile which file is being processed, updates on the percentage complete, timestamps, warning and error messages, etc.

# 9.5 - std::cin and handling invalid input

## Notes

**Robust**: A program that handles error cases well

### Validating Input

**Input Validation**: Process of checking whether user input conforms to what the program is expecting

3 Basic ways to do input validation:
- Inline: Prevent the user from typing invalid input in the first place
- Post-Entry:
  - Let the user enter whatever they want into a string,then validate whether the string is correct. If so, convert the string to the final variable format
  - Let the user enter whatever they want, let std::cin and operator>> try to extract it, and handle the error cases

Generally speaking, the programmer provides a validation function that accepts the input the user has entered so far, and returns true if the input is valid, and false otherwise

You can ensure that any input the user enters is guaranteed to be valid, because any invalid keystrokes are discovered and discarded immediately

Most often, we let std::cin and the extraction operator do the hard work
- We let the user enter whatever they want, std::cin and >> try to extract, and deal with the fallout if it fails

### A sample program

```cpp
#include <iostream>

double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        std::cout << x / y << '\n';
        return;
    }
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    printResult(x, operation, y);

    return 0;
}
```

The program asks the user to enter 2 numbers and a mathematical operator

```shell
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: *
Enter a decimal number: 7
5 * 7 is 35
```

### Types of invalid text input

Generally separate input text errors into 4 types
- Input extraction succeeds but the input ismeaningless to the program
- Input extraction succeeds but the user enters additional input
- Input extraction fails
- Input extraction succeeds but the user overflows a numeric value

### Error Case 1: Extraction Succeeds but input is meaningless

```shell
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: k
Enter a decimal number: 7
```

Do input validation, usually consists of 3 styeps:
1. Check whether the user's input was what you were expecting
2. If so, return the value to the caller
3. If not, tell the user something went wrong and have them try again

```cpp
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } // and try again
}
```

### Error Case 2: Extraction succeeds but with extraneous input

```shell
Enter a decimal number: 5*7
Enter one of the following: +, -, *, or /: Enter a decimal number: 5 * 7 is 35
```

The program prints the right answer, but the formatting is all messed up.

There is an easy way to ignore characters

```cpp
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
```

This removes up to 100 characters, but if the user entered more than 100 charactes, we'll get messy output

To ignore all characters up to the next `\n`, pass `std::numeric_limits<std::streamsize>::max()` to `std::cin.ignore()`

To ignore everything up to and including the next `\n` character, we call

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// Or just use this function
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

Updated getDouble function

```cpp
double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;

    ignoreLine();
    return x;
}
```

### Error case 3: Extraction fails

```shell
Enter a decimal number: a
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.

```

The last line keeps printing until the program isclosed

After `a` gets left in the buffer, `std::cin` goes into "failure mode"
- Once in "failure mode" future requests for input extraction will silently fail
- In order for `std::cin` to work properly again, we need to do 3 things
  - Detect that a prior extraction has failed
  - Put `std::cin` back in normal operation mode
  - Remove the input that caused the failure

```cpp
if (std::cin.fail()) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

Because `std::cin` has a Boolean conversion indicating whether the last input succeeded, it's more idomatic to write the above as following

```cpp
if (!std::cin) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

This can be integrated into our getDouble() function:

```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        // Our extraction succeeded
        ignoreLine(); // Ignore any additional input on this line
        return x;     // Return the value we extracted
    }
}
```

For fundamental types, a failed extraction due to invaid input will cause the variable to be assigned the value `0`
- It is fine to call `clear()` even when extraction hasn't failed

### Checking for EOF

An end-of-file (EOF) is a special error state that means "No more data available"
- Normally generated after an input operation fails due to no data being available

If we try to extract input from `std::cin` and there is none,by design it won't generate an EOF, it will just wait for the user to enter more input


`std::cin` can generate an EOF in certain cases, most commonly when the user enters a special key combination for their OS
- Unix: Ctrl+D
- Windows: Ctrl+Z + ENTER

The behavior is OS-specific

Typical EOF character behavior:
- If the EOF is not the first character of input: All input prior t o the EOF will be flushed, the EOF character is ignored
- If the EOF is the first character: The EOF error will be set, the input stream may or may not be disconnected

Although `std::cin.clear()` will clear an EOF error, if the input stream is disconnected, the next input request will generate another EOF error

The best thing to do is detect EOF and then terminate the program

```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```

### Error case 4: Extraction succeeds but the user overflows a numeric value

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;

    std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
    std::cout << "Enter another number between -32768 and 32767: ";
    std::cin >> y;

    std::cout << "The sum is: " << x + y << '\n';
    return 0;
}
```

```shell
Enter a number between -32768 and 32767: 40000
Enter another number between -32768 and 32767: The sum is: 32767
```

`std::cin` goes immediately into "failure mode", but also assigns the closest in-range value to the variable

### Putting it all together

Calculator with a few additional bits of error checking

```cpp
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
```

### Conclusion

Consider the following when writing your program:
- Could extraction fail?
- Could the user enter more input than expected?
- Could the user enter meaningless input?
- Could the user overflow an input?

# 9.6 - Assert and static_assert

## Notes

### Preconditions, invariants, and postconditions

**Precondition**: Any condition that must be true prior to the execution of some section of code
- Best placed at the top of a function, using an early return to return back to the caller if the precondition isn't met

```cpp
void printDivision(int x, int y)
{
    if (y == 0) // handle
    {
        std::cerr << "Error: Could not divide by zero\n";
        return; // bounce the user back to the caller
    }

    // We now know that y != 0
    std::cout << static_cast<double>(x) / y;
}
```

**Invariant**: A condition that must be true while some section of code is executing
- Often used with loops, where the loop body will only execute so long as the invariant is true

**Postcondition**: Something that must be true after the execution of some section of code

### Assertion

**Assertion**: An expression that will be true unless there is a bug in the program
- If the expression evaluates to `true`, the assertion statement does nothing
- If `false`, an error message is displayed and the program is terminated via `std::abort`

In C++ Runtime assertions are implemented via the `assert` preprocessor macro, which lives in the <cassert> header.

```cpp
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

  return 0;
}
```

When the program calls the function, `assert(gravity > 0.0)` will evaluate `false`
- Trigger the assert

```shell
dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.
```

### Making your assert statements more descriptive

Trick you can use to make your assert statements more descriptive.
- Add a string literal joined by a logical AND
```cpp
assert(found && "Car could not be found in database");
```

```shell
Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34
```

### Using assertions for unimplemented features

Assertions are also sometimes used to document cases that were not implemented because they were not needed at the time the programmer wrote the code

```cpp
assert(moved && "Need to handle case where student was just moved to another classroom");
```

### NDEBUG

The `assert` macro comes with a small performance cost that is incurred each time the assert condition is checked

Asserts should ideally never be encountered in porduction code\
Most developers prefer that asserts are only active in debug builds.

If the preprocessor macro `NDEBUG` is defined, the assert macro gets disabled

Most IDEs set `NDEBUG` by default as part of the project settings for release configurations

For testing purposes, you can enable or disable asserts within a given translation unit
- To do so, place 1 of the following on its own line **before** any #includes
- `#define NDEBUG` - disable asserts
- `#undef NDEBUG` - enable asserrts

```cpp
#define NDEBUG // disable asserts (must be placed before any #includes)
#include <cassert>
#include <iostream>

int main()
{
    assert(false); // won't trigger since asserts have been disabled in this translation unit
    std::cout << "Hello, world!\n";

    return 0;
}
```

### static_assert

**Static Assert**: An assertion that is checked at compile time rather than at runtime
- A failing `static_assert` causes a compile error

```cpp
static_assert(condition, diagnostic_message)
```

If the condition is not true, the diagnostic message is printed

```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```

Notes about `static_assert`:
- `static_assert` is evaluated by the compiler, the condition must be a constant expression
- `static_assert` can be placed anywhere in the code file
- `static_assert` is not deactivated in release builds
- Because the compiler does the evaluation, there is no runtime cost to a `static_assert`

Favor `static_assert` over `assert()` whenever possible

### Assert vs error handling

Assertions are used to detect *programming errors* during development by documenting assumptions about things that should never happen
- If they do happen, it's the fault of the programmer
- Does not allow recovery from errors
- Typically compiled-out in release builds

Error handling is used when we need to gracefully handle cases that could happen in a release build
- Either be recoverable issues or unrecoverable issues
- Both a runtime performance cost and a development time cost

### Some assert limitations and warnings

Few pitfalls and limitations to assert
- Assert itself can be imprperly written
  - The assert will either report an error where none exists, or fail to report a bug where one does exist
- `assert()` expression should have no side effects, as the assert expression won't be evaluated when `NDEBUG` is defined

`abort()` function terminates the program immediately, without a chance to do any further cleanup
- Asserts should be used only in cases where corruption isn't likely to occur if the program terminates unexpectedly

