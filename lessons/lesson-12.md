# 12.1 - Introduction to compound data types

## Notes

### Compound data types

**Compound Data Types**: Types that are defined in terms of other existing data types
- Have additional properties and behaviors that make them useful for solving certain types of problems

C++ supports the following compound types:
- Functions
- C-Style Arrays
- Pointer types:
  - Pointer to object
  - Pointer to function
- Pointer to member types:
  - Pointer to data member
  - Pointer to member function
- Reference types:
  - L-Value References
  - R-Value References
- Enumerated types:
  - Unscoped enumerations
  - Scoped enumerations
- Class Types:
  - Structs
  - Classes
  - Unions

**Class Type**: A type that is a struct, class, or union

# 12.2 - Value Categories (lvalues and rvalues)

## Notes

Besides producing values and side effects, expressions can evaluate to objects or functions

### The properties of an expression

To help determine how expressions should evaluate and where they can be used, all expressions in C++ have 2 properties: a type and a value category

### The type of an expression

The type of an expression is equivalent to the type of the value, object, or function that results from the evaluated expression

```cpp
int main()
{
    auto v1 { 12 / 4 }; // int / int => int
    auto v2 { 12.0 / 4 }; // double / int => double

    return 0;
}
```

`v1`, the compiler will determine that a division with 2 `int` operands will produce an `int` result
- `int` is the type of this expression
`v2`, compiler determines with a `double` and an `int` that it will produce a `double`
- `double` is the type of this expression

Compiler can use the type of an expression to determine whether an expression is valid in a given context

```cpp
#include <iostream>

void print(int x)
{
    std::cout << x << '\n';
}

int main()
{
    print("foo"); // error: print() was expecting an int argument, we tried to pass in a string literal

    return 0;
}
```

`print(int)` is exprecting an int parameter. The type of the expression we're passing in does not match.
- No conversion can be found
- Compiler error results

### The value category of an expression

```cpp
int main()
{
    int x{};

    x = 5; // valid: we can assign 5 to x
    5 = x; // error: can not assign value of x to literal value 5

    return 0;
}
```

One of these value statements is value, and one is not. How does the compiler know chich expressions can legally appear on either side of an assignment statement?

**Value Category**: Indicates whether an expression resolves to a value, a function, or an object of some kind

Prior to C++11, 2 value categories: `lvalue` and `rvalue`

In C++11, 3 additional value categories: `glvalue`, `prvalue`, and `xvalue` to support a new feature called `move semantics`

### Lvalue and rvalue expressions

**lvalue**: Short for "left value" or "locator value", an expression that evaluates to an identifiable object or function

"identify" is used by the C++ standard, but not well-defined
- An entity that has an identify can be differentiated from other similar entities

Entities with identities can be accessed via an identifier, reference, or pointer, and typically have a lifetime longer than a single expression/statement

```cpp
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}
```

Expression `x` is an lvalue as it evaluates to variable `x`

lvalues come in 2 subtypes:
- **Modifiable lvalues**: An lvalue whose value can be modified
- **Non-modifiable lvalue**: An lvalue whose value can't be modified

**rvalue**: Short for "right value", an expression that is not an lvalue.
- rvalue expressions evaluate to a value
- lietrals and return values of functions and operators that return by value
- Aren't identifiable, they have to be used immediately
- Only exist within the scope of the expression in which they are used

```cpp
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```

### Value categories and operators

Binary `operator+` expectsits operands to be rvalues

```cpp
#include <iostream>

int main()
{
    std::cout << 1 + 2; // 1 and 2 are rvalues, operator+ returns an rvalue

    return 0;
}
```

An assignment operator requires its left operand to be a modifiable lvalue expression
- Why ` 5 = x` doesn't work

Lvalue to rvalue conversion

```cpp
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```
Why does this work?

In cases where an rvalue is expected but an lvalue is provided, the lvalue undergoes lvalue-to-rvalue conversion so that it can e used in such context
- lvalue is evaluated to produce its value, which is an rvalue

lvalue expression `y` undergoes lvalue to rvalue conversion, which evaluates `y` to produce rvalue `2`, which then assigned to `x`

### How to differentiate lvalues and rvalues

Rule of thumb to identify lvalue and rvalue expressions
- Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression
- Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression

# 12.3 - Lvalue references

### Questions

1. Determine what values the following program prints by yourself (do not compile the program).

```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n';

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << ref << '\n';

    x = 4;

    std::cout << x << ref << '\n';

    return 0;
}
```

```shell
11
22
44
```

## Notes

**Reference**: An alias for an axisting object
- Once defined, any operation on the refernce is applied to the object being referenced
- Can use a reference to read or modify the object being referenced

C++ contains 2 types of references
- lvalue references
- rvalue references

### Lvalue references

**Lvalue reference**: An alias for an existing lvalue (like a variable)
- The type of a reference determmines what type of object it can reference
- Identified by use of a & in the type specifier:

```cpp
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```

**Reference Type**: A type that specifies a reference (`int&`)\
**Referenced Type**: The type that can be referenced (`int`)

### Lvalue reference variables

**Lvalue refernce variable**: A variable that acts as a reference to an lvalue

```cpp
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```

The type `int&` defines `ref` as an lvalue reference to an int.We then initialize with lvaue expression `x`.
- `ref` and `x ` can be used synonymously

```shell
5
5
```

Doesn't matter whether the ampersand is "attached" to the type name (`int& ref`) or the variable's name (`int &ref`), and which you choose is a matter of style
- Modern programmers tend to prefer to attach to the type

### Modifying values through a non-const lvalue reference

Can use a reference to modify the value of the object being referenced

```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```

```shell
55
66
77
```

### Reference initialization

**Reference Initialization**: References are initialized using this form of initialization

```cpp
int main()
{
    int& invalidRef;   // error: references must be initialized

    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    return 0;
}
```

When a reference is initialized with an object, we say it is **bound** to that object
- Process by which such a refernce is bound is called **reference binding**

**Referent**: The object being referenced

Non-const lvalue references can only be bound to a *modifiable* lvalue

```cpp
int main()
{
    int x { 5 };
    int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue

    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    return 0;
}
```

### A reference will (usually) only bind to an object matching its reference type

Most cases, a reference will only bind to an object whose type matches the reference type
- Som exceptions to the rule
- The compiler will try to implcitly convert the object to the referenced type and then bind the reference to that

```cpp
int main()
{
    int x { 5 };
    int& ref { x };            // okay: referenced type (int) matches type of initializer

    double d { 6.0 };
    int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
    double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)

    return 0;
}
```

### References can't be reseated (changed to refer to another object)

Once initialized, a refernce in C++ cannot be **reseated**
- It cannot be changed to reference another object
- Will compile and run, but not function as expected

```shell
#include <iostream>

int main()
{
    int x { 5 };
    int y { 6 };

    int& ref { x }; // ref is now an alias for x

    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!

    std::cout << x << '\n'; // user is expecting this to print 5

    return 0;
}
```

```shell
6
```

### Refernce scope and duration

Reference variables follow the same scoping and duration rules that normal variables do

### References and refernts have independent lifetimes

Liftime of a reference and its referent are independent\
Both are true:
- A reference can be destroyed before the object it is referencing
- The object being referenced can be destroyed before the reference

