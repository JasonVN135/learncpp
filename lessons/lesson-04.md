# 4.1 - Introduction to fundamental data types

## Notes

### Bits, bytes, and memory addressing

**Binary Digit (Bit)**: The smallest unit of memory. Can hold a value of 0 and 1.
**Memory Addresses**: Sequential units where memory is organized.
- Each bit does not get its own unique memory address.
- Each address holds a byte
**Byte**: A group of bits that are operated on as a unit
- Modern standard is byte = 8 sequential bits

### Data Types

**Data Types**: Tell the compiler how to interpret the contents of memory in some meaningful way
- When you give an object a value, the compiler and CPU take care of encoding your value into the appropriate sequence of bits for that data type.
- Then stored in memory

### Fundamental Data Types

**Fundamental Data Types (Basic Types) (Primitive Types)**: The most basic data types

- float, double, long double: Floating Point: A number with a fractional part
- bool: Integral (Boolean): True or False
- char, wchar_t, char8_t, char16_t, char32_t: Integral (Character): a single character of text
- short int, int, long int, long long int: integral (Integer): Positive and negative whole numbers
- std::nullptr_t: Null pointer: A null pointer
- void: Void: no type

### Integer vs Integral Types

An "integer" is a number with no decimal or fractional parts\
An "integral" has several different means
- Used to mean "like an integer"

- **Standard Integer Types**: short, int, long, long long (Include signed and unsigned variants)
- **Integral Types**: bool, char, standard integer types

Integral types are stored in memory as integer values, but only the standard integer types will display as an integer value
- Non-fundamental types (enum, enum class) are not integral types

### Other sets of types

C++ contains three sets of types
- The "Fundamental data types" Provide the most the basic and essential data types
- The "compond data types" provide more complex data types and allow for the creation of custom types
- 3rd type is provided by the C++ standard library
  - Broadly available and have been standardized for compatibility
  - Use of the types require the inclusion of the appropriate header and linking

Notable omission is a data type to handle strings\
**Strings**: A sequence of characters that is typically used to prepresent text
- Modern C++ strings are part of the standard library

### The _t suffix

- Many of the types defined in newre versions use a _t suffix
- _t = "type"
- Common nomenclature applied to modern types

# 4.2 - Void

## Notes

**Void**: No type
- **Incomplete Type**: A type that has been declared but not yet defined
- Compiler knows about the existence of such type, but does not have enough info to determine how much memory to allocate for objects of that type
  - Incomplete types cannot be instantiated

### Functions that do not return a value

Void is used to indicate that a function does not return a value

### Deprecated: Functions that do not take parameters

In C, void is used as a way to indicate that a function does not take any parameters
- This is considered deprecated in C++

# 4.3 - Object sizes and the sizeof operator

## Notes

### Object Sizes

Memory on modern machines is typically organized into byte-sized units
- Each byte of memory having a unique address

Most objects actually take up more than 1 byte of memory
- The amount of memory that an object uses is based on its data type

When we access some variable `x` in our code, the compiler knows how many bytes of data is needs to be retrieved

A single bit can have 2 possible values, 0 and 1
- 2 bits can hold 4 values, 00, 01, 10, 11
- 3 bits can hold 8 values, 000, 001, 010, 011, 100, 101, 110, 111

An object with *n* bits can hold 2^n unique values
- 8 bit byte can hold 2^8 values (256)
- 2 bytes can hold 2^16 (65536)

Computers can have a finite amount of free memory
- Every time we define an object, a small potion of free memory is used for as long as the object is in existence
  - Modern computers have a lot of memory, this impact is usually negligible

Table of sizes

Booleans:
- bool: Min - 1 byte, Typical - 1 byte

Characters:
- char: Min - 1 byte, Typical - 1 byte
- wchar_t: Min - 1 byte, Typical - 2 or 4 bytes
- char8_t: Min - 1 byte, Typical - 1 byte
- char16_t: Min - 2 byte, Typical - 2 byte
- char32_t: Min - 4 byte, Typical - 4 byte

Integer:
- short: Min - 2 bytes, Typical - 2 bytes
- int: Min - 2 bytes, Typical - 4 bytes
- long: Min - 4 bytes, Typical - 4 or 8 bytes
- long long: - 8 bytes, Typical - 8 bytes

Floating Points:
- float: Min - 4 bytes, Typical - 4 bytes
- double: Min - 8 bytes, Typical - 8 bytes
- long double: Min - 8 bytes, Typical - 8, 12, 16 bytes

