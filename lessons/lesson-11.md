# 11.1 - Introduction to Function Overloading

## Notes

```cpp
int add(int x, int y)
{
    return x + y;
}
```
 What if we wanted a function that can add 2 floating point numbers?

 We can define multiple functions with slightly different names

 ```cpp
 int add(int x, int y)
{
    return x + y;
}
```

What if we want to have a function with 3 integers? Managing unique names for each function quickly becomes burdensome

### Introduction to function overloading

**Function Overloading**: Create multiple functions with the same name, so long as each ientically named function has different parameters.
**Overloaded Function**: Each function sharing a name in the same scope

To overload the `add()` function we can simply declare another `add()` function

```cpp
int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    return 0;
}
```

### Introduction to overload resolution

**Overload Resolution**: When a function call is made to a function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

double add(double x, double y)
{
    return x + y;
}

int main()
{
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << '\n';
    std::cout << add(1.2, 3.4); // calls add(double, double)

    return 0;
}
```

### Making it compile

In order for a program using overloaded functions to compile, 2 things have to be true:
- Each overloaded function has to be differentiated from the other
- Each call to an overloaded function has to resolve to an overloaded function

If an overloaded function is not differentiated, or if a function call to an overloaded function can not be resolved to an overloaded function, then a complile error will result

Best Practice: Use function overloading to make your program simpler.

# 11.2 - Function overload Differentiation

## Notes

### How overloaded functions differentiated

Differentiated by number of parameters and type of parameters
- Tpye of parameters excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses

Does not differentiate by return type

### Overloading based on number of parameters

An overloaded function is differentiated so long as each overloaded function has a different number of parameters

```cpp
int add(int x, int y)
{
    return x + y;
}

int add(int x, int y, int z)
{
    return x + y + z;
}
```

### Overloading based on type of parameters

A function can be differentiated so long as each overloaded function's list of parameters types is distinct

```cpp
int add(int x, int y); // integer version
double add(double x, double y); // floating point version
double add(int x, double y); // mixed version
double add(double x, int y); // mixed version
```

Because type aliases are not distinct types, overloaded functions using type aliases are not distinct from overloads using the aliased type

```cpp
typedef int Height; // typedef
using Age = int; // type alias

void print(int value);
void print(Age value); // not differentiated from print(int)
void print(Height value); // not differentiated from print(int)
```

For paameters passed by value, the const qualifier is also not considered

```cpp
void print(int);
void print(const int); // not differentiated from print(int)
```

Ellipsis parameters are considered to be a unique type of parameters

```cpp
void foo(int x, int y);
void foo(int x, ...); // differentiated from foo(int, int)
```

Call to `foo(4, 5)` will match to `foo(int, int)` not `foo(int, ...)`

### The return type of a function function is not considered for differentiation

A function's return type is not considered when differentiating overload functions

```cpp
int getRandomValue();
double getRandomValue();
```

This will result in a compiler error. It wouldn't be clear for the compiler which function to call

Best to give them two different names

```cpp
int getRandomInt();
double getRandomDouble();
```

### Type Signature

A function's **Type Signature**: Defined as the part of the function header that are used for differentiation of the function.
- C++, this includes the function name, number of parameters, parameter type, and function-level qualifier
- Does not include the return type

### Name Mangling

**Name Mangling**: Compiler performs name mangling when compiling a function
- The compiled name of the function is altered based on various criteria, such as number and type of parameters, so that the linker has unique names to work with

# 11.3 - Functions overload resolution and ambiguous matches

## Notes

Having a set of differentiated overloaded functions is only half of the picture\
When any function call is made, the compiler must also ensure that a matching fuction declaration can be found

With overloaded functions, there can be many functions that can potentially match a function call
- Since a function call can only resolve to one of them, the compiler has to determine which overloaded function is the best match

**Overload Resolution**: The process of matching function calls to a specific overloaded function

Straightforward where the type of the function arguments and type of the function parameters match exactly

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print(5); // 5 is an int, so this matches print(int)
     print(6.7); // 6.7 is a double, so this matches print(double)

     return 0;
}
```

