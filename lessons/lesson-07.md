# 7.1 - Compound Statements

## Notes

**Compound Statement**: A block or block statement, a group of 0+ statements that is treated by the compiler as if it were a single statement
- Begins and ends with `{}`
- Statements to be executed being placed in between
- No semccolon is needed at the end of a block

### Blocks inside other blocks

Functions can't be nested inside other functions\
Blocks can be nested inside other blocks

**Outer Block**: The enclosing block
**Inner Block**: (**Nested Block**) The enclosed block

```cpp
int add(int x, int y)
{ // block
    return x + y;
} // end block

int main()
{ // outer block

    // multiple statements
    int value {};

    { // inner/nested block
        add(3, 4);
    } // end inner/nested block

    return 0;

} // end outer block
```

### Using blocks to execute multiple statements conditionally

We can replace a single statement for `if statments` with a block of statements if we want multiple statements to execute when the condition evaluates to `true`

```cpp
#include <iostream>

int main()
{ // start of outer block
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >= 0)
    { // start of nested block
        std::cout << value << " is a positive integer (or zero)\n";
        std::cout << "Double this number is " << value * 2 << '\n';
    } // end of nested block
    else
    { // start of another nested block
        std::cout << value << " is a negative integer\n";
        std::cout << "The positive of this number is " << -value << '\n';
    } // end of another nested block

    return 0;
} // end of outer block
```

### Block nesting

It is posible to put blocks inside of blocks inside of blicks

**Nesting Level (Depth)**: The nesting level of a function is the maximum number of nested blocks you can be inside at any point int the function

```cpp
#include <iostream>

int main()
{ // block 1, nesting level 1
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >  0)
    { // block 2, nesting level 2
        if ((value % 2) == 0)
        { // block 3, nesting level 3
            std::cout << value << " is positive and even\n";
        }
        else
        { // block 4, also nesting level 3
            std::cout << value << " is positive and odd\n";
        }
    }

    return 0;
}
```

There are 4 blocks, but the nesting level is 3 since you can never be inside more than 3 blocks

C++ Compiler should support 256 levels, not all do though

Best Practice: Keep nesting level to 3 or less

# 7.2 - User defined namespaces and scope reolution operator

## Notes

### Defining your own namespace

**User Defined Namespace**: Namespaces that you create in your own programs using the `namespace` keyword

```cpp
namespace NamespaceIdentifier
{
    // content of namespace here
}
```

Historically, namespace names have not been capitalized, and many style guides still recommend this
- learncpp recommends starting with capital letters

A namespace must be defined either in the global scope, or inside another namespace.
- The content of a namespace is conventionally indented 1 level
- May occasionally see an optional semicolon placed after the closing brace of a name space

```cpp
namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}
```

```cpp
namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}
```

If we compile in main, we still get an error, but because the function `doSomething` isn't in the global namespace, instead of a duplicate error

```cpp
int doSomething(int x, int y); // forward declaration for doSomething

int main()
{
    std::cout << doSomething(4, 3) << '\n'; // which doSomething will we get?
    return 0;
}
```

### Accessing a namespace with the scope resolution operator

**Scope Resoltuoin Operator**: Tells the compiler that the identifier specified by the right-hand operand should be ooked for in the scope of the left-hand operand

```cpp
int main()
{
    std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
    return 0;
}
```

### Using the scope resolution operator with no prefix

The identifier will be looked for in the global namespace

```cpp
#include <iostream>

void print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}
}

int main()
{
	Foo::print(); // call print() in Foo namespace
	::print();    // call print() in global namespace (same as just calling print() in this case)

	return 0;
}
```

### Identifier resolution from within a namespace

If an identifier inside a namespace is used with no scope resolution, the compiler will first try to find a matching declaration in the same namespace
- If no matching identifier is found, the compiler will check each containing namespace in sequence to see if a match is found
- Global namespace is checked last

```cpp
#include <iostream>

void print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}

	void printHelloThere()
	{
		print();   // calls print() in Foo namespace
		::print(); // calls print() in global namespace
	}
}

int main()
{
	Foo::printHelloThere();

	return 0;
}
```

For `print()`, if no function named `print` was found, it would have checked the containing namespace first for a function.
- In this example, the containing namespace is the global namespace.

### Forward declaration of content in namespaces

```cpp
// add.h
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}

#endif
```

```cpp
// add.cpp
#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
}
```

```cpp
// main.cpp
#include "add.h" // for BasicMath::add()

#include <iostream>

int main()
{
    std::cout << BasicMath::add(4, 3) << '\n';

    return 0;
}
```

If the forward declaration for `add()` wasn't in the namespace, then `add)()` would be declared in the global namespace instead, and the compiler would complain that it hadn't seen a declaration for the call to `BasicMath::add(4, 3)`.
- If the definition of function `add()` wasn't inside namespace `BasicMath`, the linker would complain that it couldn't find a matching definition for the call `BasicMath::ad(4, 3)`

