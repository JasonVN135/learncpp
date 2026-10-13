# 10.1 - Implicit Type Conversions

## Notes

- The process of converting data from 1 type to another is called "type conversion"
- Implicit type conversion is performed automatically by the compiler when one data type is required, but a different data type is supplied
- Explicit type conversion is requested by using `static_cast`
- Conversions do not change the data being converted, instead the conversion process uses that data as input, and produces the converted result
- When converting a value to another type, the conversion process produces a temporary object of thetarget type that holds the result of the conversion

### Why conversions are needed

Value of an objet is stored as a sequence of bits
- Different data types may represent the "same" value differently

An integer 3 needs to be converted into the equivalent floating point value `3.0`, which can then be stored in teh memory allocated for `f`

### When implicit type conversion happens

**Implicit Type Conversion**: Performed automatically by the compiler when an expression of some type is supplied in a context where some other type is expected
- Vast majority of type conversion in C++ are implicit type conversions

```cpp
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double

float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}

double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double

if (5) // int value 5 implicitly converted to type bool
{
}

void doSomething(long l)
{
}

doSomething(3); // int value 3 implicitly converted to type long
```

### Standard Conversion

C++ standard defines a collection of conversion rules known as the "standard conversions"

**Standard Conversion**: Specify how various fundamental types convert to other types within the same group

Roughly 5 categories:
- Numeric Promotions: Conversion of small integral types to `int` or `unsigned int`, and of `float` to `double`
- Numeric Conversion: Other integral and floating point conversions that aren't promotion
- Qualification Conversion: Conversions that add or remove `const` or `volatile`
- Value transformation: Conversions that change the value category of an expression
- Pointer Conversions: Conversions from `std::nullptr` to pointer types, or pointer types to other pointer types

Converting an `int` to a `float` falls under numeric conversion

Numeric conversions and numeric promotions are the most import categories

### Type conversions can fail

When a type conversion is invoked, the compiler will determine whether it can convert thevalue from the current type to the desired type
- If a valid conversion is found, the compiler will produce a new value of thedesired type
- If it can't find an acceptable conversion, the compiler will fail with a compile error

Narrowing conversions are disallwed when using brace-initialization

Cases where the compiler may not be able to figure out which of several possible type conversions is the best one to use

# 10.2 - Floating point and integral promotion

## Notes

What happens when we want our 32-bit CPU to modify an 8-bit value (char) or a 16 bit value
- Some 332-bit processors can manipulate 8 or 16-bit values directly
- Doing so is often slower than manipulating 32-bit values

### Numeric Promotion

C++ defines a category of type conversions called `numeric promotions`\
**Numeric Promotion**: The type conversion of certain narrower numeric types (such as a `char`) to certain wider numeric types (`int` or `double`) can be processed efficiently

**Value-Preserving Conversions**: All numeric promotions, every possible source value can be converted into an equal value of the destination type

### Numeric Promotion Reduces Redundancy

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

We can write functions that have `int` or `double` parameters. That same code can then be called with arguments of types that can be numerically promoted to match the type of the function parameters

### Numeric Promotion Categories

Numeric promotion rules are divided into 2 subcategories: `integral promotion` and `floating point promotion`

Only the conversions listed in these categories are considered to be numeric promotion

### Floating Point Promotions

**Floating Point Promotion**: A value of type **float** can be converted to a value of type **double**

We can write a function that takes a `double` and then call it with either a `double` or a `float` value

### Integral Promotion

**Integral Promotion**: The following conversions can be made:
- Signed char or signed short can be converted to int
- unsigned char, char8_t and unsigned short can be convertd to int if int can hold the entire range of the type, or unsigned int otherwise
- If char is signed by default, it follows teh signed char conversion rule above, if it is unisgned by default, it follows the unsigned char conversion rules above
- bool can be converted to int, with false becoming 0 and true becoming 1

Assuming an 8 bit byte and an `int` size of 4 bytes or larger, the above basically means that 
bool, char, signed char, unsigned char, shigned short, unsigned short all get promoted to `int`

For some architectures with 2 byte ints, it is possible for some of the unsigned integral types to be promoted to unsigned int rather than int

Some narrower unsignedtypes (unsigned char) may be promoted to larger signed types such as int

### Not all widening conversion are numeric promotions

Some widening type conversions (`char` to `short`, `int` to `long`) are not considered to be numeric promotions
- Such conversions do not assist in the goal of converting smaller types to larger types that can be processed more efficiently

The compiler will favor numeric promotions over numeric conversions

# 10.3 - Numeric Conversions

## Notes

