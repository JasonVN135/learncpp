# 5.1 - Constant Variables (named constants)

## Questions

## Notes

### Introduction to Constants

**Constant**: A value that may not be changed during the program's execution\
**Named Constants**: (**Symbolic Constants**) Constant values that are associated with an identifier
**Literal Constants**: Constant values that are not associated with an identifier

### Types of named constants

3 ways to define a named constant in C++:
- Constant variables
- Object-like macros with substitution text
- Enumerated Constants

### Constant variables

All variables so far are non-constant, can be changed at any time\
Some variables should be defined without changing
- Ex: Gravity of Earth near the surface (9.8 meters/second^2)

**Constant Variables**: A variable whose value cannot be changed after initialized
- Use the `const` keyword

```cpp
const double gravity { 9.8 };  // preferred use of const before type
int const sidesInSquare { 4 }; // "east const" style, okay but not preferred
```

The type of gravity is not just double, but const double.

### Const variables must be initialized

Const variables *must* be initialized when defined.
- That value can not be changed via assignment

Const variables can be initialized from other variables (including non-const ones)

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    const int constAge { age }; // initialize const variable using non-const value

    age = 5;      // ok: age is non-const, so we can change its value
    constAge = 6; // error: constAge is const, so we cannot change its value

    return 0;
}
```

### Naming your const variables

Number of different naming conventions

C developers prefer underscored, upper-case names (EARTH_GRAVITY)
C++ developers use intercapped names with a k prefix (kEarthGravity)

There is no reason they need a special naming convention
- Prefer using the same naming convention (earthGravity)

### Const functoin parameters

Function parameters can be made constant via the const keyword

```cpp
#include <iostream>

void printInt(const int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(5); // 5 will be used as the initializer for x
    printInt(6); // 6 will be used as the initializer for x

    return 0;
}
```

Making a function parameter constant enlists the compiler's help to ensure that the parameter's value is not changed inside the function
- In modern C++, we don't make value parameters `const` because we generally don't care if the function changes the value of the parameter
  - It is just a copy

### Const return value

A functions' return value may also be made const

```cpp
#include <iostream>

const int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue() << '\n';

    return 0;
}
```

For fundamental types, the `const` qualifier on a return type is simply ignored\
Best Practice: Don't use `const` when returning

### Why variables should be made constant

- Reduces the chance of bugs. Ensure that the value can't be changed by accident
- Provides more opportunity for the compiler to optimize programs
- Reduces the overall complexity of our program
  - We know that a const variable can't have its value changed, so we don't worryabout whether its value is actually changing

### Object-like macros with substitution text

```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```

The substitution text is a constant value

### Prefer constant variables to preprocessor macros

3 major problems for preprocessor macros
- Macros don't follow normal C++ scoping rules
  - When defined, all subsequent occurrences of the macro's name in the current file will be replaced
- Often harder to debug code using macros
- Macro substitution behaves differently than everything else in C++, mistakes can be easily made

### Nomenclature: type qualifiers

**Type qualifier**: (**qualifier**), a keyword that is applied to a type that modifies how the type behaves
- **const** is a **const type qualifier** or **const qualifier**

C++23 has 2 type qualifiers: `const` and `volatile`

**Volatile**: Used to tell the compiler that an object may have its value changed at any time
- Rarely-used qualifier
- Disables certain types of optimizations

# 5.2 - Literals

## Notes

**Literal constants**: (**Literals**), their meaning cannot be redefined

```cpp
return 5;                     // 5 is an integer literal
bool myNameIsAlex { true };   // true is a boolean literal
double d { 3.4 };             // 3.4 is a double literal
std::cout << "Hello, world!"; // "Hello, world!" is a C-style string literal
```

### The type of a literal

Literal value: integer value
- Examples: 5, 0, -3
- Default literal type: int

Literal value: boolean value
- Examples: true, false
- Default literal type: bool

Literal value: floating point value
- Examples: 3.14, 0.0, -1.2
- Default literal type: double (not float)

Literal value: character
- Examples: 'a', '\n'
- Default literal type: char

Literal value: C-style string
- Examples: "Hello World"
- Default literal type: const char[14]

### Literal suffixes

If the default type of a literal is not as desired, you can change the type of a literal by adding a suffix

```cpp
std::cout << 3.14f << "\n"; // float
```

### Suffix casing

Most suffixes are not case sensitive. The exception are:
- `s` and `sv` for `std::string` and `std::string_view` must be lowercase
- `l` or `L` consecutive must have the same casing (no `lL` or `Ll`)

### Integral literals

Generally won't need to use suffixes for integral literals

Examples:

```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n';  // 5 (no suffix) is type int (by default)
    std::cout << 5L << '\n'; // 5L is type long
    std::cout << 5u << '\n'; // 5u is type unsigned int

    return 0;
}
```

Most cases, it's fine to use non-suffixed `int` literals

```cpp
int main()
{
    int a { 5 };          // ok: types match
    unsigned int b { 6 }; // ok: compiler will convert int value 6 to unsigned int value 6
    long c { 7 };         // ok: compiler will convert int value 7 to long value 7

    return 0;
}
```

### Floating point literals

By default, floating point literals have a type `double`. To make them `float`, us an `f`

```cpp
#include <iostream>