Pointer:
- std::nullptr_t: Min - 4 bytes, Typical - 4 or 8 bytes

### The sizeof operator

**Sizeof operator**: An unary operator that takes either a type or a variable and returns the size of an object of that type
- Using sizeof on an incomplete type will result in a compilation error
- You can use the sizeof operator on a variable name

# 4.4 - Signed integers

## Questions

1. What would the range of a 5-bit signed integer be?
  - -16 to 15

2. What is the result of 13 / 5? What is the result of -13 / 5?
  - 2, -2
   
## Notes

**Integer**: An integral type that can represent positive and negative whole nubmers, including 0.

### Signed Integers

**Sign**: The attribute of being positive, negative or zero\
**Signed**: Number's sign is stored as part of the value
- By default, integers in C++ are signed

### Defining Signed Integers

Preferred way to define the 4 types of signed integers

```cpp
short s;      // prefer "short" instead of "short int"
int i;
long l;       // prefer "long" instead of "long int"
long long ll; // prefer "long long" instead of "long long int"
```

Although adding *int* will work, we prefer the short names\
The integer types can also take an optional *signed* keyword

```cpp
signed short ss;
signed int si;
signed long sl;
signed long long sll;
```

### Signed integer ranges

A variable with *n* bits can hold 2^n possible values\
**Range**: The set of specific values that a data type can hold
- Range of an int variable is determined by 2 factors:
  - Size (in bits)
  - Whether it is signed or not

8-bit signed int has a range of -129 to 127.

An n-bit signed variable has a range of -(2^(n-1)) to (2^(n-1)) - 1

### Overflow

**Overflow**: If during the evaluation of an expression, the result is not mathematically defined or not in the range of the representable values for its type, the behavior is undefined

**Integer Overflow**: An arithmetic operation attempts to create a value outside the range that can be represented

### Integer Devision

When dividing 2 inteers, C++ works like you'd expect whenthe quotient is a whole number\
**Integer Divison**: Doing division with 2 integers
- C++ always produces an integer result
- Any fractional portion is simply dropped

# 4.5 - Unisnged integers, and why to avoid them

## Notes

### Unsigned integers

**Unisnged Integers**: Integers that can only hold non-negative whole numbers

### Defining unsigned integers

Use the **unsigned** keyword

```cpp
unsigned short us;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
```

### Unsigned integer ranges

An n-bit unsigned variable has a range of 0 to (2^n) - 1\
Unsigned integers are well-suited for networkng and systems with little memory

### Unsigned integer overflow

If we store a number that requires more bits than available, the answer overflows.\
If an unisnged value is out of range, it is divided by one greater than the largest number of the type, and only the remainder is kept

`280` is too big for 0-255. We divide 280 by 255+1 (256), remainder is 24.
- 24 is now stored
- The number "wraps around"

### Controversy over unsigned numbers

Many developers believe to generally avoid unsigned integers. 2 problems:
- With signed values, takes little work to accidently overflow because those values are far from 0
  - With unsigned, it is much easier to overflow the bottom of the range.
- Unexpected behavior can result when you mix signed and unsigned integers
  - In C++, if there is 1 signed integer and 1 unsigned integer, the signed integer will usually be converted to an unsigned integer
  - The result will be unsigned

### When should you use unsigned numbers

- Unsigned numbers are preferred when dealing with bit manipulation
- Useful when well-defined wrap-around behavior is required
- Use of unsigned numbers is still unavoidable in some cases, mainly those having to do with array indexing.

# 4.6 - Fixed-width integers and size_t

## Notes

If you assume an `int` is 32-bit because it is most likely, then your program will probably misbehave on architectures where `int` is actuall 16-bit.

If you assume an `int` is only 16-bit to ensure your program will behave, the range of values you can store is significantly limited
- On systems with 32-bit ints, you're not making use of half of the memory allocated per int

### Why isn't the size of the int type fixed?

Because of early days of C, C opted to intentionally leave the size of an integer open so that the compiler implementers could pick a size for `int`

### Fixed-width integers

**Fixed-width integers**: An alternative set of integer types that are guaranteed to be the same size on any architecture

- std::int8_t - 1 byte - -128 to 127
- std::uint8_t - 1 byte - 0 to 256
- std::int16_t - 2 bytes - -32768 to 32767
- std::uint16_t - 2 bytes - 0 to 65535
- std::int32_t - 4 bytes - long
- std::uint32_t - 4 bytes - unsigned long
- std::int64_t - 8 bytes - long long
- std::uint64_t - 8 bytes - unsigned long long