**Numeric Conversions**: Cover additional type conversions between fundamental types

5 Basic types of numeric conversions

1. Converting an integral type to any other integral type (excluding promotion)
  
```cpp
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int
```

2. Converting a floating point type to any other floating point type (Excluding floating point promotions):

```cpp
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting a floating point type to an integral type

```cpp
int i = 3.5; // convert double to int
```

4. Converting an integral type to any floating point type

```cpp
double d = 3; // convert int to double
```

5. Converting an integral type or a floating point type to a bool

```cpp
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

### Safe and unsafe conversions

Many numeric conversions are unsafe

**Unsafe Conversion**: One where at least 1 value of the source type cannot be converted into an equal value fothe destination type

3 general safety categories:
1. **Value preserving conversions** Conversions where the destination type can exactly represent all possible values in the source tpye
    - `int` to `long` and `short` to `double`
    - A value converted using a value-preserving conversion can always be converted back to the source type

```cpp
#include <iostream>

int main()
{
    int n = static_cast<int>(static_cast<long>(3)); // convert int 3 to long and back
    std::cout << n << '\n';                         // prints 3

    char c = static_cast<char>(static_cast<double>('c')); // convert 'c' to double and back
    std::cout << c << '\n';                               // prints 'c'

    return 0;
}
```

2. **Reinterpretive Conversions**: Unsafe numeric conversions where the converted value may be different than the source value, but no data is lost.
    - Signed/unsigned conversions fall into this category
    - Such value changes are typically undesirable, and will often cause the program to exhibit unexpected or implementation-defined behavior

```cpp
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```

3. **Lossy Conversions**: Unsafe numeric conversions where data may be lost during the conversion
    - `double` to `int`
    - `double` to `float`
    - Converting a value that has lost data back to the source type will result in a value that is different than the original value

```cpp
#include <iostream>

int main()
{
    double d { static_cast<double>(static_cast<int>(3.5)) }; // convert double 3.5 to int and back
    std::cout << d << '\n'; // prints 3

    double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // convert double 1.23456789 to float and back
    std::cout << d2 << '\n'; // prints 1.23457

    return 0;
}
```

Unsafe conversions should be avoided as much as possible. This is not always possible. Unsafe conversions are used most often when:
- We can constrain the values to be converted to just those that can be converted to equal values
  - `int` can be safely converted to `unsigned int` when we can guarantee that the `int` is non-negative
- We don't mind that some data is lost because it is not relevant
  - Converting `int` to `bool` results in loss of data, but we're typically okay with this because we're just checking if the `int` has value `0` or not

### More on numeric conversions

The specific rules for numeric conversions are complicated and numerous. Most important things to remember
- All cases, converting a value into a type whose range doesn't support that value will lead to results that are probably unexpected
- Remember that overflow is well-defined for unsigned values and produces undefined behavior for signed values
- Converting from a larger integral or floating point type to a smaller type from the same family will generally work aso long as the value fits in the range of the smaller type
- In the case of floating point values, some rounding may occur due to a loss of precision in the smaller type
- Converting from an integer to a floating point number generally works as long as the value fits within the range of the floating point type
- Converting from a floating point to an integer works as long as the value fits within the range of the intger, but any fractional values are lost

# 10.4 - Narrowing Conversions, List Initialization, and Constexpr initializers

## Notes

### Narrowing Conversions

**Narrowing Conversions**: A potentially unsafe numeric conversion where the destination type may not be able to hold all of the values of the source type.

The following are defined to be narrowing:
- Floating point type to an integral type
- Floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range of the destination type
- From an integral to a floating point type, unless the value being converted is econstexpr and whose value can be stored exactly in the destination type
- Integral type to another integral type that cannot represent all values of the original type
  - Unless the value being converted is constexpr and whose value can be stored exactly i the destination type
  - Covers both wider to narrower integral conversions, as well as integral sign conversions

Narrowing conversions will result in compiler warnings, with the exeception of signed/unsigned conversions

Narrowing conversions should be avoided as much as possible, because they are potentially unsafe, and thus a source of potential errors

### Make intentional narrowing conversions explicit

Narrowing conversions are not always avoidable
- It is a good idea to convert an implicit narrowing conversion into an explicit narrowing conversion using `static_cast`
- Helps document that the narrowing conversion is intentional
- Will suppress any compiler warnings or errors that would otherwise result

### Brace initialization disallow narrowing conversion

Narrowing conversions are disallowed when using brace initialzation and attempting to do so will produce a compiler error

```cpp
int main()
{
    int i { 3.5 }; // won't compile

    return 0;
}
```