int main()
{
    std::cout << 5.0 << '\n';  // 5.0 (no suffix) is type double (by default)
    std::cout << 5.0f << '\n'; // 5.0f is type float

    return 0;
}
```

Without the f, the compiler will try to convert the literal itself.
- Converting from a double to a float will have a loss in precision
  - This will raise a warning
- It is best to add the `f` suffix yourself.

### Scientific notation for floating point literals

In scientific notation, we add an `e` to represent the exponent:

```cpp
double avogadro { 6.02e23 }; // 6.02 x 10^23 is a double literal in scientific notation
double protonCharge { 1.6e-19 }; // charge on a proton is 1.6 x 10^-19
```

### String literals

**String**: A collection of sequential characters used to represent text.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```
`Hello, world!` is a string literal.

Strings are not a fundamental type in C++
- Such strings are often called **C Strings** as they are inherited from the C-language

2 non-obvious things about C-strings:
1. All C-style string literals have an implicit null terminator
  - The string "hello" is actually six characters -> 'h', 'e', 'l', 'l', 'o', '\0'
  - **Null Terminator**: The trailing `\0` character. Used to indicate the end of the tring
  - **Null-Terimination String**: A string that ends with a null terminator
2. The null terminator can be used to determine where the string ends
  - C-style string literals are const objects that are created at the start of the program and are guarnteed to exist for the entirety of the program

### Magic Numbers

**Magic Numbers**: Literal that either has an unclear meaning or may need to be changed later

```cpp
const int maxStudentsPerSchool{ numClassrooms * 30 };
setMax(30);
```

What does 30 mean? It's not immediately obvious.\
Using magic numbers is generally considered bad practice

# 5.3 - Numeral systems (decimal, binary, hexadecimal, and octal)

## Notes

**Decimal**: Numerical digits from 0-9. Base 10

**Binary**: 2 digits: 0 and 1, often space separated in groups of 4 digits

**Numeric systems**: Fancy name for a collection of symbols used to represent numbers

### Octal and hexadecimal literas

**Octal**: Base 8, only 8 digits - 0-7.

To use octal literal, prefix your literal with a 0

```cpp
#include <iostream>

int main()
{
    int x{ 012 }; // 0 before the number means this is octal
    std::cout << x << '\n';
    return 0;
}
```

```shell
10
```

**Hexadecimal**: Base 16, counted with 0-9, then A-F, A = 11, B = 12, etc.

To use hexadecimal literal, prefix your literal with a 0x (Or 0X)

```cpp
#include <iostream>

int main()
{
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    std::cout << x << '\n';
    return 0;
}
```

```shell
15
```

### Using hexadecimal to represent binary

There are 16 values for hexadecimal
- A single hexadecimal digit encompasses 4 bits
- A pair of hexadecimal digits represent a full byte

Hexadecimal are often used to represent memory addresses or raw data in memory

### Binary literals

Before C++14, there is no support for binary literals. Hexadecimal provide a work around.

```cpp
#include <iostream>

int main()
{
    int bin{};    // assume 16-bit ints
    bin = 0x0001; // assign binary 0000 0000 0000 0001 to the variable
    bin = 0x0002; // assign binary 0000 0000 0000 0010 to the variable
    bin = 0x0004; // assign binary 0000 0000 0000 0100 to the variable
    bin = 0x0008; // assign binary 0000 0000 0000 1000 to the variable
    bin = 0x0010; // assign binary 0000 0000 0001 0000 to the variable
    bin = 0x0020; // assign binary 0000 0000 0010 0000 to the variable
    bin = 0x0040; // assign binary 0000 0000 0100 0000 to the variable
    bin = 0x0080; // assign binary 0000 0000 1000 0000 to the variable
    bin = 0x00FF; // assign binary 0000 0000 1111 1111 to the variable
    bin = 0x00B3; // assign binary 0000 0000 1011 0011 to the variable
    bin = 0xF770; // assign binary 1111 0111 0111 0000 to the variable

    return 0;
}
```

In C++14 and forward, you can use the `0b` prefix