### Warning: std::int8_t and std::uint8_t typically behave like chars

Modern compilers typically treat `std::int8_t` and `std::uint8_t` the same as `signed char` and `unsigned char`

### Other fixed-width downsides

- Not guaranteed to be defined on all architectures
  - Only exist on systems where there are fundamental integral types that match their width and following a certain binary representation
  - Fail to compile on architecture that doesn't support a fixed-width integer
  - Only a problem for exotic mainframe or embedded architectures
- It may be slower than a wider type on some architectures
  - CPU might be faster at processing 64-bit integers
  - Modern programs are often constrained by memory usage rather than CPU

### Fast and least integral types

C++ also defines 2 alternative sets of integers that are guaranteed to exist

Fast types are integral type that can be processed most quickly by the CPU\
Least types provide the smallest signed/unsigned integer type that's at least a certain size

```cpp
#include <cstdint> // for fast and least types
#include <iostream>

int main()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
	std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
	std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";

	return 0;
}
```

```shell
least 8:  8 bits
least 16: 16 bits
least 32: 32 bits

fast 8:  8 bits
fast 16: 32 bits
fast 32: 32 bits
```

Have their own downsides
- Not many programmers actually use them
- Lack of familiarity can lead to errors
- Fast types can also lead to memory wastage, as their actual size may be significantly larger than indicated by their name
- Program may exhibit different behaviors on architectures where they resolve to different sizes

### Best Practices for Integral Types

- Prefer `int` when size of integer doesn't matter
  - Age should always fit for 16 bit
- Prefer `std::int#_t` when storing a quantity that needs a guaranteed range
- Prefer `std::uint#_t` when doing bit manipulation or well-defined wrap-around behavior is required (cryptography or random number generation)

Avoid the following
- `short` and `long`
- Fast and least integral types
- Unsigned types for holding quantities
- 8-bit fixed width integer types
- Any compiler-specific fixed-width integers

### What is std::size_t

```cpp
#include <iostream>

int main()
{
    std::cout << sizeof(int) << '\n';

    return 0;
}
```

```shell
4
```

`sizeof` returns a value of type `std::size_t`
- **std::size_t**: An alias for an implementation-defined unsigned integral type
  - Compiler decides if `std::size_t` is an unsigned int, unsigned long, unsigned long long, etc.

If you need to use `std::size_t`, <cstddef> is the best header to include

```cpp
#include <cstddef>  // for std::size_t
#include <iostream>

int main()
{
    int x { 5 };
    std::size_t s { sizeof(x) }; // sizeof returns a value of type std::size_t, so that should be the type of s
    std::cout << s << '\n';

    return 0;
}
```

# 4.7 - Introduction to scientific notation

## Questions

1. Convert the following numbers to scientific notation, and determine how mayn significant digits each has
- 34.50 = 3.450e1, 4 sigfigs
- 0.004000 = 4.000e-3, 4 sigfigs
- 123.005 = 1.23005e2, 6 sigfigs
- 146000 = 1.46e5, 3 sigfigs
- 146000.001 = 1.46000001e5, 9 sigfigs
- 0.0000000008 = 8e-10, 2 sigfigs
- 34500.0 = 3.45000e4, 6 sigfigs
- 146000 = 1.46000e5, 6 sigfigs

## Notes

**Scientific Notation**: Useful shorthand for writing lengthy numbers in a concise manner
- significand x 10^exponent
- Numbers in scientific notation are written with 1 digit before the decimal point, the rest of the digits after

### Significant digits

**Significant Digits**: The digits in the significand.
- The more significant digits, the more precise a number is

In scientific notation, write `3.14` as `3.14e0` = 3 significant digits
- `3.14159` would be written as `3.14159e0` = 6 significant digits

### Trailing Zeros

Trailing zeros after a decimal point are considered significant, so we keep them:

- 87.0g = 8.70e1
- 87.000g = 8.7000e1

Numbers with no decimal point, trailing zeros are considered to be insignificant by default

- 2100 = 2.1e3

But, if we know that this number was measured precisely (the actual number is between two numbers), we should instead treat those zeros as significant

- 2100 = 2.100e3

A number with a trailing decimal point indicates the zeros are significant

- 2100. = 2.100e3

# 4.8 - Floating point numbers

## Notes

**Floating point**: Variables that can hold a number with a fractional component
- floating refers to the fact that the decimal point can "float", support a variable number of digits before and after the decminal point
- Always signed

### C++ Floating point types

3 fundamental floating point data types:
- `float`: Single-precision
- `double`: Double-precision
- `long double`: Extended-precision