### Multiple namespace blocks are allowed

It's legal to declare namespace blocks in multiple locations.
- All declarations within the namespace are considered part of the namespace

```cpp
// circle.h
#ifndef CIRCLE_H
#define CIRCLE_H

namespace BasicMath
{
    constexpr double pi{ 3.14 };
}

#endif
```

```cpp
// growth.h
#ifndef GROWTH_H
#define GROWTH_H

namespace BasicMath
{
    // the constant e is also part of namespace BasicMath
    constexpr double e{ 2.7 };
}

#endif
```

Each standard library header file contains its declaration inside a `namespace std` block contained within that header file

### Nessted namespace

NNamespaces can be nested inside other namespaces

```cpp
#include <iostream>

namespace Foo
{
    namespace Goo // Goo is a namespace inside the Foo namespace
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

Because Goo is inside Foo, we access `add` as `Foo::Goo::add`

C++17, nested namespaces can also be declared this way:
```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

If you need to add clarations to just `Foo`, you can create a separate `Foo` namespace

```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Foo
{
     void someFcn() {} // This function is in Foo only
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

### Namespace aliases

**Namespace aliases**:  Allow temporarily shorten a long sequence of namespaces into something shorter

```cpp
#include <iostream>

namespace Foo::Goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = Foo::Goo; // active now refers to Foo::Goo

    std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()

    return 0;
} // The Active alias ends here
```

### How to use a namespace

Namespaces were designed primarily as a mechanism for preventing naming collisions
- Small applications typically do not need to be placed in namespaces
  - Larger personal projects that include lots of 3rd party libraries, will use namespace to prevent naming collision
- Any code distributed to others should definitely be namespaced to prevent conflicts with the code it is integrated into
  - Placing library code inside a namespace allows the user to see the contents of your libary by using their editor's auto-complete and suggestion feature
- In multi-team organizations, 2-level or even 3-level namespaces are often used to prevent naming conflicts between code generated by different teams

# 7.3 - Local Variables

## Questions

1. Write a program that asks the user to enter two integers, one named smaller, the other named larger. If the user enters a smaller value for the second integer, use a block and a temporary variable to swap the smaller and larger values. Then print the values of the smaller and larger variables. Add comments to your code indicating where each variable dies. Note: When you print the values, smaller should hold the smaller input and larger the larger input, no matter which order they were entered in.

The program output should match the following:

```shell
Enter an integer: 4
Enter a larger integer: 2
Swapping the values
The smaller value is 2
The larger value is 4
```

2. What’s the difference between a variable’s scope, duration, and lifetime? By default, what kind of scope and duration do local variables have (and what do those mean)?

Variable's scope is from their point of declaration to the end of the block it is defined in.\
Duration is the rules that govern when and how a variable will be created and destroyed\
Lifetime is the actual amount of time a variable lived for from start to end.

Local variables have automatic duration

## Notes

### Local Variables have block scope

**Block Scope**: Scoped from their point of definition to the end of the block they are defined within

Although function parameters are not defined inside the funciton body, for typical functions they can be considered to be part of the scope of the function body block

```cpp
int max(int x, int y) // x and y enter scope here
{
    // assign the greater of x or y to max
    int max{ (x > y) ? x : y }; // max enters scope here

    return max;
} // max, y, and x leave scope here
```

### All variable names within a scope must be unique

Variable names must be unique within a given scope, otherwise any reference to thename will be ambiguous

### Local variables have automatic storage duration

**Storage Duration**: A variable's duration determines what rules govern when and how a variable will be created and destroyed.
- Most cases, a variable's storage duration directly determines its `lifetime`

**Automatic Storage Duration**: Local variables are created at the point of definition and destroyed at the end of the block they are defined in
- Local variables are sometimes called **Automatic Variables**

### Local variables in nested blocks

The nested blocks are considered part of the scope of the outer block in which they are defined. Variables defined in the outer block can be seen inside a nested block

```cpp
#include <iostream>