If you actually want to do a narrowing conversion inside a brace initialization, use `static_cast` to convert the narrowing conversion into an explicit conversion

```cpp
int main()
{
    double d { 3.5 };

    // static_cast<int> converts double to int, initializes i with int result
    int i { static_cast<int>(d) };

    return 0;
}
```

### Some constexpr conversions aren't considered narrowing

When the source value of anarrowing conversion isn't known until runtime, the result of the conversion also can't be determined until runtime
- Whether the narrowing conversion preserves the value or not also can't be determined until runtime

```cpp
#include <iostream>

void print(unsigned int u) // note: unsigned
{
    std::cout << u << '\n';
}

int main()
{
    std::cout << "Enter an integral value: ";
    int n{};
    std::cin >> n; // enter 5 or -5
    print(n);      // conversion to unsigned may or may not preserve value

    return 0;
}
```

A compiler that has signed/unsigned warnings enabled will issue a warning for this case

Most of the narrowing conversions definitions have an exception clause that begins with "unless the value being converted is constexpr and..."

When the source value of a narrowing conversion is constexpr, the specific value to be converted must be known to the compiler
- The compiler can perform the conversion itself, and then check whether the value was preserved
- If not preserved, the compiler can halt compilation with an error
- If preserved, the conversion is not considered to be narrowing


```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```

Conversions from a floating point type to an integral type do not have a constexpr exclusion clause, so these are always considered narrowing conversion even when the value to be converted is constexpr and fits in the range of the destination

Conversions from a constexpr floating point type to a narrower floating point type are not considered narrowing even when there is a loss in precision

```cpp
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results
```

### List initialization with constexpr initializer

These constexpr exception clauses are incredibly useful when list initializing non-int/non-double objects
- We can use an int or double literal initialization value
- 
Allows us to avoid:
- Having to use literal suffixes in most cases
- Having to clutter our initializations with a static_cast

```cpp
int main()
{
    // We can avoid literals with suffixes
    unsigned int u { 5 }; // okay (we don't need to use `5u`)
    float f { 1.5 };      // okay (we don't need to use `1.5f`)

    // We can avoid static_casts
    constexpr int n{ 5 };
    double d { n };       // okay (we don't need a static_cast here)
    short s { 5 };        // okay (there is no suffix for short, we don't need a static_cast here)

    return 0;
}
```

Also works with copy and direct initialization

Initializing a narrower or lesser ranking floating point type with a constexpr value is allowed as long as the value is in range of the destination type

```cpp
int main()
{
    float f { 1.23456789 }; // not a narrowing conversion, even though precision lost!

    return 0;
}
```

# 10.5 - Arithmetic Conversions

## Notes

But what happens when the operands of a binary operator are of different types?

```cpp
??? y { 2 + 3.5 };
```

In C++, certain operators require that their operands be the same type, if one of these operators is invoked with operands of different types, one or both of the operands will implicitly convert to match types using a set of rules called **usual arithmetic conversions**
- The matching type produced as a result of the usual arithmetic conversion rule is the **common type** of the operand

### The operators that require operands of the same type

The following operators require their operands of the same type:
- Binary arithmetic operators: +, -, *, /, %
- Binary relational operators: <, >, <=, >=, ==, !=
- binary bitwise arithmetic operators: &, |, ^
- Conditional operator ?

### The usual arithmetic conversion rules

The compiler has a ranked list of types:
- Long double (Highest)
- double float
- long long
- long
- int (lowest)

The following rules are applied to find a matching type:

Step 1:
- If one operand is an integral type and the other a floating point type, the integral opreands is converted tot he type of the floating point operand
- Otherwise, any integral operands are numerically promoted
Step 2:
- After promotion, if one operand is signed and the other unsigned, special rules apply
- Otherwise, the operand with lower rank is converted to the type of the operand with higher rank

Special Rules
- If the rank of the unsigned operand is greater than or equal to the rank of the signed operand, the signed operand is converted to the type of the unsigned operand
- If the type of the signed operand can represent all the values of the type of the unisnged ooperand, the type of the unsigned operand is converted to the type of the signed operand
- Otherwise, both operands are converted to the corresponding unsigned type of the signed operand

### Examples

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    int i{ 2 };
    std::cout << typeid(i).name() << '\n'; // show us the name of the type for i

    double d{ 3.5 };
    std::cout << typeid(d).name() << '\n'; // show us the name of the type for d

    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}
```

The `double` operand has the highest priority, so the lower priority `int` is converted to `double`.

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```

Neither operand appears on the priority list, point operands undergo integral promotion to type `int`.

