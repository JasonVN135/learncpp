# 1.1 - Statements and the structure of a program

## Questions

1. What is a statement?
  - **Statement**: A type of instruction that causes the program to *perform some action*
2. What is a function?
  - **Function**: A collection of statements that get performed sequentially. 
3. What is the name of the function that all programs must have?
  - **main**
4. What happens when the program is run?
  - It executes the statements in main in sequential order.
5. What symbol are statements in C++ often ended with?
  - Semicolons (;)
6. What is a syntax error?
  - When the program deviates from the standard syntax of the language
7. What is the C++ Standard Library
  - A library filled with precompiled code that has been "packaged up" for reuse in other programs

## Notes

### Statements

Statements: Smallest independent unit of computaiton in the C++ language.
Most but not all statments in C++ end in a semicolon. Lines that end in a semicolon are probably statements

Different kinds of statements
- Declaration statements
- Jump statements
- Expression statements
- Compound statements
- Selection/Conditional statements
- Iteration/Loop statements
- Try blocks

### Functions and the **main** function

**Function**: A collection of statements that get executed sequentially
- Every C++ program must have a special function named **main**

When a program is run, statements inside **main** are run in sequential order
Progras typically terminate (finish running) the last statement inside function **main**
- Fairly common shorthand to append a pair of parenthesis to the end of the funtion's name.

**Identifier** The name of a function

### Characters and text

**Character**: A written symbol or mark (letter, digit, punctuation mark, mathematical mark)
**Text** Sequence of characters (also **string**)
- Text also used to mean plain text, text that contains only characters that appear on a standard keyboard, no special formatting or styling. Ex: No bold, italics, tables.
- C++ programs are written as plain text.

Computers have "control characters". Characters that have special meaning to the computer system, but either aren't intended to be displayed, or displays as something other than a single visible character.
- Ex: "escape", "tab", "backspace"

### Dissecting Hello world!

```cpp
#include <iostream>

int main()
{
   std::cout << "Hello world!";
   return 0;
}
```

**#include <iostream>**: Preprocessor directive
- `#include` indicates that we would like to use the contents of the `iostream` library
- `iostream` part of the C++ standard library that allows us to read and write text from/to the console.
  - Used for `std::cout`

**int main()**: Tells the compiler we're going to write a function whose name is main

**{ }**: Tells which lines are part of the *main* function.

**std::cout**: The first statement that will execute when we run our program
- Stands for "character output"
- `<<`: Allow us to display information on the console

**return 0**: A return statement, when an executable program finishes running.
- Send a value back to the operating system in order to indicate whether it ran successfully or not
- `0`: Everything went okay

### Syntax and syntac errors

**Syntax**: The set of rules that describe how specific words can be arranged to form valid sentences in a lnaguage
*Syntax Error*: When your program does something that deviates from the syntax of the language. The compiler will halt compilation
- Syntax rules of C++ are strictly defined and upheld

# 1.2 - Comments

## Notes

**Comment**: A programmer-readable note that is inserted directly into the source code of the program
- For programmer use only
- Ignored by compiler

### Single-line comments

`//`: Single-line comment. Ignore everything from the `//` symbol to the end of the line
- Used for quick comments about a single line of code
- Often placed above the line it is commenting

```cpp
// std::cout lives in the iostream library
std::cout << "Hello world!\n";

// this is much easier to read
std::cout << "It is very nice to meet you!\n";

// don't you think so?
std::cout << "Yeah!\n";
```

### Multi-line comments
`/* */`: Denotes a C-style multi-line comment.
- Everything in between the symbols are ignored
- Sometimes beautify with a `*` at the start of each line
- Cannot be nested

```cpp
/* This is a multi-line comment.
 * the matching asterisks to the left
 * can make this easier to read
 */
```

### Proper use of comments

1. For a given library, program or function, best used to describe *what* the library, program, or function does
  - Typically placed at the top of the file or library, or immediately preceding the function
2. Within a library, program or function, used to describe *how* the code is going to accomplish its goal
3. At the statement level, used to describe *why* the code is doing something
  - Bad statement comment explains *what* the code is doing
  - If you need to write *what*, you should rewrite your statement, not comment.

```cpp
// Bad Comment
// Set sight range to 0
sight = 0;

// Good Comment
// The player just drank a potion of blindness and can not see anything
sight = 0;

// Good Comments
// We decided to use a linked list instead of an array because
// arrays do insertion too slowly.

// We're going to use Newton's method to find the root of a number because
// there is no deterministic way to solve these equations.
```

Comments should be written in a way that makes sense to someone who has no idea what the code does

