# 13.1 - Introduction to program-defineed (user-defined) types

## Notes

### What are user-defined / program-defined types?

**User-Defined Types**: (**Program defined Types**) Allowing the creation of entirely new custom types that we can use in our programs

C++ has 2 different categories of compound types that can be used to create program-defined types:
- Enumerated types
- Class types

### Defining Program-defined types

**Type Definition**: The definition for  aprogram-defined type

```cpp
// Define a program-defined type named Fraction so the compiler understands what a Fraction is
// (we'll explain what a struct is and how to use them later in this chapter)
// This only defines what a Fraction type looks like, it doesn't create one
struct Fraction
{
	int numerator {};
	int denominator {};
};

// Now we can make use of our Fraction type
int main()
{
	Fraction f { 3, 4 }; // this actually instantiates a Fraction object named f

	return 0;
}
```

This doesn't allocate any memory, it just tells the compiler what a `Fraction` looks like, so we can allocate object of a `Fraction` type later


Program-defined type definitions must end in a semicolon

### Naming program-defined types

Program-defined types are named starting with a capital letter and don't use a suffix
- `Fraction`, not `fraction`, `fraction_t`, or `Fraction_t`

### Using program-defined types throughout a multi-file program

Every code file that uses a program-defined type needs to see the full type definition before it is used
- A forward declaration is not sufficient
- Required so that the compiler knows how much memory to allocate for objects of that type

Program-defined types are typically defined in the header files, and then #included into any code file that requires that type definition

```cpp
// Fraction.h
#ifndef FRACTION_H
#define FRACTION_H

// Define a new type named Fraction
// This only defines what a Fraction looks like, it doesn't create one
// Note that this is a full definition, not a forward declaration
struct Fraction
{
	int numerator {};
	int denominator {};
};

#endif
```

```cpp
// Fraction.cpp
#include "Fraction.h" // include our Fraction definition in this code file

// Now we can make use of our Fraction type
int main()
{
	Fraction f{ 3, 4 }; // this actually creates a Fraction object named f

	return 0;
}
```

### Type definitions are partially exempt from the one-definition rule

The one-defintion rule requires that each function and global variable only have one definition per program

Using forward declaration in a similar manner doesn't work for types, because the compiler typically needs to see the full definition to use a given type
- Must be able to propagate the full type definition to each code file that needs it

Types are partially exempt from the one-definition rule: a given type is allowed to be defined in multiple code files

You can still only have 1 type definition per code file
- ALl of the type definitions for a given type must be identical otherwise, undefined behavior will result

# 13.2 - Unscoped enumeration

## Questions

1. Define an unscoped enumerated type named MonsterType to choose between the following monster races: orc, goblin, troll, ogre, and skeleton.

```cpp

enum MonsterType
{
  orc,
  gobline,
  troll,
  ogre,
  skeleton,
};
```

2. Put the MonsterType enumeration inside a namespace. Then, create a main() function and instantiate a troll. The program should compile.

```cpp
namespace Monster
{
  enum MonsterType
  {
    orc,
    gobline,
    troll,
    ogre,
    skeleton,
  };
}

int main()
{
  [[maybe_unused]] Monster::MonsterType troll {Monster::troll};
}
```

## Notes

### Enumerations

**Enumeration**: A compound data type whose values are restricted to a set of named symbolic constants

C++ supports 2 kinds of enumerations, unscoped enumeration and scoped enumeration

### Unscoped enumeations

Unscoped enumerations are defined via the `enum` keyword

```cpp
// Define a new unscoped enumeration named Color
enum Color
{
    // Here are the enumerators
    // These symbolic constants define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    red,
    green,
    blue, // trailing comma optional but recommended
}; // the enum definition must end with a semicolon

int main()
{
    // Define a few variables of enumerated type Color
    Color apple { red };   // my apple is red
    Color shirt { green }; // my shirt is green
    Color cup { blue };    // my cup is blue

    Color socks { white }; // error: white is not an enumerator of Color
    Color hat { 2 };       // error: 2 is not an enumerator of Color

    return 0;
}
```

Used the `enum` keyword to tell the compiler that we are defining an unscoped enumeration, with the name `Color`

Defined enumerators for the `Color` type: `red`, `green`, `blue`.
- These enumerators define the specific values that type `Color` is restricted to
- Must be separated by a comma'

Most common to define 1 enumeator per line, but in simple cases, they may all be defined on a single line

Type definition for `Color` ends with a semicolon

We instantiated 3 variables of type `Color`
- Memory is allocated for each of these objects
- Enumerators are implicitly constpexr

### Naming enumerations and enumerators

The names of enumerated types start with a capital letter

Enumerators must be given names, there is no common naming convention for enumerator names
- Modern C++ guidelines typically recommend avoiding all caps naming convetion, as all caps is typically used for preprocessor macros and may conflict
- Also avoid the convention starting with a capital letter, as names beginning with a capital letter are typically reserved for program-defined types

### Enumerated types are distinct types

**Distinct Type**: The compiler can distinguish it from other types

Enumerators defined as part of one enumerated type can't be used with objects of another enumerated type

```cpp
enum Pet
{
    cat,
    dog,
    pig,
    whale,
};

enum Color
{
    black,
    red,
    blue,
};

int main()
{
    Pet myPet { black }; // compile error: black is not an enumerator of Pet
    Color shirt { pig }; // compile error: pig is not an enumerator of Color

    return 0;
}
```

### Putting enumerations to use

Enumerated types are best used when you have a smallish set of related constants, and objects only need to hold 1 of those values at a time

```cpp
enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum CardinalDirections
{
    north,
    east,
    south,
    west,
};

enum CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
};
```

Sometimes funcitons will return a status code to the caller to indicate whether the funciton executed successfully or encountered an error

```cpp
enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}
```

The caller can test the function's return vale against the appropriate enumerator, which is easier to understand than testing the return result for a specific integer value

```cpp
if (readFileContents() == readResultSuccess)
{
    // do something
}
else
{
    // print error message
}
```

Enumerated types can also make for useful function parameters when the user needs to make a choice between 2+ options

```cpp
enum SortOrder
{
    alphabetical,
    alphabeticalReverse,
    numerical,
};

void sortData(SortOrder order)
{
    switch (order)
    {
        case alphabetical:
            // sort data in forwards alphabetical order
            break;
        case alphabeticalReverse:
            // sort data in backwards alphabetical order
            break;
        case numerical:
            // sort data numerically
            break;
    }
}
```

Many use enumerations to define Booleans

### The scope of unscoped enumerations

Unscoped enumerations are numed such because they put their enumerator names into the same scope as the enumeration definition itself

```cpp
enum Color // this enum is defined in the global namespace
{
    red, // so red is put into the global namespace
    green,
    blue,
};

int main()
{
    Color apple { red }; // my apple is red

    return 0;
}
```

`Color` is defined in global scope
- All enumeration names also go into global scope
- Pollutes the global scope and significantly raises the chance of naming collisions
- Enumartor name can't be used in multiple enumerations within the same scope

```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

enum Feeling
{
    happy,
    tired,
    blue, // error: naming collision with the above blue
};

int main()
{
    Color apple { red }; // my apple is red
    Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

    return 0;
}
```

Unscoped enumerations also provide a named scope region for their enumerators
- We can access the enumerators of an unscoped enumeration as follows:

```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

int main()
{
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color

    return 0;
}
```

### Avoiding enumartor naming collisions

One option is to prefix each enumerator with the name of the enumeration itself

```cpp
enum Color
{
    color_red,
    color_blue,
    color_green,
};

enum Feeling
{
    feeling_happy,
    feeling_tired,
    feeling_blue, // no longer has a naming collision with color_blue
};

int main()
{
    Color paint { color_blue };
    Feeling me { feeling_blue };

    return 0;
}
```

Still pollutes the namespace but reduces the chance for naming collisio by making the names longer and unique

Better option is to put the enumerated types inside a namespace

```cpp
namespace Color
{
    // The names Color, red, blue, and green are defined inside namespace Color
    enum Color
    {
        red,
        green,
        blue,
    };
}

namespace Feeling
{
    enum Feeling
    {
        happy,
        tired,
        blue, // Feeling::blue doesn't collide with Color::blue
    };
}

int main()
{
    Color::Color paint{ Color::blue };
    Feeling::Feeling me{ Feeling::blue };

    return 0;
}
```

A related option is to use a scoped enumeration

### Comparing against enumerators

Can use the equality operators (`operator==` and `operator!=`) to test whether an enumerator has the value of a particular enumerator or not

```cpp
#include <iostream>

enum Color
{
    red,
    green,
    blue,
};

int main()
{
    Color shirt{ blue };

    if (shirt == blue) // if the shirt is blue
        std::cout << "Your shirt is blue!";
    else
        std::cout << "Your shirt is not blue!";

    return 0;
}
```

We use an if statement to test whether `shirt` is equal to the enumerator `blue`

# 13.3 - Unscoped Enumerator Integral Conversion

## Questions

1. True or false. Enumerators can be:
    - Given an integer value: True
    - Given no explicit value: True
    - Given a floating point value: False
    - Given a negative value: True
    - Given a non-unique value: True
    - Given the value of prior enumerator: True
    - Given a non-constexpr value: False

## Notes

Enumerators are symbolic constants
- These enumerators have values that are of an integeral type

When we define an enumeration, each enumerator is automatically associated with an integer value based on its position in theenumerator list
- By default, the first enumerator is given the integral value `0`
- Each subsequent enumerator has a value one greater than the previous enumerator

```cpp
enum Color
{
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt actually stores integral value 2

    return 0;
}
```

It is possible to explicitly define the value of enumerators. 
- These inegral values can be positive or negative
- Can share the same values as other enumerators
- Any non-defined enumerators are given a value of 1 greater than the previous enumerator

```cpp
enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
```

Because `horse` and `giraffe` have been given the same value, they are non-distinct

Best practice: Avoid assiging explicit values to your enumerators unless you have a compelling reason to do so

### Value-initializing an enumeration

If an enumeration is zero-initialized (which happens when we use value-initializaation), the enumeration will be given value `0`, even if there is no corresponding enumerator with that value

```cpp
#include <iostream>

enum Animal
{
    cat = -3,    // -3
    dog,         // -2
    pig,         // -1
    // note: no enumerator with value 0 in this list
    horse = 5,   // 5
    giraffe = 5, // 5
    chicken,     // 6
};

int main()
{
    Animal a {}; // value-initialization zero-initializes a to value 0
    std::cout << a; // prints 0

    return 0;
}
```

2 Semantic consequences
- If there is an enumerator with value 0, value-initialization defaults the enumeration to the meaning of that enumerator
- If there is no enumerator with value 0, value initialization makes it easy to create a semantically invalid enumeration

Best Practice
- Make the enumerator representing 0 the one that is the best default meaning for your enumeration
- If no good default meaning exists, consider adding an "invalid" or "unknown" enumerator that has value 0, so that state is explicitly documented and can be explicitly handled where appropriate

### Unscoped enumerations will implicitly convert to integral values

An unscoped enumeration will implicitly convert to an integral value
- Enumerators are compile time constants, this is a constexpr conversion

```cpp
#include <iostream>

enum Color
{
    black, // assigned 0
    red, // assigned 1
    blue, // assigned 2
    green, // assigned 3
    white, // assigned 4
    cyan, // assigned 5
    yellow, // assigned 6
    magenta, // assigned 7
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

    return 0;
}
```

Enumerated types hold integral values, so you might expect this to print

```shell
Your shirt is 2
```

The compiler will first try to find a function or operator that matches the enumerated type.
- When the compiler tries to compile `std::cout << shirt`, the compiler will look to see if `operator<<` knows how to print an object of type `Color`
- If the compiler can't find a match, it will then check if `operator<<` knows how to print an object of the integral type that the unscoped enumeration converts to

### Enumeration size and underlying type (base)

Enumerators have values that are of an integral type\
**Underlying Type**: The specific integral type used to represent the value of enumerators

Unscoped Enumertions, the C++ standard does not specify which specific integral type should be used as the underlying type
- Most compilers will use `int`, unless a larger type is required

Possible to explicitly specify an underlying type for an enumeration

```cpp
#include <cstdint>  // for std::int8_t
#include <iostream>

// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
    black,
    red,
    blue,
};

int main()
{
    Color c{ black };
    std::cout << sizeof(c) << '\n'; // prints 1 (byte)

    return 0;
}
Best pract
```

Best Practice: Specify the base type of an enumeration only when necessary

### Integer to unscoped enumerator conversion

The compiler will not implicitly convert an ineger to an unscoped enumeration
- The following will produce a compiler error

```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
    pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

    return 0;
}
```

2 Ways around this
1. You can explicitly convert an integer to an unscoped enumerator using `static_cast`
- Also safe to static_cast any integral value that is in range of the target enumeration's underlying type, even if there are no enumerators representing that value
- Static casting a value outside the range of the underlying type will result in undefined behavior

```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
    pet = static_cast<Pet>(3);       // our pig evolved into a whale!

    return 0;
}
```

2. As of C++17, if an unscoped enumeration has an explicitly specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value

```cpp
enum Pet: int // we've specified a base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet1 { 2 }; // ok: can brace initialize unscoped enumeration with specified base with integer (C++17)
    Pet pet2 (2);   // compile error: cannot direct initialize with integer
    Pet pet3 = 2;   // compile error: cannot copy initialize with integer

    pet1 = 3;       // compile error: cannot assign with integer

    return 0;
}
```

# 13.4 - Converting an enumeration to and from a string

## Notes

Because `operator<<` doesn't know how to print a `Color`, the compiler will implicitly convert `Color` into an integral value and print that instead

### Getting the name of an enumerator

Typical way is to write a function that allows us to pass in an enumerator and returns the enumerator's name as a string
- Requires some way to determine which string should be returned for a given enumerator

Can use a switch statement to switch on integral values or an enumerated value

```cpp
#include <iostream>
#include <string_view>

enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    constexpr Color shirt{ blue };

    std::cout << "Your shirt is " << getColorName(shirt) << '\n';

    return 0;
}
```

Another way to do it is mapping enumerators to strings with arrays

### Unscoped enumerator input

For an input case, we define a `Pet` enumeration. The language doesn't know how to input a `Pet` using `std::cin`

```cpp
#include <iostream>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

int main()
{
    Pet pet { pig };
    std::cin >> pet; // compile error: std::cin doesn't know how to input a Pet

    return 0;
}
```

One simple way to work around this is to read in an integer, and use `static_cast` to convert the integer to an enumerator