int main()
{ // outer block

    int x { 5 }; // x enters scope and is created here

    { // nested block
        int y { 7 }; // y enters scope and is created here

        // x and y are both in scope here
        std::cout << x << " + " << y << " = " << x + y << '\n';
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    return 0;
} // x goes out of scope and is destroyed here
```

### Local variables have no linkage

**Linkage**: Determines whether a declaration of the same identifier in a different scope refers to the same object or function

Local variables have no linkage.
- Each declaration of an identifier with no linkage refers to a unique object or fuction

### Variables should be defined in the most limited scope

If a variable is only used within a nested block, it should be defined inside that nested block

By limiting the scope of a variable, you reduce the complexity of the program because the number of active variables is reduced
- Makes it easier to see where variables are used

Example of when you may need to declarae a variable wel before its first use.

```cpp
#include <iostream>

int main()
{
    int y { 5 }; // we're declaring y here because we need it in this outer block later

    {
        int x{};
        std::cin >> x;

        // if we declared y here, immediately before its actual first use...
        if (x == 4)
            y = 4;
    } // ... it would be destroyed here

    std::cout << y; // and we need y to exist here

    return 0;
}
```

# 7.4 - Introduction to global variables

## Notes

**Global Variables**: Variables that are declared *outside* of a function

### Declaring global variables

Global variables are declared at the top of a file, below the includes, in the global namespace.

```cpp
#include <iostream>

// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    g_x = 3;
    std::cout << g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << g_x << '\n';

    // global variables can be seen and used everywhere in the file
    g_x = 5;
    std::cout << g_x << '\n';

    return 0;
}
// g_x goes out of scope here
```

### The scope of global variables

**Global Namespace Scope**: (**Global Scope**), Identifiers declared in the global namespace have global scope. They are visible from the point of declaration until the end of the **File**, in which they are declared

Once declared a global variable can be used anywhere in the file from that point onward

Global variables can also be defined inside a user-defined namespace

```cpp
#include <iostream>

namespace Foo // Foo is defined in the global scope
{
    int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    Foo::g_x = 3;
    std::cout << Foo::g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << Foo::g_x << '\n';

    // global variables can be seen and used everywhere in the file
    Foo::g_x = 5;
    std::cout << Foo::g_x << '\n';

    return 0;
}
```

Although limited to namespace Foo, the name is still globally accessible

Best Practice: Prefer defining global variables inside a namespace rather than in the global namespace

### Global Variables have Static Duration

**Static Duration**: Global variables are created when the program starts, and destroyed when it ends\
**Static Variables**: Variables with static duration

### Naming Global Variables

By comvention, some devs prefix global variales with `g` or `g_`
- Helps avoid naming collisions with other identifiers
- Helps prevent inadvertant name shadowing
- Helps indicate that the prefixed var persist beyond the scope of the function

Global variables defined inside a user-defined namespace often omit the prefix
- It doesn't hurt if you want to keep the prefix

### Global Variables

Variables with static duration are zero-initialized by devault

```cpp
int g_x;       // no explicit initializer (zero-initialized by default)
int g_y {};    // value initialized (resulting in zero-initialization)
int g_z { 1 }; // list initialized with specific value
```

### Constant global variables

Global variables can be constant, Constant global variables must be initialized

```cpp
#include <iostream>

const int g_x;     // error: constant variables must be initialized
constexpr int g_w; // error: constexpr variables must be initialized

const int g_y { 1 };     // const global variable g_y, initialized with a value
constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';
}

int main()
{
    doSomething();

    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';

    return 0;
}
// g_y and g_z goes out of scope here
```

### Word of caution about (non-constant) global variables

New programmers are often tempted to use lots of global variables
- Use of non-constant global variables should be generally avoided

# 7.5 - Variable shadowing (name hiding)

## Notes

Each block defines its own scope region

What happens when we have a variable inside a nested block that has the same name as a variable in an outer block

**Name Hiding**: (**Shadowing**), the nested variable "hides" the outer variable in areas where they are both in scope

### Shadowing of local variables

```cpp
#include <iostream>

int main()
{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
} // outer block apples destroyed
```

```shell
5
10
5
```

If the nested block `apples` had not been defined, the name `apples` in the nested block would still refer to the outer block `apples`, so the assignment of the value `10` to `apples` would have been applied

### Shadowing of global variables

Local variables with the same name as a global variable will shadow the global variable wherever the local variable is in scope.

```cpp
#include <iostream>
int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}

int main()
{
    int value { 7 }; // hides the global variable value (wherever local variable value is in scope)

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    return 0;
} // local value is destroyed
```

```shell
local variable value: 8
global variable value: 5
```

Because global variables are part of the global namespace, we can use the scope operator (::) with no prefix to tell the compiler we mean the global variable instead of the local variable

```cpp
#include <iostream>
int value { 5 }; // global variable

int main()
{
    int value { 7 }; // hides the global variable value
    ++value; // increments local value, not global value

    --(::value); // decrements global value, not local value (parenthesis added for readability)

    std::cout << "local variable value: " << value << '\n';
    std::cout << "global variable value: " << ::value << '\n';

    return 0;
} // local value is destroyed
```

### Avoid Variable Shadowing

Generally be avoided, can lead to inadvertent errors when the wrong variable is used/modified
- Also avoid shadowing global variables as well.

### gcc users

GCC and Clang support the `-Wshadow`, generate warnings if a variable is shadowed

# 7.6 - Internal Linkage

## Notes

**Internal Linkage**: Identifiers with internal linkage can be seen and used within a single translation unit, but it is not accessible from other units
- If 2 source files have identically named identifiers with internal linkage, those identifiers will be treated as independent
  - Does not result in an ODR violation

### Global Variables with internal linkage

**Internal **Variables**: global variables with internal linkage

To make a non-constant global variable internal, use the `static` keyword

```cpp
#include <iostream>

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}
```

Const and constexpr global variables have internal linkage by default

```cpp
// a.cpp
[[maybe_unused]] constexpr int g_x { 2 }; // this internal g_x is only accessible within a.cpp
```

```cpp
// main.cpp
#include <iostream>