```cpp
#include <iostream>

int main()
{
    int x { 5 };

    {
        int& ref { x };   // ref is a reference to x
        std::cout << ref << '\n'; // prints value of ref (5)
    } // ref is destroyed here -- x is unaware of this

    std::cout << x << '\n'; // prints value of x (5)

    return 0;
} // x destroyed here
```

```shell
5
5
```

### Dangling references

**Dangling Reference**: When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists
- Accessing a dangling reference leads to undefined behavior

### References aren't objects

A reference is not required to exist or occupy storage
- The compiler will optimize references away by replacing all occurrences of a reference with the referent
- Isn't always possible, refernces may take storage

Because references aren't objects, they can't be used anywhere an object is required
- Can't have a reference to a reference, since an lvalue reference must reference an identifier
- Cases where you need a referencee that is an object or a reference that can be reseated
  - `std::reference_wrapper` provides a solution

# 12.4 - Lvalue references to const

## Notes

### Lvalue reference to const

**Const Reference**: By using the `const` keyword when declaring an lvalue reference, we ctell an lvalue reference to treat the obect it is referencing as const

```cpp
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    return 0;
}
```

Can be used to access but not odify the value being referenced

```cpp
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
```

### Initializing an lvalue reference to const with a modifiable lvalue

Lvalue reference to const can also bind t modifiable lvalue
- The object being referenced is treated as const when accessed through the reference

```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
```

### initializing an lvalue reference to const with an rvalue

Lvalues references to const can also bind to rvalues

```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // okay: 5 is an rvalue

    std::cout << ref << '\n'; // prints 5

    return 0;
}
```

A temporary object is created and initialized with the rvalue, the reference to const is bound to that temporary object

### initializing an lvalue reference to const with a value of a different type

Lvalue references to const can even bind to values of a different type, so long as those values can be implicitly converted to the reference type

```cpp
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
```

A temporary object of type `double` is created and initialized with int `5`. `Const double& r1` is bounded to that temporary double object.

A temporary object of type `int` is created and initialized iwth car value `a`. `Const int& r2` is bound to that temporary int object

When we print r2, it prints as an int rather than a char

### Const references bound to temporary objects extend the lifetime of temporary objects

Temporary objects are normally destroyed at the end of the expression

C++ has a special rule: when a const lvalue reference is *directly* bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference

```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    std::cout << ref << '\n'; // Therefore, we can safely use it here

    return 0;
} // Both ref and the temporary object die here
```

# 12.5 - Pass by lvalue reference

## Notes

Pass By Vale, an argument passed to a function is copied into the function's parameter
- We're making acopy of our argument's value, only to use it briefly and then destroy it

### Some objects are expensive to copy

Class types are usually expensive to copy
- We want to avoid making unecessary copies of objects that are expensive to copy

### Pass by reference

**Pass By Reference**: We declare a function parameter as a reference type rather than as a normal type
- Each reference parameter is bound to the appropriate argument
- The reference acts as an alias for the argument, no copy of the argument is made

```cpp
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
```

When `printValue(x)` is called, lvalue reference parameter `y` is bound to argument `x`.
- Binding a reference is always inexpensive, no copy of `x` needs to be made
- It's accessing the actual argument `x` rather than a copy of `x`

### Pass by reference allows us to change the value of an argument

Since a reference acts identically to the object being referenced, when using pass by reference, any changes made to the reference parameter *will* affect the argument

```cpp
#include <iostream>

void addOne(int& y) // y is bound to the actual object x
{
    ++y; // this modifies the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has been modified

    return 0;
}
```

```shell
value = 5
value = 6
```

The ability for functions to modify the value of arguments passed in can be useful

### Pass by reference can only accept modifiable lvalue arguments

Because a reference to a non-const value can only bind to a modifiable lvalue, pass by reference only works with arguments that are modifiable lvalues.
- Significantly lmits the usefulness of pass by reference to non-const
- We can not pass const variables or literals

```cpp
#include <iostream>

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue

    printValue(5); // error: 5 is an rvalue

    return 0;
}
```

# 12.6 - Pass by const lvalue reference

## Notes

A reference to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues
- If we make a reference parameter const, then it will be able to bind to any type of argument

```cpp
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```

Offers the same primary benefits as pass by non-const reference, while also guaranteeing that the function can **not** change the value being referenced

```cpp
void addOne(const int& ref)
{
    ++ref; // not allowed: ref is const
}
```

### Passing arguments of different type to a const lvalue reference parameter

Const lvalue reference can bind to a value of a different type, as long as the value is convertible ito the type of the reference

Primary motivation for allowing this is so that we can pass a value as an argument to either a value parameter or a const reference parameter in exactly the same way

```cpp
#include <iostream>

void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double& d)
{
    std::cout << d << '\n';
}

int main()
{
    printVal(5); // 5 converted to temporary double, copied to parameter d
    printRef(5); // 5 converted to temporary double, bound to parameter d

    return 0;
}
```

If a conversion occurs first, this will typically result in a copy being made, which can be suboptimal

### Mixing pass by value and pass by reference

```cpp
#include <string>

void foo(int a, int& b, const std::string& c)
{
}

int main()
{
    int x { 5 };
    const std::string s { "Hello, world!" };

    foo(5, x, s);

    return 0;
}
```

### When to use pass by value vs pass by reference

Rule of thumb that will serve you well in the majority of the cases
- Fundamental types and enumerated types are cheap to copy, so they are pass by value
- Class types can be expensive to copy, so they are typically passed by const reference

### For function parameters, prefer `std::string_view` over `const std::string&` in most cases

`std::string_view` is the better choice, it can handle a wider range of argument types efficiently
- Also allows the caller to pass in a substring without having to copy that substring into its owns tring first

```cpp
void doSomething(const std::string&);
void doSomething(std::string_view);   // prefer this in most cases
```

Few cases where using a `const std::string&` parameter may be more appropriate:
- Using C++14 or older, `std::string_view` isn't available
- Function needs to call some other function that takes a C-style string or `std::string parameter`, then `const std::string&` may be a better choice
  - `std::string_view` is not guaranteed to be null-terminated
  - Does not efficiently convert back to a `std::string`

# 12.7 - Introduction to Pointers

## Questions

1. What values does this program print? Assume a short is 2 bytes, and a 32-bit machine.

```cpp
#include <iostream>

int main()
{
	short value{ 7 }; // &value = 0012FF60
	short otherValue{ 3 }; // &otherValue = 0012FF54

	short* ptr{ &value }; // ptr to 7

	std::cout << &value << '\n';
	std::cout << value << '\n';
	std::cout << ptr << '\n';
	std::cout << *ptr << '\n';
	std::cout << '\n';

	*ptr = 9;

	std::cout << &value << '\n';
	std::cout << value << '\n';
	std::cout << ptr << '\n';
	std::cout << *ptr << '\n';
	std::cout << '\n';

	ptr = &otherValue;

	std::cout << &otherValue << '\n';
	std::cout << otherValue << '\n';
	std::cout << ptr << '\n';
	std::cout << *ptr << '\n';
	std::cout << '\n';

	std::cout << sizeof(ptr) << '\n';
	std::cout << sizeof(*ptr) << '\n';

	return 0;
}
```

```shell
0012FF60
7
0012FF60
7

0012FF60
9
0012FF60
9

0012FF54
3
0012FF54
3

4
2
```

2. What’s wrong with this snippet of code?

```cpp
int v1{ 45 };
int* ptr{ &v1 }; // initialize ptr with address of v1

int v2 { 78 };
*ptr = &v2;     // assign ptr to address of v2
```