```cpp
#include <iostream>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

int main()
{
    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    if (input < 0 || input > 3)
        std::cout << "You entered an invalid pet\n";
    else
    {
        Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet
        std::cout << "You entered: " << getPetName(pet) << '\n';
    }

    return 0;
}
```

Should only `static_cast<Pet>(input)` once we know `input` is in range of the enumerator

### Getting an enumeration from a string

Converting a string to an enumeraton requires solving a couple of challenges

```cpp
#include <iostream>
#include <optional> // for std::optional
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    // We can only switch on an integral value (or enum), not a string
    // so we have to use if-statements here
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    std::string s{};
    std::cin >> s;

    std::optional<Pet> pet { getPetFromString(s) };

    if (!pet)
        std::cout << "You entered an invalid pet\n";
    else
        std::cout << "You entered: " << getPetName(*pet) << '\n';

    return 0;
}
```

It would be better if we could just `std::cin >> pet`, but it is possible

# 13.5 - Introduction to overloading the I/O Operators

## Notes

### Introduction to operator overloading

**Operator Overloading**: Lets us define overloads of existing operators, so that we can make those operators work with our program-defined data types

- Define a function using the name of the operator as the function's name
- Add a parameter of the appropriate type for each operand (in left-to-right oder)
  - One of these parameters must be a user-defined type, otherwise the compiler will error
- Set the return type to whatever type makes sense
- Use a return statement to retrun the result of the operations

When the compiler encounters the use of an operator in an expression and one or more of the operands is a user-defined type, the compiler will check to see if there is an overloaded operator function that it can use to resolve that call

### Overloading `operator<<` to print an enumerator

When the expression is evaluated, the compiler will look for an overloaded `operator<<` function that can handle arguments of type `std::ostream` and `int`
- It will find such a function and call it
- `std::cout` is used to output `x` to the console
- `Operator<<` function returns its left-operand, so that subsequence calls to `operator<<` can be chained

```cpp
#include <iostream>
#include <string_view>

enum Color
{
	black,
	red,
	blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream& operator<<(std::ostream& out, Color color)
{
    out << getColorName(color); // print our color's name to whatever output stream out
    return out;                 // operator<< conventionally returns its left operand

    // The above can be condensed to the following single line:
    // return out << getColorName(color)
}

int main()
{
	Color shirt{ blue };
	std::cout << "Your shirt is " << shirt << '\n'; // it works!

	return 0;
}
```

```shell
Your shirt is blue
```

### Overloading `operator>>` to input an enumerator

We can also teach `operator>>` how to input an enumeration

```cpp
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

// pet is an in/out parameter
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };
    if (match) // if we found a match
    {
        pet = *match; // dereference std::optional to get matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // pet = {};

    return in;
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

    return 0;
}
```

# 13.6 - Scoped enumerations (enum Classes)

## Questions

1. Define an enum class named Animal that contains the following animals: pig, chicken, goat, cat, dog, duck. Write a function named getAnimalName() that takes an Animal parameter and uses a switch statement to return the name for that animal as a std::string_view (or std::string if you’re using C++14). Write another function named printNumberOfLegs() that uses a switch statement to print the number of legs each animal walks on. Make sure both functions have a default case that prints an error message. Call printNumberOfLegs() from main() with a cat and a chicken. Your output should look like this:

```shell
A cat has 4 legs.
A chicken has 2 legs.
```

```cpp
#include <iostream>

enum class Animal
{
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck,
};

std::string_view getAnimalName(Animal animal)
{
    switch (animal)
    {
        case Animal::pig: return "pig";
        case Animal::chicken: return "chicken";
        case Animal::goat: return "goat";
        case Animal::cat: return "cat";
        case Animal::dog: return "dog";
        case Animal::duck: return "duck";
        default: return "???";
    }
}

int printNumberOfLegs(Animal animal)
{
    switch (animal)
    {
        case Animal::pig: return 4;
        case Animal::chicken: return 2;
        case Animal::goat: return 4;
        case Animal::cat: return 4;
        case Animal::dog: return 4;
        case Animal::duck: return 2;
        default: return -1;
    }
}


int main()
{
    Animal cat {Animal::cat};
    Animal chicken {Animal::chicken};

    std::cout << "A " << getAnimalName(cat) << " has " << printNumberOfLegs(cat) << " legs.\n";
    std::cout << "A " << getAnimalName(chicken) << " has " << printNumberOfLegs(chicken) << " legs.\n";
    return 0;
}
```

## Notes

Although unscoped enumerations are distinct types in C++, they are not type safe, and will allow you to do things that don't make sense

```cpp

int main()
{
    enum Color
    {
        red,
        blue,
    };

    enum Fruit
    {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    if (color == fruit) // The compiler will compare color and fruit as integers
        std::cout << "color and fruit are equal\n"; // and find they are equal!
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```

Because of such challenes, the C++ designers determined that a cleaner solution for enumerations would be of use

### Scoped Enumerations

**Scoped Enumerations**: (**Enum Class**), Work similarly to unscoped eumerations but have 2 primary differences
- They won't implicitly convert to integers
- Enumerators are only placed into the scope region of the enumeration
  - Not into the scope region where the enumeration is defined

Use the keyword `enum class`, the rest of the scoped enumeration definition is the same as an unscoped enumeration definition

```cpp
#include <iostream>
int main()
{
    enum class Color // "enum class" defines this as a scoped enumeration rather than an unscoped enumeration
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    enum class Fruit
    {
        banana, // banana is considered part of Fruit's scope region
        apple,
    };

    Color color { Color::red }; // note: red is not directly accessible, we have to use Color::red
    Fruit fruit { Fruit::banana }; // note: banana is not directly accessible, we have to use Fruit::banana

    if (color == fruit) // compile error: the compiler doesn't know how to compare different types Color and Fruit
        std::cout << "color and fruit are equal\n";
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```

### Scoped enumerations defined their own scope regions

Scoped enumerations placed their enumerators only in the scope region of the enumeration
- Scoped enumerations act like a namespace for their enumerators
- Helps reduce global namespace pollution and the potential for name conflicts when scoped enumerations are used in the global scope

```cpp
#include <iostream>

int main()
{
    enum class Color // "enum class" defines this as a scoped enum rather than an unscoped enum
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    std::cout << red << '\n';        // compile error: red not defined in this scope region
    std::cout << Color::red << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)

    Color color { Color::blue }; // okay

    return 0;
}
```

There is no need to put scoped enumerations inside another scope region, unless there's some other compelling reason do so

### Scoped enumerations don't implicitly convert to integers

Scoped enumerators won't implicitly convert to integers
- Most cases, this is a good thing because it rarely makes sense to do so
- Helps prevent semantic erros

You can still compare enumerators from within the same scoped enumeration

```cpp
#include <iostream>
int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color shirt { Color::red };

    if (shirt == Color::red) // this Color to Color comparison is okay
        std::cout << "The shirt is red!\n";
    else if (shirt == Color::blue)
        std::cout << "The shirt is blue!\n";

    return 0;
}
```

There are occasionally cases where it is useful to be able to trea a scoped enumerator as an integral value
- You can explicitly convert a scoped enumerator to an integer by using `static_cast`
- In C++23, a better hoice is `std::to_underlying()` defined in `<utilitiy>`
  - Converts an enumerator to a value of the underlying type of the enumeration