What happens in cases where the argument types in the function call don't exactly match the parameter types in any of the overloaded functions?

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print('a'); // char does not match int or double, so what happens?
     print(5L); // long does not match int or double, so what happens?

     return 0;
}
```

Which is the best conversion to make in each case?

### Resolving Overloaded Function Calls

When a function call is made to an overloaded function, the compiler steps through a sequence of rules to determine which of the overloaded functions is the best match

Each step, the compiler applies a bunch of different type conversions to the arguments in the function call. For each conversion applied, the compiler checks if any of the overloaded functions are now a match.

After all conversions have been applied and checked for matches, the step si done, the results will be 1 of 3 possibilities
- No matching functions were found. Compiler moves to the next step of the sequence
- A single matching function was found. This function is considered to be the best match
  - The matching process is now complete
  - Subsequent steps are not executed
- More than 1 matching function was found. The compiler will issue an ambiguous match compile error

### Argument Matching Sequence

Step 1: The compiler tries to find an exact match\
This happens in 2 phases
1. The compiler will see if there is a function where the type of the arguments exactly match

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(0);   // exact match with foo(int)
    foo(3.4); // exact match with foo(double)

    return 0;
}
```

2. The compiler will apply a number of trivial conversions ot the arguments in the function call\
**Trivial Conversions**: A set of specific conversion rules that will modify types for purposes of finding a match
- lvalue to rvalue conversions  
- qualification conversions (non-const to const)
- Non-reference to reference conversions

```cpp
void foo(const int)
{
}

void foo(const double&) // double& is a reference to a double
{
}

int main()
{
    int x { 1 };
    foo(x); // x trivially converted from int to const int

    double d { 2.3 };
    foo(d); // d trivially converted from double to const double& (non-ref to ref conversion)

    return 0;
}
```

Matches made via the trivial conversions are considered exact matches, meaning the following program results in an ambiguous match

```cpp
void foo(int)
{
}

void foo(const int&) // int& is a reference to a int
{
}

int main()
{
    int x { 1 };
    foo(x); // ambiguous match with foo(int) and foo(const int&)

    return 0;
}
```

Step 2: If no exact match is found, the compiler tries to find a match by applying numeric promotion to the argument
- If after numeric promotion, a match is found, the function call is resolved

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo('a');  // promoted to match foo(int)
    foo(true); // promoted to match foo(int)
    foo(4.5f); // promoted to match foo(double)

    return 0;
}
```

Step 3: If no match is found via numeric promotion, the compiler tries to find a match by applying numeric conversions to the arguments

```cpp
#include <string> // for std::string

void foo(double)
{
}

void foo(std::string)
{
}

int main()
{
    foo('a'); // 'a' converted to match foo(double)

    return 0;
}
```

Step 4: If no match is found via numeric conversion, the compiler tries to find a match through any user-defined conversions
- Certain types (e.g. classes) can define conversions to other types that can be implicitly invoked

```cpp
// We haven't covered classes yet, so don't worry if this doesn't make sense
class X // this defines a new type called X
{
public:
    operator int() { return 0; } // Here's a user-defined conversion from X to int
};

void foo(int)
{
}

void foo(double)
{
}

int main()
{
    X x; // Here, we're creating an object of type X (named x)
    foo(x); // x is converted to type int using the user-defined conversion from X to int

    return 0;
}
```

After applying a user-defined conversion, the compiler may apply additional implicit promotions or conversions to find a match
- If our user-defined conversion had been to type `char` instead of `int`, the compiler would have used the user-defined conversion to `char` and then promoted the result into an `int` to match

Step 5: if no match is found via user-defined conversion, the compiler will look for a matching function that uses ellipsis

Step6: If no matches have been found by this point, the compiler gives up and will issue a compile error

### Ambiguous Matches

With non-overloaded functions, each function call will either resolve to a function, or no match will be found and the compiler will issue a compile error

```cpp
void foo()
{
}

int main()
{
     foo(); // okay: match found
     goo(); // compile error: no match found

     return 0;
}
```

**Ambigious Match**: 3rd outcome of overloaded functions. When the compiler finds 2 or more functions that can be made to match in the same step
- The compiler will stop matching and issue a compile error stating that it has found an ambiguous function call

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(5L); // 5L is type long

    return 0;
}
```

Single `5L` is type `long`, it can't be promoted.
- `long` can be converted to both `int` and `double`

### Resolving ambiguous matches

Am ambiguous match needs to be disambiguated before your program will compile\
A few ways to resolve ambiguous matches:
1. The best way is simply to define a new overloaded function that takes parameters of exactly the type you are trying to call the function with
2. Alternatively, explicitly cast the ambiguous arguments to match the type of the function you want to call
  - `foo(5L)` turn into `foo(static_cast<int>(5L))`