### Signed and unsigned issues

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer

    return 0;
}
```

The `int` operand is converted to an `unsigned int`. Making `5u - 10u`, because unsigned can't be negative, it wraps around to

```shell
unsigned int 4294967291
```

```cpp
#include <iostream>

int main()
{
    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
```

`-3` is converted to a very large `unsigned int`, making the expression not true to what is normally expected

### std::common_type and std::common_type_t

We'll encounter cases whee it is useful to know what the common type of two type is
- `std::common_type` and the useful type alias `std::common_type_t can be used for just this purpose
- Found in the `<type_traits>` header

`std::common_type_t<int, double>` returns the common type of `int` and `double`

# 10.6 - Explicit type conversions (casting) and static_cast

## Questions

1. What's the difference between implicit and explicit type conversions
- Implicit is when the compiler/runtime performs the type conversion on it's own. Explicit is when we tell the compiler to perofrm a type conversion with a cast.

## Notes

In the case where you are using literal operands, replacing 1 or both integer literals with double literals will causing floating point division to happen instead of integer division:

```cpp
double d = 10.0 / 4.0; // does floating point division, initializes d with value 2.5
```

What if you are using variables instead of literals?
```cpp
int x { 10 };
int y { 4 };
double d = x / y; // does integer division, initializes d with value 2.0
```

Because integer division is used here, variable `d` will end up with the value `2.0`
- How do we want the compiler to know we want to do floating point division

**Type Casting Operrators**: Used by the programmer to have the compiler perform type conversions\
**Explicit Type Conversions**: Casts are explicit requests by the programmer

### Type casting

C++ supports 5 different types of casts
- `static_cast`: Compile-time type conversions between related types, is safe
- `dynamic_cast`: Runtime type conversions on pointers or references in a polymorphic hierarchy, is safe
- `const_cast`: Adds or removes const, only safe for adding const
- `reinterpret_cast`: Reinterprets the bit-level representation of one type as if it were another type, is not safe
- C-style casts: Performs some combination of `static_cast`, `const_cast`, or `reinterpret_cast`, is not safe

**named casts**: The first 4 types of casts

`const_cast` and `reinterpret_cast` should generally be avoided because they are only useful in rare cases and can be harmful if used incorrectly

### C-Style Cast

**C-Style Cast**: Casting is done via `operator()`, with the name of the type to convert to placed inside the parentheses.
- The value to convert to placed immediately to the right of the closing parenthesis.

```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    std::cout << (double)x / y << '\n'; // C-style cast of x to double

    return 0;
}
```

Convert `x` to a `double`.

**Function-Style Cast**: An alternative form of C-style cast, which resembles a function call:
- A bit easier to tell what is being converted

```cpp
std::cout << double(x) / y << '\n'; //  // function-style cast of x to double
```

A couple reasons C-Style Cast is avoided in C++
- It can actually perform a variety of different conversions depending on how it is used
  - Include a stat cast, const cast, or a reinterpret cast
  - C-Style Cast isn't clear which cast it will actually perform
  - Opens the door for inadvertent misuse
- C-Style casts are just a type name, parenthesis, and variable or value, they are both difficult to identify and even more difficult to search
- Named casts are easy to spot and search for

### `static_cast` should be used to cast most values

**Static Cast**: Used when we want to explicitly convert a value of 1 type into a value of another type

```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a

    return 0;
}
```

```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // static cast x to a double so we get floating point division
    std::cout << static_cast<double>(x) / y << '\n'; // prints 2.5

    return 0;
}
```

`static_cast<double>(x)` returns a temporary `double` object containing the converted value `10.0`.
- This temporary is then used as the left-operand

2 important properties of `static_cast`
- Provides compile-time type checking, if we try to convert a value to a type and the compiler doesn't know how to perform that conversion, we will get a compilation error
- Less powerful than a C-Style Cast, it will prevent certain kinds of dangerous conversions

### Using `static_cast` to make narrowing conversions

Compilers will often issue warnings when apotentially unsafe (narrowing) implicit type conversion is performed

```cpp
int i { 48 };
char ch = i; // implicit narrowing conversion
```

If we used list initialization, the compiler would yield an error

To get around this, we can use a static cast to explicitly convert our integer to a `char`

```cpp
int i { 48 };

// explicit conversion from int to char, so that a char is assigned to variable ch
char ch { static_cast<char>(i) };
```

We'll explicitly tell the compiler that this conversion is intended, and we accept responsibility for the consequences

```cpp
int i { 100 };
i = i / 2.5;
```

Converting a `double` to an `int` may result in loss of data and the compiler may issue a warning

Using `static_cast` tells the compiler we intend to lose data

```cpp
int i { 100 };
i = static_cast<int>(i / 2.5);
```

### Casting vs initializing a temporary object

Say we have some variable `x` that we need to convert to an `int`. 2 conventional ways to do this:
1. `static_cast<int>(x)`, returns a temporary `int` object *direct-initialized* with `x`
2. `int {x}`, which creates a temporary `int` object `direct-list-initialized` with `x`

We should avoid `int (x)`, the C-style cast.
- This returns a temporary `int` direct-initialized with the value of `x`
- Also has the downside metnioned in the C-Style cast section

3 notable differences between the `static_cast` and the direct-list-initialized temporary
1. `int {x}` uses list initialization, which disallows narrowing conversions
    - Great when initializing a variable
    - But when using a cast, it is presumed we know what we're doing, and if we want to do a cast that might lose some data, we should be able to do that
    - narrowing conversion restriction canb e an impediment
2. `static_cast` makes it clearer that we are intending to perform a conversion
3. Direct-list-initialization of a temporary only allows single-word type names
    - Several places within C++ where only single-word type names are allowed
    - While `int {x}` is valid, `unsigned int {x}` is not

Generally prefer `static_cast` over direct-list initialization of a temporary

# 10.7 - Typedefs and type aliases

## Questions

1. Given the following function prototype, conver the `int` return value to a type alias named `PrintError`.

```cpp
int printData();
```

```cpp
using PrintError = int;
PrintError printData();
```

## Notes

### Type Aliases

**Using**: A C++ keyword that creates an alias for an existing data type.

```cpp
using Distance = double; // define Distance as an alias for type double
```

A type alias can be used anywhere a type is needed

```cpp
Distance milesToDestination{ 3.4 }; // defines a variable of type double
```

When the compiler encounters a type alias name, it will substitute in the aliased type

```cpp
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double

    Distance milesToDestination{ 3.4 }; // defines a variable of type double

    std::cout << milesToDestination << '\n'; // prints a double value

    return 0;
}
```

### Naming type aliases

There hasn't been a lot of consistency in how type aliases have been named

3 Common naming conventions
- End in a "_t". Often used by the standard library for globally scoped names
  - Most popular when defining your own type aliases
  - Fallen out of favor in modern C++ as "_t" has been reserved for globally scoped type
- End in a "_type". Used by some standard library types (`std::string`) to name nested type aliases
  - Used to name nested type aliases (e.g. `std::string::size_type`)
  - Many such nested type aliases do not use a suffix at all (e.g., `std::string::iterator), usage is inconsistent
- No Suffix
  - Modern C++, the convention is to name type aliases that you define yourself starting with a capital letter, and using no suffix

Cmmon to see this usage:

```cpp
void printDistance(Distance distance); // Distance is some defined type
```

### Type aliases are not distinct types

An alias does not actually define a new, distinct type. It just instroduces a new identifier for an existing type
- Completely interchangeable with the aliased type

```cpp
int main()
{
    using Miles = long; // define Miles as an alias for type long
    using Speed = long; // define Speed as an alias for type long

    Miles distance { 5 }; // distance is actually just a long
    Speed mhz  { 3200 };  // mhz is actually just a long

    // The following is syntactically valid (but semantically meaningless)
    distance = mhz;

    return 0;
}
```

Because the compiler does not prevent these kinds of semantic errors for type aliases,we say that aliases are not **type safe**.

### The scope of a type alias

Scope is a property of an identifier, type alias identifiers follow the same scoping rules as variable identifiers
- Type alias defined inside a block has block scope and is usable only within the block
- Type alias defined in the global namespace has global scope and is usable to the end of the file

They can be defined in a header file and #included into any code files that needs to ues the definition

```cpp
// mytypes.h

#ifndef MYTYPES_H
#define MYTYPES_H

    using Miles = long;
    using Speed = long;

#endif
```

### Typedefs

**Typedef**: Short for type definition, an older way of creating an alias for a type
- Uses the `typedef` keyword

```cpp
// The following aliases are identical
typedef long Miles;
using Miles = long;
```

It's easy to forget whether the name of the typedef or the name of the type to alias comes first

```cpp
typedef Distance double; // incorrect (typedef name first)
typedef double Distance; // correct (aliased type name first)
```

The syntax for typedefs can get ugly with more complex types

```cpp
typedef int (*FcnType)(double, char); // FcnType hard to find
using FcnType = int(*)(double, char); // FcnType easier to find
```

Prefer type aliases over typedefs

### Using type aliases for platform independent coding

1 primary use is to hide platform specific details
- Some platofrms, `int` is 2 bytes, others 4 bytes

It is fairly common for cross-platform programs to use type aliases to define aliases that include the type's size in bits

```cpp
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
```

This is also why when you print an 8-bit fixed width integer using `std::cout`, you're likely to get a character value, For example

```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int8_t x{ 97 }; // int8_t is usually a typedef for signed char
    std::cout << x << '\n';

    return 0;
}
```

```shell
a
```

### Using type aliases to make complex types easier to read

In advanced C++, types can be complicated and lengthy to manually enter on your keyboard

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
{
    // some code here
    return false;
}

int main()
{
     std::vector<std::pair<std::string, int>> pairlist;

     return 0;
}
```

It is easier to use a type alias

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}