```cpp
#include <iostream>
#include <utility> // for std::to_underlying() (C++23)

int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color color { Color::blue };

    std::cout << color << '\n'; // won't work, because there's no implicit conversion to int
    std::cout << static_cast<int>(color) << '\n';   // explicit conversion to int, will print 1
    std::cout << std::to_underlying(color) << '\n'; // convert to underlying type, will print 1 (C++23)

    return 0;
}
```

You can also `static_cast` an integer to a scope enumerator, which can be useful when doing input from users

```cpp
#include <iostream>

int main()
{
    enum class Pet
    {
        cat, // assigned 0
        dog, // assigned 1
        pig, // assigned 2
        whale, // assigned 3
    };

    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet

    return 0;
}
```

As of C++17, you can list initialize a scoped enumeration using an integral value without the `static_cast`

```cpp
// using enum class Pet from prior example
Pet pet { 1 }; // okay
```

Best Practice: Favor scope enumeration over unscoped enumerations unless there's a compellig reason

### Easing the conversion of scoped

If you find yourself in the situation where it would be useful to make conversion of scoped enumerators to integers easily, a useful hack is to overload the unary `operator+` to perform this conversion

```cpp
#include <iostream>
#include <type_traits> // for std::underlying_type_t

enum class Animals
{
    chicken, // 0
    dog, // 1
    cat, // 2
    elephant, // 3
    duck, // 4
    snake, // 5

    maxAnimals,
};

// Overload the unary + operator to convert an enum to the underlying type
// adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
// In C++23, you can #include <utility> and return std::to_underlying(a) instead
template <typename T>
constexpr auto operator+(T a) noexcept
{
    return static_cast<std::underlying_type_t<T>>(a);
}

int main()
{
    std::cout << +Animals::elephant << '\n'; // convert Animals::elephant to an integer using unary operator+

    return 0;
}
```

### `using enum` statement C++20

`using enum` statement imports all of the enumerators from an enum into the curent scope
- Allow us to access the enum class enumerators without having to prefix each with the name of the enum class

```cpp
#include <iostream>
#include <string_view>

enum class Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix

    switch (color)
    {
    case black: return "black"; // note: black instead of Color::black
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    Color shirt{ Color::blue };

    std::cout << "Your shirt is " << getColor(shirt) << '\n';

    return 0;
}
```

# 13.7 - Introduction to structs, members, and member selection

## Notes

many instances in programming where we need more than 1 variable in order to represent something interesting.

If we want to write a programw here we need to store information about the employees in a company, we might be interested in keeping track of attributes

If we use independent variables, that might look like this:

```cpp
std::string name;
std::string title;
int age;
int id;
int managerId;
double wage;
int birthdayYear;
int birthdayMonth;
int birthdayDay;
int hireYear;
int hireMonth;
int hireDay;
```

It's not immediately clear whether these variables are actually related or not

If we want more employees, we need to define 12 more variables for each employee

**Struct** (Short for **structure**), A program-defined data type that allows us to bundle multiple variables together into a single type

### Defining strcts

We have to tell the compilerwhat our struct type looks like before we can begin using it

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

`struct` keyword is used to tell the compiler that we're definng a struct

**Data members**: The variables that are part of the struct
- Empty curly braces after each member variable ensures that the member variables inside our `Employee` are value initialized when an `Employee` is created

`Employee` is just a type definition - no objects are actually created at this point

### Defining Struct Objects

Simply define a variable of type `Employee`

```cpp
Employee joe {}; // Employee is the type, joe is the variable name
```

When the code is executed, an Employee object is instantiated that contains the 3 data members
- Empty braces enures our object is value-initialized

### Accessing members

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    return 0;
}
```

To access a specific member variable, we use **Member Selection Operation** (`operator.`)
- Used in between the struct variable name and the member name

```cpp
joe.age
```

Possible to do normal operations on them, including assignment, arithmetic, comparison, etc.

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    joe.age = 32;  // use member selection operator (.) to select the age member of variable joe

    std::cout << joe.age << '\n'; // print joe's age

    return 0;
}
```

We only need to create 1 new name per struct variable 
- the member names are fixed as part of the struct type definition

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};
    joe.id = 14;
    joe.age = 32;
    joe.wage = 60000.0;

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };
    std::cout << "Joe and Frank have lived " << totalAge << " total years\n";

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than Frank\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // Frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age; // use pre-increment to increment Joe's age by 1

    return 0;
}
```

# 13.8 - Struct Aggregate Initialization

## Notes

### Data members are not initialized by default

Data members are not initialized by default

```cpp
#include <iostream>

struct Employee
{
    int id; // note: no initializer here
    int age;
    double wage;
};

int main()
{
    Employee joe; // note: no initializer here either
    std::cout << joe.id << '\n';

    return 0;
}
```

When `joe` is instantiated, the member variables will also be uninitialized
- We get undefined behavior if we try to print the value of `joe.id`

### What is an aggregate?

**Aggregate Data Type**: Any type that can contain multiple data members
- Some types of aggregates allow members to have different types (e.g. Structs)
- Others require that all members must be a single type (e.g. Arrays)

Structs with only data members are aggregates

### Aggregate initialization of a struct

**Aggregate Initialization**: Allows ust o directly initalize the members of aggregates
- Provide an **Initializer List** as an initilizaer, which is just a braced list of comma-separated values

2 Primary forms of aggregated initialization

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)

    return 0;
}
```

**Memberwise Initialization**: Each member in the struct is initialized in the order of declaration
- Both of these initialization forms do memberwise initialization

Best Practice: Prefer the braced list form when initializing aggregates

In C++20, we can also initialize (some) aggregates using a paraenthesized list of values

```cpp
Employee robert ( 3, 45, 62500.0 );  // direct initialization using parenthesized list (C++20)
```

The last recommended option, as it doesn't currently work with aggregates that utilize brace ellision (`std::array`)

### Missing initializers in an initializer list

If an aggregate is iniitalized but the number of initilization values is fewer than the number of members:
- Each member without an explicit initializer is initialized as follows:
  - If the member has a default member initializer, that is used
  - Else, the member is copy-initialized from an empty initializer list
    - This will perform value-initialization on those members

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage { 76000.0 };
    double whatever;
};

int main()
{
    Employee joe { 2, 28 }; // joe.whatever will be value-initialized to 0.0

    return 0;
}
```

Because `joe.wage` wasn't given an explicit initializer, but has a default member initializer, `joe.wage` will be initialized to `76000.0`

Because `joe.whatever` wasn't given an explicit initializer, `joe.whatever` is value-initialized to `0.0`

### Overloading `operator<<` to print a struct

We can overload `operator<<` with a struct

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;
    return out;
}

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0
    std::cout << joe << '\n';

    return 0;
}
```

A struct can hold nultiple values
- How you format the output is entirely up to you

### Const struct

Variables of a struct type can be const (or constexpr), just like all const variables, they must be initialized

```cpp
struct Rectangle
{
    double length {};
    double width {};
};

int main()
{
    const Rectangle unit { 1.0, 1.0 };
    const Rectangle zero { }; // value-initialize all members

    return 0;
}
```

### Designated initializers C++20

When initializing a struct from a list of values, the initializers are applied to the members in order of declaration

```cpp
struct Foo
{
    int a {};
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // f.a = 1, f.c = 3

    return 0;
}
```