static int g_x { 3 }; // this separate internal g_x is only accessible within main.cpp

int main()
{
    std::cout << g_x << '\n'; // uses main.cpp's g_x, prints 3

    return 0;
}
```

```shell
3
```

Because `g_x` is internal to each file, `main.cpp` has no idea that `a.cpp` also has a variable named `g_x`

### Functions with internal linkage

Functions identifiers also have linkage. Functions default to external linkage
- Can be set to interna via the `static` keyword

```cpp
// add.cpp
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
[[maybe_unused]] static int add(int x, int y)
{
    return x + y;
}
```

```cpp
// main.cpp
#include <iostream>

int add(int x, int y); // forward declaration for function add

int main()
{
    std::cout << add(3, 4) << '\n';

    return 0;
}
```

This program won't link

### The one-definition rule and internal linkage

We noted that the ODR says that an object/function can't have more than one definition

Worth noting that internal objects/funcitons that are defined in different files are considered to be independent entities
- Ther is no violation of the ODR. Each internal object only has one definition

### `static` vs unnamed namespaces

In C++, we use `static` for giving identifiers internal linkage is falling out of favor.
- Unnamed namespaces can give internal linkage to a wider range of identifiers
- They are better suited for giving many identifiers internal linkage

### Why bother giving identifiers internal linkage?

2 reasons to give indentifiers iternal linkage:
- There is an identifier we want to make sure isn't accessible to other files. Could be a global variable we don't want messed with, or a help function we don't want to be called
- To be pedantic about avoiding naming collisions
  - Identifiers with internal linkage aren't exposed to the linker, they can only collide with names in the same translation unit

Best Practice:
- Give identifiers internal linkage when you have an explicit reason to disallow access from other files
- Consider giving all identifiers you don't want accessible to other files interal linkage
  - Use an unnamed namespace for this

```cpp
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```

# 7.7 - External linkage and variable forward declarations

## Questions

1. What kind of scope, duration, and linkage do global variables have?

Global variables have global scope, they can be accessed from the point of declaration to the end of the file they are defined in.\
Static duration, they are created when the program starts, and destroyed when the program ends\
Either internal or external linkage, via the static and extern keywords

## Notes

**External Linkage**: An identifier with external linkage can be seen and used both from the file in which it is defined, and from other code files
- Identifiers with external linkage are truly "global" in that they can be used anywhere in your program

Identifiers with external linkage are visible to the linker, allowing the linker to do 2 things:
- Connect an identifier used in one translation unit with the appropriate definition in another unit
- Dedupliate inline identifiers so 1 canonical definition remains

### Functions have external linakge by default

In order to call a function defined in another file, you must place a `forward declaration` for the function in any other file wishing to use the function.
- Forward declaration tells the compiler about the existene of the function
- Linker connects the function calls to the actual function definition

```cpp
// a.cpp
#include <iostream>

void sayHi() // this function has external linkage, and can be seen by other files
{
    std::cout << "Hi!\n";
}
```

```cpp
// main.cpp
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
    sayHi(); // call to function defined in another file, linker will connect this call to the function definition

    return 0;
}
```

### Global variables with external linkage

**External Variables**: Global variables with external linkage. Can use the `extern` keyword to do so

```cpp
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

Non const global variables are external by default

### Variable forward declaration via the extern keyword

To actually use an external global variable that has been defined in another file, you must place a `forward declaration` for the global variable in any other files.
- For variables, creating a forward declaration is done via the `extern` keyword

```cpp
// main.cpp
#include <iostream>

extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```

```cpp
// a.cpp
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```

If you want to define an uninitialized non-const global variable, do not use the extern keyword
- C++ will think you're trying to make a forward declaration

Function forward declarations don't need the `extern` keyword. 
- Compiler is able to tell whether you're defining a new function or making a forward declaration based on whether you supply a function body or not

Variables forward declarations *do* need the `extern` keyword to help differentiate uninitialized variables definitions from variable forward declarations

### Avoid using `extern` on non-const global variable with an initializer

Compiler may issue a warning about `extern int g_x {1};`

Conventionally, `extern` is applied to a non-const variable when we want a forward declaration.
- Adding an initializer makes the statement a definition

Best Practice: 
- Only use `extern` for global variable forward declarations or const global variable definitions
- Do not use `extern` for non-const global variable definitions

```cpp
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```

# 7.8 - Why (non-const) global variables are evil

## Notes

Global variables are 1 of the most historically abused concepts in the language

### Why (non-const) global variables are evil

Global variable values can be changed by any function that is called
- No easy way for the programmer to know that this will happen

Global variables make the program's state unpredictable. every function call becomes potentially dangerous, and the Programmer has no easy way of knowing which ones are dangerous and which ones aren't