```cpp
#include <iostream>

int main()
{
    int bin{};        // assume 16-bit ints
    bin = 0b1;        // assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;     // assign binary 0000 0000 0000 1010 to the variable
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    return 0;
}
```

### Digit separator

Because long literals can be hard to read, C++15 also adds the ability to use a quotation mark (') as a digit separator
- Separators can not occur before the first digit of the value

```cpp
#include <iostream>

int main()
{
    int bin { 0b1011'0010 };  // assign binary 1011 0010 to the variable
    long value { 2'132'673'462 }; // much easier to read than 2132673462
    int bin { 0b'1011'0010 };  // error: ' used before first digit of value


    return 0;
}
```

### Outputting vales in decimal, octal, or hexadecimal

You can change the output format with `std::dec`, `std::oct`, and `std::hex`

### Outputting values in binary

C++ standard library includes a type called `std::bitset` (<bitset> header)

We can define a `std::bitset` variable and tell how many bits we want to store.
- The number of bits must be a compile-time constant
- `std::bitset` can be initialized with an integral value in any format

```cpp
#include <bitset> // for std::bitset
#include <iostream>

int main()
{
	// std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

	return 0;
}
```

### Outputting values in binary using the Format / Print library

In C++20 and C++23 we have better options

```cpp
#include <format> // C++20
#include <iostream>
#include <print> // C++23

int main()
{
    std::cout << std::format("{:b}\n", 0b1010);  // C++20, {:b} formats the argument as binary digits
    std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

    std::println("{:b} {:#b}", 0b1010, 0b1010);  // C++23, format/print two arguments (same as above) and a newline

    return 0;
}
```

```shell
1010
0b1010
1010 0b1010
```

# 5.4 - The as-if rule and compile-time optimization

## Notes

### introduction to optimization

**Optimization**: The process of modifying software to make it work more efficiently
- Run faster, or use fewer resources
**Profiler**: Program that can be used to see how long various parts of the program are taking to run and which are impactng overall performance
**Optimizer**: Typically work at a low-level, looking for ways to improve statements or expressions by rewriting, reordering, or eliminating them

Because optimization involves some tradeoffs, compilers typically support multiple optimization levels that determine whether they optimize, how aggressively, and what kind of optimization they prioritize.

### The as-if rule

**As-if Rule**: The compiler can modify a program however it likes in order to produce more optimized code
- So long as those modifications do not affect a programs "observable behavior"

### An optimization opportunity

```cpp
#include <iostream>

int main()
{
	int x { 3 + 4 };
	std::cout << x << '\n';

	return 0;
}
```

`3 + 4` can be changed to just `7`, to reduce the number of times this is caluclated

### Compile-time evaluation

**Compile-time Evaluation**: When the compiler fully or partially evaluates an expression at compile-time

### Constant folding

**Constant folding**: An optimization technique where the compiler replaces expressions that have literal operands with the result of the expression

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

### Constant propagation

**Constant Propagation**: Optimization technique where the compiler replaces variables known to have constant values with their actual values

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

The compiler turns it into
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```

### Dead Code Elimination

**Dead Code Elimination**: Optimization technique where the compiler removes code that may be executed but has no effect on the program's behavior

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```

x is never used, this will result in:

```cpp
#include <iostream>

int main()
{
	std::cout << 7 << '\n';

	return 0;
}
```

**Optimized Out**: When a variable is removed from a program because it is no longer needed

### Const variables are easier to optimize

There are things we can do to help the compiler optimize more effectively

We can help the compiler effectively by using constant variables wherever possible

### Optimization can make programs harder to debug

Why isn't optimization turned on by default?
- Variables, expressions, statements, and function calls may be rearranged, modified, replaced or removed
- Can be hard to debug compiled code that no longer correlates very well with the original
- We have little visibility and few tools to help us understand what the compiler is doing

Debug builds will leave optimizations turned off, so that the compiled code will more closely match the source code

### Nomenclature: Compile-time constants vs runtime constants

**Compile-Time constant**: A constant whose value is known at compile-time
- Literals
- Constant objects whose initializers are compile-time constants
**Runtime constant**: Constant whose value is determined in a rntime context
- Constant function parameters
- Constant objects whose initializers are non-constant or runtime constant

```cpp
#include <iostream>

int five()
{
    return 5;
}

int pass(const int x) // x is a runtime constant
{
    return x;
}

int main()
{
    // The following are non-constants:
    [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value isn't known until runtime

    return 0;
}
```

# 5.5 - Constant Expressions

## Questions

1. For each statement, identify:
- Whether the initializer is a constant expression or non-constant expression.
- Whether the variable is a constant expression or non-constant expression.

- `char a { 'q' };`
  - Initializer: constant expression
  - Variable: non-constant expression
- `const int b { 0 };`
  - Initializer: constant expression
  - Variable: constant expression
- `const double c { 5.0 };`
  - Initializer: constant expression
  - Variable: non-constant expression
- `const int d { a * 2 }; // a defined as char a { 'q' };`
  - Initializer: non-constant expression
  - Variable: non-constant expression
- `int e { c + 1.0 }; // c defined as const double c { 5.0 };`
  - Initializer: constant expression
  - Variable: non-constant expression
- `const int f { d * 2 }; // d defined as const int d { 0 };`
  - Initializer: constant expression
  - Variable: constant expression
- `const int g { getNumber() }; // getNumber returns an int by value`
  - Initializer: non-constant expression
  - Variable: non-constant expression
- `const int h{}`
  - Initializer: No explicit initializer -> constant expression
  - Variable: Constant expression


## Notes

Expressions are required to evaluate at runtie

```cpp
const double x { 1.2 };
const double y { 3.4 };
const double z { x + y }; // x + y may evaluate at runtime or compile-time
```

The expression `x + y` would normally evaluate at runtime, but since `x` and `y` are known at compile-time, the compiler may opt to perform compile-time evaluation
- `z` will be initialized at compile-time calculated to `4.6`

In other cases, C++ requires an expression that can be evaluated at compile-time

`constexpr` variable require an initializer that can be evaluated at compile-time

```cpp
int main()
{
    constexpr int x { expr }; // Because variable x is constexpr, expr must be evaluatable at compile-time
}
```
- In cases where a constant expression is required but one is not provided, the compiler will error and halt compilation

### The benefits of compile-time programming

As-if rule is reliant on the sophistication of the compiler to actually determine what can evalutate at compile time
- There is a section of code we really want to execute at compile-time, it may or may not
- The as-if rule is applied invisibly to us, we get no feedback from the compiler

**Compile-time Programming**: C++ provides ways for us to be explicit about what parts of code we want to evaluate at compile time.

These features help improve software:
- Performance: Makes programs faster and smaller. More code we can ensure is capable of evaluating at compile-time, the more performance benefit we'll see
- Versatility: Always use code in places that require a compile-time value
- Predictability: Can have the compiler halt compilation if it determines that code cannot be executed at compile-time
- Quality: Reliably detect certain kinds of programing errors at compile-tie
- Quality: Undefined behavior is not allowed at compile-time.

### Constant Expressions

**Constant Expression**: A non-empty sequence of literals, constant variables, operators, and function calls, all of which must be evaluated at compile-time
- Each part of the expression must be evaluatable at compile-time

**Runtime Expression**: An expression that is not a constant expression

### What can be in a comstant expression?

Contain the following:
- Literals (e.g. '5', '1.2')
- Most operators with constant expression operands (e.g. `3+4`, `2 * sizxeof(int)`)
- Const integral variables with a const expression initializer (e.g. `const int x { 5 };`)
  - In modern C++, `constexpr` is preferred
- `Constexpr` values
- `constexpr` functions

Can also contain:
- Non-type template parameters
- Enumerators
- Type traits
- Constexpr lambda xpressions

The following cannot be used in a constant expression:
- Non-const variables
- Const non-integral variables (doubles, floats, long doubles)
- Return values of non-constexpr functions
- Function parameters, een when the function is constexpr
- Operators with operands that are not const expressions
- Operators `new`, `delete`, `throw`, `typeid`, and `operator,` (comma)

### Examples of constnat and non-constant expressions

```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```

```cpp
// Const integral variables with a constant expression initializer can be used in constant expressions:
const int a { 5 };           // a is usable in constant expressions
const int b { a };           // b is usable in constant expressions (a is a constant expression per the prior statement)
const long c { a + 2 };      // c is usable in constant expressions (operator+ has constant expression operands)

// Other variables cannot be used in constant expressions (even when they have a constant expression initializer):
int d { 5 };                 // d is not usable in constant expressions (d is non-const)
const int e { d };           // e is not usable in constant expressions (initializer is not a constant expression)
const double f { 1.2 };      // f is not usable in constant expressions (not a const integral variable)
```

### When constant expressions are evaluated at compile-time

The compiler is only *required* to evaluate constnat expressions at compile-time in contexts that *require* a constant expression

**Manifestly Constant-Evaluated Expression**: Expressions that must be evaluated at compile-time

```cpp
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```

`x` is usable ina constant expression. Initializer must be evaluated at compile-time\
`y` is non-const, so not usable in a constant expression.
- The compile can decide to evaluate the initializer at compile-time or runtime

### Why compile-time expressions must be constant

Constants cannot have their values changed. A constant variable whose initializer is evaluated at compile-time will always have a value that is known at compile-time

# 5.6 - Constexpr variable

## Notes

### The compile-time `const` challenge

1 way to create a variable that is used in a const expression is with `const`.\
The use of `const` to create variables that can be used in constant expressions has a few challenges

The use of `const` does not make it immediately clear whether the var is usable in a const expression or not.

```cpp
const int d { someVar };    // not obvious whether d is usable in a constant expression or not
const int e { getValue() }; // not obvious whether e is usable in a constant expression or not
```

Not obvious if usable depending on how `someVar` and `getValue()` are defined
- Have to inspect the definitions of the variables

Use of `const` doesn't provide a way to inform the compiler that we require a varaible that is usable ina constant expression
- It will just silently create a var that can only be used in runtime expression

### The `constexpr` keyword

**constexpr**: Variable is always a compile-time constant
- Must be initialized with a constant expression, otherwise a compilation error will result

```cpp
#include <iostream>

// The return value of a non-constexpr function is not constexpr
int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr

    return 0;
}
```

`constexpr` works for variables with non-integral types (doubles, floats, etc.)

### Meaning of const vs constexpr for variables

- `const`: The value of an object cannot be changed after initialization.
  - The value of the initializer may be known at compile-time or runtime
  - The object can be evaluated at runtime
- `constexpr`: The object can be used in a constant expression
  - The value of the initializer must be known at compile-time
  - The object can be evaluated at runtime or compile-time

`constexpr` is not part of an object's type
- A variable defined as `constexpr int` is type `const int`

Best Practice:
- Any constant variable whose initializer is a constant expression should be declared as `constexpr`
- Any constant variable whose initializer is not a constant expression should be declared as `const`

### Const and constexpr function parameters

Because the initialization of function parameters happens at runtime, this leads to 2 consequences:
- `const` function parameters are treated as runtime constants
- Function parameters cannot be declared as `constexpr`, since their initialization value isn't determined until runtime.

### A brief introduction to constexpr functions

**Constexpr function**: A function that can be called in a constant expression
- Must evaluate at compile-time when the constant expression it is part of must evaluate at compile time
- To be eligible for compile-time exectuion, all arguments must be constant expressions

The `constexpr` keyword is placed in the function declaration before the return type

```cpp
#include <iostream>

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int m1 { max(5, 6) };            // ok
    const int m2 { max(5, 6) };      // ok
    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
    const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time

    return 0;
}
```

# 5.7 - Introduction to std::string

## Questions

1. Write a program that asks the user to enter their full name and their age. As output, tell the user the sum of their age and the number of characters in their name (use the std::string::length() member function to get the length of the string). For simplicity, count any spaces in the name as a character.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your age: ";
    int age{}; // age needs to be an integer, not a string, so we can do math with it
    std::cin >> age;

    // age is signed, and name.length() is unsigned -- we shouldn't mix these
    // We'll convert name.length() to a signed value
    int nameLen { static_cast<int>(name.length()) }; // get number of chars in name (including spaces)
    std::cout << "Your age + length of name is: " << age + nameLen << '\n';

    return 0;
}
```

## Notes

C++ has introduced 2 addtional string types that are much easier and safer to work with
- `std::string`
- `std::string_view` (C++17)

### Introducing std::string

`std::string` lives in the <string> header.

```cpp
#include <string> // allows use of std::string