C++ does not defin the actual size of these types
- `float`: Typical Size: 4 bytes
- `double`: Typical Size: 8 bytes
- `long double`: Typical Size: 8, 12, or 16 bytes

`long double` size can vary.

```cpp
float f;
double d;
long double ld;
```

When using floating point literals, always include at least 1 decimal place.
- Helps the compiler understand that the number is a floating point number, not an integer

```cpp
int a { 5 };      // 5 means integer
double b { 5.0 }; // 5.0 is a floating point literal (no suffix means double type by default)
float c { 5.0f }; // 5.0 is a floating point literal, f suffix means float type

int d { 0 };      // 0 is an integer
double e { 0.0 }; // 0.0 is a double
```

Floating point literals default to type double. An `f` suffix is used todenote a literal of type float.

### Printing floating point numbers

```cpp
#include <iostream>

int main()
{
	std::cout << 5.0 << '\n';
	std::cout << 6.7f << '\n';
	std::cout << 9876543.21 << '\n';

	return 0;
}
```

Results:

```shell
5
6.7
9.87654e+06
```

`std::cout` printed 5. By default `std::cout` will not print the fractional part of the numbe rif the fractional part is 0\
`std::cout` printed in scientific notation as well.

Floating pont ranges
- 4 bytes single precision
  - Range: +/- 1.18 * 10^-38 to +/- 3.4 * 10^38, and 0
  - Precision: 6-9 sigfigs, typically 7
- 8 bytes double precision
  - Range: +/- 2.23 * 10^-308 to +/- 1.80 * 10^308, and 0
  - Precision: 15-18 sigfigs, typically 16
- 16 bytes quadruple precision
  - Range: +/- 3.36 * 10^-4932 to +/- 1.18 * 10^4932, and 0
  - Precision: 18-21 sigfigs
- x87 extended precision
  - Range: +/- 3.36 * 10^-4932 to +/- 1.18 * 10^4932, and 0
  - Precision: 33-36 sigfigs

### Floating point precision

An infinite precision number would require infinite memory to store 1/3. We typically only have 4 or 8 bytes per value.
- The limited memory means floating point numbers can only store a certain number of sigfigs
- Any additonal sig digits are lost or represented imprecisely

**Precision**: Defines how many sigfigs a floating point number can represent without information loss


### Outputting floating point values

Outputting floating point numbers with `std::cout` has a default precision of 6
- Assumes all floating point vars are only significant to 6 digits

```cpp
#include <iostream>

int main()
{
    std::cout << 9.87654321f << '\n';
    std::cout << 987.654321f << '\n';
    std::cout << 987654.321f << '\n';
    std::cout << 9876543.21f << '\n';
    std::cout << 0.0000987654321f << '\n';

    return 0;
}
```

```shell
9.87654
987.654
987654
9.87654e+006
9.87654e-005
```

We can override the default precision by using an output manipulator function name `std::setprecision()`.
- **Output manipulators**: Alter how data is output
  - Defined in the `iomanip` header

```cpp
#include <iomanip> // for output manipulator std::setprecision()
#include <iostream>

int main()
{
    std::cout << std::setprecision(17); // show 17 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
    std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double

    return 0;
}
```

```shell
3.3333332538604736
3.3333333333333335
```

Numbers certainly aren't precise to 17 digits.

### Rounding errors make floating point comparison tricky

Floating point umbers are tricky to work with due to non-obvious differences between binary and decimal numbers
- 0.1 is represented by the infinit sequence: 0.00011001100110011.. because of precision problems

Mathematical operations tend to make rounding errors grow.
- Continued operations would cause this error to become increasingly significant

### NaN and Inf

IEEE 754 compatible formats have additional values:
- **Inf**: Represents infinity. Inf is signed and can be positive (+Inf) or negative (-Inf)
- **NaN**: Stands for "Not a Number". Several different kinds of NaN
- Signed zero. There are separate representations for "positive zero" (+0.0) and "negative zero" (-0.0)

# 4.9 Boolean Values

## Notes

**Boolean**: A type for only 2 possible outcomes, true or false.

### Boolean variables

Booleans can have only 2 possible values: true and false

```cpp
bool b;
```

To initialize/assign a Boolean variable, use `true` and `false`

```cpp
bool b1 { true };
bool b2 { false };
b1 = false;
bool b3 {}; // default initialize to false
```

The logical NOT operator (!) can be used to flip a Boolean value from `true` to `false`, or `false` to `true`