Best Practice: Use local variables instead of global variables when possible

### The initialization order problem of global variables

Initialization of static variables happens as part of program startup, before the `main` function is executed. happens in 2 phases:

**Static Initialization**: 2 phases
- **Consttant Initialization**: Global variales with constexpr initializers are initialized to those values
- Global variables without initializers are zero-initialized

**Dynamic Initialization**: More complex and nuanced, global variables with non-constexpr initializers are initialized

Non-constexpr Initializer:
```cpp
int init()
{
    return 5;
}

int g_something{ init() }; // non-constexpr initialization
```

Within a single file, for each phase, global variables are generally initialized in order of definition.
- Be careful not to have variables dependent on the initialization value of other variables that won't be initialized until later

```cpp
#include <iostream>

int initX();  // forward declaration
int initY();  // forward declaration

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
    return g_y; // g_y isn't initialized when this is called
}

int initY()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}
```

```shell
0 5
```

Avoid initializing objects with static duration using other objects with static duration from a different translation unit

### What are very good reasons to use non-const global variables?

In most cases, using local variables and passing them as arguments to other functions is preferablee\
Som cases, judicious use of non-const global variables can actually reduce program complexity

Log file, probably makes sense to define this as global\
Random number generator

Any use of global variables should meet at least the following 2 criteria:
- There should only ever be one of the thing the variable represents in your program
- Its use should be ubiquitous throughout your program

### Protecting yourself from global destruction

If you do find a good use for a non-const global variable:
- Prefix all non-namespaced global variables with "g" or "g_"
- Or put them in a namespace
- Instaead of allowing direct access to global variables, it's better practice to "encapulsate" the variable
  - Make the variable only be accessed from within the file it's declared in
- When writing ann otherwise standalone function that uses the global varaible, don't use the variable directly in your function body.
  - Pass it in as an argument instead
  - Your function ever needs to use a different value for some circumstance, you can simply vary the argument

# 7.9 Inline functions and variables

## Notes

There is a certain amount of performance overhead when using a new function
- The CPU must store the address of the current instruction it is executing along with the values of various CPU registers
- Parameters must be instantiated and then initialized
- Execution path has to jump to the code in the function
- When the function ends, the program has to jump back to the location of the function call, and the return value has to be copied so it can be output

**Overhead**: All of the extra work that must happen to setup, facilitiate, and/or cleanup after some task

For small function, the overhead cost can be larger than the time needed to actually execute the function's code

### Inline expansion

**Inline Expansion**: A process where a function call is replaced by the code from the called function's definition

If the compiler expanded the `min()` calls in the above example, teh resulting code would look like:

```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0
}
```

```cpp
#include <iostream>

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n';
    std::cout << ((3 < 2) ? 3 : 2) << '\n';
    return 0;
}
```

This allows us to avoid the overhead of those calls while preserving the results of the code

### Performance of inline code

Inline expansion can also allow the compiler to optimize the resulting code more efficiently
- Because `((5 < 6) ? 5 : 6)` is now a constant expression, the compiler could further optimize the first statement to just `5`

Inline expansion has its own potential cost:
- If the body of the function being expanded takes more instructions than the fucntion call being replaced, then each inline expansion will cause the executable to grow larger

Inline expansion is best suited to simple, short functions

### When inline expansion occurs

Every function falls into 1 of 2 categories, where calls to the function:
- May be expanded
- Can't be expanded

Most functions fall into the "may" category

Most common kind of function that can't be expanded inline is a function whose definition is in another translation unit

### The inline keyword, historically

C++ provided the keyword `inline`, originally intended to be used as a hint to the compiler that a funtion would (probably) benefit from being expanded inline

**Inline Function**: A function that is declared using the `inline` keyword

```cpp
#include <iostream>

inline int min(int x, int y) // inline keyword means this function is an inline function
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```

Modern C++, the `inline` keyword is no longer used

### The inline keyword, modernly

The term `inline` has evolved to mean "multiple definitions are allowed". An inline function is one that is allowed to be defined in multiple translation units (without violating ODR)

2 Primary requirements:
- Compiler needs to be able to see the full definition of an inline function in each translation unit where the function is used
  - Only 1 such definition can occur per translation unit
- The definition can occur after the point of use if a forward declaration is also provided
  - However, the compiler will likely not be able to perform inline expansion until it has seen the definition
- Every definition for an inline function must be identical, otherwise undefined behavior will result

The linker will consolidate all inline function definitions for an identifier into a single definition

```cpp
// main.cpp
#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; }

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

```cpp
// math.cpp
inline double pi() { return 3.14159; }

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

Both files have a definition for function `pi()`, because the function has been marked as `inline`, this is acceptable, and the linker will de-duplicate them.
- If you remove `inline`from both definitions, you'll get an ODR violation

Inline functions are typically defined in header files

```cpp
// pi.h
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif
```