We dereference the ptr, now looking at the value itself and tried to assign the address to type int which is invalid

## Notes

A normal variable:

```cpp
char x {}; // chars use 1 byte of memory
```

A piece of memory from RAM will be assigned to this object.
- Say variable `x` is assigned memory address `140`
- When we use variable `x` in an expression or statement, the program will go to memory address `140` to access the value stored there

This is also true with reference
```cpp
int main()
{
    char x {}; // assume this is assigned memory address 140
    char& ref { x }; // ref is an lvalue reference to x (when used with a type, & means lvalue reference)

    return 0;
}
```

`ref` acts like an alias for `x`, whenever we use `ref`, the program will go to memory address `140`

### The address-of operator (&)

**Address-of Operator**: Retunrs the memory address of its operand

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    return 0;
}
```

```shell
5
0027FEA0
```

For objects that use more than 1 byte of memory, address-of will return the memory address of the first byte used by the object

The & symbol tends to cause confusion because it has different meanings depending on context
- When following a type name, & denotes an lvalue reference: `int& ref`
- When used in a unary context in an expression, & is the address-of operator `std::cout << &x`
- When used in a binary context in an expression &, is the BITWISE AND operator `std::cout << x & y`

### Dereference Operator (*)

The most useful thing we can do with an address is access the value stored at that address

**Dereference Operator**: (*), returns the value at a given memory address as an lvalue

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

    return 0;
}
```

```shell
5
0027FEA0
5
```

Getting the memory address of a variable and then immediately dereferencing that address to get a value isn't that useful

### Pointers

**Pointer**: An object that holds a `memory address` as its value
- Allows us to store the address of some other object to use later

**Pointer Type**: A type that specifies a pointer (int *)
- Pointer types are declared using an asterisk

```cpp
int;  // a normal int
int&; // an lvalue reference to an int value

int*; // a pointer to an int value (holds the address of an integer value)
```

```cpp
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer

    return 0;
}
```

Best Practice: When declaring a pointer type, place the asterisk next to the type name

### Pointer initialization

Pointers are not initialized by default\
**Wild Pointer**: A pointer that has not been initialized
- Contain a garbage address, and dereferencing a wild pointer will result in undefined behavior
- You should always initialize your pointers to a known value

```cpp
int main()
{
    int x{ 5 };

    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    return 0;
}
```

When we initialize or assign a value to a pointer, that value has to be an address
- Pointers are used to hold the address of another variable

We can use the dereference operator (*) to access the value at that address

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x

    int* ptr{ &x }; // ptr holds the address of x
    std::cout << *ptr << '\n'; // use dereference operator to print the value at the address that ptr is holding (which is x's address)

    return 0;
}
```

```shell
5
5
```

The type of the pointer has to match the type of the object being pointed to

```cpp
int main()
{
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object

    return 0;
}
```

Initializing a pointer with a literal value is disallowed

### Pointers and assignment

We can use assignment with pointers in 2 different ways:
1. Change what the pointer is pointing at
2. Change the value being pointed at

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr initialized to point at x

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

    int y{ 6 };
    ptr = &y; // // change ptr to point at y

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)

    return 0;
}
```

```shell
5
6
```

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // initialize ptr with address of variable x

    std::cout << x << '\n';    // print x's value
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

    std::cout << x << '\n';
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    return 0;
}
```

```shell
5
5
6
6
```

### Pointers behave much like lvalue references

Pointers and lvalue references behave similarly

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int& ref { x };  // get a reference to x
    int* ptr { &x }; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    return 0;
}
```

```shell
555
666
777
```


Pointers and references both provide a way to indirectly access another object

The primary difference is that with pointers, we need to explicitly get the address to point at, and have to explicitly dereference the pointer to get the value
- With references, the address-of and dereference happens implicitly

Differences between pointers and references worth mentioning:
- References must be initialized, pointers are not required to be initialized (but should be)
- References are not objects, pointers are
- References can not be reseated, pointers can change what they're pointing at
- References must always be bound to an object, pointers can point to nothing
- References are "safe", pointers are inherently dangerous

### The address-of operator returns a pointer

The address of operator (&) doesn't return the address of its operand as a literal.
- It returns a pointer to the operand
- Given variable `int x`, `&x` returns `int*`, the address of x.

### The size of pointers

Dependent upon the architecture the executable is compiled for
- 32-bit executable uses 32-bit memory addresses, pointer on a 32-bite machine is 32-bits (4 bytes)
- 64-bit executable, a pointer would be 64 bits (8 bytes)
  - True regardless of the object being pointed to

### Dangling pointers

**Dangling Pointers**: A pointer that is holding the address of an object that is no longer valid
- Due to being destroyed

Dereferencing a dangling pointer will lead to undefined behavior

Any other use of an invalid pointer *value* has implementation-defined behavior
- You can assign an invalid pointer a new value, such as nullptr
- Any other operation that use the invalid pointer's value will yield implmentation defined behavior

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x };

    std::cout << *ptr << '\n'; // valid

    {
        int y{ 6 };
        ptr = &y;

        std::cout << *ptr << '\n'; // valid
    } // y goes out of scope, and ptr is now dangling

    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer

    return 0;
}
```

### Conclusion

Pointers are variables that hold a memory address
- Can be dereferenced using the dereference operator to retrieve the value at the address they are holding
- Dereferencing a wild/dangling pointer will result in undefined behavior and will probably crash your application

Pointers are both more flexible than references and more dangerous

# 12.8 - Null Pointers

## Questions

1a. Can we determine whether a pointer is a null pointer or not? If so, how?
- Yes `if (ptr == nullptr)` or even `if (ptr)`.

1b. Can we determine whether a non-null pointer is valid or dangling? If so, how?
- No

2. For each subitem, answer whether the action described will result in behavior that is: predictable, undefined, or possibly undefined. If the answer is “possibly undefined”, clarify when.

Assigning the address of an object to a non-const pointer
- Predictable

Assigning nullptr to a pointer
- Predictable

Dereferencing a pointer to a valid object
- Predictable

Dereferencing a dangling pointer
- undefined

Dereferencing a null pointer
- undefined

Dereferencing a non-null pointer
- possibly undedefined. Don't know if the non-null pointer is dangling

3. Why should we set pointers that aren’t pointing to a valid object to ‘nullptr’?
- To reduce the number of dangling pointers present. Having a nullptr is better and can easily be checked and handled

## Notes

### Null Pointers

**Null Value**: A special value that means something has no value
- Pointers can hold a null value
- Pointer is not point at anything

**Null Pointer**: A pointer that points to nothing

```cpp
int main()
{
    int* ptr {}; // ptr is now a null pointer, and is not holding an address

    return 0;
}
```

A pointer that is initially set to null can later be changed to point at a valid object

```cpp
#include <iostream>