3. If your argument is a literal, you can use the literal suffix to ensure your literal is interpreted as the correct type

### matching for functions with multiple arguments

If there are multiple arguments, the compiler applies the matching rules to each argument in turn.
- The function chosen is the one for which each argument matches at least as well as all the other functions, with at least 1 argument matching better than all the other functions

The function chosen must provide a better match than all the other candidate functions for at least 1 parameter, and no worse for all of the other parameters

If no function can be found, the call will be considered ambiguous

```cpp
#include <iostream>

void print(char, int)
{
	std::cout << 'a' << '\n';
}

void print(char, double)
{
	std::cout << 'b' << '\n';
}

void print(char, float)
{
	std::cout << 'c' << '\n';
}

int main()
{
	print('x', 'a');

	return 0;
}
```

This is an ambiguous call

# 11.4 - Deleting Functions

## Notes

### Deleting a function using the `= delete` specifier

**= delete**: In cases where we have a function that we explicitly do not want to be called, we can define that function as deleted.
- If the compiler matches a function call to a deleted function, compilation will be halted with a compile error

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(97);   // okay

    printInt('a');  // compile error: function deleted
    printInt(true); // compile error: function deleted

    printInt(5.0);  // compile error: ambiguous match

    return 0;
}
```
`printInt('a')` is a direct match for `printInt(char)` which was deleted
- The compiler thus produces a compilation error

`printInt(5.0)`, the compiler will try to find a best match
- Although `printInt(int)` is the only non-deleted function, the deleted functions are still considered as cnadidates in function overload resolution
- None of these functions are unambiguously the best match, the compiler will issue an ambiguous match compilation error

### Deleting all non-matching overloads

```cpp
#include <iostream>

// This function will take precedence for arguments of type int
void printInt(int x)
{
    std::cout << x << '\n';
}

// This function template will take precedence for arguments of other types
// Since this function template is deleted, calls to it will halt compilation
template <typename T>
void printInt(T x) = delete;

int main()
{
    printInt(97);   // okay
    printInt('a');  // compile error
    printInt(true); // compile error

    return 0;
}
```

# 11.5 - Default Arguments

## Notes

**Default Argument**: A default value provided for a function parameter

```cpp
void print(int x, int y=10) // 10 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

When making a function call, the caller can optionally provide an argument for any function parameter that has a default argument.
- If the caller provides an argument, the value fo the argument in the function call is used
- If the caller doesn't provide an argument, the value of the default argument is used

```cpp
#include <iostream>

void print(int x, int y=4) // 4 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(1, 2); // y will use user-supplied argument 2
    print(3); // y will use default argument 4, as if we had called print(3, 4)

    return 0;
}
```

```shell
x: 1
y: 2
x: 3
y: 4
```

You must use the equals sign to specify a default argument, using parenthesis or brace initialization won't work

```cpp
void foo(int x = 5);   // ok
void goo(int x ( 5 )); // compile error
void boo(int x { 5 }); // compile error
```

Default arguments are handled by the compiler at the call site.

When the compiler sees `print(3)`, it will rewrite this function call as `print(3, 4)`.

### When to use default arguments

Excellent option when a function needs a value that has a reasonable default value, but for which you wnat to let the caller override if they wish

```cpp
int rollDie(int sides=6);
void openLogFile(std::string filename="default.log");
```

Default arguments are also useful in cases where we need to add a new parameter to an existing function
- If we add a new parameter without a default argument, it will break all existing function calls
- If we add a new parameter with a default argument instead, all existing function calls will still work

### Multiple default arguments

A function can have multiple parameters with default arguments

```cpp
#include <iostream>

void print(int x=10, int y=20, int z=30)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

int main()
{
    print(1, 2, 3); // all explicit arguments
    print(1, 2); // rightmost argument defaulted
    print(1); // two rightmost arguments defaulted
    print(); // all arguments defaulted

    return 0;
}
```

```shell
Values: 1 2 3
Values: 1 2 30
Values: 1 20 30
Values: 10 20 30
```

C++ does not support a function call syntax such as `print(,,3)`\
3 Major consequences
1. In a function call, any explicitly provided arguments must be the leftmost arguments (arguments with default cannot be skipped)