int main()
{
    std::string name {}; // empty string

    return 0;
}
```

You can initialize or assign values as you would expect

```cpp
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    name = "John";               // change name to "John"

    return 0;
}
```

Strings can be composed of numeric characters as well

### String output with `std::cout`

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name { "Alex" };
    std::cout << "My name is: " << name << '\n';

    return 0;
}
```

```shell
My name is: Alex
```

Empty strings will print nothing

### `std:: string` can handle strings of different lengths

`std::string` can store strings of different lengths

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    std::cout << name << '\n';

    name = "Jason";              // change name to a longer string
    std::cout << name << '\n';

    name = "Jay";                // change name to a shorter string
    std::cout << name << '\n';

    return 0;
}
```

If `std::string` doesn't have enough memory to store a string, it will request additional memory (at runtime) using dynamic memory allocation
- This ability to acquire additional memory is part of what makes `std::string` flexible, but slow

### String input with `std::cin`

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

```shell
Enter your full name: John Doe
Enter your favorite color: Your name is John and your favorite color is Doe
```

The `>>` extract the first string, as it will return when it encounters a white space


### Use `std::getline() to input text`

To read a full line of input, use `std::getline()`
- `std::getline()` requires 2 arguments, `std::cin` and the string variable

```cpp
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

### What is `std::ws`