### Commenting out code

**Commenting out**: Converting 1+ lines of code into a comment
- Provides a convenient way to (temporarily) exclude parts of your code from being included in your compiled program
- For multiple single line comments in VS Code: `Ctrl + /`

Reasons to comment out code:
- New code won't compile yet, and you need to run the program. Comment out to run the program, the uncomment to continue working on it.
- Written new code but it won't compile correctly. Commenting out broken code will ensure the bbroken code doesn't execute and cause problems until you can fix it.
- To find the source of an error.
- Want to replace one piece of code with another piece of code.

# 1.3 - Introduction to objects and variables

## Questions

1. What is data?
  - Any information that can be moved, processed, or stored by a computer
2. What is a value?
  - A single piece of data
3. What is an object
  - A region of memory that is used to store a value
4. What is a variable?
  - A named object
5. What is an identifier?
  - A way to distinguish an object, the name of a variable
6. What is a data type used for?
  - Determines what kind of value the object will store.
7. What is an integer?
  - A number that can be represented without fractional values.

## Notes

### Data and values

**Data**: Any information that can be moved, processed, or stored by a computer.
- Can be acquired from file, databases, a network, or the user providing input

Programs are colletions of instructions that manipulate data to produce a desired result

**value**: A single piece of data (Sometimes called *data value*)
- Numbers: 5, -6.7
- Characters: 'h', '$'
- Text (In double quotes): "Hello", "H"
  - Can contain 0+ characters

**literals**: Values placed directly into the source code
- Literals are read only values, so their values can't be modified

### Random Access Memory

**Random Access Memory (RAM)**: The main memory in a computer
- When we run a program, the operating ysstem loads the program into RAM
- Any data that is hardcoded into the program itself is loaded at this point

The OS also reserves some additional RAM for the program to use while it is running.
- Common uses:
  - Store values entered by the user
  - Store data read in from a file/network
  - Store values calculated while the program is running so they can be used again later

RAM is like a series of numbered boxes that can be used to store data while the program is running

### Objects and Varables

Direct memory access is discouraged. Instead we access memory indirectly through an object

**Object**: Represents a region of storage (in RAM or a CPU register) that can hold a value

Rather than "go get the value stored in mailbox number 7532", we say "go get the value storedby this object"
- Let the compiler figure out where and how to retrieve the value.
- We focus on using objects to store and retrieve values
- Not worry about where in memory those objects are actually being placed

**Variable**: An object with a name

### Variable definition

**Definition**: A way to tell the compiler we want a variable in our program.
- There is a difference between definition and declaration.
- Definition statement can be used to tiell the compiler that we want to use a variable in our program

```cpp
int x; // define a variable named x (of type int)
```

**Compile-Time**: When the program is being compiled
- When encountering the definition, the compiler makes a note to itself that we want a variable witht eh name `x` with a data type `int`
- The compiler will know that we are referring to this variable when we use the identifier `x`

A variable created via a definition statement is said to be **defined**.

### Variable Creation

**Runtime**: When the program is loaded into memory and run.
**Allocation**: The process of reserving storage for an object's use
- At runtime, each object is given an actual storage location (In RAM or CPU register) that can be used to store values

### Data Types

**Data Type**: Commonly called `type`, determines what kind of value the object will store.
**Integer**: A number than can be written without a fractional component.
- The data type of an object must be known at compile-time

### Defining multiple variables

Possible to define multiple variables of the *same type* in a single statement by separating the names with a comma

```cpp

int x;
int y;

// This is the same thing
int x, y;

// This isn't doable
int x, int y;
int x, double y;
```

# 1.4 - Variable assignment and initialization

## Questions

1. What is the difference between initialization and assignment?
  - Assignment occurs after definition or when assigning a new value. Initialization when providing an initial value right when it is first defined.
2. What form of initialization should you prefer when you want to initalize a variable with a specific value?
  - List-initialization
3. What are default-initialization and value-initialization? What is the behavior of each? Which should you prefer?
  - Default initialization has no initializer. No value is set at all. Value initialization will attempt to set the object value to 0 if possible. Use default when you will assign a value later. Use value when you still plan to use the variable.

## Notes

### Variable Assignemnt

**Assignemnt**: Giving a variable a value using the `=` operator.
- `=` is the **assignment operator**

```cpp
int width; // define an integer variable named width
width = 5; // assignment of value 5 into variable width

// variable width now has value 5
```

**Copy-assignment**: Copies the value on the right-hand side of the `=` to the variable on the left-hand side.

Values can be printed via `std::cout` and `<<` after it has been assigned