```cpp
void print(std::string_view sv="Hello", double d=10.0);

int main()
{
    print();           // okay: both arguments defaulted
    print("Macaroni"); // okay: d defaults to 10.0
    print(20.0);       // error: does not match above function (cannot skip argument for sv)

    return 0;
}
```

2. If a paremeter is given a default argument, all subsequent parameters (to the right) must also be given default arguments

```cpp
void print(int x=10, int y); // not allowed
```

3. If more than one parameter has a default argument, the leftmost parameter should be the one most likely to be explicitly set by the user

### Default arguments can not be redeclared, and must be declared before use

Once declared, a default argument can not be redeclared in the same translation unit.
- A function with a forward declaration and a function definition, the default argument can be declared in either, but not both

```cpp
#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The default argument must also be declared in the translation unit before it can be used

```cpp
#include <iostream>

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

Best practice is to declare the default argument in the forward declaration and not int he function definition, as the forward declaration is more likely to be seen by other files and included bfore use

```cpp
// foo.h
#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```

```cpp
// main.cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);

    return 0;
}
```

### Default arguments and function overloading

Functions with default arguments may be overloaded

```cpp
#include <iostream>
#include <string_view>

void print(std::string_view s)
{
    std::cout << s << '\n';
}

void print(char c = ' ')
{
    std::cout << c << '\n';
}

int main()
{
    print("Hello, world"); // resolves to print(std::string_view)
    print('a');            // resolves to print(char)
    print();               // resolves to print(char)

    return 0;
}
```

### Default arguments can lead to ambiguous matches

```cpp
void foo(int x = 0)
{
}

void foo(double d = 0.0)
{
}

int main()
{
    foo(); // ambiguous function call

    return 0;
}
```

The compiler can't tell whether `foo()` should resolve to `foo(0)` or `foo(0.0)`

```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)

int main()
{
    print(1, 2);   // will resolve to print(int, int)
    print(1, 2.5); // will resolve to print(int, double)
    print(1);      // ambiguous function call

    return 0;
}
```

# 11.6 - Function Templates

## Questions

1. Describe why construction blueprints are a type of template.
- The construction blueprint itself is just a piece of paper that describes how to construct a building. Using the blueprint, construction crews can quickly erect many buildings with an identical structure. However, the specific material types used for each building can vary (e.g. what type of material is used for the siding of the building), and don’t need to be determined until the buildings are actually built.



## Notes

Say you want to write a function to calculate the maximum of 2 numbers

```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
```

While the caller can pass different values, the type of the parameters is fixed, the caller can only pass `int` values

If we create it with doubles

```cpp
double max(double x, double y)
{
    return (x < y) ? y: x;
}
```

The actual implementation is the same.
- Creating overloaded functions with the same implementation but different parameters is a pain

### Introduction to C++ Templates

The template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types


**Template**: Describes what a function or class looks like
- A template can use one or more placeholder types.
- A placeholder type represents some type that is not known at the time the template is defined

Once a template is defined, the compiler can use the template to generate as many overloaded functions or classes as needed, each using different actual types

Because the actual types aren't determined until the template is used in a program, the author of the template doesn't have to try to anticipate all of hte actual types that might be used

### Function Templates

**Function Templates**: A function like definition that is used to generate one or more overloaded functions, each with a different set of actual types

**Primary Template**: The initial function template that is used to generate other functions\
**Instantiated Functions**: The functions generated from the primary template

**Placeholder Types**: Used for any parameter types, return types, or types used in the function body that we want to be specified later

3 different kinds of template parameters:
- Type template parameters (Template parameter represents a type)
- Non-type template parameters (Template parameter represents a constexpr value)
- Template template parameters (Template parameter represents a template)

### Creating a `max()` function template

```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
}
```

We used type `int` 3 times in the function

To create a function template for `max()`
1. Replace any actual types that we want to be specified later with type template parameters

```cpp
T max(T x, T y) // won't compile because we haven't defined T
{
    return (x < y) ? y : x;
}
```

2. Going to tell the compiler that this is a template, and that `T` is a type template parameter that is a placeholder for any type
- **Template Parameter Declaration**: Which defines any template parameters that will be subsequently used
- Scope of a template parameter declaration is strictly limited to the function template that follows
- Each function template or class tempalte needs its own tempalte parameter declaration

```cpp
template <typename T> // this is the template parameter declaration defining T as a type template parameter
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```