```cpp
// main.cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

```cpp
// math.cpp
#include "pi.h" // will include a copy of pi() here

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

**Header-Only Libraries**: 1 or more header files that implement some capability.
- Popular because there are no source files that need to be added to a project to use them and nothing that needs to be linked
- Simply #include the header-only library and then can use it

### Why not make all functions inline and defined in a header file

Doing so can increase compile times

An inline function #included into 6 translation units will have its definition compiled 6 times
- A function defined in a source file will have its definition compiled only once

If a funciton defined in a source file changes, only that single source file needs to be recompiled
- With an inline function, every code file that includes that header needs to recompile

### Inline variables C++17

**Inline Variables**: Variables that are allowed to be defined in multiple files
- Work similarly to inline functions
- Have the same requirements\

# 7.10 - Sharing global constants across multiple files (using inline variables)

## Notes

It's best to declar constant values that are used everywhere (gravity, pi, avagadro's number) once in a central location and use them wherever needed

### Global constants as internal variables

Prior to C++17, the following is the easiest and most common solution

```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define your own namespace to hold constants
namespace constants
{
    // Global constants have internal linkage by default
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

Every time *constant.h* gets #included, each of these variables is copied into the including code file
- Header guards won't stop this from happening

This introduces 2 challenges
- Changing a single constnat value requires recompiling every file that includes the constant header, lengthy build times
- If the constants are larger in size and can't be optimized away, this can use a lot of memory

### Global constants as external variables

One way to avoid these problems is to turn constants into external variables
- Can have a single variable that is shared across all files
- Define the constants in a .cpp file, and put forward declarations in the header

```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    // Since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    // We can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
    extern const double pi;
    extern const double avogadro;
    extern const double myGravity;
}

#endif
```

Symbolic constants will get instantiated only once instead of in each code file

Couple downsides
- Because the variable definitions are constexpr, they are constant expressions only within the file they are actually defined in (constant.cpp)
- Outside of the file where theya re defined, these variables can't be used in a constant expression
- Because constant expressions can typically be optimized more than runtime epxressions, the compiler may not be able to optimize these as much

### Global constants as inline variables C++17

```cpp
// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

```cpp
// main.cpp
#include "constants.h"

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

We can include `constants.h` into as many code files as we want
- These variables will only be instantiated once and shared across all code files
- Retain the downside of requiring every file that includes the constant header be recompiled

Best Practice: If you need global constants and compiler is C++17 capable, prefer inline constexpr global variables in the header file

# 7.11 - Static Local Variables

## Questions

1. What effect does using keyword static have on a global variable? What effect does it have on a local variable?

On local variables, the variable will remain to exist even if traditionally it will go out of scope. Static on global variables make the variable internally linked, meaning it can't be accessed by other files.

## Notes

The term `static` is confusing in C++

### Static local variables

Using the `static` keyword ona  local variable changes its duration from automatic to static duration.
- The variable is now created at the start of the program, and destroyed at the end.
- Static variable will retain its value even after it goes out of scope

```cpp
#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```

Because `s_value` has been declared as `static`, it is created at the program start

When `s_value` goes out of scope at the end of the function, it is not destroyed

```shell
2
3
4
```

### ID Generation

1 of the most common uses for static duration local variables is for unique ID generation

```cpp
int generateID()
{
    static int s_itemID{ 0 };
    return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
}
```

The first time this function is called, it returns `0`. The second time, `1`. 

### Static local constants

Static local variables can be made const (or constexpr)

1 good use is when you have a function that needs to ues a const value, but creating or initializing the object is expensive
- If you used a normal local variable, the variable would be created and initialized every time

With a const/constexpr static local variable, you can create and initialize the expensive object once, then reuse it whenever the function is called

### Don't use static local variables to alter flow

```cpp
#include <iostream>

int getInteger()
{
	static bool s_isFirstCall{ true };

	if (s_isFirstCall)
	{
		std::cout << "Enter an integer: ";
		s_isFirstCall = false;
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger() };
	int b{ getInteger() };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}
```

```shell
Enter an integer: 5
Enter another integer: 9
5 + 9 = 14
```

We made the code harder to understand.

One bettwer way of implementing is to pass `s_isFirstCall` as a parameter

```cpp
#include <iostream>

// We'll define a symbolic constant with a nice name
constexpr bool g_firstCall { true };

int getInteger(bool bFirstCall)
{
	if (bFirstCall)
	{
		std::cout << "Enter an integer: ";
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger(g_firstCall) };  // so that it's clearer what the argument represents here
	int b{ getInteger(!g_firstCall) };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}

```

# 7.12 - Scope, duration, and linkage summary

## Notes

### Scope summary

An identifier's scope determines where the identifier can be accessed within the source code
- Variables with **Block Scope** Can only be accessed from the point of declaration until the end of the block in whcih they are declared
  - Local variables
  - Function parameters
  - Program-defiend type definitions