`std::ws` is an input manipulator, telling `std::cin` to ignore any leading whitespace before extraction.

### The length of a `std::string`

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```

```shell
Alex has 4 characters
```

The returned length of a `std::string` does not unclude the implicit null-terminator character.
- The return type is most likely `size_t`.
- To assign it to int, you need to static cast it to int

```cpp
int length { static_cast<int>(name.length()) };
```

### Initializing a `std::string` is expensive

A copy of the string used to initialize an std::string is made
- Making copies of strings is expensive, so care should be taken to minimize the number of copies made

### Do not pass `std::string` by value

When a `std::string` is passed to a function by value, the parameter must be instantiated and initalized.
- Expensive copy
- Use `std::string_view` instead

### Returning a std::string

The return value is normally copied from the function back to the caller.\
It is okay to return a `std::string` by value when the expression of the return statement resolves to any of the following:
- A local variable of type `std::string`
- A `std::string` that has been returned by value from another function call or operator
- A `std::string` temporary that is created as part of the return statement

### Literals for `std::string`

Double-quoted string literals are C-style strings by default\
You can create `std::string` literals with an s suffix.

```cpp
#include <iostream>
#include <string> // for std::string

int main()
{
    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;
}
```

It is fine to initalize a `std::string` object with a C-style string literal.
- Few cases where the literals make things easier

### Constexpr strings

A `constexpr std::string` will likely generate an error
- Use `std::string_view` for constexpr strings

# 5.8 - Introduction to std::string_view

## Notes

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    std::cout << s << '\n';

    return 0;
}
```