Start with the keyword `template`, tells the compiler that we're creating a template.\
Specify all of the template parameters inside angled brackets `<>`.\
For each type template parameter, we use the keyword `typename` or `class`, followed by the name of the type template parameter `T`

### Naming Template Parameters

It's conventional to use a single capital letter when the tempalte parameter is used in a trivial or obvious way

We don't need to give `T` a complex name, because it's obviously just a placeholder type for the values being compared

If a type template parameter has a non-obvious usage or specific requirements that must be met, there are 2 common conventions for such names
- Starting with a capital letter (`Allocator`)
- Prefixed with a `T` (`TAllocator`)

# 11.7 - Function Template Instantiation

## Notes

### Using a Function Template

Function templates are not actually functions, they have 1 job: generate functions

To use our `max<T>` function template, we can make a function call with the following syntax:

```cpp
max<actual_type>(arg1, arg2); // actual_type is some actual type, like int or double
```

**Template Arguments**: Specifies the actual type that will be used in place of template type

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

The compiler will determine that a function definition for `max<int>(int, int)` doesn't already exist
- The compiler will implicitly use `max<T>` function template to create 1

**Function Template Instantiation**: The process of creating functions from function templates\
**Implicit Instantiation**: When a function is instantiated due to a function call\
**Function Instance**: A function that is instantied from a template
**Primary Template**: The template from which a specialization is produced

The compiler essentially clones the primary template and replaces the template type with the actual type we've specified

```cpp
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

### Template argument deduction

In most cases, the actual types we want to use for instantiation will match the type of our function parameters

In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type

**Template Argument Deduction**: Have the compiler deduce the actual type that should be used from the argument types in the function call

```cpp
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
```

The compiler will see that we haven't provided an actual type, so it will attempt to deduce an actal type from the function arguments that will allow it to generate a `max()` function 

Difference between these 2 is how the compiler resolves the function call from a set of overloaded functions

`max<>(1, 2)`, the compiler will only consider `max<int>` template function overloads\
`max(1, 2)`, the compiler will consider both `max<int>` template function overloads and `max` non-template function overloads

In both a template function and a non-template function are equally viable, the non-template function will be preferred

### Function templates with non-template parameters

It's possible to create function templates that have both temmplate parameters and non-template parameters

```cpp
// T is a type template parameter
// double is a non-template parameter
// We don't need to provide names for these parameters since they aren't used
template <typename T>
int someFcn(T, double)
{
    return 5;
}

int main()
{
    someFcn(1, 3.4); // matches someFcn(int, double)
    someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
    someFcn(1.2, 3.4); // matches someFcn(double, double)
    someFcn(1.2f, 3.4); // matches someFcn(float, double)
    someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double

    return 0;
}
```

The return type can also be any type.

### Instantiated Functions may not always compile

What if we tried something like this?

```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::string hello { "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

The compiler will generate and compile this:

```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x);

template<>
std::string addOne<std::string>(std::string x)
{
    return x + 1;
}

int main()
{
    std::string hello{ "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

This will generate a compile error, because `x + 1` doesn't make sense when `x` is a `std::string`

### Instantiated functions may not always make sense semanticlly

The compiler will successfully compile an instantiated function template as long as it makes sense syntactically

The compiler doesn't have any way to check that such a function actually makes sense semantically

```cpp
#include <iostream>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne("Hello, world!") << '\n';

    return 0;
}
```

We're calling `addOne()` on a C-Style String literal. What does that actually mean semantically?

### Function Templates and default arguments for non-template parameters

Function templates can have default arguments for non-template parameters. Each function instantiated from the template will use the same default argument

```cpp
#include <iostream>

template <typename T>
void print(T val, int times=1)
{
    while (times--)
    {
        std::cout << val;
    }
}

int main()
{
    print(5);      // print 5 1 time
    print('a', 3); // print 'a' 3 times

    return 0;
}
```

### Beware function templates with modifiable static local variables

When a static variable is used in a function template, each function instantiated from that template will have a separate version of the static local variable

This is rarely a problem if the static local variable is const, but if the static local variable is one that is modified, the results may not be as expected

```cpp
#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}
```

```shell
1) 12
2) 13
1) 14.5
```

This is what the compiler actually compiles and executes

```cpp
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
```

Each have their own independent static local variable named `id`

### Generic Programming

Because template types can be replaced with any actual type, template types are sometimes called **GTeneric Type**
- Templates can be written agnostically of specific types, programming with templates is sometimes called **generic programming**

C++ typically has a strong focus on types and type checking
- Generic programming lets us focus on the logic of algorithms and design of data structures without having to worry so much about type information

## 11.8 - Function Templates with Multiple Template Types

## Notes

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';  // compile error

    return 0;
}
```