What would happen if you were to update this struct definition to add a new member that is not the last member

```cpp
struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0

    return 0;
}
```

**Designated Initializers**: Allow you to explicitly define which initialization values map to which members
- Members can be initialized using list or copy initialization, and must be initialized in the same order in whcih theyare declared in the struct
- Members not designated an initializer will be value initialized

```cpp
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}
```

Designed initializers are nice as they provide some level of self-documentation and help ensure you don't inadvertently mix up the order o the initializers
- But they clutter up the initalizer list significantly
- There's no enforcement that designated initializers are being used consistenly everywhere an aggregated is initialized

### Assignment with an initilizer list

We can assign values to members of structs individually

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };

    joe.age  = 33;      // Joe had a birthday
    joe.wage = 66000.0; // and got a raise

    return 0;
}
```

You can assign values to structs using an initializer list

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

### Assignment with designated initializers (C++20)

Designated initializers can also be used in a list assignment

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

### Initializing a struct with another struct of the same type

A struct may also be initialized using another struct of the same type

```cpp
#include <iostream>

struct Foo
{
    int a{};
    int b{};
    int c{};
};

std::ostream& operator<<(std::ostream& out, const Foo& f)
{
    out << f.a << ' ' << f.b << ' ' << f.c;
    return out;
}

int main()
{
    Foo foo { 1, 2, 3 };

    Foo x = foo; // copy-initialization
    Foo y(foo);  // direct-initialization
    Foo z {foo}; // direct-list-initialization

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << z << '\n';

    return 0;
}
```

This uses the standard forms of initialization that we're familiar with (copy, direct, or direct-list-intialization)

Most commonly seen when initializing a struct with the return value of a function that returns a struct of the same type

# 13.9 - Default Member Initialization

## Notes

When we define a struct type, we provide a default initialization value for each member as part of the type definition.
- For members not marked as `static`, this process is sometimes called **Non-Static Member Initialization**
- Initialization value is called a **Default Member Initializer**

```cpp
struct Something
{
    int x;       // no initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2

    return 0;
}
```

### Explicit initialization values take precedence over default values

Explicit values in a list initializer always take precedence over default member initialization values

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x, s2.y, and s2.z (no default values are used)

    return 0;
}
```

### Missing initializer in an initilizer list when default values exist

If a default member initializer is provided for a given member, that default member initializer will be used instead

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s3 {}; // value initialize s3.x, use default values for s3.y and s3.z

    return 0;
}
```

### Recapping the initialization possibilites

If an aggregate is defined with an initialization list:
- If an explicit initialization value exists, that explicit value is used
- If an initializer is missng and a default member initializer exists, the default is used
- If an initializer is missing and no default member initializer exists, value initialization occurs

If an aggregate is defined with no initializer list
- If a default member initializer exists, the default is used
- If no default member initializer exists, the member remains uninitialized

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1;             // No initializer list: s1.x is uninitialized, s1.y and s1.z use defaults
    Something s2 { 5, 6, 7 }; // Explicit initializers: s2.x, s2.y, and s2.z use explicit values (no default values are used)
    Something s3 {};          // Missing initializers: s3.x is value initialized, s3.y and s3.z use defaults

    return 0;
}
```

### Always provide default values for your members

To avoid the possibility, of uninitialized members, simply ensure that each member has a default value

```cpp
struct Fraction
{
	int numerator { }; // we should use { 0 } here, but for the sake of example we'll use value initialization instead
	int denominator { 1 };
};

int main()
{
	Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
	Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
	Fraction f3 { 6 };    // f3.numerator initialized to 6, f3.denominator defaulted to 1
	Fraction f4 { 5, 8 }; // f4.numerator initialized to 5, f4.denominator initialized to 8

	return 0;
}
```

Best Practice: Provide a default value for all members. This ensures that your members will be initialized even if the variable definition doesn't include an initializer list

### Default initialization vs value initialization for aggregates

```cpp
Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
```

`f1` is default initialized, and `f2` is value initialized, but the values will be the same
- Which do we prefer

Value initialization case (`f2`) is sager, because it will ensure any members with no default values are value initialized

Preferring value initialization has 1 more benefit:
- It's consistent with how we initialize objects of other types

It's not uncommon for programmers to use default initialization instead
- Partly for historic reasons
- Partly because there is a particular case where default initialization can be more efficient than value initialization

# 13.10 - Passing and returning structs

## Questions

1. You are running a website, and you are trying to calculate your advertising revenue. Write a program that allows you to enter 3 pieces of data:

How many ads were watched.
What percentage of users clicked on an ad.
The average earnings per clicked ad.
Store those 3 values in a struct. Pass that struct to another function that prints each of the values. The print function should also print how much you made for that day (multiply the 3 fields together).

```cpp
#include <iostream>

// First we need to define our Advertising struct
struct Advertising
{
    int adsShown {};
    double clickThroughRatePercentage {};
    double averageEarningsPerClick {};
};

Advertising getAdvertising()
{
    Advertising temp {};
    std::cout << "How many ads were shown today? ";
    std::cin >> temp.adsShown;
    std::cout << "What percentage of ads were clicked on by users? ";
    std::cin >> temp.clickThroughRatePercentage;
    std::cout << "What was the average earnings per click? ";
    std::cin >> temp.averageEarningsPerClick;

    return temp;
}

void printAdvertising(const Advertising& ad)
{
    std::cout << "Number of ads shown: " << ad.adsShown << '\n';
    std::cout << "Click through rate: " << ad.clickThroughRatePercentage << '\n';
    std::cout << "Average earnings per click: $" << ad.averageEarningsPerClick << '\n';

    // The following line is split up to reduce the length
    // We need to divide ad.clickThroughRatePercentage by 100 because it's a percent of 100, not a multiplier
    std::cout << "Total Earnings: $"
        << (ad.adsShown * ad.clickThroughRatePercentage / 100 * ad.averageEarningsPerClick) << '\n';
}

int main()
{
    // Declare an Advertising struct variable
    Advertising ad{ getAdvertising() };
    printAdvertising(ad);

    return 0;
}
```

2. Create a struct to hold a fraction. The struct should have an integer numerator and an integer denominator member.

Write a function to read in a Fraction from the user, and use it to read-in two fraction objects. Write another function to multiply two Fractions together and return the result as a Fraction (you don’t need to reduce the fraction). Write another function that prints a fraction.

Your program’s output should match the following:

```shell
Enter a value for the numerator: 1
Enter a value for the denominator: 2

Enter a value for the numerator: 3
Enter a value for the denominator: 4

Your fractions multiplied together: 3/8
```

```cpp
#include <iostream>

struct Fraction
{
    int numerator {};
    int denominator {};
};

Fraction getFraction()
{
    std::cout << "Enter a value for the numerator: ";
    int num{};
    std::cin >> num;

    std::cout << "Enter a value for the denominator: ";
    int den{};
    std::cin >> den;

    return Fraction{num, den};
}

void multiplyFractions(Fraction& fraction1, Fraction& fraction2)
{
    int num {fraction1.numerator * fraction2.numerator};
    int den {fraction1.denominator * fraction2.denominator};
    std::cout << "Your fractions multiplied together: " << num << "/" << den << "\n";
}

int main()
{

    Fraction fraction1{getFraction()};
    std::cout << "\n";
    Fraction fraction2{getFraction()};

    multiplyFractions(fraction1, fraction2);

    return 0;
}
```