```cpp
#include <iostream>

int main()
{
	int width; // define a variable named width
	width = 5; // copy assignment of value 5 into variable width

	std::cout << width; // prints 5

	width = 7; // change value stored in variable width to 7

	std::cout << width; // prints 7

	return 0;
}
```

First, execution begins at the top of the `main` function.\
Memory for `width` is allocated.\
Then we assign `width` the value of 5\
We the print 5 to the console.\
We then assign the value 7 to `width`. Any prior value is overwritten.\
Thus we output 7 for the `width`.

Normal variables can only hold ` value at a time.

### Variable initialization

**Initalization**: Providing an initial value for the object when first defined.
- The syntax used to initialize an object is called an **initializer**.

### Different forms of initialization

```cpp
int a;         // default-initialization (no initializer)

// Traditional initialization forms:
int b = 5;     // copy-initialization (initial value after equals sign)
int c ( 6 );   // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
int d { 7 };   // direct-list-initialization (initial value in braces)
int e {};      // value-initialization (empty braces)
```
As of C++17, copy-initialization, direct-initalization, and direct-list-initalization behave identically in most cases

### Default-initialization

**Default-initialization**: When no initializer is provided. Default-initialization performs no initalization, and leaves the variable with an indeterminate value

### Copy-initialization

**Copy-initialization**: When an initial value is provided after an equal sign.
- Inherited from C.
- Copies the value from the right to the left
- Fallen out of favor in modern c++ due to being less efficient for some complex types, but has been fixed/remedied in C++17

### Direct-initalization

**Direct-initalization**: When an initial value is provided inside parenthesis
- Initially introduced to allow more efficient initialization of complex objects (Class types)
- Fallen out of favor in modern C++, due to being supersed by direct-list-initialization.
- Still finding use in certain cases

### List-initalization

**List-initialization**: Initialization with curly braces
- Also called uniform initialization or brace initialization.
- Modern way to initializae objects
- Used to provide a initialization syntax that works in almost all cases, behaves consistently
- Has an umabiguous syntax that makes it easy to tell where we're initializing an object

### List-initialization disallows narrowing conversion

Primary benefit is that "narrowing conversions" are disallowed
- Compiler is required to produce a diagnostic (compilation error or warning) when trying to initialize a variable with a value the variable cannot hold.

```cpp
int main()
{
    // An integer can only hold non-fractional values.
    // Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold.
    // Such a conversion is a narrowing conversion, since the fractional part of the value will be lost.

    int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

    int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
    int w3 (4.5);   // compiles: w3 direct-initialized to value 4

    return 0;
}
```

### Value-initialization and zero-initialization

**Value-initialization**: When a variable is initialized using an empty set of braces
- Most cases, value-initialization will implicitly initialize the variable to zero.
**Zero-initialization**: When zeroing occurs

```cpp
int width {}; // value-initialization / zero-initialization to value 0
```

### List initialization is the preferred form

List initialization is preferred as it works in most cases and more consistent.\
It disallows narrowing conversions.\
Supports initalization witha  lsit of values\

#### Q: When should I initialize with { 0 } vs {}?

Use direct-list-initialzation when you're actually using the initial value.

```cpp
int x { 0 };    // direct-list-initialization with initial value 0
std::cout << x; // we're using that 0 value here
```

Use value-initialization when the object's value is temporary and will be replaced.

```cpp
int x {};      // value initialization
std::cin >> x; // we're immediately replacing that value so an explicit 0 would be meaningless
```

### Instantiation

**Instantiation**: Fancy word that means a variable has been created and initalized.
- Instantiated objects are sometimes called an **instance**.
  - Term is applied to class type objets, occassionally applied to other types.

### Initializing multiple variables

You can initialize multiple variables defined on the same line

```cpp
int a = 5, b = 6;          // copy-initialization
int c ( 7 ), d ( 8 );      // direct-initialization
int e { 9 }, f { 10 };     // direct-list-initialization
int i {}, j {};            // value-initialization

int a, b = 5;     // wrong: a is not initialized to 5!
int a = 5, b = 5; // correct: a and b are initialized to 5
```

### Unused initialized variable warnings

Modern compilers will typicall generate warnings if a variable is initialized but not used.

When compiling with GCC and "treat warnings as errors" on, the following error is generated and fails to compile:
```shell
prog.cc: In function 'int main()':
prog.cc:3:9: error: unused variable 'x' [-Werror=unused-variable]
```

### The [[maybe_unused]] attribute (C++17)

```cpp
#include <iostream>