```cpp
bool b1 { !true }; // b1 will be initialized with the value false
bool b2 { !false }; // b2 will be initialized with the value true
```

`true` is stored as integer `1` and `false` is stored as integer `0`.
- Boolean values are evaluated to integers `0` and `1`, because they are stored as integral values

### Printing Boolean values

```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b {false};
    std::cout << b << '\n'; // b is false, which evaluates to 0
    std::cout << !b << '\n'; // !b is true, which evaluates to 1
    return 0;
}
```

```shell
1
0
0
1
```

### std::boolalpha to print true or false

If you want `std::cout` to print `true` or `false`, you can output `std::boolalpha`.
- This manipulates the way `std::cout` outputs `bool` values

```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n';
    std::cout << false << '\n';
    return 0;
}
```

```shell
1
0
true
false
```

### Integer to Boolean conversion

You can initialize a variable using integer literals 0 (false) and 1 (true), you should really use false and true.
- Other integer literals cause compilation errors

```cpp
#include <iostream>

int main()
{
	bool bFalse { 0 }; // okay: initialized to false
	bool bTrue  { 1 }; // okay: initialized to true
	bool bNo    { 2 }; // error: narrowing conversions disallowed

	std::cout << bFalse << bTrue << bNo << '\n';

	return 0;
}
```

In any context where an integer can be converted to a Boolean, the integer `0` is `false` and any other integer is converted to `true`

```cpp
#include <iostream>

int main()
{
	std::cout << std::boolalpha; // print bools as true or false

	bool b1 = 4 ; // copy initialization allows implicit conversion from int to bool
	std::cout << b1 << '\n';

	bool b2 = 0 ; // copy initialization allows implicit conversion from int to bool
	std::cout << b2 << '\n';

	return 0;
}
```

### Inputting Boolean values

By default, `std::cin` only accepts numeric input for Boolean variables 0 and 1. 
- Any other numeric values will be interpreted as `true`, and will cause `std::cin` to enter failure mode.
- Any non-numeric value will be interpreted as `false` and will cause `std::cin` to enter failure mode.
- To allow `std::cin` to accept the words `false` and `true`, use `std::boolalpha and std::noboolalpha

```cpp
#include <iostream>

int main()
{
	bool b{};
	std::cout << "Enter a boolean value: ";

	// Allow the user to input 'true' or 'false' for boolean values
	// This is case-sensitive, so True or TRUE will not work
	std::cin >> std::boolalpha;
	std::cin >> b;

	// Let's also output bool values as `true` or `false`
	std::cout << std::boolalpha;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```

### Boolean return values

Boolean values are often used as the return values for functions that check whether something is true or not
- Functions typically start with the word *is* or *has*

```cpp
#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << x << " and " << y << " are equal? ";
    std::cout << isEqual(x, y) << '\n'; // will return true or false

    return 0;
}
```

# 4.10 - Introduction to If Statements

## Questions

1. What is an early return, and what is its behavior?
- Early returns are returns that aren't the last statement in a function. They will return back to the function that called it when the return-statement is executed.

2. A prime number is a whole number greater than 1 that can only be divided evenly by 1 and itself. Write a program that asks the user to enter a number 0 through 9 (inclusive). If the user enters a number within this range that is prime (2, 3, 5, or 7), print “The digit is prime”. Otherwise, print “The digit is not prime”.

```cpp
#include <iostream>

int main()
{
  
    std::cout << "Enter a number [0-9]: ";

    int x{};
    std::cin >> x;

    if (x < 0 || x > 9) {
        std::cout << "The digit is out of range\n";
    }
    else if (x == 2 || x == 3 || x == 5 || x == 7) {
        std::cout << "The digit is prime\n";
    }
    else {
        std::cout << "The digit is not prime\n";
    }

    return 0;
}
```

3. How can the length of the following code be reduced (without changing the formatting)?

```cpp
#include <iostream>

bool isAllowedToTakeFunRide()
{
  std::cout << "How tall are you? (cm)\n";

  double height{};
  std::cin >> height;

  if (height >= 140.0)
    return true;
  else
    return false;
}

int main()
{
  if (isAllowedToTakeFunRide())
    std::cout << "Have fun!\n";
  else
    std::cout << "Sorry, you're too short.\n";

  return 0;
}
```

```cpp
#include <iostream>

bool isAllowedToTakeFunRide()
{
  std::cout << "How tall are you? (cm)\n";

  double height{};
  std::cin >> height;

  return (height >= 140.0);
}