3. In the solution to the prior quiz question, why does getFraction() return by value instead of by reference?
- If you return by reference, the value being reference will go out of scope and get deleted. This will cause the reference to be dangling which will cause unexpected behavior.

## Notes

If we want to pass an employee to a function, we have to pass three variables

```cpp
#include <iostream>

void printEmployee(int id, int age, double wage)
{
    std::cout << "ID:   " << id << '\n';
    std::cout << "Age:  " << age << '\n';
    std::cout << "Wage: " << wage << '\n';
}

int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    printEmployee(id, age, wage);

    return 0;
}
```

Passing each variable independently would be time consuming and error prone

### Passing structs (By Reference)

We can pass the entire struct to a function that needs to work with the members
- Generally passed by reference (typically const reference) to avoid making copies

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };

    // Print Joe's information
    printEmployee(joe);

    std::cout << '\n';

    // Print Frank's information
    printEmployee(frank);

    return 0;
}
```

```shell
ID:   14
Age:  32
Wage: 24.15

ID:   15
Age:  28
Wage: 18.27
```

### Passing temporary structs

In cases where we only use a variable once, having togive the variable a name and separate the creation and use of that variable can increase complexity
- It may be preferable to use a temporary object instead
- Temporary objects are not variables, so it doesn't have an identifier

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    // Print Joe's information
    printEmployee(Employee { 14, 32, 24.15 }); // construct a temporary Employee to pass to function (type explicitly specified) (preferred)

    std::cout << '\n';

    // Print Frank's information
    printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter)

    return 0;
}
```

A few more things about temporary objects
- They are created and initialized at the point of definition, and are destroyed at the end of the full expression in which they are created
- Evaluation of a temporary object is an rvalue expression
- When used as a function argument, it will only bind to parameters that accept rvalues
  - This includes pass by value and pass by const references
  - Excludes pass by non-const reference and pass by address

### Returning structurs

Consider the case where we have a function that needs to return a point in 3D Cartesian space

Once common way to return a struct:

```cpp
#include <iostream>

struct Point3d
{
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}

int main()
{
    Point3d zero{ getZeroPoint() };

    if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
        std::cout << "The point is zero\n";
    else
        std::cout << "The point is not zero\n";

    return 0;
}
```

```shell
The point is zero
```

Structs defined inside functions are usually returned by value, so as not to return a dangling reference

```cpp
Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}
```

We can make our function slightly better by returning a temporary object instead

```cpp
Point3d getZeroPoint()
{
    return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

### Deducing the return type

In the case where the function has an explicit return, we can even omit the type in the return statement

This is considered implicit conversion

```cpp
Point3d getZeroPoint()
{
    // We already specified the type at the function declaration
    // so we don't need to do so here again
    return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

Since i this case we're returning all Zero Values, we can use empty braces to return a value-initialized Point3d

```cpp
Point3d getZeroPoint()
{
    // We can use empty curly braces to value-initialize all members
    return {};
}
```

### Structs are an important building block

While structs are useful, classes build directly on top of the concept

# 13.11 - Struct miscellany

## Notes

### Structs with program-defined members

Structs can have members that are other program-defined types

We can define one program defined type in the global scope, then use it as a member of another program-defined type

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Company
{
    int numberOfEmployees {};
    Employee CEO {}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

Types can also be nested inside other types, so if an Employee only existed as part of a Company, the Employee type could be nested inside the Company struct

```cpp
#include <iostream>

struct Company
{
    struct Employee // accessed via Company::Employee
    {
        int id{};
        int age{};
        double wage{};
    };

    int numberOfEmployees{};
    Employee CEO{}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

This is more often done with classes

### Structs that are owners should have data members that are owners

Owners manage their own data, and control when it is destroyed\
Viewers view someone else's data, and do not control when it is altered or destoryed

Most cases, we want our structs to be owners of the data they contain
- The data members will be valid for as long as the struct is
- The value of those data members won't change unexpectedly

Easiest way to make a struct an owner is to give each data a type that is an owner (not a viewer, poitner, or reference)
- If a struct or class has data members that are all owners, then the struct/class itself is automatically an owner

Best Practice: In most cases, we want our structs to be owners

String data members are always always of type `std::string` and not type `std::string_view`

### Struct size and data structure alignment

Typically the size of a struct is the sum of the size of all its members, but not always

```cpp
#include <iostream>

struct Foo
{
    short a {};
    int b {};
    double c {};
};

int main()
{
    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

    return 0;
}
```

```shell
The size of short is 2 bytes
The size of int is 4 bytes
The size of double is 8 bytes
The size of Foo is 16 bytes
```

We can only say that the size of the struct will be at least as large sa the size of all the variables it contains.
- It could be larger

**Padding**: The compiler will sometimes add gaps into structures

The compiler is invisibly adding 2 bytes of padding after member `a`

This can have a pretty big impact o the size of the struct.

```cpp
#include <iostream>

struct Foo1
{
    short a{}; // will have 2 bytes of padding after a
    int b{};
    short c{}; // will have 2 bytes of padding after c
};

struct Foo2
{
    int b{};
    short a{};
    short c{};
};

int main()
{
    std::cout << sizeof(Foo1) << '\n'; // prints 12
    std::cout << sizeof(Foo2) << '\n'; // prints 8

    return 0;
}
```

```shell
12
8
```

You can minimize padding by defining your members in decreasing order size

# 13.12 - Member selection with pointers and references

## Notes

### Member selection for structs and references to structs

You can use the member selection operator (.) to select member from a struct object

Since references to an object act just like the object itself, we can also use the member selection operator to select a member from a reference to a struct

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

void printEmployee(const Employee& e)
{
    // Use member selection operator (.) to select member from reference to struct
    std::cout << "Id: " << e.id << '\n';
    std::cout << "Age: " << e.age << '\n';
    std::cout << "Wage: " << e.wage << '\n';
}

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    printEmployee(joe);

    return 0;
}
```

### Member selection for pointers to structs

The member selection operator (.) can't be used directly on a pointer to a struct

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

    return 0;
}
```

With normal variables or references, we can access objects directly. Because pointers hold addresses, we first need to dereference the pointer to get the object before we can do anything

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    return 0;
}
```

This is a bit ugly.

**Member Selection From Pointer Operator (->)**: Or Arrow Pointer, that can be used to select members from a pointer to an object

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    return 0;
}
```

Works identically to the member selection operator, but does an implicit dereference of the pointer object before selecting the member
- `ptr->id` is equivalent to `(*ptr).id`

Much less prone to error because the indirection is implicitly done for you

### Chaining `operator->`

If the member accessed via `operator->` is a pointer to a class type, `operator->` can be applied again in the same expression to access the member of that class type

```cpp
#include <iostream>

struct Point
{
    double x {};
    double y {};
};

struct Triangle
{
    Point* a {};
    Point* b {};
    Point* c {};
};