When `s` is initialized, the C-style string is copied into memory allocated for `std::string s`. The initializing and copying is slow

```cpp
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    printString(s);

    return 0;
}
```

We have to copy the string multiple times, which is needless copying for a string.

### std::string_view C++17

`std::string_view` addresses the problems
- Lives in the <string_view> header
- Provides read-only access to an *existing* string without making a copy
  - **Read-only**: We can access and use the value being viewed, but not modified

```cpp
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```

No extra copies of `Hello, world!` are made\
`s` is provided read-only access to the string.
- When passed as an argument, the `str` is initialized from `s` without making a copy of the string

### `std::string_view` can be initialized with many different types of strings

`std::string_view` objects can be initialized with a C-string, `std::string`, or other `std::string_view`

### `std::string_view` parameters will accept many different types of string arguments

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str)
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```

### `std::string_view` will not implicitly convert to `std::string`

`std::string` makes a copy of its initializer.
- C++ won't allow implicit conversion of a `std::string_view` to a `std::string`
- This helps prevent accidental expensive copies

If desired to convert, 2 options:
- Explicitly create a `std::string` with a `std::string_view` initializer
- Convert an existing `std::string_view` to a `std::string` using `static_cast`

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printString(std::string str)
{
	std::cout << str << '\n';
}

int main()
{
	std::string_view sv{ "Hello, world!" };

	// printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string

	std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string

	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

	return 0;
}
```

### Assignment changes what the `std::string_view`

Assigning a new string to `std::string_view` causes the variable to view a new string
- It doesn't modify the prior string being viewed

### Literals for `std::string_view`

Can create string literals with type `std::string_view` by using a `sv` suffix.

### constexpr `std::string_view`

`std::string_view` has full support for constexpr.
- This makes `constexpr std::string_view` the preferred choice when string symbolic constants are needed

# 5.9 - std::string_view (part 2)

## Notes

### An introduction to owners and viewers

Ownership can be expensive. Responsibility to acquire, manage, and properly dispose of the objects you own\
Viewing is inexpensive. You have no responsibility for the object you are viewing, but you also have no control over those objects\

### `std::string` is a (sole) owner

Why does `std::string` make an expensive copy of its initializer?
- When an object is instantiated, memory is allocated for that object to store whatever data it needs
- Memory is reserved for the object, it is a safe space.
- `std::string` and many other objects copy the initialization value so that they can have their own independent value to access and manipulate later
- The object is no longer relianton the initializer in anyway
- The cost of independence is an expensive copy

### `std::string_view` is a viewer

`std::string_view` takes a different approach
- `std::string_view` creates an inexpensive view of the initialization string
- When the view is destroyed, the object being viewed is not affected
- `std::string_view` remains dependent on the initializer through its lifetime.
  - If the string being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result

**Dangling View**: A `std::strin_view` that is viewing a string that has been destroyed