int main()
{
    int* ptr {}; // ptr is a null pointer, and is not holding an address

    int x { 5 };
    ptr = &x; // ptr now pointing at object x (no longer a null pointer)

    std::cout << *ptr << '\n'; // print value of x through dereferenced ptr

    return 0;
}
```

### The nullptr keyword

**nullptr**: Keyword reprsents a null pointer literal
- Can use `nullptr` to explicitly initialize or assign a pointer a null value

```cpp
int main()
{
    int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer

    int value { 5 };
    int* ptr2 { &value }; // ptr2 is a valid pointer
    ptr2 = nullptr; // Can assign nullptr to make the pointer a null pointer

    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter

    return 0;
}
```

Best Practice: Use `nullptr` when you need a null pointer literal for initialization, assignment, or passing a null pointer to a function

### Dereferencing a null pointer results in undefined behavior

Dereferencing a null pointer also leads to undefined behavior
- May crash your program

Accidentally dereferencing null and dangling pointers is one of the most common mistakes C++ programmers make

### Checking for null pointer

We can use a conditional to test Boolean values for `true` or `false`.
- Can use a conditional to test whether a pointer has a `nullptr` or not

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    if (ptr == nullptr) // explicit test for equivalence
        std::cout << "ptr is null\n";
    else
        std::cout << "ptr is non-null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence

    return 0;
}
```

Compare the pointer itself, do not dereference.

Pointers will also implicitly convert to Boolean values
- A null pointer converts to `false`
- A non-null pointer converts to `true`
- Skip explicitly test for nullptr and just use the implicit conversion to boolean to test whether a pointer is a null pointer

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    // pointers convert to Boolean false if they are null, and Boolean true if they are non-null
    if (ptr) // implicit conversion to Boolean
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit conversion to Boolean

    return 0;
}
```

### Use nullptr to avoid dangling pointers

We need to ensure our code does not dereference a nul pointer
- can avoid by using a conditional to ensure a pointer is non-null before trying to dereference it

```cpp
// Assume ptr is some pointer that may or may not be a null pointer
if (ptr) // if ptr is not a null pointer
    std::cout << *ptr << '\n'; // okay to dereference
else
    // do something else that doesn't involve dereferencing ptr (print an error message, do nothing at all, etc...)
```

What about dangling pointers?
- There is no way to detect whether a pointer is dangling, we need to avoid having any dangling pointers in our program in the first place
- Ensure that any pointer that is not point at a valid object is set to `nullptr`

Avoiding dangling pointers isn't easy, when an object is destroyed, any pointers to that object will be left dangling
- Such pointers are *not* nulled automatically

### Legacy null pointer literals: 0 and NULL

Older code, may see 2 other literal values used instead

`0`: in the context of pointers, `0` is specially defined to mean a null value
- The only time you can assign an integral literal to a pointer

```cpp
{
    float* ptr { 0 };  // ptr is now a null pointer (for example only, don't do this)

    float* ptr2; // ptr2 is uninitialized
    ptr2 = 0; // ptr2 is now a null pointer (for example only, don't do this)

    return 0;
}
```

The preprocessor macro `NULL`, defined in `<stddef>` header
- Inherited from C, commonly used to indicate a null pointer

Both should be avoided in modern C++

### Favor references over pointers whenever possible

Pointers and references both give us the ability to access some other object indirectly

Pointers hav ethe additional ability of being able to change what theya re pointing at, and to be pointed to null
- Inherently dangerous

# 12.9 - Pointers and Const

## Notes

What happens if the value we want to point at is const?

```cpp
int main()
{
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: cannot convert from const int* to int*

    return 0;
}
```

Can't set a normal pointer to point at a const variable

### Pointer to const value

**Pointer to a Const Value**: (**Pointer To Const**) A (non-const) pointer that points to a const value

To declare a pointer to a const value, use the `const` keyword before the pointer's data type:

```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // okay: ptr is pointing to a "const int"

    *ptr = 6; // not allowed: we can't change a const value

    return 0;
}
```

Because a pointer to const is not const itself, we can change what the pointer is pointing at by assigning the pointer to a new address

```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // ptr points to const int x

    const int y{ 6 };
    ptr = &y; // okay: ptr now points at const int y

    return 0;
}
```

A pointer to const can point to non-const variables too. 
- A pointer to const treats the value being pointed to as constant, regardless of whether the object at that address was initially defined as const or not.

```cpp
int main()
{
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"

    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    return 0;
}
```

### Const pointers

**Const Pointer**: A pointer whose address can not be changed after initialization

Use the `const` keyword after the asterisk in the pointer declaration

```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // const after the asterisk means this is a const pointer

    return 0;
}
```

`ptr` is a const pointer to a non-const int value

A const pointer must be initialized upon definition, and this value can't be changed via assignment

```cpp
int main()
{
    int x{ 5 };
    int y{ 6 };

    int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
    ptr = &y; // error: once initialized, a const pointer can not be changed.

    return 0;
}
```

Because the *value* being pointed to is non-const, it is possible to change the value being pointed to via dereferencing the const pointer

```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // ptr will always point to x

    *ptr = 6; // okay: the value being pointed to is non-const

    return 0;
}
```

### Const pointer to a const value

**Const Pointer to a const value**: Use the `const` keyword both before the type and after the asterisk

```cpp
int main()
{
    int value { 5 };
    const int* const ptr { &value }; // a const pointer to a const value

    return 0;
}
```

A const pointer to a const value can not have its adadress changed, nor can the value it is pointing to be changed through the pointer
- Only be dereferenced to get the value it is pointing at

# 12.10 - Pass by Address

## Notes

```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str

    return 0;
}
```

When we pass arguement `str` by value, the function receives a copy of the argument
- Any changes to `val` are made to the copy, not the original argument

When we pass argument `str` by reference, the reference parameter is bound to the actual argument
- Avoids making a copy of the argument
- Because it is const, we are not allowed to change `ref`
  - If `ref` were non-const, any changes we made to `ref` would change `str`

Both cases provided the actual object `str` to be passed as an argument

### Pass by address

**Pass By Address**: Instead of providing an object as an argument, the caller provides an object's address (via a pointer)
- This pointer (holding the address of the object) is copied into a pointer parameter of the called function
- The fuction can then dereference that pointer to access the object whose address was passed

```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
```

We pass in the address of `str`, using the address-of operator
- `&str` will create a pointer holding the address of `str
- The address is then *copied* into the function parameter

If we already had a pointer variable holding the address of `str`, we could use that instead

```cpp
int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    std::string* ptr { &str }; // define a pointer variable holding the address of str
    printByAddress(ptr); // pass str by address, does not make a copy of str

    return 0;
}
```

### Pass by address doesn't make a copy of the object being pointed to

When we pass a `std::string` by address, we're not copying the actual `std::string` object, we're copying the pointer from the caller to the caled function
- Pass by address is fast and avoids making a copy of the argument object

### Pass by address allows the function to modify the argument's value

Because this is the address of the actual argument object being passed, if the function parameter is a pointer to non-const, the function can modify the argument via the pointer parameter

```cpp
#include <iostream>

void changeValue(int* ptr) // note: ptr is a pointer to non-const in this example
{
    *ptr = 6; // change the value to 6
}

int main()
{
    int x{ 5 };

    std::cout << "x = " << x << '\n';

    changeValue(&x); // we're passing the address of x to the function

    std::cout << "x = " << x << '\n';

    return 0;
}
```

```shell
x = 5
x = 6
```

If a function is not supposed to modify the object being passed in, the funciton parameter should be made a pointer-to-const:

```cpp
void changeValue(const int* ptr) // note: ptr is now a pointer to a const
{
    *ptr = 6; // error: can not change const value
}
```

We also typically don't const pointer function parameters. Make 2 assertions:
- A `const` keyword used to make a pointer function parameter a const pointer provides little value
- A `const` keyword used to differentiate a pointer-to-const from a pointer-to-non-const that can modify the object passed in is significant