int main()
{
    // Here's some math/physics values that we copy-pasted from elsewhere
    double pi { 3.14159 };
    double gravity { 9.8 };
    double phi { 1.61803 };

    std::cout << pi << '\n';  // pi is used
    std::cout << phi << '\n'; // phi is used

    // The compiler will likely complain about gravity being defined but unused

    return 0;
}
```

C++17 introduced `[[maybe_unused]]` attribute. Allows us to tell the compiler that we're okay with a variable being unused.
- Should only be applied selectively to variables that have a specific and legitimate reasoning for being unused

```cpp
#include <iostream>

int main()
{
    [[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
    [[maybe_unused]] double gravity { 9.8 }; // Don't complain if gravity is unused
    [[maybe_unused]] double phi { 1.61803 }; // Don't complain if phi is unused

    std::cout << pi << '\n';
    std::cout << phi << '\n';

    // The compiler will no longer warn about gravity not being used
```

# 1.5 - Introduction to iostream: cout, cin, and endl

## Questions

1. Considering the following program that we used above:
```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter a number: "; // ask user for a number
    int x{}; // define variable x to hold user input
    std::cin >> x; // get number from keyboard and store it in variable x
    std::cout << "You entered " << x << '\n';

    return 0;
}
```
What would the output for each input be:
- A letter (h):
  - 0, x will default to 0
- A number with a fraction (3.2, 3.7)
  - 3, >> uses copy, so the fraction will be removed
- A small negative int (-3):
  - -3. Extraction is successful. The `-` is acceptable for int.
- A word (Hello):
  - 0, H is not accepted, Hello is left in the buffer
- A big number (3 billion):
  - 2147483647, number is too big for an integer type
- A small number with letters (123abc):
  - 123, 123 is read, then stops at a
- A few letters with numbers (abc123):
  - 0, a stops the extraction
- (   +5) 3 spaces and +5:
  - 5, removes leading spaces, `+` is accepted
- 5b6:
  - 5, reads 5, then drops at `b`

2. Create a program to ask the user to enter 3 values. The program should print these values. The program should match the following output:
```shell
Enter three numbers: 4 5 6
You entered 4, 5, and 6.
```

```cpp
#include <iostream>

// Reads 3 numbers from user input in terminal and prints the input in a formatted message.
int main() {

  int x {}, y {}, z{};

  std::cout << "Enter three numbers: ";
  std::cin >> x >> y >> z;

  std::cout << "You entered " << x << ", " << y << ", and " << z << ".\n";

  return 0;
}

## Notes

### The input/output library

**Input/Output Library (io library)**: Part of the C++ library that deals with asic input and output

Need to include the *iostream* header at the top of any code file that uses the content defined in *iostream*.

### std::cout

**std::cout**: Send data to the console to be printed as text
- Can also print numbers
- Can print values of variables

```cpp
#include <iostream> // for std::cout

int main()
{
    std::cout << 4; // print 4 to console

    int x{ 5 }; // define integer variable x, initialized with value 5
    std::cout << x; // print value of x (5) to console

    return 0;
}
```

Using the insertion key (<<) can be used multiple times in a single statment to concatenate (link) multiple pieces of output

```cpp
#include <iostream> // for std::cout

int main()
{
    std::cout << "Hello" << " world!";
    return 0;
}
```

### std::endl to output newline

Separating output statements don't result in separate lines of output on the console.
**newline**: An OS-specific character/sequence of characters that moves the cursor to the start of the next line

```cpp
#include <iostream> // for std::cout and std::endl

int main()
{
    std::cout << "Hi!" << std::endl; // std::endl will cause the cursor to move to the next line
    std::cout << "My name is Alex." << std::endl;

    return 0;
}
```

Best Practice: Output a newline whenever a line of output is complete

### std::cout is buffered

Requested output "gets in line", and is stored in a region of memory set aside to collect requests (**Buffer**).\
Periodically, the buffer is **flushed**: All data collected in the buffer is transferred to its destination (The console).

### std::endl vs \n

`std::endl` does 2 jobs, output a newline and flushes the buffer (which is slow). 
- Outputing multiple lines with `std::endl` will have multiple flushes which is slow.
`\n`: A special symbol that the compiler interprests as a new line character.
- Can be embedded into existing double-quoted text

```cpp
#include <iostream> // for std::cout

int main()
{
    int x{ 5 };
    std::cout << "x is equal to: " << x << '\n'; // single quoted (by itself) (conventional)
    std::cout << "Yep." << "\n";                 // double quoted (by itself) (unconventional but okay)
    std::cout << "And that's all, folks!\n";     // between double quotes in existing text (conventional)
    return 0;
}
```

Use single quotes ('') to represent a single character. Double quotes ("") to represent text.
- `\n` is treated as 1 character.
- Using "\n" is fine, just unconventional.

### std::cin

`std::cin`: Stands for "character input", reads input from the keyboard. Extracted with `>>`.

```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter a number: "; // ask user for a number

    int x{};       // define variable x to hold user input (and value-initialize it)
    std::cin >> x; // get number from keyboard and store it in variable x

    std::cout << "You entered " << x << '\n';
    return 0;
}
```

The program will wait for user input at `std::cin`. Once you hit `Enter`, the number you enter will be assigned to `x`.

Possible to input more than one value on a single line.

```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter two numbers separated by a space: ";

    int x{}; // define variable x to hold user input (and value-initialize it)
    int y{}; // define variable y to hold user input (and value-initialize it)
    std::cin >> x >> y; // get two numbers and store in variable x and y respectively

    std::cout << "You entered " << x << " and " << y << '\n';

    return 0;
}
```

### std::cin is buffered

Inputting data is also a 2 stage process
- Individual characters you enter as input are added to the end of an input buffer (inside std::cin). The enter key is stored as `\n`
- Extraction operator `>>` removes characters from the front of the input buffer and converts them into a value that is assigned (copy assignment) to the associated variable
- Each line of input data in the input buffer is terminated by a `\n` character

### Basic extraction process

Explanation of >> for input
1. If `std::cin` is not n a good state (prior extraction failed, `std::cin` has not yet been cleared), no extraction is attempted, extraction aborts immediately
2. Leading whitespace characters (space, tabs, newliens at the front) are discarded. This will discard an unextracted newline character remaining from a prior line of input
3. If input buffer is empty, `>>` will wait for the user to enter more data. Leading whitespace is dicarded from the entered data
4. `>>` Extracts as many consecutie characters as it can, until it encounters either a newline character (End of Input) or a character that is not valid for the variable. If an extraction fails, it will default the value to 0.

# 1.6 - Uninitialized variables and undefined behavior

## Questions

1. What is an unitialized variable? Why should you avoid using them?
  - An unitialized variable are variables that have yet to be assigned a value. It can be difficult to debug as the program may compile even if it is not running correctly.
2. What is undefined behavior, and what can happen if you do something that exhibits undefined behavior?
  -The result of executing code whose behavior is not well-defined by the C++ language. It can crash, produce random otuput, or incorrect output.

## Notes

### Uninitialized Variables

C/C++ does not automatically initialize most variables to a given value.\
**Uninitialized Variable**: A variable that has not been given a known value (through initialization or assignment)

```cpp
int x; // An uninitalized variable
```

This lack of initialization is a performance optimization inherited from C
- For now, always initialized your variables

Using values of uninitialized variables can lead to unexpected results

```cpp
#include <iostream>

int main()
{
    // define an integer variable named x
    int x; // this variable is uninitialized because we haven't given it a value

    // print the value of x to the screen
    std::cout << x << '\n'; // who knows what we'll get, because x is uninitialized

    return 0;
}
```

The value that is printed will be random.\
Most modern compilers will attempt to detect if a variable is being used without being given a value.
- If detected, they will generally issue a compile-time warning or error

### Undefined Behavior

**Undefined Behavior (UB)**: The result of executing code whose behavior is not well-defined by the C++ language.

Code implementing undefined behavior may exhibit any of the following symptoms: Your program:
  - Produces different results every time
  - Consistently produces the same incorrect result
  - Behaves inconsistently
  - Seems like it's working but produces incorrect results later in the program
  - Crashes
  - Works on some compilers but not others
  - Works until you change some other seemingly unrelated code

### Implementation-defined behavior and unspecified behavior

**Implementation**: A specific compiler and the associated standard library it comes with
- Some cases, the C++ language standard allows the implementation to determine how some aspect of the language will behave.
**Implementation-defined behavior**: Behavior that is defined by the implementation
**Unspecified behavior**: Almost identical to implementation-defined behavior in that the behavior is left up to the implementation to defined, but the implementation is not required to docuemnt the behavior
- Generally want to avoid implementation-defined and unspecified behavior.

# 1.7 - Keywords and naming identifiers

## Questions

1. Indicate whether each variable name is conventional, unconventional, or invalid
- int sum {}; Conventional
- int _applies {}; Unconventional
- int VALUE {}; unconventional
- int my variable name {}; invalid
- int TotalCustomers {}; unconventional
- int void {}; invalid
- int numFruit {}; conventional
- int 3some {}; invalid
- int meters_of_pipe {}; conventional

## Notes

### Keywords

**Keywords**: Reserved words in C++ which have special meanings within the C++ language.

C++ Also defines special identifiers: *override final, import, and module*
- These have a specific meaning when used in certain context but are not reserved otherwise.

### Identifier naming rules

Few rules that must be followed when naming identifiers:
- Ca not be a keyword
- Can only be composed of letters, numbers, and underscore characters
  - Cannot contain symbols nor whitespace
- Must begin witha  letter or an underscore, not a number
- C++ is case sensitive, dinstinguishing between lower and upper case. 
  - nvalue != nValue != NVALUE

### Identifier naming best practices

1. variables names should begin with a lowercase letter.
  - If the variable name is a single word/acronym, the whole thing should be written in lowercase
  - Most often, functions also start with lowercase letter
  - Starting with capital letters is typically used for user-defined types (structs, classes, enums)
  - If multi-word, 2 approaches
    - separate with underscores (snake case)
    - intercapped (camelCase, We'll use this)
2. Avoid naming identifiers with an underscore.
   - Typically reserved for OS, library, and/or compiler use
3. Name of your identifier should make clear what the value they are holding means
4. Avoid abbreviations, except when they are comon and unambiguous (num, cm, idx)
5. For variable declaration, it can be useful to use a comment to describe what a variable is going to be used for

# 1.8 Whitespace and Basic Formatting

## Notes

**Whitespace**: Aterm that refers to characters that are used for formatting purposes
- Primarily spaces, tabs, and newlines
- Used for:
  - Separating certain language elements
  - Inside text
  - Formatting code

### Some language elements must be whitespace-separate

Mostly occurs when 2 keywords/identifiers must be placed consecutively, so the compiler can tell it apart.

```cpp
int x; // int and x must be whitespace separated

int main(); // int and main must be whitespace separated
```

Compiler doesn't care how much whitespace is used, as long as some exist. The following are valid:

```cpp
int x;
int                y;
            int
z;
```

Certain cases, new lines are separators. Single-line comments are terminated by newlines

```cpp
std::cout << "Hello world!"; // This is part of the comment and
this is not part of the comment
```

### Quoted text takes the amount of whitespace literally

Inside quoted text, the amount of whitespace is taken literally

```cpp
std::cout << "Hello world!";
// Two different things
std::cout << "Hello              world!";

std::cout << "Hello
     world!"; // Newlines not allowed!
```

Quoted text separated by nothing but whitespace will be concatenated
```cpp
std::cout << "Hello "
     "world!"; // prints "Hello world!"
```

### Using whitespace to format

Whitespace is otherwise generally ignored
- Can use whitespace wherever we like to format our code

```cpp
// This is bad
#include <iostream>
int main(){std::cout<<"Hello world";return 0;}

// This is great
#include <iostream>

int main()
{
    std::cout << "Hello world";

    return 0;
}
```

### Basic formatting

C++ does not enforce any kind of formatting restrictions on the programmer
- C++ is a whitespace-independent language
- The best styles are the ones that produces the most readable code and provide the most consistency

Recommendations for basic formatting:
1. Tabs = 4 spaces 
2. Opening braces on their own lines
```cpp
int main()
{
    // Statement
}
```
3. Each statement within curly braces should start 1 tab in from the opening brace of the function it belongs to.
```cpp
int main()
{
    std::cout << "Hello world!\n"; // tabbed in one tab (4 spaces)
    std::cout << "Nice to meet you.\n"; // tabbed in one tab (4 spaces)
}
```
4. Lines shoudl not be too long. 80 characters has been the de facto standard for max line length
5. If a long line is split with an operator (e.g. << or +), the operator should be placed at the beginning fo the next line, not the end of the current line
```cpp
std::cout << 3 + 4
    + 5 + 6
    * 7 * 8;
```
6. Use whitespace to make your code easier to read by aligning values or coments or adding space between blocks of code
```cpp
cost          = 57;
pricePerItem  = 24;
value         = 5;
numberOfItems = 17;
```

Best Practice: Be consistent with whatever style has already been adopted.

# 1.9 Introduction to literals and operators

## Questions

1. For each, indicate what output they produce:
- std::cout << 3 + 4 << '\n'; 7
- std::cout << 3 + 4 - 5 << '\n'; 2
- std::cout << 2 + 3 * 4 << '\n'; 14

Extra:
```cpp
int x { 2 };
std::cout << (x = 5) << '\n';
```
- 5

## Notes

### Literals

```cpp
std::cout << "Hello world!";
int x { 5 };
```

**Literal**: Also literal constant, fixed value that has been inserted directly into the source code.
- The value of a literal is fixed and cannot be changed
- 5 is always 5, literals are called constants

```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n'; // print the value of a literal

    int x { 5 };
    std::cout << x << '\n'; // print the value of a variable
    return 0;
}
```

The value 5 can be printed directly. In a variable the value must be fetched from the memory of the variable represented.
- Literals are constant while variables can be changed

### Operators
**Operation**: Process involving 0+ input values that produces a new value
**Operator**: The symbol that denotes the operation to be performed
**Return Value**: The output of an operation

**Arity**: The number of operands that an operator takes as input

4 Different arities:
- **Unary**: Operators that act on one operand.
  - `-`: The negative. Turns a `5` into `-5`
- **Binary**: Acts on 2 operands (left and right).
  - `+`: Takes operands 3 and 4 and applies math for an output of 7
  - `<<std::in>>`: Takes `std::cout` and a value to output to perform its action
- **Ternary**: Acts on 3 operands. Only the conditional operator
- **Nulliary**: Acts on zero operands. Only the `throw` operator.

### Chaining Operators

Operators can be chained together such that the output of one operator can be used as the input for another operator.
- PEMDAS order operates as normal

### Return value and side effects

There are a few operators that do not produce return values (delete and throw)\
Some operators have additional behaviors with **side effects**, an observable effect of an operator or function beyond producing a return value
- `x = 5` has the side effect of assigning value 5 to variable x
- `std::cout << 5` has the side effect of print 5 to the console

# 1.10 - Introduction to expressions

## Questions

1. What is the difference between a statement and an expression?
  - statements are used when we want the program to perform an action, expressions are for calculations
2. Indicate whether each of the following lines are *statements that do not contain expressions, statements that contain expressions,* or are *expression statements*
- int x; statements that do not contain expressions
- int x = 5; statements that contain expressions
- x = 5; expression statements
- foo(); expression statement
- std::cout << x; expression statement
1. Determine what values the following program outputs. Do not compile this program. Just work through it line by line in your head.
```cpp
#include <iostream>

int main()
{
	std::cout << 2 + 3 << '\n';

	int x{ 6 };
	int y{ x - 2 };
	std::cout << y << '\n';

	int z{};
	z = x;
	std::cout << z * x << '\n';

	return 0;
}
```
Output: 5\n
4\n
36\n

## Notes

### Expressions

```cpp
// five() is a function that returns the value 5
int five()
{
    return 5;
}

int main()
{
    int a{ 2 };             // initialize variable a with literal value 2
    int b{ 2 + 3 };         // initialize variable b with computed value 5
    int c{ (2 * 3) + 4 };   // initialize variable c with computed value 10
    int d{ b };             // initialize variable d with variable value 5
    int e{ five() };        // initialize variable e with function return value 5

    return 0;
}
```

The initializers above make use of a variety of different entities: literals, variables, operators, and function calls.
- All make use of an expression

**Expression**: A non-empty sequence of lieterals, variables, operators, and function calls that calculate a value.
**Evaluation**: The process of executing an expression
**Result (return value)**: The resulting value produced from the expression

Expressions do not end in a semicolon, and cannot be compiled by themselves.
```cpp
int x{ 2 + 3 }; // 2 + 3 is an expression that has no semicolon -- the semicolon is at the end of the statement containing the expression
```

If you were to break this statement down into its syntax, it would look like:
- `type identifier { expression}`

### Expression Statements
Certain expressions (Ex: x = 5) are used for their side effects (Assigning value) rather than the value they produce (x).
**Expression statement**: A statement that consists of an expression followed by a semicolon.

Expression: `x = 5`\
Expression Statement: `x = 5;`\
- Any result generated by the expression is discarded.
- `x = 5`: The return value of the operator= (x), is discarded, and that's fine.

### Useless expression statements

The expression `2 * 3;` is an expression statement whose expression evaluates to the result of value of *6*, which is then discarded.

### Subexpressions, full expressions, and compound expressions

```cpp
2               // 2 is a literal that evaluates to value 2
2 + 3           // 2 + 3 uses operator+ to evaluate to value 5
x = 4 + 5       // 4 + 5 evaluates to value 9, which is then assigned to variable x
```

**Subexpression**: An expression used as an operand.
- Subexpression of `x = 4 + 5` are `x` and `4 + 5`
  - Subexpression of `4 + 5` are `4` and `5`
**Full Expression**: An expression that is not a subexpression
- All `2`, `2 + 3`, and `x = 4 + 5` are full expressions, as they aren't the subexpression of something else.
**Compound Expression**: An expression that contains 2+ uses of operators
- `x = 4 + 5` is a compound expression (= and +)

# 1.11 - Developing your first program

## Questions

1. Modify the solution to the “best solution” program above so that it outputs like this (assuming user input 4):
```shell
Enter an integer: 4
Double 4 is: 8
Triple 4 is: 12
```

```cpp
#include <iostream>

int main()
{
  std::cout << "Enter an integer: ";
  
  int value {0};
  std::cin >> value;

  std::cout << "Double that number is: " << (value * 2) << "\n";
  std::cout << "Triple that number is: " << (value * 3) << "\n";

  return 0;
}
```

## Notes

### Multiply by 2

Create a program that asks the user to enter an int, wait, then tells what 2 times that number is.

```shell
Enter an integer: 4
Double that number is: 8
```

```cpp
#include <iostream>

int main()
{
  std::cout << "Enter an integer: ";
  
  int value {0};
  std::cin >> value;

  std::cout << "Double that number is: " << (value * 2) << "\n";

  return 0;
}
```

# 1.x - Chapter 1 Summary and Quiz

## Review

- **Statement**: Type of instruction that causes the program to perform some action
  - Often terminated by a semicolon
- **Function**: A colletion of statements that execute sequentially. Every C++ program must include a special function named *main*.
- **Identifier**: The name of a function
- **Syntax**: The rules that govern how elements of the C++ language are constructed
- **Syntax Error**: Occurs when you violate the grammatical rules of the language
- **Comments**: Allows the programmer to leave notes in the code
- **Data**: Any information that can be moved, processed, or stored by a computer
- **Value**: A single piece of data
- **Definition Statement**: Used to create a variable
- **Instantiated**: When a variable is assigned a memory address
- **Data Type**: Tells the compiler how to interpret a piece of data into a meaningful value
- **Integer**: A number that can be written without a fractional component
- **Copy Assignment**: Used to assign an already created variable a value
- **initialization**: Process of specifying an initial value for an object
- **Initializer**: Syntax used to initialize an object

Initialization Types
- Default Initialization - int x; - Most cases, leaves variable with indeterminate value
- Copy Initialization - int x = 5;
- Direct Initialization - int x (5); - Sometimes called parenthesis initialization
- Direct-List Initialization - int x {5}; - Narrowing conversions disallowed
- Copy-List Initialization - int x = {5}; - Narrowing conversions disallowed
- Value initialization - int x {}; - Usually performs zero-initialization

**std::cout**: And `operator<<` allow us to output the result of an expression to the console
**std::endl**: Outputs a newline character, forcing console cursore to move to the next line, and flushes any pending coutcome to the console.
**std::cin**: And `operator>>` allow us to get a value from the keyboard.
**Uninitialized variable**: A variable that has not been given a value.
**Undefined Behavior**: Trying to get the value of an uninitialized variable.
**Keywords**: C++ reserved names
**Literal Constant**: Fixed value inserted directly into the source code
**Operation**: Process involving 0+ input values to perform an action
**Operator**: Determines the operation to be performed
**Unary Operators**: Take 1 operands
**Binary Operators**: Take 2 operands
**Ternary Operators**: Take 3 operands
**Nullary Operators**: Take 0 Operands
**Expression**: Sequence of literals, variables, operators, and function calls that are evaluated to produce a single output value
**Evaluation**: The calculation of expression output
**Result/Return Value**: The value produced from the expression
**Expression Statement**: An expression that includes a semicolon at the end

## Quiz

1. What is the difference between initialization and assignment? How many times can a variable be initialized or assigned a value?
  - Intialization: Assigns a value to the variable on creation.
  - Assignments: Assign a new value to an existing variable.
  - A variable can be initialized once, but assigned as many times.

2. When does undefined behavior occur? What are the consequences of undefined behavior?
  - Undefined behavior occurs when trying to perform actions with uninitialized variables.
  - An error will typically occur or random/unexpected results will occur

3. Write a program that asks the user to enter a number, and then enter a second number. The program should tell the user what the result of adding and subtracting the two numbers is.

The output of the program should match the following (assuming inputs of 6 and 4):

```shell
Enter an integer: 6
Enter another integer: 4
6 + 4 is 10.
6 - 4 is 2.
```

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int firstNum{0};
    std::cin >> firstNum;

    std::cout << "Enter another integer: ";

    int secondNum{0};
    std::cin >> secondNum;

    std::cout << firstNum << " + " << secondNum << " is " << firstNum + secondNum << ".\n";
    std::cout << firstNum << " - " << secondNum << " is " << firstNum - secondNum << ".\n";

    return 0;
}
```