int main()
{
  if (isAllowedToTakeFunRide())
    std::cout << "Have fun!\n";
  else
    std::cout << "Sorry, you're too short.\n";

  return 0;
}
```

## Notes

**If Statement**: Allows us to execute one or more lines of code only if some condition is true

The simplest *if statement*:

```shell
if (condition) 
  true_statement;
```

**Condition**: An expression that evaluates to a boolean value
- If the condition of an if statment evaluates to true, then the statement executes
- If the condition is false, then the statement is skipped

### A Sample program using an if statement

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";

    return 0;
}
```

### If-Else

We can use an if-else statement to perform one or the other action.

```shell
if (condition)
    true_statement;
else
    false_statement;
```

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";
    else
        std::cout << "The value is non-zero\n";

    return 0;
}
```

### Chaining if statements

If we want to check if several things are true or false in sequence, you can use an else if statement.

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x > 0)
        std::cout << "The value is positive\n";
    else if (x < 0)
        std::cout << "The value is negative\n";
    else
        std::cout << "The value is zero\n";

    return 0;
}
```

### Non-Boolean conditionals

Our conditionals have been either Boolean values (true or false), Boolean variables, or functions that return a Boolean value
- What happens if your conditional is an expression that does not evaluate to a boolean value?

The result of the conditional expression is converted to a Boolean value
- Non-zero values get converted to `true`
- Zero values get converted to `false` 

```cpp
#include <iostream>

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```

### If-statements and early returns

**Early Return**: A return-statement that is not the last statement in a function
- Cause the function to return to the caller when the return statement is executed

```cpp
void print()
{
    std::cout << "A" << '\n';

    return; // the function will always return to the caller here

    std::cout << "B" << '\n'; // this will never be printed
}
```

Early returns provide a way to conditionalize the return value of our function

```cpp
#include <iostream>

// returns the absolute value of x
int abs(int x)
{
    if (x < 0)
        return -x; // early return (only when x < 0)

    return x;
}

int main()
{
    std::cout << abs(4) << '\n'; // prints 4
    std::cout << abs(-3) << '\n'; // prints 3

    return 0;
}
```

# 4.11 - Chars

## Notes

**Char data type**: Designed to hol a single `character`\
**Character**: Can be a single letter, number, symbol, or whitespace

The integer stored by a `char` variable are intepreted as an `ASCII character`\
**ASCII**: Stands for American Standard Code for information interchange
- Defines a particular way to represent English characters (plus other symbols) as numbers between 0-127

Character literals are always placed between single quotes ('1', 'q', '%')

Code 0-31 and 127 are called unprintable chars
- Designed to control peripheral devices such as printers
- Most are obsolete now

Code 32-126 are printable characters.
- Represent letters, number characters, and punctuation that most computers use to display basic English text

### Initializing chars

You can initialize char variables using character literals or integers:

```cpp
char ch2{ 'a' }; // initialize with code point for 'a' (stored as integer 97) (preferred)
char ch1{ 97 }; // initialize with integer 97 ('a') (not preferred)
```

### Printing chars

When using `std::cout`, to print a char, it outpusts the char variable as an ASCII character

### Inputting chars

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: ";

    char ch{};
    std::cin >> ch;
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

```shell
Input a keyboard character: q
You entered: q
```

`std::cin` will let you enter multiple characters, but a char can only hold 1 character.
- Only the first input character is extracted into the variable
- The rest of the user input is left in the input buffer
  - Can be extracted with subsequent calls to `std::cin`

### Extracting whitespace characters

Extracting input ignores leading whitespace
- Can lead to unexpected results when trying to extract whitespace characters to a char variable

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

```shell
Input a keyboard character: a b
You entered: a
You entered: b
```

One simple way to address this is to use the `std::cin.get()` function to perform the extraction instead
- `std::cin.get()` does not ignore leading whitespace

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin.get(ch); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

### Char size, range, and default sign

Char is defined by C++ to always be 1 byte in size
- Char may be signed or unsigned
- To hold ASCII characters, you don't ened to specify a sign
  - Both signed and unsigned chars hold values between 0 annd 127

### Escape Sequence

**Escape Sequences**: Special characters that starts with a `\` backslash
- Most common: `\n` - newline
- Another: `\t` - horizontal tab

```cpp
#include <iostream>

int main()
{
    std::cout << "First part\tSecond part";
    return 0;
}
```

```shell
First part	Second part
```

Other escape sequences:
- `\'` - single quote
- `\"` - double quote
- `\\` - backslash

### Difference between putting symbols in single and double quotes