int main()
{
     VectPairSI pairlist; // instantiate a VectPairSI variable

     return 0;
}
```

### Using type aliases to document the meaning of a value

Type aliases can also help with code documentation and comprehension

```cpp
int gradeTest();
```

What does the integer mean? A letter grade? The number of questions missed?

```cpp
using TestScore = int;
TestScore gradeTest();
```

Makes it a little more obvious that the function is returning a type that represents a test score\
Creating a type alias just to document the return type of asingle function isn't worth
- But if you have multiple functions passing or returning such a type, alias might be worthwhile

### Using type aliases for easier code maintenance

Type aliases allow you t change the underlying type of an object withou having to update lots of hardcoded types.

If you were using a `short` to hold student's ID number, then later decided to use a `long` isntead, you'd have to comb through code to replace `short` with `long`

If you used an alias `using StudentId = short;` to `using StudentId = long` it would be simpler
- Caution is necesary when a type is changed, as the behavior of the program may also change

### Downsides and conclusions

They introduce another identifier into your code that needs to be understood.
- If this isn't offset by some benefit to readability or comprehension, then the type alias is doing more harm than good

Type aliases should be used primarily in cases where there is a clear benefit to code readability or code maintenance
- Most useful when they can be used in many places throughout your code, rather than in fewer places

# 10.8 - Type deduction for objects using the auto keyword

## Notes

There's a subtle redundancy in simple variable definition

```cpp
double d{ 5.0 };
```

We are required to provide an explicit type for all objects. That's why we specified variable `d` is of type `double`

The literal `5.0` also has type double.

In cases where we want a variable and its initializer to have the same type, we've effectively providing the same type information twice

### Type deduction for initialized variables

**Type Deduction**: (**Type Inference**) Feature that allows the compiler to deduce the type of an object from the object's initializer

Type deduction can be invoked by using the `auto` keyword in place of the variable's type

```cpp
int main()
{
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto i { 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
    auto x { i }; // i is an int, so x will be deduced as an int

    return 0;
}
```

Because function calls are valid expressions, we can even use type deduction when our initializer is a non-void function call

```cpp
int add(int x, int y)
{
    return x + y;
}

int main()
{
    auto sum { add(5, 6) }; // add() returns an int, so sum's type will be deduced as an int

    return 0;
}
```

Literal suffixes can be used in combination with type deduction to specify a particular type

```cpp
int main()
{
    auto a { 1.23f }; // f suffix causes a to be deduced to float
    auto b { 5u };    // u suffix causes b to be deduced to unsigned int

    return 0;
}
```

Variables using type deduciton may also use other specifiers/qualifiers, such as `const` or `constexpr`

```cpp
int main()
{
    int a { 5 };            // a is an int

    const auto b { 5 };     // b is a const int
    constexpr auto c { 5 }; // c is a constexpr int

    return 0;
}
```

### Type deduction must have something to deduce from

Will not work for objects that either do not have initializers or have empty initializers.
- Also won't work when the initializer has type `void`

The following is not valid:

```cpp
#include <iostream>

void foo()
{
}

int main()
{
    auto a;           // The compiler is unable to deduce the type of a
    auto b { };       // The compiler is unable to deduce the type of b
    auto c { foo() }; // Invalid: c can't have type incomplete type void

    return 0;
}
```

### Type deduction drops `const` from the deduced type

In most cases, type deduction will drop the `const` from deduced types

```cpp
int main()
{
    const int a { 5 }; // a has type const int
    auto b { a };      // b has type int (const dropped)

    return 0;
}
```

If you want a deduced type to be const, you must supply the `const` yourself as part of the definiton

```cpp
int main()
{
    const int a { 5 };  // a has type const int
    const auto b { a }; // b has type const int (const dropped but reapplied)


    return 0;
}
```

### Type deduction for string literals

String literals in C++ have a string type. The following won't work as expected:

```cpp
auto s { "Hello, world" }; // s will be type const char*, not std::string
```

If you want the type deducd from a string literal to be `std::string` or `std::string_view`, you'll need to use the `s` or `sv` suffix

```cpp
#include <string>
#include <string_view>

int main()
{
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    return 0;
}
```

### Type deduction and constexpr

Because `constexpr` is not part of the type system, it cannot be deducd as part of type deduction.
- `constexpr` variable is implicitly const, and this const will be dropped during type deduction

```cpp
int main()
{
    constexpr double a { 3.4 };  // a has type const double (constexpr not part of type, const is implicit)

    auto b { a };                // b has type double (const dropped)
    const auto c { a };          // c has type const double (const dropped but reapplied)
    constexpr auto d { a };      // d has type const double (const dropped but implicitly reapplied by constexpr)

    return 0;
}
```

### Type deduction benefits and downsides

Benefits:

If 2 or more variables are defined on sequential lines, the names of the variables will be lined up, helping to increase readability

```cpp
// harder to read
int a { 5 };
double b { 6.7 };

// easier to read
auto c { 5 };
auto d { 6.7 };
```

Type deduction only works on variables that have initializers, so if you are in the habitof using type deduction, it can help avoid unintentionally uninitialized variables

```cpp
int x; // oops, we forgot to initialize x, but the compiler may not complain
auto y; // the compiler will error out because it can't deduce a type for y
```

You are guaranteed that there will be no unintended performance-impacting conversions

```cpp
std::string_view getString();   // some function that returns a std::string_view

std::string s1 { getString() }; // bad: expensive conversion from std::string_view to std::string (assuming you didn't want this)
auto s2 { getString() };        // good: no conversion required
```

Downsides:

Type deduction obscures an object's type information in the code
- A good IDE should be able to show youthe deduced type
- It's still a bit easier to make type-based mistakes when using type deduciton

```cpp
auto y { 5 }; // oops, we wanted a double here but we accidentally provided an int literal
```

Similar cases occur when a variable is `unsigned`
- Since we don't want to mix signed and unsigned values, explicitly knowing that a variable has an unsigned type is generally something that shouldn't be obscured

If the type of an initializer changes, the type of the variable using type deduction will also change, perhaps unexpectedly

```cpp
auto sum { add(5, 6) + gravity };
```

If the return type of `add` changes from int to double, or `gravity` changes from int to double `sum` will also change type from int to double

Best Practice: Use type deduction for your variables when the type of the object doesn't matter
- Favor an explicit type when you require a specific type that differs from the type of the initializer, or when your object is used in a context where making the type obvious is useful

# 10.9 - Type deduction for functions

## Notes

### Return type deduction with `auto`

Since the compiler already has to deduce the return type from the return statement, in C++14, the `auto` keyword was extended to do function return type deduction

```cpp
auto add(int x, int y)
{
    return x + y;
}
```

Because the return statement is returning an `int` value, the compiler will deduce that the return type of this function is `int`

When using an `auto` return type, all return statements within the function must return values of the same type, otherwise an error will result

```cpp
auto someFcn(bool b)
{
    if (b)
        return 5; // return type int
    else
        return 6.7; // return type double
}
```

Two return statements return values of different types, so the compiler will give an error

### Benfits of return type deduction

Having the compiler deduce the funtion's return type negates the risk of a mismatched return type

Can be particularly useful when a function's return type is fragile
- Being explicit about the return type means having to update all relevant return types when an impacting change is made to the implementations

In other cases, the return type of a function may either be long and complex, or ot be that abvious
- `auto` can be used to simplify

```cpp
// let compiler determine the return type of unsigned short + char
auto add(unsigned short x, char y)
{
    return x + y;
}
```

### Downsides of return type deduction

2 major downsides to return type deduction:

Functions that use an `auto` return type must be fully defined before they can be used
- A forward declaration is not sufficient

```cpp
#include <iostream>

auto foo();

int main()
{
    std::cout << foo() << '\n'; // the compiler has only seen a forward declaration at this point

    return 0;
}

auto foo()
{
    return 5;
}
```

WWhen using typededuciton with objects, the initializer is always present as part of the same statement, so it's usually not overly burdensome to determine what type will be deduced,
- With type deduciton for functions that is not the case
- Function's prototype gives no indiciation as to what type the function actually returns
- Generally we prefer to be explicit about types that are part of an interface

There isn't much consensus on best practices for function return type deduction
- Recommend generally avoiding return type deduction for functions

### Trailing return type syntax

**Trailing Return Syntax**: The return type is specified after the rest of the funciton prototype

Consider the function

```cpp
int add(int x, int y)
{
  return (x + y);
}
```

This could be the equivalent as

```cpp
auto add(int x, int y) -> int
{
  return (x + y);
}
```

`auto` does not perform type deduction - it is just part of the syntax to use a trailing return type

Why would you want to use this?
1. Function with complex return types,a trailing return tyype can make the funciton easier to read

```cpp
#include <type_traits> // for std::common_type

std::common_type_t<int, double> compare(int, double);         // harder to read (where is the name of the function in this mess?)
auto compare(int, double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)
```

2. The trailing return type syntax can be used to align the names of your functions, which makes consecutive function declarations easier to read

```cpp
auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
auto printSomething() -> void;
auto generateSubstring(const std::string &s, int start, int len) -> std::string;
```

3. If we have a function whose return type must be deduced based on the type of the parameters, a normal return type will not suffice, because the compiler has not yet seen the parameters at that point

```cpp
#include <type_traits>
// note: decltype(x) evaluates to the type of x

std::common_type_t<decltype(x), decltype(y)> add(int x, double y);         // Compile error: compiler hasn't seen definitions of x and y yet
auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; // ok
```

4. Trailing return syntax is also required for some advanced features of C++ such as lambdas

Recommend the continued use of the traditional function return syntax except in situations that require the trailing return syntax

### Type deduction can't be used for function parameters

```cpp
#include <iostream>

void addAndPrint(auto x, auto y)
{
    std::cout << x + y << '\n';
}

int main()
{
    addAndPrint(2, 3); // case 1: call addAndPrint with int parameters
    addAndPrint(4.5, 6.7); // case 2: call addAndPrint with double parameters

    return 0;
}
```

Type deduction doesn't work for function parameters, and prior to C++20, the above program won't compile

In C++20, the `auto` keyword was extended so that the above program will compile and function correctly
- `auto` is not invoking type deduction in this case
- It is triggering a different feature called `function templates` that was designed to actually handle such cases

# 10.x - Chapter 10 summary and quiz

## Review

**Type Conversion**: Process of converting a value from one data type to another data type
**Implicit Type Conversion**: Performed whenever 1 data type is expected, but a different data type is supplied
**Standard Conversions**: Built-in conversions between its fundamental types
**Numeric Promotion**: Conversion of certain smaller numeric types to certain larger numeric types so that the CPU can operate on data that matches the natural data size for the processor
**Value Preserving**: No loss of value or precision
**Numeric Conversion**: A type conversion between fundamental types that isn't a numeric promotion
**Narrowing Conversion**: Numeric conversion that may result in the loss of value or precision
**Usual Arithmetic Conversions**: If operands of different types are provided, one or both of the operands will be implicitly converted to match types using a set of rules
**Explicit Type Conversions**: Performed when the programmer explicitly requests conversion via a cast
**Cast**: Represents a request by the programmer to do an explicit type conversion
**Typedef and Type Aliases**: Allow the programmer to create an alias for a data type.
**Auto**: Keyword with a number of uses
**Type Deduction**: Deduce a variable's type rom its initiailizer

## Quiz

1. What type of conversion happens in each of the following cases? Valid answers are: No conversion needed, numeric promotion, numeric conversion, won’t compile due to narrowing conversion. Assume int and long are both 4 bytes.

```cpp
int main()
{
    int a { 5 }; // 1a List Initialization
    int b { 'a' }; // 1b Numeric Promotion
    int c { 5.4 }; // 1c Narrowing Conversion
    int d { true }; // 1d Promotion
    int e { static_cast<int>(5.4) }; // 1e Conversion

    double f { 5.0f }; // 1f Promotion
    double g { 5 }; // 1g Conversion

    // Extra credit section
    long h { 5 }; // 1h Conversion

    float i { f }; // 1i (uses previously defined variable f) narrowing
    float j { 5.0 }; // 1j conversion

}
```

2. 
- Update the following program to use type aliases for degrees and radians values:

```cpp
#include <iostream>

namespace constants
{
    constexpr double pi { 3.14159 };
}

double convertToRadians(double degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    double degrees{};
    std::cin >> degrees;

    double radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}
```

```cpp
#include <iostream>

using Radians = double;
using Degrees = double;

namespace constants
{
    constexpr double pi { 3.14159 };
}

Radians convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radians radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}
```

- Given the definitions for degrees and radians in the previous quiz solution, explain why the following statement will or won’t compile:

```cpp
radians = degrees;
```

This will compile as underlying type of both radians and degrees is `double`.