This program won't compile. We'ree passing arguments for 2 different types. 
- Because we're making a function call without using angled brackets to specify an actual type, the compiler will first look to see if there is a non-template match for `max(int, double)`
- Compiler will see if it can find a template match
- `T` can only represent a single type.
  - No type for `T` that would allow the compiler to instantiate function template `max<T>(T, T)` for 2 different parameter types

Conversion is done only when resolving function overloads, not when performing template argument deduction
- It helps keep things simple: we either find an exact match between the function call arguments and template type parameters, or we don't
- Allows us to create function templates for cases where we want to ensure that 2 or more parameters have the same type

### Use static_cast to convert the argumens to matching types

Convert the argments into matching types

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)

    return 0;
}
```

The solution is awkward and hard to read

### Provide an explicit type template argument

If we had written a non-template `max(double, double)` funciton, then we would be able to call `max(int, double)` and let the implicit type conversion rules convert our `int` argument into a `double` so the function call could be resolved

```cpp
#include <iostream>

double max(double x, double y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // the int argument will be converted to a double

    return 0;
}
```

When the compiler is doing template argument deduction, it won't do any type conversions
- We don't have to use template argument deduction if we specify an explicit type template argument to be used instead

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';

    return 0;
}
```

It would be even nicer if we didn't even have to think about the types when making a function call to `max` at all

### Function templates with multiple template a type parameters

Rewrite our function template in such a way that our parameters can resolve to different types. Rather than using 1 template type parameter `T`, we'll now use two `T` and `U`

```cpp
#include <iostream>

template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>

    return 0;
}
```

The example doesn't work right. If you compile and run the program, it will produce:

```shell
3
```

The declared return type of our funtion is `T`, and `T` is an `int`

Return type deduction via `auto` is useful, we'll let the compiler deduce what the retur type should be from the return statement

```cpp
#include <iostream>

template <typename T, typename U>
auto max(T x, U y) // ask compiler can figure out what the relevant return type is
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}
```

### Abbreviated function templates C++20

C++20 introduces a new use of the `auto` keyword. 
- When the `auto` keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each auto parameter becoming an independent template type parameter
- This method for creating a function template is called **abbreviated function template**

```cpp
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}
```

This is shorthand in C++20 for the following:

```cpp
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

When you want each template type parameter to be an independent type, this form is preferred as the removal of the template parameter declaration line makes your code more conside and readable

There isn't an easy abbreviated function template when you want more than 1 auto parameter to be the same type

### Function templates may be overloaded

Function templates may also be overloaded. Such overloads can have a different number of tempalte types and/or a different number or type of function parameters

```cpp
#include <iostream>

// Add two values with matching types
template <typename T>
auto add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
auto add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
auto add(T x, U y, V z)
{
    return x + y + z;
}

int main()
{
    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

    return 0;
}
```

The rules for determining which of multiple matching function templates should be preferred are called "partial ordering of function templates"

If multiple function templates can match a call and the compiler can't determine which is more restrictive, the compiler will error with an ambiguous match

# 11.9 - Non-type template parameters

## Questions

1. Write a constexpr function template with a non-type template parameter that returns the factorial of the template argument. The following program should fail to compile when it reaches `factorial<-3>()`.

```cpp
// define your factorial() function template here

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    factorial<-3>(); // should fail to compile

    return 0;
}
```

```cpp
// define your factorial() function template here
template<int N>
constexpr int factorial()
{
    static_assert(N >= 0, "factorial(): N must be non-negative")
    int total {1};
    for (int i {1}; i <= N; ++i)
    {
        total *= i;
    }
    return total
}

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    factorial<-3>(); // should fail to compile

    return 0;
}
```

## Notes

### Non-Type Template Parameters

**Non-Type Template Parameter**: A template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument

A non-type template parameter can be any of the followng types:
- Integral type
- Enumeration type
- `std::nullptr_t`
- A floating point type (since C++20)
- A pointer or reference to an object
- A pointer or reference to a function
- A pointer or reference to a member function
- A literal class type (since C++20)

### Defining our own non-type template parameters

Example that uses an int non-type template parameter

```cpp
#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}
```

```shell
5
```

In the angled brackets, we're defining a non-type template parameter named `N` that will be placeholder for a value of type `int`.

Our call to `print()` uses `5` as the non-type template argument.
- When the compiler sees this call, it will instantiate a function that looks like

```cpp
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
```

Much like `T` is typically used as the name for the first type template parameter, `N` is conventionally used as the name of an int non-type template parameter

### What are non-type template parameters useful for?

As of C++20, function parameters cannot be constexpr

If we have a function like:
```cpp
#include <cassert>
#include <cmath> // for std::sqrt
#include <iostream>