- Single quotes treat text like a `char` literal
- Double quotes treat text as a C-style string literal, which contains multiple characters

### Other char types, wchar_t, char8_t, char16_t, char32_t

Other character encoding standards exist to map integers (of varying sizes) to characters in other languages

Unicode standard maps over 144_000 integers to characters in many different languages

`char16_t` and `char32_t` were added to C++11 to provide support for 16-bit and 32-bit Unicode characters

Won't need the other char types unless you plan on making your program Unicode compatible

Avoid `wchar_t` (unless interfacing with the Windows API)

# 4.12 - Introduction to type conversion and static_cast

## Questions

1. Write a short program where the user is asked to enter a single character. Print the value of the character and its ASCII code, using static_cast.

```cpp
#include <iostream>

int main()
{
  std::cout << "Enter a single character: ";

  char ch{};
  std::cin >> ch;

  std::cout << "You entered '" << ch <<"', which has ASCII code " << static_cast<int>(ch) << ".\n";

  return 0;
}
```

2. 


## Notes

### Implicit Type Conversion

**Type Conversion**: The process of converting data from 1 type to another.
- In most cases, C++ will allow us to convert values of 1 fundamental type to another

**Implicit Type Conversion**: The compiler does type conversion on our behalf without us explicitly asking

```cpp
#include <iostream>

void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	int y { 5 };
	print(y); // y is of type int

	return 0;
}
```

### Type conversion of a value produces a new value

The type conversion process does not modify the value supplying the data to be converted
- The conversion process uses the data as input, and produces the converted result

The conversion does not change `y` from `int` to `double`
- The conversion uses the value of `y (5)` as input, and returns a temporary object of type `double` with value `5.0`.

### Implicit type conversion warnings

There are a few cases where type conversion is not sufficient

```cpp
#include <iostream>

void print(int x) // print now takes an int parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5.5); // warning: we're passing in a double value

	return 0;
}
```

The compiler will generate a warning about a possible loss of data

### Explicit type conversion via the static_cast operator

C++ supports a second method of type conversion

**Explicit Type Conversion**: Allow us to explicitly tell the compiler to convert a value from 1 type to another.
- Use the `static_cast` operator

```cpp
static_cast<new_type>(expression)
```

```cpp
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int

	return 0;
}
```

Because we use explicit cast, the compiler will not generate a warning about a possible loss of data

### Using static_cast to convert char to int

If we want to print the integral value instead of the char, we can use static_cast from `char` to `int

```cpp
#include <iostream>

int main()
{
  char ch{ 97 }; // 97 is ASCII code for 'a'
    // print value of variable ch as an int
    std::cout << ch << " has value " << static_cast<int>(ch) << '\n';

  return 0;
}
```

### Sign conversion using static_cast

Signed integral values can be converted to unsigned integral values, and vice-versa

If the value being converted can be represented int he destination type, the value will remain unchanged

```cpp
#include <iostream>

int main()
{
    unsigned int u1 { 5 };
    // Convert value of u1 to a signed int
    int s1 { static_cast<int>(u1) };
    std::cout << s1 << '\n'; // prints 5

    int s2 { 5 };
    // Convert value of s2 to an unsigned int
    unsigned int u2 { static_cast<unsigned int>(s2) };
    std::cout << u2 << '\n'; // prints 5

    return 0;
}
```

If not:
- If the destination type is unsigned, the value will be modula wrapped
- If the destination type is signed, the value is implementation defined prior to C++20, or modulo wrapped as of C++20

```cpp
#include <iostream>

int main()
{
    int s { -1 };
    std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

    unsigned int u { 4294967295 }; // largest 32-bit unsigned int
    std::cout << static_cast<int>(u) << '\n'; // implementation-defined prior to C++20, -1 as of C++20

    return 0;
}
```

```shell
4294967295
-1
```

### std::int8_t and std::uint8_t likely behave like chars instead of integers

Most compilers define and treat `std::int8_t` and `std::uint8_t` identically to types `signed char` and `unsigned char` respectively

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int8_t myInt{65};      // initialize myInt with value 65
    std::cout << myInt << '\n'; // you're probably expecting this to print 65

    return 0;
}
```

On most systems, this program will print `A` instead of `65`.
- This isn't guaranteed, as some will print `65`

Use `static_cast` to ensure printing the correct type

# 4.x - Chapter 4 summary and quiz

## Review