If we only used non-const pointer function parameters, then all uses of `const` are significant
- As soon as we start using `const` for const pointer function parameters, then it becomes more difficult to determine whether a given use of `const` is significant or not
- Harder to notice pointer-to-non-const paramaters

Prefer pointer to const function parameters over pointer to non const fucntion parameters, unless the function needs to modify the object passed in
- Do not mae function parameters const pointers unless there is some specific reason to do so

### Null Checking

```cpp
#include <iostream>

void print(int* ptr)
{
	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };
	print(&x);

	int* myPtr {};
	print(myPtr);

	return 0;
}
```

I the call to `print(myPtr)`, `myPtr` is a null pointer, so function parameter `ptr` will also be a null pointer

When passing a parameter by address, care should be taken to ensure the pointer is not a null ponter bfore you dereference the value

```cpp
#include <iostream>

void print(int* ptr)
{
    if (ptr) // if ptr is not a null pointer
    {
        std::cout << *ptr << '\n';
    }
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

In most cases, it is more effective to test whether the function parameter is null as a precondition, and handle the negative case immediately

```cpp
#include <iostream>

void print(int* ptr)
{
    if (!ptr) // if ptr is a null pointer, early return back to the caller
        return;

    // if we reached this point, we can assume ptr is valid
    // so no more testing or nesting required

    std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

### Prefer pass by (const) reference

Pass by reference has the same benefits as pass by address without the risk of inadvertently dereferencing a null pointer

Pass by const reference has a few other advantages over pass by address
- Because an object being passed by address must have an address, only lvalue can be passed by address
  - Pass by const reference is more flexible, as it can accept ravlues too
- The syntax for pass by reference is natural, as we can just pass in literals or objects
  - Pass by address, our code ends up littered with & and *

Most things that can be done with pass by address are better accomplished through other methods

# 12.11 - Pass by address (part 2)

## Notes

### Pass by address for "optional" arguments

One of the more common uses for pass by address is to allow a function to accept an "optional" argument

```cpp
#include <iostream>

void printIDNumber(const int *id=nullptr)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(&userid); // we know the user's ID now

    return 0;
}
```

In many cases, function overloading is a better alternative to achieving the same result:

```cpp
#include <iostream>

void printIDNumber()
{
    std::cout << "Your ID is not known\n";
}

void printIDNumber(int id)
{
    std::cout << "Your ID is " << id << "\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(userid); // we know the user is 34

    printIDNumber(62); // now also works with rvalue arguments

    return 0;
}
```

### Changing what a pointer parameter points at

When we pass an address to a function, that address is copied from the argument into the pointer parameter.

```cpp
#include <iostream>

// [[maybe_unused]] gets rid of compiler warnings about ptr2 being set but not used
void nullify([[maybe_unused]] int* ptr2)
{
    ptr2 = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```

The program print

```shell
ptr is non-null
ptr is non-null
```

Changing the address held by the pointer parameter had no impact on the address held by the argument

### pass by address by reference

We can pass a normal variable by reference, we can also pass pointers by reference

```cpp
#include <iostream>

void nullify(int*& refptr) // refptr is now a reference to a pointer
{
    refptr = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```

```shell
ptr is non-null
ptr is null
```

### std::nullptr_t

Since `nullptr` can be differentiated from int values, it must have a different type
- `nullpyt` has type `std::nullptr_t` defined in `<cstddef>`
- Can hold one value: `nullptr`

Useful in 1 situation: If we want to write a function that accepts only a `nullptr` literal argument, we can make the parameter a `std::nullptr_t`

```cpp
#include <iostream>
#include <cstddef> // for std::nullptr_t

void print(std::nullptr_t)
{
    std::cout << "in print(std::nullptr_t)\n";
}

void print(int*)
{
    std::cout << "in print(int*)\n";
}

int main()
{
    print(nullptr); // calls print(std::nullptr_t)

    int x { 5 };
    int* ptr { &x };

    print(ptr); // calls print(int*)

    ptr = nullptr;
    print(ptr); // calls print(int*) (since ptr has type int*)

    return 0;
}
```

The one case that might be a little confusing is when we call `print(ptr)` when `ptr` is holding the value `nullptr`
- Function overloading matches on types, not values, and `ptr` has type `int*`. 
- `print(std::nullptr_t)` isn't in consideration

### There is only pass by value

While the computer can often optimize references away entirely, there are cases where this is not possible and a reference is actually needed.
- Normally impemented by the compiler using pointers
- Behind the scenes, pass by reference is essentially just a pass by address

Pass by address just copies an address from the caller to the called function, which is just passing an address by value

C++ really passes everything by value

# 12.12 - Return by reference and return by address

## Notes

### Return by Reference

In cases where we're passing a class type back to the caller, we may want to return by reference instead

**Return By Reference**: Returns a reference that is bound to the object being retured, which should avoid making a copy of the return value
- Simply define the return value of the funciton to be a reference type

```cpp
std::string&       returnByReference(); // returns a reference to an existing std::string (cheap)
const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)
```

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName { "Calculator" }; // has static duration, destroyed at end of program

    return s_programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    return 0;
}
```

Because `getProgramNmae()` returns a const reference, the function will return a const reference for `s_programName` making a copy.
- That const reference can then be used by the caller to access the value of `s_programName`

### The object being returned by reference must exist after the function returns

1 major caveat: The programmer *must* be sure that the object being referenced outlives the function returning the reference
- Otherwise the reference will be left dangling and use of that reference will result in undefined behavior

Because `s_programName` has static duration, `s_programName` will exist until the end of the program

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName()
{
    const std::string programName { "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName(); // undefined behavior

    return 0;
}
```

The result of the program is undefined

Most compilers will produce a warning or error if you try to return a local variable by refernce, but compilers sometimes have trouble detecting more complicated cases

### lifetime extension doesn't work across function boundaries

```cpp
#include <iostream>

const int& returnByConstReference()
{
    return 5; // returns const reference to temporary object
}

int main()
{
    const int& ref { returnByConstReference() };

    std::cout << ref; // undefined behavior

    return 0;
}
```

This results in the creation and return of a temporary reference bound to a temporary object holding value `5`.
- The returned reference is copied into a temporary reference in the scope fo the caller
- The temporary object then goes out of scope, leaving the temporary reference in the scope of the caller dangling

Another example:

```cpp
#include <iostream>

const int& returnByConstReference(const int& ref)
{
    return ref;
}

int main()
{
    // case 1: direct binding
    const int& ref1 { 5 }; // extends lifetime
    std::cout << ref1 << '\n'; // okay

    // case 2: indirect binding
    const int& ref2 { returnByConstReference(5) }; // binds to dangling reference
    std::cout << ref2 << '\n'; // undefined behavior

    return 0;
}
```

A temporary object is created to hold value `5`, which function parameter `ref` binds to. The function just returns this reference back to the caller, which then uses the reference to initialize `ref2`.
- Because this is not a direct binding to the temporary object, lifetime extension doesn't apply

### Don't return non-const static local variables by reference

Returning non-const static local variables by reference is fairly non-idiomatic and should be avoided

```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

int main()
{
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << id1 << id2 << '\n';

    return 0;
}```

```shell
22
```

`id1` and `id2` are referencing the same object
- Can be fixed by making `id1` and `id2` normal variables, rather than references so they save a copy of the return value rather than a reference to `s_x`

Best Practice: Avoid returning references to non-const local static variables