double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}
```

Because `-5.8` is a literal, it would be better if we could static_assert so that errors such as this one would be caught at compile-time

`static_assert` requires a constant expression, and function parameters can't be constexpr.

If we changed the function parameter to a non-type template parameter instead, we can do exactly as we want

```cpp
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```

This version fails to compile. When the compiler encounters `getSprt<-5.0>()`, it will instantiate and call a function that looks something like this

```cpp
template <>
double getSqrt<-5.0>()
{
    static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
        return std::sqrt(-5.0);

    return 0.0;
}
```

The static_assert condition is false, so the compiler asserts out

### Implicit conversions for non-type template arguments

Certain non-type template arguments can be implicitly converted in order to match a non-type template parameter of a different type

```cpp
#include <iostream>

template <int N> // int non-type template parameter
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // no conversion necessary
    print<'c'>(); // 'c' converted to type int, prints 99

    return 0;
}
```

`c` is converted to an `int` in order to match the non-type template parameter of function template `print()`

Only certain types of constexpr conversions are allowed. Most common types include:
- Interal promotion
- Integral conversion
- User-defined conversions
- Lvalue to rvalue conversion (some variable `x` to the value of `x`)

This list is less permissive than the type of implicit conversions allowed for list initialization

Unlike with normal functions, the algorithm for matching function template calls to function template definitions is not sophisticated, and certain matches are not prioritized over others based on the type of conversion required

### Type deduction for non-type template parameters using `auto` C++17

As of C++17, non-type template parameters may use `auto` to have the compiler deduce the non-type template parameter from the template argument

```cpp
#include <iostream>

template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`

    return 0;
}
```

Produce the expected result

```shell
5
c
```

# 11.10 - Using Function templates in multiple files

## Notes

Consider the following program, which doesn't work correctly

```cpp
// main.cpp
#include <iostream>

template <typename T>
T addOne(T x); // function template forward declaration

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

```cpp
// add.cpp
template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}
```

If `addOne` were a non-template function, this program would be fine. But we get a linker error iinstead

In `main.cpp` we call `addOne<int>` and `addOne<double>`
- Since the compiler can't see the definition for function template `addOne`, it can't instantiate those funcitons inside `main.cpp`
- It sees the forward declaration for `addOne`, and will assume those functions exist elsewhere and will be linked in later

It will see the definition for function template `addONe`, there are no uses of this template in `add.cpp`, so the compiler will not instantiate anything

The linker is unable to connect the call to `add<int>` and `addOne<double>` in `main.cpp` to the actual funtions, because those funcitons were never instantiated


Most conventional way to address this is to put all your template code in a header file instead

```cpp
// add.h
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif
```

```cpp
// main.cpp
#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
Any files that need access to the template can #include the relevant header, and the template definition will be copied by the preprocessor into the source file

Doesn't violate ODR, as ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files

If a function is instantiated in multiple files, how does that not cause a violation?
- Functions implicitly instantiated from templates are implicitly inline.
- Inline functions can be defined in multiple files, so long as the definition is identical in each

Another example of a function template being placed in a header file

```cpp
// max.h
#ifndef MAX_H
#define MAX_H

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

#endif
```

```cpp
// foo.cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo()
{
	std::cout << max(3, 2) << '\n';
}
```

```cpp
// main.cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

int main()
{
    std::cout << max(3, 5) << '\n';
    foo();

    return 0;
}
```

Best Practice: Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed
- Allows the compiler to see the full template definition and insantiated the template when needed

# 11.x - Chapter 11 summary and quiz

## Review