- **Binary Digit**: **Bit**, the smallest unit of memory
- **Byte**: The smallest unit amount of memory that can be addressed directly
- **Data Type**: Tells the compiler how to interpret the contents of memory in some meaningful way
- **Void**: Used to indicate no type. Primary used to indicate that a function does not return a value
- **sizeof**: Operator used to return the size of a type in bytes
- **Signed integer**: Used to hold positive and negative whole numbers, including 0
- **Range**: The set of values that a specific data type can hold
- **Unsigned Integer**: Hold positive numbers and 0. Generally be avoided
- **Fixed-width Integers**: Integers with guaranteed size, may not exist on all architectures
- **size_t**: An unsigned integral type that is used to represent the size or length of objects
- **Scientific Notation**: A shorthand way of writing lengthy numbers
- **Significant digits (sigfigs)**: Digits in the significand
- **Floating point**: Set of types designed to hold real numbers.
- **Precision**: A number defines how many significant digits it can represent without information loss
- **Rounding Error**: Can occur when too many significant digits are stored in a floating point umber
- **Boolean**: Used to store `true` or `false`
- **If statmenets**: Allow us to execute one or more lines of code if some condition is true
- **Else statement**: Used to execute a statement when a prior if-statement condition evaluates to false
- **Char**: Used to store values that are interpreted as an ASCII character

## Quiz

1. Pick the appropriate data type for a variable in each of the following situations. Be as specific as possible. If the answer is an integer, pick int (if size isn’t important), or a specific fixed-width integer type (e.g. std::int16_t) based on range.

- The age of the user (in years) (assume the size of the type isn’t important)
  - int
- Whether the user wants the application to check for updates
  - bool
- pi (3.14159265)
  - double
- The number of pages in a textbook (assume size is not important)
  - int
- The length of a couch in feet, to 2 decimal places (assume size is important)
  - float
- How many times you’ve blinked since you were born (note: answer is in the millions)
  - std::int32_t
- A user selecting an option from a menu by letter
  - char
- The year someone was born (assuming size is important)
  - std::int16_t

2. Write the following program: The user is asked to enter 2 floating point numbers (use doubles). The user is then asked to enter one of the following mathematical symbols: +, -, *, or /. The program computes the answer on the two numbers the user entered and prints the results. If the user enters an invalid symbol, the program should print nothing.

```cpp
#include <iostream>

double getValue() {
    std::cout << "Enter a double value: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator() {
    std::cout << "Enter a double value: ";
    char x{};
    std::cin >> x;
    return x;

}

int main()
{
    double x{getValue()};
    double y{getValue()};
    char ch{getOperator()};

    if (ch == '+') {
        std::cout << x << " + " << y << " = " << (x + y) << "\n";
    }
    else if (ch == '-') {
        std::cout << x << " - " << y << " = " << (x - y) << "\n";
    }
    else if (ch == '*') {
        std::cout << x << " * " << y << " = " << (x * y) << "\n";
    }
    else if (ch == '/') {
        std::cout << x << " / " << y << " = " << (x / y) << "\n";
    }

    return 0;
}
```

3. Write a short program to simulate a ball being dropped off of a tower. To start, the user should be asked for the height of the tower in meters. Assume normal gravity (9.8 m/s2), and that the ball has no initial velocity (the ball is not moving to start). Have the program output the height of the ball above the ground after 0, 1, 2, 3, 4, and 5 seconds. The ball should not go underneath the ground (height 0).

Use a function to calculate the height of the ball after x seconds. The function can calculate how far the ball has fallen after x seconds using the following formula: distance fallen = gravity_constant * x_seconds2 / 2

```cpp
#include <iostream>

double getStartingHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double x{};
    std::cin >> x;
    return x;
}

double calculateNewHeight(int time, double originalHeight) 
{
    double gravity {9.8};
    double heightFallen = gravity * time * time / 2;
    double newHeight = originalHeight - heightFallen;
    return newHeight;
}

void printCurrentHeight(int time, double height) {

    if (height > 0) {
        std::cout << "At " << time << " seconds, the ball is at height: " << height << " meters.\n";
    }
    else {
        std::cout << "At " << time << " seconds, the ball is on the ground.\n";
    }
}

int main()
{

    double height{ getStartingHeight() };

    printCurrentHeight(0, calculateNewHeight(0, height));
    printCurrentHeight(1, calculateNewHeight(1, height));
    printCurrentHeight(2, calculateNewHeight(2, height));
    printCurrentHeight(3, calculateNewHeight(3, height));
    printCurrentHeight(4, calculateNewHeight(4, height));
    printCurrentHeight(5, calculateNewHeight(5, height));

    return 0;
}
```