### `std::string_view` is best used as read-only function parameter

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str) // now a std::string_view, creates a view of the argument
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```

### Improperly using `std::string_view`

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv{};

    { // create a nested block
        std::string s{ "Hello, world!" }; // create a std::string local to this nested block
        sv = s; // sv is now viewing s
    } // s is destroyed here, so sv is now viewing an invalid string

    std::cout << sv << '\n'; // undefined behavior

    return 0;
}
```

`sv` will won't know that `s` has been destroyed. When using `sv`, we are accessing an invalid object, and undefined behavior results.

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string getName()
{
    std::string s { "Alex" };
    return s;
}

int main()
{
  std::string_view name { getName() }; // name initialized with return value of function
  std::cout << name << '\n'; // undefined behavior

  return 0;
}
```

Return values are temporary objects that are destroyed at the end of the full expression containing the function call
- Must either use this return value immediately or copy it for later

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    using namespace std::string_literals;
    std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
    std::cout << name << '\n'; // undefined behavior

    return 0;
}
```

Do not initialize a `std::string_view` with a `std::string` literal as `std::string literals are temporary. It's okay to initialize with an object, not the literal


### Revalidating an invalid `std::string_view`

Invalidated objects can be revalidated by setting them back to a known good state\
We can assign an invalidated `std::string_view` with a valid string to view.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, universe!"

    return 0;
}
```

### Be careful returning a `std::string_view`

Returning a `std::string_view` can be dangerous
- Local variables the `std::string_view` might have been viewing in the function are often destroyed

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view getBoolName(bool b)
{
    std::string t { "true" };  // local variable
    std::string f { "false" }; // local variable

    if (b)
        return t;  // return a std::string_view viewing t

    return f; // return a std::string_view viewing f
} // t and f are destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    return 0;
}
```

2 main cases where a `std::string_view` can be returned safely
- It's fine to return C-style string literals from a function that has a return type of `std::string_view`
- It is generally okay to return a function parameter of type `std::string_view`

```cpp
#include <iostream>
#include <string_view>

std::string_view getBoolName(bool b)
{
    if (b)
        return "true";  // return a std::string_view viewing "true"

    return "false"; // return a std::string_view viewing "false"
} // "true" and "false" are not destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // ok

    return 0;
}
```

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
{
    if (s1 < s2)
        return s1;
    return s2;
}

int main()
{
    std::string a { "World" };
    std::string b { "Hello" };

    std::cout << firstAlphabetical(a, b) << '\n'; // prints "Hello"

    return 0;
}
```

### View modification functions

Because `std::string_view` is a view, it contains functions that let us modify our view by "closing the curtains"
- `remove_prefix()` removes characters from the left side of the view
- `remove_suffix()` removes characters from the right side of the view

```cpp
#include <iostream>
#include <string_view>

int main()
{
	std::string_view str{ "Peach" };
	std::cout << str << '\n';

	// Remove 1 character from the left side of the view
	str.remove_prefix(1);
	std::cout << str << '\n';

	// Remove 2 characters from the right side of the view
	str.remove_suffix(2);
	std::cout << str << '\n';

	str = "Peach"; // reset the view
	std::cout << str << '\n';

	return 0;
}
```

```shell
Peach
each
ea
Peach
```

### `std::string_view` can view a substring