int main()
{
    Point a {1,2};
    Point b {3,7};
    Point c {10,2};

    Triangle tr { &a, &b, &c };
    Triangle* ptr {&tr};

    // ptr is a pointer to a Triangle, which contains members that are pointers to a Point
    // To access member y of Point c of the Triangle pointed to by ptr, the following are equivalent:

    // access via operator.
    std::cout << (*(*ptr).c).y << '\n'; // ugly!

    // access via operator->
    std::cout << ptr -> c -> y << '\n'; // much nicer
}
```

Adding whitespace between the members and `operator->` can make it a bit easier to distinguish the members being accessed from the operator

### Mixing pointers and non-pointers to members

The member selection operator is always applied to the currently selected variable.\
If you have a mix of pointers and normal member variables, you can see member selections where . and -> are both used in sequence

```cpp
#include <iostream>
#include <string>

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Animal puma{ "Puma", { 5 } };

    Animal* ptr{ &puma };

    // ptr is a pointer, use ->
    // paw is not a pointer, use .

    std::cout << (ptr->paw).claws << '\n';

    return 0;
}
```

In the case of `(ptr->paw).claws)`, parentheses aren't necessary since both `->` and `.` evaluate in left to right order but it does help readability

# 13.13 - Class Templates

## Notes

### Aggregate types have similar challenges

We have similar challenges with aggregate types

Say we're writing a program where we need to work with pairs of `int` values, and need  to determine which of the 2 numbers is larger

```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

constexpr int max(Pair p) // pass by value because Pair is small
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    return 0;
}
```

We discover that we also need pairs of `double` values, so we update our program

```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

struct Pair // compile error: erroneous redefinition of Pair
{
    double first{};
    double second{};
};

constexpr int max(Pair p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair p) // compile error: overloaded function differs only by return type
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    Pair p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n";

    return 0;
}
```

This won't compile

### Class Templates

**Class Template**: A template definition for instantiating class types

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```

We start a class template definition with a template parameter declaration
- Begin with the `template` keyword
- Specify all of the template types that our class template will use inside angled brackets
- Each template type that we need, we use the keyword `typename`, followed by the name of the template type `T`

We define our struct like usual, except we can use our template type (`T`) wherever we want a templated type that will be replaced with a real type later

Compiler results

```cpp
#include <iostream>

// A declaration for our Pair class template
// (we don't need the definition any more since it's not used)
template <typename T>
struct Pair;

// Explicitly define what Pair<int> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<int>
{
    int first{};
    int second{};
};

// Explicitly define what Pair<double> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<double>
{
    double first{};
    double second{};
};

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```

### Using our class template in a function

Because the compiler treats `Pair<int>` and `Pair<double>` as separate types, we cuold use overloaded funcitons that are differentiated by parameter type

```cpp
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair<double> p) // okay: overloaded function differentiated by parameter type
{
    return (p.first < p.second ? p.second : p.first);
}
```

What we really want is a function that can take a pair of any type
- We want a function that takes a parameter of type `Pair<T>`, where T is a template type parameter

We need a function template for this job

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // call to max<double> using template argument deduction (prefer this)

    return 0;
}
```

The `max()` function template takes in a `Pair<t>`. We need the compiler to understand what `T` is.
- We need to start our function with a template parameter declaration that defines template type `T`

### Class templates with template type and non-template type members

Class templates can have some members using a tempalte type and other members using anormal type

```cpp
template <typename T>
struct Foo
{
    T first{};    // first will have whatever type T is replaced with
    int second{}; // second will always have type int, regardless of what type T is
};
```

### Class Templates with multiple template types

Class templates can also have multiple template types

```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    Pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    Pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    Pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```

To define multiple template types, in our template parameter declaration, we separate each of our desired template types with a comma

### Making a function template work with more than one class type

```cpp
template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```

Because we've explicitly defined the function parameter as a `Pair<T, U>`, only arguments of type `Pair<T, U>` will match
- This is ideal if we only want to be able to call our function with a `Pair<T, U>` argument

In some cases, we may write function templates that we want to use with any type that will successfully compile
- We simply use a type template parameter as the function parameter instead

```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

struct Point
{
    int first{};
    int second{};
};

template <typename T>
void print(T p) // type template parameter will match anything
{
    std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}

int main()
{
    Pair<double, int> p1{ 4.5, 6 };
    print(p1); // matches print(Pair<double, int>)

    std::cout << '\n';

    Point p2 { 7, 8 };
    print(p2); // matches print(Point)

    std::cout << '\n';

    return 0;
}
```

The body of the function will compile successfully for any class type that has a `first` and `second` member

There is one case that can be misleading
```cpp
template <typename T, typename U>
struct Pair // defines a class type named Pair
{
    T first{};
    U second{};
};

template <typename Pair> // defines a type template parameter named Pair (shadows Pair class type)
void print(Pair p)       // this refers to template parameter Pair, not class type Pair
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```

You might expect that this function will only match when called with a `Pair` class type argument
- This version of `print()` is functionality identically to the prior version where the template parameter was named `T`, and will match with *any* type

### std::pair

Working with pairs of data is common, C++ contains a class template named `std::pair` in `<cutility>`.

```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    // the members of std::pair have predefined names `first` and `second`
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    std::pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    std::pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```

### Using class templates in multiple functions

Class templates are typically defined in header files so they can be included into any code file that needs them
- Both template definitions and type definitions are exempt from the one-definition rule

```cpp
// pair.h
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

#endif
```

```cpp
// foo.cpp
#include "pair.h"
#include <iostream>

void foo()
{
    Pair<int> p1{ 1, 2 };
    std::cout << max(p1) << " is larger\n";
}
```

```cpp
// main.cpp
#include "pair.h"
#include <iostream>

void foo(); // forward declaration for function foo()

int main()
{
    Pair<double> p2 { 3.4, 5.6 };
    std::cout << max(p2) << " is larger\n";

    foo();

    return 0;
}
```

# 13.14 - Class template argument deduction (CTAD) and deduction guide

## Notes

### Class template argument deduction (CTAD) C++17

When instantiating an object from a class template, the compiler can deduce the template types from the types of the object's initializer

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
    std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    return 0;
}
```

CTAD is only performed if no template argument list is present, both of the following are errors

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
    std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced

    return 0;
}
```

We can use literal suffixes to change the deduced type

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair p1 { 3.4f, 5.6f }; // deduced to pair<float, float>
    std::pair p2 { 1u, 2u };     // deduced to pair<unsigned int, unsigned int>

    return 0;
}
```

### Template argument deduciton guides C++17

Most cases, CTAD works right out the box
- Certain cases, the compiler may need a little extra help understanding how to deduce the template arguments properly

The following program doesn't compile in C++17 only

```cpp
// define our own Pair type
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

int main()
{
    Pair<int, int> p1{ 1, 2 }; // ok: we're explicitly specifying the template arguments
    Pair p2{ 1, 2 };           // compile error in C++17 (okay in C++20)

    return 0;
}
```

In C++17, CTAD doesn't know how to deduce the template arguments for aggregate class templates
- We can provide the compiler with a **deduction guide**
- **Deduction Guide**: Tells the compiler how to deduce the template arguments for a given template

```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    return 0;
}
```

Use the same template type definition for `Pair` class
- On the right hand side of the arrow, we have the type that we're helping the compiler to deduce
- Left side, we tell  the compiler what kind of declaration to look for

We're telling the compiler that if it sees a declaration of a `Pair` with 2 arguments, it should deduce the type to be a `Pair<T, U>`

Similar example for a Pair that takes a single template type:

```cpp
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

int main()
{
    Pair<int> p1{ 1, 2 }; // explicitly specify class template Pair<int> (C++11 onward)
    Pair p2{ 1, 2 };      // CTAD used to deduce Pair<int> from the initializers (C++17)

    return 0;
}
```