Return a const reference to a const local static variable is sometimes done if the local variable being returned by reference is expensive to create and/or initialize

Returning a const reference to a const global variable is also sometimes done as a waay to encapsulate access to a global variable

### Assigning/Initializing a normal variable with a returned reference makes a copy

If a function returns a reference, and that referenced is used to initialize or assign to a non-reference variable, the return value will be copied

```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()

    std::cout << id1 << id2 << '\n';

    return 0;
}
```

The value of the returned reference is copied into the normal variable
- If a program returns a dangling reference, the reference is left dangling before the copy is made
- Leads to unexpected behavior

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // will return a const reference
{
    const std::string programName{ "Calculator" };

    return programName;
}

int main()
{
    std::string name { getProgramName() }; // makes a copy of a dangling reference
    std::cout << "This program is named " << name << '\n'; // undefined behavior

    return 0;
}
```

### It's okay to return reference parameters by reference

If a parameter is passed into a funciton by reference, it's safe to return that parameter by reference

```cpp
#include <iostream>
#include <string>

// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world) << '\n';

	return 0;
}
```

```shell
Hello
```

It's okay for an rvalue passed by const reference to be returned by const reference

When an argument for a const reference parameter is an rvalue, it's okay to return that parameter by const reference
- Rvalues are not destroyed until the end of the full expression in which they are created

```cpp
#include <iostream>
#include <string>

const std::string& foo(const std::string& s)
{
    return s;
}

std::string getHello()
{
    return "Hello"; // implicit conversion to std::string
}

int main()
{
    const std::string s{ foo(getHello()) };

    std::cout << s;

    return 0;
}
```

rvalue is passed by const reference to `foo()` and then returned by const reference back to the caller before it is used to initialize `s`.

### The caller can modify values through the reference

When an argument is passed to a function by non-const refernce, the function can use the reference to modify the value of the argument
- When a non-const reference is returned from a function, the caller can use the reference to modify the value being returned

```cpp
#include <iostream>

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7

    std::cout << a << b << '\n';

    return 0;
}
```

```shell
57
```

### Return by address

**Return By Address**: Works almost identically to return by reference, except a pointer to an object is returned instead of a reference to an object
- Same primary caveat as return by reference: The object being returned by address must outlive the scope ofthe function returning the address

Major advantage of return by address is that we can have the function return `nullptr` if there is no valid object to return

Major disadvantage of return by address is that the caller has to remember to do a `nullptr` check before dereferencing the return value, otherwise a null pointer dereference may occur

Best Practice: Prefer return by reference over return by address unless the ability to return "no object" is important

# 12.13 - In and out parameters

## Notes

A function and its caller communicate with each other via 2 mechanisms: parameters and return values
- Typically we'll pass arguments by value or by const reference, but there are times when we may need to do otherwise

### In Parameters

**In Parameters**: Parameters that are used only for receiving input from the caller

```cpp
#include <iostream>

void print(int x) // x is an in parameter
{
    std::cout << x << '\n';
}

void print(const std::string& s) // s is an in parameter
{
    std::cout << s << '\n';
}

int main()
{
    print(5);
    std::string s { "Hello, world!" };
    print(s);

    return 0;
}
```

Typically passed by value or by const reference

### Out Parameters

**Out Parameter**: A function parameter that is used only for the purpose of returning information back to the caller

```cpp
#include <cmath>    // for std::sin() and std::cos()
#include <iostream>

// sinOut and cosOut are out parameters
void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    // sin() and cos() take radians, not degrees, so we need to convert
    constexpr double pi { 3.14159265358979323846 }; // the value of pi
    double radians = degrees * pi / 180.0;
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}

int main()
{
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees{};
    std::cout << "Enter the number of degrees: ";
    std::cin >> degrees;

    // getSinCos will return the sin and cos in variables sin and cos
    getSinCos(degrees, sin, cos);

    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';

    return 0;
}
```

### Out parameters have an unnatural usage syntax

Out parameters have a few downsides
- The caller must instantiate objects and pass them as arguments, even if it doesn't intend to use them
- These objects must be able to be assigned to, which means they can't be made const
- The caller must pass in objects, these values can't be used as temporary, or easily used single expressions

```cpp
#include <iostream>

int getByValue()
{
    return 5;
}

void getByReference(int& x)
{
    x = 5;
}

int main()
{
    // return by value
    [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
    std::cout << getByValue() << '\n';      // can use temporary return value in expression

    // return by out parameter
    int y{};                // must first allocate an assignable object
    getByReference(y);      // then pass to function to assign the desired value
    std::cout << y << '\n'; // and only then can we use that value

    return 0;
}
```

### Out-parameters by reference don't make it obvious the arguments will be modified

When we assign a function's return value to an object, it is clear that the value of the object is being modified

```cpp
getSinCos(degrees, sin, cos);
```

It is not clear from this function call that `degrees` is an in paameter, but `sin` and `cos` are out parameters

Using pass by address instead of pass by reference can in some case help make out parameters more obvious by requiring the caller to pass in the address of objects as arguments

```cpp
void foo1(int x);  // pass by value
void foo2(int& x); // pass by reference
void foo3(int* x); // pass by address

int main()
{
    int i{};

    foo1(i);  // can't modify i
    foo2(i);  // can modify i (not obvious)
    foo3(&i); // can modify i

    int *ptr { &i };
    foo3(ptr); // can modify i (not obvious)

    return 0;
}
```


Out parameters should be avoided unless no other good options exist

### In/Out Parameters

**In-Out Parameter** In rare cases, a function will actually use the value of an out-parameter before overwriting its value

### When to pass by non-const reference

If you're going to pass by reference in order to vvoid making a copy of the argument, you should almost always pass by const reference

2 primary cases where pass by non-const reference may be the better choice
1. Use pass by non-const reference when a parameter is an in-out parameter
    - Giving the function a good name can help

```cpp
void modifyFoo(Foo& inout)
{
    // modify inout
}

int main()
{
    Foo foo{};
    modifyFoo(foo); // foo modified after this call, slightly more obvious

    return 0;
}
```

2. Use pass by non-const reference when a function would otherwise return an object by value to the caller, but making a copy of that object is *extremely expensive*
    - Especially if the function is called many times in a performance-critical section of code

```cpp
void generateExpensiveFoo(Foo& out)
{
    // modify out
}

int main()
{
    Foo foo{};
    generateExpensiveFoo(foo); // foo modified after this call

    return 0;
}
```

# 12.14 - Type deduction with pointers, references, and const

## Notes

Default type deduction will drop `const` from types:

```cpp
int main()
{
    const double a { 7.8 }; // a has type const double
    auto b { a };           // b has type double (const dropped)

    constexpr double c { 7.8 }; // c has type const double (constexpr implicitly applies const)
    auto d { c };               // d has type double (const dropped)

    return 0;
}
```

Const can be reapplied by adding the `const` (or `constexpr`) qualifier to the definition of the deducted type

```cpp
int main()
{
    double a { 7.8 };    // a has type double
    const auto b { a };  // b has type const double (const applied)

    constexpr double c { 7.8 }; // c has type const double (constexpr implicitly applies const)
    const auto d { c };         // d is const double (const dropped, const reapplied)
    constexpr auto e { c };     // e is constexpr double (const dropped, constexpr reapplied)

    return 0;
}
```

### Type deduciton drops references

Type deduction will also drop references

```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref { getRef() }; // type deduced as std::string (not std::string&)

    return 0;
}
```

The reference qualifier is dropped, so the type of the `ref` is deducted as `std::string`
- If you want the deduced type to be a reference, you can reapply the reference at the point of definition

```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref1 { getRef() };  // std::string (reference dropped)
    auto& ref2 { getRef() }; // std::string& (reference dropped, reference reapplied)

    return 0;
}
```

### Top-level const and low-level const

**Top Level Const**: A const qualifier that applies to an object itself:

```cpp
const int x;    // this const applies to x, so it is top-level
int* const ptr; // this const applies to ptr, so it is top-level
// references don't have a top-level const syntax, as they are implicitly top-level const
```

**Low Level Const**: A const qualifier that applies to the object being referenced or pointed to:

```cpp
const int& ref; // this const applies to the object being referenced, so it is low-level
const int* ptr; // this const applies to the object being pointed to, so it is low-level
```

A reference to a const value is always a low-level const, a pointer can have a top-level, low-level, or both kinds of const

```cpp
const int* const ptr; // the left const is low-level, the right const is top-level
```

Type deduction drops only top-level consts

### Type deduction and const references

If the initializer is a refrence to const, the reference is dropped first, and then any top level const is dropped from the result:

```cpp
#include <string>