While ``std::string_view` can be used to view an entire string, they also can view a substring without making a copy.\
**Substring**: A contiguous sequence of characters within an existing string

### `std::string_view` may or may not be null-terminated

The ability of viewing substring is a consequence.
- If `std::string_view` is only viewing a middling portion of a string, the substring is not null terminated

`std::string_view` does keep track of the length of the string/substring it is viewing
- It doesn't need the null-terminator
- Converting `std::string_view` to `std::string` will work regardless

### Guide on when to use `std::string` vs `std::string_view`

**Variables**:

`std::string`:
- Need a string you can modify
- Need to store user-inputted text
- Need to store the return value of a function that returns `std::string`

`std::string_view`:
- Need read-only access to part/all of a string that already exists
- You need a suymbolic constant for a C-style string
- Need to continue viewing the return value of a function that returns a C-style string or a non-dnagling `std::string_view`

**Function Parameters**:

`std::string`:
- The function needs to modify the string passed without affecting the caller
- Using standard C++14 or older
`std::string_view`:
- The function needs a read-only string
- The function needs to work with non-null-terminated strings

**Return Types**:

`std::string`: 
- The return value is a `std::string` local variable or function parameter
- The return value is a function call or operator that returns a `std::string` by value

`std::string_view`:
- The function returns a C-style string literal or local `std::string_view` that has been initialized with a C-style string literal
- The function returns a `std::string_view` parameter

**Insights**

Things to remember about `std::string`:

- Initializing and copying `std::string` is expensive, so avoid this as much as possible.
- Avoid passing `std::string` by value, as this makes a copy.
- If possible, avoid creating short-lived `std::string` objects.
- Modifying a `std::string` will invalidate any views to that string.
- It is okay to return a local `std::string` by value.

Things to remember about `std::string_view`:

- `std::string_view` is typically used for passing string function parameters and - returning string literals.
- Because C-style string literals exist for the entire program, it is always okay to set a `std::string_view` to a C-style string literal.
- When a string is destroyed, all views to that string are invalidated.
- Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
- A `std::string_view` may or may not be null-terminated.

# 5.x - Chapter 5 summary and quiz

## Review

- **Constant**: A value that may not be changed during the program's execution
- **Named Constant**: A constant value that is associated with an identifier
- **Literal Constant**: A constant value not associated with an identifier
- **Constant Variable**: A variable whose value can not be chnaged
- **const**: Keyword used to make a variable constant
- **Type Qualifier**: A keyword that is applied to a type that modifies how that type behaves
- **Constant Expression**: An expression that can be evaluated at compile-time
- **Runtime Expression**: An expression that is not a constant expression
- **Compile-Time Constant**: A constant whose value is known at compile-time
- **Runtime Constant**: A constant whose initialization value isn't know until runtime
- **constexpr**: Variable must be a compile-time constant, and initialized with a constant expression
- **Literals**: Values inserted directly into the code
- **Magic Number**: A literal that either has an unclear meaning or may need to be changed later
- **Decimal Numbers**: 10 digits
- **Binary Numbers**: 2 digits
- **Octal Numbers**: Base 8
- **Hexadecimal**: Base 16
- **Numeral Systems**: Collection of symbols used to represent numbers
- **string**: A collection of sequential characters that is used to represent text
- **std::string**: Offers an easy and safe way to deal with text strings
- **std::string_view**: Provides read-only access to an existing string
- **Dangling View**: A `std::string_view` that is viewing a string that has been destroyed
- **Invalidated**: Views that are no longer valid
- **substring**: A contiguous sequence of characters within an existing string

## Quiz

1. 
- Why are named constants often a better choice than literal constants?
  - They can be defined in one location and used repeatedly
- Why are const/constexpr variables usually a better choice than #defined symbolic constants?
  - #defined constants do not show up in the debugger and might have naming conflicts if multiple variables share the same identifier

2. Find 3 issues in the following code:

Sample desired outputs:
```shell
How old are you?
6
Allowed to drive a car in Texas: No

How old are you?
19
Allowed to drive a car in Texas: Yes
```

```cpp
#include <cstdint> // for std::uint8_t
#include <iostream>

int main()
{
  std::cout << "How old are you?\n";

  std::uint8_t age{}; // Defines as a char type
  std::cin >> age;

  std::cout << "Allowed to drive a car in Texas: ";

  if (age >= 16) // Magic Number
      std::cout << "Yes";
  else
      std::cout << "No";

  std::cout << '.\n'; // Uses single quote for multi variable

  return 0;
}
```

3. What are the primary differences between std::string and std::string_view? What can go wrong when using a std::string_view?
- std::string creates a copy of it's initialized value. std::string can be modified. std::string_view has read only access to an already existing string. If the object the std::string_view is observing changes or is removed, it can result in undesired behavior.

4. Write a program that asks for the name and age of two people, then prints which person is older.

Here is the sample output from one run of the program:

```shell
Enter the name of person #1: John Bacon
Enter the age of John Bacon: 37
Enter the name of person #2: David Jenkins
Enter the age of David Jenkins: 44
David Jenkins (age 44) is older than John Bacon (age 37).
```

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string getName(int num)
{
    std::cout << "Enter the name of person #" << num << ": ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    return name;
}

int getAge(std::string_view sv)
{
    std::cout << "Enter the age of " << sv << ": ";
    int age{};
    std::cin >> age;

    return age;
}

void printOlder(std::string_view name1, int age1, std::string_view name2, int age2)
{
    if (age1 > age2)
        std::cout << name1 << " (age " << age1 <<") is older than " << name2 << " (age " << age2 <<").\n";
    else
        std::cout << name2 << " (age " << age2 <<") is older than " << name1 << " (age " << age1 <<").\n";
}

int main()
{
    const std::string name1{ getName(1) };
    const int age1 { getAge(name1) };

    const std::string name2{ getName(2) };
    const int age2 { getAge(name2) };

    printOlder(name1, age1, name2, age2);

    return 0;
}
```

5. In the solution to the above quiz, why can’t variable age1 in main be constexpr?
- The return type of getAge is not a constant expression. It can't be evaluated at compile time as it takes a user input