- Variables and functions with **global scope** Can be accessed from the point of declaration until the end of the file
  - Global variables
  - Functions
  - Program-defined type deinitions

### Duration summary

A variable's duration determines when it is created and destroyed
- **Automatic Duration**: Created at the point of definition, destroyed when the block they are part of is exited
  - Local variables
  - Function parameters
- **Static Duration**: Created when the pgoram begins and destroyed when the program ends
  - Global variables
  - Static local variables
- **Dynamic Duration**: Created and destroyed by programmer request:
  - Dynamically allocated variables

### linkage summary

Linkage determines whether a declaration of the same identifier in a different scope refers to the same entity or not. Local variables have no linkage
- **No Linkage**: Another declaration of the same identifier refers to a unique entity.
  - Local variables
  - Program-defined type identifiers (enum and classes) declared inside a block
- **Internal Linkage**: Declaration of the same identifier within the same translation unit refers to the same object or function
  - Static global variables
  - Static functions
  - Const global variables
  - Unnamed namespaces and anything defined within them
- **External Linkage**: A declaration of the same identifier within the entire program refers to the same object or function
  - Non-static function
  - Non-const global variables
  - Extern const global variables
  - Inline const global variables
  - Namespaces

# 7.13 - Using declarations and using directives

## Notes

### Qualified and unqualified names

**Qualified name**: A name that includes an associated scope
- names are qualified with a namespace using the scope resolution operator

```cpp
std::cout // identifier cout is qualified by namespace std
::foo // identifier foo is qualified by the global namespace
```

**Unqualified name**: Name that does not include a scoping qualifier
- `cout` and `x` don't have an associated scope

### Using-declarations

**Using Declarations**: Use an unqualified name as an alias for a qualified name

```cpp
#include <iostream>

int main()
{
   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
   cout << "Hello world!\n"; // so no std:: prefix is needed here!

   return 0;
} // the using declaration expires at the end of the current scope
```

`using std::cout` tells the compiler that we're going to be using the object `cout` from `std` namespace
- `std::cout` will be preferred

The using declaration is active from the point of declaration to the end of the scope in which it is declared

### Using-directives

**Using Directive**: Allows all identifiers in a given namespace to be referenced without qualification from the scope of the using-directive

```cpp
#include <iostream>

int main()
{
   using namespace std; // all names from std namespace now accessible without qualification
   cout << "Hello world!\n"; // so no std:: prefix is needed here

   return 0;
} // the using-directive ends at the end of the current scope
```

All the names in the `std` namespace should be accessible without qualification in the current scope

### Problems with using-directives

1. Using directives allow unqualified access to all of the names in the namespace
2. Using directives do not prefer names from the namespace identifier by the using-directive over other names

```cpp
#include <iostream>

namespace A
{
	int x { 10 };
}

namespace B
{
	int x{ 20 };
}

int main()
{
	using namespace A;
	using namespace B;

	std::cout << x << '\n';

	return 0;
}
```

Refuse to compile with an "ambiguous symbol" error

### The scope of using-statements

If a using-declaration or using directive is used within a block, the names are applicable to just that block.
- Reduces the chances for naming collisions  to occur to just within that block

If a using-declaration or using-directive is used in a namespace, the names are applicable to the entire rest of the file


### Do no use using-statmeents in header files, or before an #include directive

Using-statements should not be placed anywhere where they might have an impact on code in a different file
- Using-statments should not be used in header files, nor before an #include directive
- We can't control which other headers might be #included before our header

The only place it is truly safe ito use using statements is in our source (.cpp) files, after the #includes

### Cancelling or replacing a using statment

Once a using-statement has been declared, there's no way to cancel or replace it with a different using statement

```cpp
int main()
{
    using namespace Foo;

    // there's no way to cancel the "using namespace Foo" here!
    // there's also no way to replace "using namespace Foo" with a different using statement

    return 0;
} // using namespace Foo ends here
```

Best you can do is intentionally limit the scope of the using statement

```cpp
int main()
{
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // using namespace Foo expires

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // using namespace Goo expires

    return 0;
}
```

Best Practice:
- Prefer explicit namespace qualifiers over using-statements
- Avoid using-directives altogether
  - Using declarations are okay in .cpp files, after the #include directives
- Do not use using-statements in header files

# 7.15 - Unnamed and inline namespaces

## Notes

### Unnamed (anonymous) namespaces

**Unnamed Namespace**: A namespace that is defined without a name