const std::string& getConstRef(); // some function that returns a reference to const

int main()
{
    auto ref1{ getConstRef() }; // std::string (reference dropped, then top-level const dropped from result)

    return 0;
}
```

Since `getConstRef()` returns a `const std::string&`, the reference is dropped first, leaving us with a `const std::string`. 
- This const is now a top-level const, so it is also dropped, leaving the deduced type as `std::string

We can reapply a reference and/or const

```cpp
#include <string>

const std::string& getConstRef(); // some function that returns a const reference

int main()
{
    auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
    const auto ref2{ getConstRef() };  // const std::string (reference dropped, const dropped, const reapplied)

    auto& ref3{ getConstRef() };       // const std::string& (reference dropped and reapplied, low-level const not dropped)
    const auto& ref4{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not dropped)

    return 0;
}
```

Best Practice: If you want a const reference, reapply the `const` qualifier even when it's not strictly necessary. It makes your intent clear and helps prevent mistakes

### What about constexpr reference?

Constexpr is not part of an expression's type, so it is not deduced by `auto`

When defining a const reference (e.g. `const int&`), the const applies to the object being referenced, not the reference itself
- When defining a constexpr reference to a const variable (e.g. `constexpr const int&`), we need to apply both `constexpr` (which applies to the reference) and `const` (which applies to the type being referenced)

### Type deduction and pointers

Type deduction does not drop pointers

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() }; // std::string*

    return 0;
}
```

Can also use an asterisk in conjuction with pointer type deduction (auto *) to make it clearer that the deduced type is a pointer

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() };  // std::string*
    auto* ptr2{ getPtr() }; // std::string*

    return 0;
}
```

### The difference between auto and auto*

When we use `auto` with a pointer type initializer, the type deduced for `auto` includes the pointer

When we use `auto*` with a pointer type initializer, the type deduced for auto does *not* include the pointer, the pointer is reapplied afterward after the type is deduced

The practical effect is the same

Couple of difference between `auto` and `auto*` in practice
- `auto*` must resolve to a pointer initializer, otherwise a compile error will result
- There are differences in how `auot` and `auto*` behave when we introduce `const` into the equation

### Type deduction and const pointers


With pointers, we have both the const pointer and the pointer to const case to think about

Only top level const is dropped during pointer type deduction

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    const auto ptr1{ getPtr() };  // std::string* const
    auto const ptr2 { getPtr() }; // std::string* const

    const auto* ptr3{ getPtr() }; // const std::string*
    auto* const ptr4{ getPtr() }; // std::string* const

    return 0;
}
```

Either `auto const` or `const auto` says "make the deduced pointer a const pointer"
- The deduced type is `std::string*`, then const is applied, making the final type `std::string* const`

When we use `auto*`, the order of the qualifiers matter
- `const` on the left means "make the deduced pointer a pointer to const"
- `const` on the right means "make the deduced pointer type a const pointer"

```cpp
#include <string>

int main()
{
    std::string s{};
    const std::string* const ptr { &s };

    auto ptr1{ ptr };  // const std::string*
    auto* ptr2{ ptr }; // const std::string*

    auto const ptr3{ ptr };  // const std::string* const
    const auto ptr4{ ptr };  // const std::string* const

    auto* const ptr5{ ptr }; // const std::string* const
    const auto* ptr6{ ptr }; // const std::string*

    const auto const ptr7{ ptr };  // error: const qualifer can not be applied twice
    const auto* const ptr8{ ptr }; // const std::string* const

    return 0;
}
```

Best Practice: If you want a const pointer, pointer to const, or const pointer to const, reapply th `const` qualifiers even when it's not strictly necessary, as it makes your intent clear and helps prevent mistakes

### Summary

Top-level vs low-level const
- A top-level const applies to the object itself
  - `const int x` or `int* const ptr`
- A low-level const applies to the object accessed through a reference or pointer
  - `const int& ref` or `const int* ptr`

What type deduction deduces
- First drops any references, unless deduced type is defined as a reference.
  - For a const reference, dropping the reference will cause the (low level) const to become a top level const
- Then drops any top-level const, unless the deduced type is defined as `const` or `constexpr`
- Constexpr is not part of the type system, so is never deduced. Must always be explicitly applied to the deduced type
- Type deduction does not drop pointers
- Always explicitly define the deduced type as a reference, `const`, or `constexpr`, and even if these qualifiers

Type deduction and pointers:
- When using `auto`, the deduced type will be a pointer only if the initializer is a pointer
  - When using `auto*` the deduced type is always a pointer, even if the initializer is not a pointer
- `auto const` and `const auto` both make the deduced pointer a const pointer
  - No way to explicitly specify a low-level const using `auto`
- `auto* const` makes the deduced pointer a const pointer
  - `const auto*` makes the deduced pointer a pointer to const

# 12.15 - std::optional

## Notes

Covered 2 different ways to have a function return an error back to the caller:
- Have a void returning function return a bool instead (indiciating success or failure)
- Have a value returning function return a sentinel value to indicate an error

```cpp
#include <iostream>

// The reciprocal of x is 1/x, returns 0.0 if x=0
double reciprocal(double x)
{
    if (x == 0.0) // if x is semantically invalid
       return 0.0; // return 0.0 as a sentinel to indicate an error occurred

    return 1.0 / x;
}

void testReciprocal(double d)
{
     double result { reciprocal(d) };
     std::cout << "The reciprocal of " << d << " is ";
     if (result != 0.0)
         std::cout << result << '\n';
     else
         std::cout << "undefined\n";
}

int main()
{
    testReciprocal(5.0);
    testReciprocal(-4.0);
    testReciprocal(0.0);

    return 0;
}
```

There are a number of potential downsides
- The programmer must know which sentinel value this funciton is using to indicate an error 
- A different version of the same function may use a different sentinel value
- This method does not work for functions where all possible sentinel values are valid return values

### Returning a `std::optional`

C++17 introduces `std::optional`, a class template type that implements an optional value.
- `std::optional<T>` can either have a value of type `T`, or not.

```cpp
#include <iostream>
#include <optional> // for std::optional (C++17)

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n'; // get the value
    else
        std::cout << "Result 1: failed\n";

    std::optional<int> result2 { doIntDivision(5, 0) };

    if (result2)
        std::cout << "Result 2: " << *result2 << '\n';
    else
        std::cout << "Result 2: failed\n";

    return 0;
}
```

We can construct a `std::optional<T>` with our without a value

```cpp
std::optional<int> o1 { 5 };            // initialize with a value
std::optional<int> o2 {};               // initialize with no value
std::optional<int> o3 { std::nullopt }; // initialize with no value
```

To see if a `std::optional has a value we can choose:

```cpp
if (o1.has_value()) // call has_value() to check if o1 has a value
if (o2)             // use implicit conversion to bool to check if o2 has a value
```

To get the value from `std::optional`, we can do:

```cpp
std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
```

`std::optional` has a usage syntax that is essentially identical to a pointer:

Hold no value
- Pointer: initialize/assign `{}` or `std::nullptr`
- std::optional: initialize/assign `{}` or `std::nullopt`
Hold a value
- Pointer: initialize/assign an address
- std::optional: Initialize/assign a value
Chck if has value
- Pointer: Implicit conversion to bool
- std::optional: Implicit conversion to bool or `has_value()`
Get value
- Pointer: dereference
- std::optional: dereference or `value()`

Semantically, pointer and `std::optional` are quite different
- A pointer has reference semantics, it references some other object, and assignment copies the pointer, not the object.
  - If we return a pointer by address, the pointer is copied back to the caller, not the object being pointed to.
  - We can't return a local object by address, as we'll copy that object's address back to the caller, and then the object will be destroyed, leaving a returned pointer dangling
- A `std::optional` has value semantics, it actually contains its value, and assignment copies the value
  - If we return a `std::optional` by value, the `std::optional` is copied back to the caller
  - We can return a value from the function back to the caller using `std::optional`

### Pros and const of returning a `std::optional`

Returning a `st::optional` is nice:
- Using `std::optional` effectively documents that a function may return a value or not
- We don't have to remember which value is being returned as a sentinel
- The syntax for using `std::optional` is convenient and intuitive

Downsides:
- We have to make sure the `std::optional` contains a value before getting the value, if we dereference a `std::optional` that doesn't contain a value, we get undefined behavior
- `std::optional` doesn't provide a way to pass back information about why the function failed

### Using std::optional` as an optional function parameter

`std::optional` is a way for a function to accept an optional argument

```cpp
#include <iostream>
#include <optional>

void printIDNumber(std::optional<const int> id = std::nullopt)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(userid); // we know the user's ID now

    printIDNumber(62); // we can also pass an rvalue

    return 0;
}
```

2 advantages to this approach:
1. It effectively documents that the parameter is option
2. We can pass in an rvalue (since `std::optional` will make a copy)

Because `std::optional` makes a copy of its argument, this becomes a problematic when `i` is an expensive-top-copy type like `std::string`

As of C++23, `std::optional` does not support references
- Only use `std::optional<T>` as an optional parameter only when `T` would normally be passed by value, Otherwise, use `const T*`

# 12.x - Chapter 12 summary and quiz

## Review

- **Compound Data Types**: Data types that can be constructed from fundamental data types
- **Value Category**: Indicates whether an expression resolves to a value, a function, or an object of some kind
- **lvalue**: Expression that evaluates to a function or an object that has an identity
- **Identity**: An object/function with an identity has an identifier or an identifiable memory address
- **Modifiable Lvalues**: Lvalues that can be modified
- **Non-Modifiable Lvalues**: Lvalues whose values can't be modified
- **Rvalue**: An expression that is not an lvalue
- **Reference**: An alias for an existing object, once a reference has been defied, any operation ont he refernence is applied to the object being referenced
- **Lvalue reference**: An alias for an existing lvalue
- **Lvalue Reference Variable**: A variable that acts as a reference to an lvalue
- **Bound**: When a reference is initialized with an object, we say it is bound to the object
- **Referenct**: The object being referenced
- **Reseated**: A reference can not be changed to reference another object
- **Dangling Reference**: When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists
- **Lvalue reference to a const value**: Using a `const` kewod when declaraing an lvaue reference, we tell an lvalue reference to treat the object it is referencing as a const
- **Temporary Object**: An object that is created for temporary use within a single expression
- **Pass by Reference**: Declare a function parameter as a reference rather than as a normal variable
- **Address-Of Operator**: (&), returns the memory address of its operands
- **Dereference Operator**: (*), returns the value of a given memory address as an lvalue
- **Pointer**: An object that holds a *memory address* as its value
- **Wild Pointer**: A pointer that has not been initialized
- **Dangling Pointer**: A pointer that is holding the address of an object that is no longer valid
- **Null Value**: A special value that means something has no value
- **Null Pointer**: Whena pointer is holding a null value, means the pointer is not pointing to anything
- **Pointer to a const value**: A non const pointer that points to a constant value
- **Cost Pointer**: A pointer whose address can not be changed after initialization
- **Const Pointer to a Const Value**: Can not have its address changed, nor can the value it is pointing to be changed through the pointer
- **Pass By Address**: The coller provides an object's address via a pointer
- **Return by Reference**: Returns a reference that is bound to the object being returned, which avoids amaking a copy of the rteurn value
- **Return by Address**: Almost identically to return by reference, except a pointer to an object is returned instead of a reference to an object

## Quiz

1. For each of the following expressions on the right side of operator <<, indicate whether the expression is an lvalue or rvalue:
```cpp
std::cout << 5;:
```
- rvalue

```cpp
int x { 5 };
std::cout << x;
```
- lvalue

```cpp
int x { 5 };
std::cout << x + 1;
```
- rvalue

```cpp
int foo() { return 5; }
std::cout << foo();
```
- rvalue

```cpp
int& max(int &x, int &y) { return x > y ? x : y; }
int x { 5 };
int y { 6 };
std::cout << max(x, y);
```
- lvalue

2. What is the output of this program?

```cpp
#include <iostream>

int main()
{
	int x{ 4 };
	int y{ 6 };

	int& ref{ x };
	++ref;
	ref = y;
	++ref;

	std::cout << x << ' ' << y;

	return 0;
}

```shell
7 6
```

3. Name two reasons why we prefer to pass arguments by const reference instead of by non-const reference whenever possible.
- If we don't need the ability to modify the reference, it is best to set as const reference so that we don't accidently modify the argument
- non-const reference can only allow modifiable lvalues, meaning you have to define the value first. const reference can take a literal/rvalue

4. What is the difference between a const pointer and a pointer-to-const?
- Const pointer means that the pointer itself is constant. You can't change what the pointer is pointing to. YOu can change the value the pointer is pointer though. `auto* const`
- Pointer-to-const means treat the value the pointer is pointer to as const. You can change what the pointer is pointing to. You can't change the value the pointer is pointing to `const auto*`

5. Write a function named sort2 which allows the caller to pass 2 int variables as arguments. When the function returns, the first argument should hold the lesser of the two values, and the second argument should hold the greater of the two values.

Hint: The std::swap() function (in the <algorithm> header) can be used to swap the values of two variables. e.g. std::swap(x, y) swaps the values of the variables x and y.

The following code should run and print the values noted in the comments:

```cpp
#include <iostream>

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}
```

```cpp
#include <iostream>

void sort2(int& x, int& y)
{
    if (y < x)
    {
        int temp {x};
        x = y;
        y = temp;
    }
}

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}
```