- **Function Overloading**: Allows us to create multiple functions with the same name, so long as each identically named function has different set of parameter types
- **Overload Resolution**: When a function call is made to function that has been overloaded, the compiler will try to match the function call to the appriorpriate overload based on the arguments used in the function call
- **Ambiguous Match**: Occurs when the compiler finds 2+ functions that can match a function call to an overloaded function and can't determine which one is best
- **Default Argument**: A default value provided for a function parameter
- **Function Template**: Allow us to create a function-like definitio that serves as a pattern for creating related functions.
- **Type Template Parameters**: Placeholders for any type we want to be specified later
- **Template Parameter Declaration**: Syntax that tells the compiler we're defining a template and declares the template types
- **Function Template Instantiation**: The process of creating functions from function templates
- **Function Instance**: An instantiated function
- **Template Argument Deduction**: Allows the compiler to deduce the actual type that should be used to instantiate a function from the arguments of the function call
- **Generic Types**: Template types
- **Abbreviated Function Template**: Using auto keyword as parameter type in a normal function
- **Non-Type Template Parameter**: Template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument

## Quiz

1a. What is the output of this program and why?

```cpp
#include <iostream>

void print(int x)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    short s { 5 };
    print(s);

    return 0;
}
```
- `int 5`. It will look for the best match. The best match will use numeric promotion which promotes the short to an int. It then found the print(int x) which is the best option

1b. Why won’t the following compile?

```cpp
#include <iostream>

void print()
{
    std::cout << "void\n";
}

void print(int x=0)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5.0f);
    print();

    return 0;
}
```
The compiler doesn't know if `print();` is calling `print()` or `print(int x=0)`. Since the second has x as a default, it is capable of calling either or. **Default parameters aren't considered for overloaded functions**

1c. Why won't the following compile?

```cpp
#include <iostream>

void print(long x)
{
    std::cout << "long " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5);

    return 0;
}
```
- Neither fuction has a priority in the steps of function overloading. Each are equally possible in numeric conversion.

2. Write a function template named add() that allows the users to add 2 values of the same type. The following program should run:

```cpp
#include <iostream>

// write your add function template here

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

	return 0;
}
```

```shell
5
4.6
```

```cpp
#include <iostream>

// write your add function template here
template <typename T>
T add(T x, T y)
{
    return x + y;
}

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

	return 0;
}
```

Write a function template named mult() that allows the user to multiply one value of any type (first parameter) and an integer (second parameter). The second parameter should not be a template type. The function should return the same type as the first parameter. The following program should run:

```cpp
#include <iostream>

// write your mult function template here

int main()
{
	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	return 0;
}
```

```cpp
#include <iostream>

// write your mult function template here
template <typename T, typename U>
auto mult(T x, U y)
{
    return x * y;
}

int main()
{
	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	return 0;
}
```

Write a function template named sub() that allows the user to subtract two values of different types. The following program should run:

```cpp
#include <iostream>

// write your sub function template here

int main()
{
	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}
```

```cpp
#include <iostream>

// write your sub function template here
template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

int main()
{
	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}
```

3. What is the output of this program and why?

```cpp
#include <iostream>

template <typename T>
int count(T) // This is the same as int count(T x), except we're not giving the parameter a name since we don't use the parameter
{
    static int c { 0 };
    return ++c;
}

int main()
{
    std::cout << count(1) << '\n';
    std::cout << count(1) << '\n';
    std::cout << count(2.3) << '\n';
    std::cout << count<double>(1) << '\n';

    return 0;
}
```

```shell
1
2
1
2
```

The first count will create a count function of `int count(int)`, then the static int `c` is initialized and incremented to 1. The second count increments it to 2. But the third count creates a new function of `int count(double)`, creating its own static int `c` which is incremented to 1. The last count calls `int count(double)` and increments it to 2.

4. What is the output of this program?

```cpp
#include <iostream>

int foo(int n)
{
    return n + 10;
}

template <typename T>
int foo(T n)
{
    return n;
}

int main()
{
    std::cout << foo(1) << '\n'; // #1 Uses the non template function

    short s { 2 };
    std::cout << foo(s) << '\n'; // #2 Uses a template function with type short

    std::cout << foo<int>(4) << '\n'; // #3 Using <> makes it use a template function, with type int

    std::cout << foo<int>(s) << '\n'; // #4 Using <int> makes it use a template function

    std::cout << foo<>(6) << '\n'; // #5 Using <> only matches function templates

    return 0;
}
```

```shell
11 
2
4
2
6
```