```cpp
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

All content declared in an unnamed namespace is treated as if it is part of the parent namespace
- Even though function doSoemthing() is defined in unnamed, the function itself is accessible from the parent (global)

Another effect of unnamed namespaces is that all identifiers inside an unnamed namespace are treated as if they have internal linkage
- The content of an unnamed namespace can't be seen outside of the file in which the unnamed namespace is defined

Unnamed namespaces are typically used when ou have a lot of content that you want to ensure stays local to a given translation unit
- It's easier to cluster such content in a single unnamed namespace than individually mark them `static`

Generally not be used in header files


### Inline namespaces

If you want to change a function without breaking other code, you can use inline namespaces

**Inline Namespaces**: A namespace that is typically used to version content
- Anything declared inside an inline namespace is considered part of the parent namespace
- Inline namespaces don't affect linkage

```cpp
#include <iostream>

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}
```

### Mixing inline and unnamed namespaces

A namespace can be both inline and unnamed

```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace // declare an inline unnamed namespace
{
    void doSomething() // has internal linkage
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    // there is no V2 in this example, so we can't use V2:: as a namespace prefix

    doSomething(); // calls the inline version of doSomething() (which is the anonymous one)

    return 0;
}
```

In such cases, it's probably better to nest an anonymous namespce inside an inline namespace

```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace V2 // declare an inline namespace named V2
{
    namespace // unnamed namespace
    {
        void doSomething() // has internal linkage
        {
            std::cout << "V2\n";
        }

    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V2)

    return 0;
}
```

# 7.x - Chapter 7 summary and quiz

## Review

- **Compound Statement**: A group of 0+ statements that is treated by the compiler as if it were a single statement.
- **User-defined namespace**: Namespaces that are defined by you for your own declaration
- **Scope Resolution Operator**: (::), tells the compiler that the identifier specified by the right hand operand should be looked for in the scope of the left-hand operand
- **Block Scope**: They are in scope from their point of definition to the end of the block they are defined within
- **Automatic Storage Duration**: They are created at the point of definition and destroyed at the end of the block they are defined in
- **Shadow**: An identically named variable in an outer block
- **File Scope**: They are visible from the point of declaration untilthe end of the file in which they are declared in
- **Static Duration**: They are created when the program starts, and destroyed when it ends
- **Linkage**: Determines whether other declarations of theat name refer tot the same object or not
- **Internal Linkage**: Can be seen and used within a single file, but not accessible from other files
- **External Linkage**: Can be seen and used both from the file in which they are defined, and other code files
- **Qualified Name**: A name that includes an associated scope
- **Unqualified Name**: A name that does not include a scoping qualifier
- **Using Statmenet**: Can be used to avoid having to qualify identifiers with an explicit namespace
- **Using declaration**: Allows us to use an unqualified name as an alias for a qualified name
- **Using directive**: Imports all of the identifiers from a namespace into the scope of the using directive
- **Inline Expansion**: A process where a function call is replaced by the code from the called function's definition
- **Inline Function**: A function that is declared using the `inline` keyword
- **Inline variable**: Variables that are allowed to be defined in multiple files
- **Header-Only Libraries**: 1 or more header files that implement some capability
- **Unnamed Namespaces**: Implicitly treat all contents of the namespace as if it had internal linkage
- **Inline Namespaces**: Provide some primitiver versioning capabilities for namespaces

## Quiz

1. Fix the following program:

```cpp
#include <iostream>

int main()
{
	std::cout << "Enter a positive number: ";
	int num{};
	std::cin >> num;


	if (num < 0)
		std::cout << "Negative number entered.  Making positive.\n";
		num = -num;

	std::cout << "You entered: " << num;

	return 0;
}
```

```cpp
#include <iostream>

int main()
{
	std::cout << "Enter a positive number: ";
	int num{};
	std::cin >> num;


	if (num < 0) {// Need to add brackets
		std::cout << "Negative number entered.  Making positive.\n";
		num = -num;
    }
	std::cout << "You entered: " << num;

	return 0;
}
```

2. Write a file named constants.h that makes the following program run. If your compiler is C++17 capable, use an inline constexpr variable. Otherwise, use a normal constexpr variable. maxClassSize should have value 35.

```cpp
// main.cpp
#include "constants.h"
#include <iostream>

int main()
{
	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > Constants::maxClassSize)
		std::cout << "There are too many students in this class";
	else
		std::cout << "This class isn't too large";

	return 0;
}
```

```cpp
# ifndef CONSTANTS_H
# define CONSTANTS_H

// constants.h
namespace Constants
{
    inline constexpr int maxClassSize{35}
}

# endif
```

3. Write a function int accumulate(int x). This function should return the sum of all of the values of x that have been passed to this function.

```cpp
// main.cpp
#include <iostream>

int main()
{
    std::cout << accumulate(4) << '\n'; // prints 4
    std::cout << accumulate(3) << '\n'; // prints 7
    std::cout << accumulate(2) << '\n'; // prints 9
    std::cout << accumulate(1) << '\n'; // prints 10

    return 0;
}
```

```cpp
// main.cpp
#include <iostream>

int accumulate(int add)
{
    static int total{0};
    total += add
    return total;
}

int main()
{
    std::cout << accumulate(4) << '\n'; // prints 4
    std::cout << accumulate(3) << '\n'; // prints 7
    std::cout << accumulate(2) << '\n'; // prints 9
    std::cout << accumulate(1) << '\n'; // prints 10

    return 0;
}
```