### Template types parameters with default values

Template parameters can be given default values. These will be used when the template parameter isn't explicitly specified and can't be deduced

```cpp
template <typename T=int, typename U=int> // default T and U to type int
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    Pair p3;                   // uses default Pair<int, int>

    return 0;
}
```

Our definition of `p3` doesn't explicitly specify types for the type template parameters, nor is there an initializer for these types to deduce
- The compiler will use the types specified in the defaults, which means `p3` will be of type `Pair<int, int>`

### CTAD doesn't work with non-static member initialization

When initializing the member of a class type using non-static member initialization, CTAD will not work in this context
- All template arguments must be explicitly specified

```cpp
#include <utility> // for std::pair

struct Foo
{
    std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
    std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
};

int main()
{
    std::pair p3{ 1, 2 };           // ok, CTAD can be used here
    return 0;
}
```

### CTAD Doesn't work with function parameters

CTA is for class template *argument* deduction, not class template *parameter* deduction.
- It will only deduce the type of template arguments, not template parameters

```cpp
#include <iostream>
#include <utility>

void print(std::pair p) // compile error, CTAD can't be used here
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

# 13.15 - Alias Tempaltes

## Notes

Creating a type alias for a class template where all template arguments are explicitly specified works just like a normal type alias

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
void print(const Pair<T>& p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    using Point = Pair<int>; // create normal type alias
    Point p { 1, 2 };        // compiler replaces this with Pair<int>

    print(p);

    return 0;
}
```

### Alias Templates

We might want a type alas for a template class where not all of the template arguments are defined as part of the alias

**Alias Template**: A template that can be used to instantiated type aliases, just like type aliases do not define distinct types
- Alias templates do not define distinct types

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's our alias template
// Alias templates must be defined in global scope
template <typename T>
using Coord = Pair<T>; // Coord is an alias for Pair<T>

// Our print function template needs to know that Coord's template parameter T is a type template parameter
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}

int main()
{
    Coord<int> p1 { 1, 2 }; // Pre C++-20: We must explicitly specify all type template argument
    Coord p2 { 1, 2 };      // In C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works

    std::cout << p1.first << ' ' << p1.second << '\n';
    print(p2);

    return 0;
}
```

Unlike normal type aliases, alias templates must be defined in the global scope

Prior to C++20, we must explicitly specify the template arguments when we instantiate an object using an alias template
- C++20 **Alias Template Deduction**: Deduce the type of the template arguments crom an initializer in cases where the aliased type would work with CTAD
- Because CTAD doesn't work on function parameters, when we use an alias template as a function parameter, we must explicitly define the template argument used by the alias template

```cpp
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}
```

# 13.x - Chapter 13 summary and quiz

## Review

- **Program-Defined type**: A custom type that we can create for use in our own programs
- **Type Definition**: The definition of a program-defined type
- **Enumeration**: A compound data type where every possible value is defined as a symbolic constant
- **Distinct Types**: The compiler can differentiate them from other types
- **Unscoped Enumeration**: Put their enumerator names into the same scope as the enumeration definition itself
  - Provide a named scope region for their enumerators
- **Scoped Enumerations**: Work similarly to unscoped enumerations but won't implicitly convert to integers
  - Enumerators are only placed into the scope region of the enumeration
- **Struct**: A program-defined data type that allows us to dundle multiple variables together into a single type
- **Data Members**: Variables that are part of the struct
- **memer Selection Operator '.'**: Used to access a specific member variable
- **Member Selection From Pointer Operator '->'**: Used to access a specific member variable from pointers to struct
- Aggregate data **type**: Any type that can contain multiple data members
- **Aggregates**: Arrays and Structs with only data members
- **Aggregate Initialization**: Allow us to directly initialize the members of aggregates
- **Initializer List**: A list of comman separated values
- **Memberwise Initialization**: Each member in the struct is initialized in the order of declaration
- **Designated Initializers**: Allow you to explicitly define which initialization values map to which members
- **Non-Static Member Initialization**: Can provide a default initialization value for each member as part of the type definition
- **Default Member Initialization**: The initialization value for non-static member initialization
- **Padding**: The compiler will sometimes add gaps into structures so the size of a structure may be larger thant the sum of the size of its members
- **Class Template**: A template defintion for instantiating class types
- **Class Template Argument Deductionb: A feature that allows the compiler to deduce the template type arguments from an initializer**

## Quiz

1. In designing a game, we decide we want to have monsters, because everyone likes fighting monsters. Declare a struct that represents your monster. The monster should have a type that can be one of the following: an ogre, a dragon, an orc, a giant spider, or a slime.

Each individual monster should also have a name (use a std::string), as well as an amount of health that represents how much damage they can take before they die. Write a function named printMonster() that prints out all of the struct’s members. Instantiate an ogre and a slime, initialize them using an initializer list, and pass them to printMonster().

Your program should produce the following output:

```shell
This Ogre is named Torg and has 145 health.
This Slime is named Blurp and has 23 health.
```

```cpp
#include <iostream>
#include <string>
#include <string_view> // C++17

// Our monster struct represents a single monster

struct Monster
{
	// Define our different monster types as an enum
	enum Type
	{
		ogre,
		dragon,
		orc,
		giant_spider,
		slime,
	};

	Type type{};
	std::string name{}; // the Monster should be an owner of its name
	int health{};
};

// Return the name of the monster's type as a string
// Since this could be used elsewhere, it's better to make this its own function
constexpr std::string_view getMonsterTypeString(Monster::Type type)
{
	switch (type)
	{
	case Monster::ogre:          return "Ogre";
	case Monster::dragon:        return "Dragon";
	case Monster::orc:           return "Orc";
	case Monster::giant_spider:  return "Giant Spider";
	case Monster::slime:         return "Slime";
	}

	return "Unknown";
}

// Print our monster's stats
void printMonster(const Monster& monster)
{
	std::cout << "This " << getMonsterTypeString(monster.type) <<
		" is named " << monster.name <<
		" and has " << monster.health << " health.\n";
}

int main()
{
	Monster ogre{ Monster::ogre, "Torg", 145 };
	Monster slime{ Monster::slime, "Blurp", 23 };

	printMonster(ogre);
	printMonster(slime);

	return 0;
}
```

2. Specify whether objects of each of the given types should be passed by value, const address, or const reference. You can assume the function that takes these types as parameters doesn’t modify them.

a. `char`: passed by value
b. `std::string`: const reference
c. `unsinged long`: passed by value
d. `bool`: passed by value
e. Enumerated type: passed by value
f. 
```cpp
struct Position
{
  double x{};
  double y{};
  double z{};
};
```
- const reference
g. 
```cpp
struct Player
{
  int health{};
  // The Player struct is still under development.  More members will be added.
};
```
- const reference
h. `int` Null is a valid argument: const address
i. `std::string_view`: pass by value

3. Create a class template named Triad that has 3 members of the same template type. Also create a function template named print that can print a Triad. The following program should compile:

```cpp
int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}
```

```cpp
#include <iostream>
#include <string>
#include <string_view>

template <typename T>
struct Triad
{
    T x {};
    T y {};
    T z {};
};

template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(Triad<T> triad)
{
    std::cout << "[" << triad.x << ", " << triad.y << ", " << triad.z << "]";
}

int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}
```