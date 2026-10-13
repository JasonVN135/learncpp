# 16.1 - Introduction to containers and arrays

## Notes

## The variable scalability challenge

Consider a scenario where we want to record the test scores for 30 students and calculate the average score for the class

```cpp
// allocate 30 integer variables (each with a different name)
int testScore1 {};
int testScore2 {};
int testScore3 {};
// ...
int testScore30 {};
```

And to calculate the average score:

```cpp
int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
```

Very repetitive

If we need to modify our program to accommodate another student who was just added, we'll have to scan the entire codebase and manually add in `testScore31`

### Containers

**Container**: A data type that provides storage for a collection of unnamed objects/elements
- Strings are containers, providing storage for a collection of characters

### The elements of a container are unnamed

While the container object itself typically has a name, the elements of a container are unnamed
- We can put as many elements in our container as we desire, without having togive each element a unique name
- This is what distinguishes containers from other types of data structures

If the elements themselves are unnamed, how do we access them?
- Each container provides 1+ methods to access its elements

### The length of the container

**Length**: The number of elements in a container

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

**Size**: Commonly used for the number of elements in a container
- Size can also refer to the number of bytes of memory used

### Container operations

Containers typically implement a significant subset of the following operations:
- Create a container
- Access to element
- Insert and remove elements
- Get the number of elements in the container

Containers may also provide other operations that assist in managing the collection of elements

Modern programming languages typically provide a variety of different container types
- Differ in terms of which operations they actually support, and how performant those operations are

Every container has a set of strengths and limitations

### Element Types

Containers are **homogenous**: The elements of a container are required to have the same type
- Some containers use a preset type, but more often the element type can be set by the user of the container

Makes containers flexible, as we don't need to create a new container type for each different element type

### Containers in C++

**Containers Library**: Part of the C++ standard library that contains various class types that implement some common types of containers
**Container Class**: A class type that implements a container

C++, the definition of "container" is narrower than the general programming definition
- ONly the class type in the Container library are considered to be containers in C++

`std::vector` and `std::array` see by far the most use

### Introduction to arrays

**Arrays**: A container data type that stores a sequence of values **contiguously**
- Each element is placed in an adjacent memory location with no gaps
- Allow fast, direct access to any element

C++ contains 3 primary array types 
- (C-style) arrays
- `std::vector` container class
- `std::array` container class

(C-style) arrays were inherited from C
- Defined as part of the core C++ language
- Typically called "arrays", but in C++, called **C Arrays**

`std::vector` was introduced to be safer and easier to use
- Most flexible of the 3 array types

`std::array` introducted in C++11, as a direct replacement for C-style arrays
- More limited than `std::vector`, but can also be more efficient, especially for smaller arrays

# 16.2 - Introduction to `std::vector` and list constructors

## Quiz

1. Define a std::vector using CTAD and initialize it with the first 5 positive square numbers (1, 4, 9, 16, and 25).

```cpp

int main()
{
	std::vector<int>vec {1, 4, 9, 16, 25};

	return 0;
}
```

2. What’s the behavioral difference between these two definitions?

```cpp
std::vector<int> v1 { 5 };
std::vector<int> v2 ( 5 );
```
- Top one initializes a vector of length 1 with a value of 5
- Bottom one initializes a vector of length 5 with all values being 0

3. Define a std::vector (using an explicit template type argument) to hold the high temperature (to the nearest tenth of a degree) for each day of a year (assume 365 days in a year).

```cpp
int main()
{
	std::vector<double>temperatures(365);

	return 0;
}
```

4. Using a std::vector, write a program that asks the user to enter 3 integral values. Print the sum and product of those values.

```cpp
int main()
{
	std::vector<int>values(3);

	std::cout << "Enter 3 integers: ";

	std::cin >> values[0];
	std::cin >> values[1];
	std::cin >> values[2];

	std::cout << "The sum is: " << (values[0] + values[1] + values[2]) << "\n";
	std::cout << "The product is: " << (values[0] * values[1] * values[2]) << "\n";

	return 0;
}
```

## Notes

### Introduction to `std::vector`

`std::vector` is defined in the <vector> header as a class template

`std::vector<int>` declares a `std::vector` whose elements are of type `int`

```cpp
#include <vector>

int main()
{
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements

	return 0;
}
```

A vector with no elements may not seem useful not, but we'll encounter this again

### Initializing a `std::vector with a list of values

May want to initialize our container with values. Use list initialization with the specific initialization values we want

```cpp
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```

### List constructors and initializer list

**List Constructor**: Allows us to construct an instance of the container using an initializer list. Does 3 things
- Ensures the container has enough storage to hold all the initialization values
- Sets the length of the container to the number of elements in the initializer list
- Initializes the elements to the values in the initializer list

When we provide a container with an initializer list of values, the list constructor is called, and the container is constructed using that list of values

Best Practice: Use list initialization with an initializer list of values to construct a container with those element values

### Accessing array elements using the subscript operator (operator[])

The most common way to access array elements is by using the name of the array along with the subscript operator (`operator[]`)
- To select a speicif element, inside the square brackets of the subscript operator, we provide an integral value that identifiers which element we want to select

**Subscript**: The integral value used


Because the indexing starts with 0 instead of 1, we say arrays in C++ are **Zero-Based**

Can cause some linguistic ambiguity, because when we talk about array element 1, it may not be clear whether we're talking about the first array element

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "The first prime number is: " << primes[0] << '\n';
    std::cout << "The second prime number is: " << primes[1] << '\n';
    std::cout << "The sum of the first 5 primes is: " << primes[0] + primes[1] + primes[2] + primes[3] + primes[4] << '\n';

    return 0;
}
```

```shell
The first prime number is: 2
The second prime number is: 3
The sum of the first 5 primes is: 28
```

We no longer have to define 5 differently-named variables to hold our 5 prime values

### Subscript out of bounds

The index provided must select a valid element of the array
- For an array of length N, the subscript must be a value between 0 and N-1 (inclusive)

**Bounds Checking**: Checking to see whether the index is within the bounds
- Operator[] doesn't do any bounds checking

Passing an invalid index will return an undefined behavior

### Arrays are contiguous in memory

Elements are always allocated contiguously in memory
- The elements are all adjacent in memory

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```

```shell
An int is 4 bytes
00DBF720
00DBF724
00DBF728
```

Arrays are one of the few container types that allow for **random access**, meaning any element in the container can be accessed directly
- Random access to array elements is typically efficient, and makes arrays very easy to use

### Constructing a `std::vector` of a specific length

We can create `std::vector` and initialize it with an initilizer list with 10 placeholder values:

```cpp
std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
```

We can instead use an explicit constructor that takes a single `std::size_t` value defining the length of the `std::vector` to construct:

```cpp
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

### Non-Empty Initializer Lists Prefer List Constructors

Consider this definition

```cpp
std::vector<int> data{ 10 }; // what does this do?
```
 
- `{ 10 }` can be interpreted as an initializer list, length 1 with a value 10
- `{ 10 }` can be intepreted as constructing a length 10, with 0 values

When a class type definition matches more than one constructor, the match is considered ambiguous and a compilation error results
- C++ has a special rule, when an initializer list is non-empty, a matching list constructor will be selected over other matching constructors

To help clarify what happens in various initialization cases

```cpp
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor

// Default init
std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor
```

Best Practice: When constructing a container with initializers that are not element values, use direct initialization

### Const and constexpr `std::vector`

Objects of type `std::vector` can be made `const`

```cpp
#include <vector>

int main()
{
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified

    return 0;
}
```

Must be initialized, and then cannot be modified
- Elements are treated as if they were const

The element type of a `std::vector` must not be defined as `const`
- `std::vector<const int>` is disallowed

`std::vector` cannot be made `constexpr`
- Use `std::array` for `constexpr`

# 16.3 - std::vector and the unsigned length and subscript

## Questions

1. Initialize a std::vector with the following values: ‘h’, ‘e’, ‘l’, ‘l’, ‘o’. Then print the length of the array (use std::size()). Finally, print the value of the element with index 1 using the subscript operator and the at() member function.

The program should output the following:

```shell
The array has 5 elements.
e
```

```cpp
#include <chrono>
#include <random>
#include <iostream>
#include <vector>

int main()
{
	std::vector<char> data{'h', 'e', 'l', 'l', 'o'};

    std::cout << "The array has " << data.size() << " elements.\n";
    std::cout << data.at(1) << "\n";
	return 0;
}
```

2. 
a. What is size_type and what is it used for?
- size_type is a nested typedef that is an alias for the type used to store the length (and indices, if supported) of a standard library container.

b. What type does size_type default to? Is it signed or unsigned?
- std::size_t, which is an unsigned type.

c.  Which functions to get the length of a container return size_type?
- The size() member function and std::size both return size_type

## Notes

### Contaienr length sign problem

The data type used for subscripting an array should match the data type used for storing the length of the array
- Elements in the longest possible array can be indexed, and no more

When the container class in the C++ standard library was being designed, the designers had to choose whether to make the length signed or unsigned
- Chose to make it unsigned

Using an unsigned type allows arrays of greater length due to the extra bit, and range checking the subscript requires 1 conditional check instead of 2

Generally regarded as having been the wrong choice
- Using unsigned values to try to enforce non-negatie doesn't work due to the implicit conversion rules
- The commonly used `operator[]` doesn't do range-checking either

### A review: sign conversions are narrowing conversions, except when constexpr

Sign conversions are considered to be narrowing conversions because a signed or unsigned type cannot hold all the values contained in the range of the opposing type
- When performd, the compiler will issue an error in contexts where narrowing conversions are disallowed
- May or may not issue a warning in other contexts

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    int s { 5 };

    [[maybe_unused]] unsigned int u { s }; // compile error: list initialization disallows narrowing conversion
    foo(s);                                // possible warning: copy initialization allows narrowing conversion

    return 0;
}
```

If the value to be sign converted is constexpr and can be converted to an equivalent value in the opposing type
- The sign conversion is *not* considered to be narrowing
- The compiler can guarantee that the conversion is safe, or halt the compilation in process

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    [[maybe_unused]] unsigned int u { s }; // ok: s is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                // ok: s is constexpr and can be converted safely, not a narrowing conversion

    return 0;
}
```

### The length and indices of `std::vector` have type `size_type`

`std::size_t` is a typedef for some large unsigned integral type, usually `unsigned long` or `unsigned long long`

Each of the standard library contains classes defines a nested typedef member named `size_type`
- An alias for the type used for the length of the container

`size_type` is almost always an alias for `std::size_t` but can be overridden to use a different type

When accessing the `size_type` member of a container class, we must scope qualify it with the fully templated name of the container class
- Ex: `std::vector<int>::size_type`

### Getting the length of a `std::vector` using the `size()` member funciton or `std::size()`

Can ask a container class object for its length using the `size()` member function

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```

```shell
length: 5
```

`std::vector` and most other container types in `C++` only has `size()` and not `length()`

C++17, we can also use the `std::size()` non-member function

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)

    return 0;
}
```

Simplest thing to store the length is to use a static_cast of the result to the desired type:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    int length { static_cast<int>(prime.size()) }; // static_cast return value to int
    std::cout << "length: " << length ;

    return 0;
}
```

### Getting the length of a `std::vector` using `std::ssize()` C++20

C++20 introduces the `std::ssize()` non-member function, which returns the length as a large *signed* integral type

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type

    return 0;
}
```

The only function of the 3 ways whch returns the length as a signed type

Couple ways to store the length in a variable with a signed type
1. If you are going to assign the length to an `int` variable, you should static_cast the result to `int` to make any such conversion explicit

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    int length { static_cast<int>(std::ssize(prime)) }; // static_cast return value to int
    std::cout << "length: " << length;

    return 0;
}
```

2. You can use `auto` to have the compiler deduce the correct signed type to use for the variable

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    auto length { std::ssize(prime) }; // use auto to deduce signed type, as returned by std::ssize()
    std::cout << "length: " << length;

    return 0;
}
```

### Accessing array elements using `operator[]` does not bound check

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3];  // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```

`operator[]` does not do bound checking
- The idnex for operator[] can be non-const

### Accessing array elements using the `at()` member function does runtime bounds checking

The `at()` function can be used to do array access with runtime bounds checking

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)

    return 0;
}
```

Call to `prime.at(9)` fails at runtime because 9 is not a valid index for this array
- The `at()` function generates an error that terminates the program
- The index passed to `at()` can be non const

`at()` is slower but safer than `operator[]`
- `operator[]` is typically used over `at()`
- Better to do bounds checking prior to indexing

### Indexing `std::vector` with a constexpr int


We can let the compiler implicitly convert this to a `std::size_t` without it being a narrowing conversion

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion

    constexpr int index { 3 };         // constexpr
    std::cout << prime[index] << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion

    return 0;
}
```

### Indexing `std::vector` with a non-constexpr value

The subscripts used to index an array can be non-const

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::size_t index { 3 };           // non-constexpr
    std::cout << prime[index] << '\n'; // operator[] expects an index of type std::size_t, no conversion required

    return 0;
}
```

We generally want to avoid using unsigned types to hold quantities

When our subscript is a non-constexpr signed value, we run into problems

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    int index { 3 };                   // non-constexpr
    std::cout << prime[index] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion

    return 0;
}
```

`index` is a non-constexpr signed int
- Subscript of `operator[]` defined as part of `std::vector` has a type `size_type`
- When we call `prime[index]`, our signed int must be converted to `std::size_t`

Such conversion should not be dangerous
- But when performed at runtime, this is considered to be a narrowing conversion
- Compiler should produce a warning about his being an unsafe conversion

Because array subscripting is common, and each such conversion will generate a warning, this can easily clutter up compilation log

Many ways to avoid this
- All inevitably end up cluttering or complicating your code in some way

Simplest solution is use a variable of type `std::size_t` as your index
- Do not use this variable for anything but indexing

# 16.4 - Passing std::vector

## Questions

1. Write a function that takes two parameters: a std::vector and an index. If the index is out of bounds, print an error. If the index is in bounds, print the value of the element.

The following sample program should compile:

```cpp
#include <iostream>
#include <vector>

// Write your printElement function here

int main()
{
    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1);

    return 0;
}
```

```shell
The element has value 2
Invalid index
The element has value 1.1
Invalid index
```

```cpp
#include <iostream>
#include <vector>

// Write your printElement function here
template <typename T>
void printElement(const std::vector<T>& vec, int index)
{
    int vecSize {static_cast<int>(vec.size())};
    if (index < 0 || index >= vecSize)
    {
        std::cout << "Invalid index\n";
    }
    else
    {
        std::cout << "The element has value " << vec[index] << "\n"; 
    }
}

int main()
{
    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1);

    return 0;
}
```



## Notes

An object of type `std::vector` can be passed to a function just like any other object
- If we pass `std::vector` by value, an expensive copy will be made

Typically pass `std::vector` by (const) reference to avoid such copies

```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    return 0;
}
```

### Passing `std::vector` of different element types

`passByRef()` function expects a `std::vector<int>`, we are unable to pass vectors with different element types

In C++17 or newer, you might try to use CTAD to solve this problem

```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector& arr) // compile error: CTAD can't be used to infer function parameters
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 }; // okay: use CTAD to infer std::vector<int>
    passByRef(primes);

    return 0;
}
```

CTAD doesn't work with function parameters

Great place to make use of function templates

We can create a function template that uses the same template parameter declaration:

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

### Passing a `std::vector` using a generic template or abbreviated function template

Can also create a function template that will accept any type of object

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const T& arr) // will accept any type of object that has an overloaded operator[]
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

In C++20, we can use an abbreviated function template to do the same thing

```cpp
#include <iostream>
#include <vector>

void passByRef(const auto& arr) // abbreviated function template
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

Both will accept an argument of any type that will compile
- Can be desiaable when writing functions that we might want to operator on more than just `std::vector`
  - Ex: `std::array`, `std::string`
- Downside is that it may lead to bugs if the function is passed an object of a type that compiles but doesn't make sense semantically

### Asserting on array length

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    printElement3(arr);

    return 0;
}
```

While `printElement3(arr)` works fine in this case, there's a potential bug
- The program prints the value of the array element with index 3
- The compiler will happily let you pass in arrays where index 3 is out of bounds

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7 }; // a 2-element array (valid indexes 0 and 1)
    printElement3(arr);

    return 0;
}
```

One option is to assert on `arr.size()`, which will catch such errors when run in debug build configuration
- Because `std::vector::size()` is a non-constexpr function, we can only do a runtime assert here

Best option is to avoid writing functions that rely on the user passing in a vector with a minimum length in the first place

# 16.5 - Returning std::vector, and an introduction to move semantics

## Notes

When we need to pass a `std::vector` to a function, we pass it by const reference so that we don't make an expensive copy

It is actually okay to return a `std::vector` by value

### Copy semantics

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    std::vector arr2 { arr1 };          // copies arr1 into arr2

    arr1[0] = 6; // We can continue to use arr1
    arr2[0] = 7; // and we can continue to use arr2

    std::cout << arr1[0] << arr2[0] << '\n';

    return 0;
}
```

When `arr2` is initialized with `arr1`, the copy constructor of `std::vector` is called

Making a copy is the only reasonable ting to do in this case

**Copy Semantics**: Refers to the rules that determine how copies of objects are made
- When we say a type supports copy semantics, we mean that objects of that type are copyable
- When we say copy semantics are being invoked, that means we've done something that will make a copy of an object

For class types, copy semantics are typically implemented via the copy constructor
- Defines how objects of that type are copied

The statement `std::vector arr2 {arr1};` invokes copy semantics, resulting in a call to the copy constructor of `std::vector`
- Makes a copy of each data member of `arr1` into `arr2`
- End result is that `arr1` is equivalent to `arr2`

### When copy semantics is not optimal

```cpp
#include <iostream>
#include <vector>

std::vector<int> generate() // return by value
{
    // We're intentionally using a named object here so mandatory copy elision doesn't apply
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    return arr1;
}

int main()
{
    std::vector arr2 { generate() }; // the return value of generate() dies at the end of the expression

    // There is no way to use the return value of generate() here
    arr2[0] = 7; // we only have access to arr2

    std::cout << arr2[0] << '\n';

    return 0;
}
```

`arr2` is being initialized using a temporary object returned from function `generate()`
- The temporary object is an rvalue will be destroyed at the end of the initialization expression

The temporary object can't be used beyond that point
- The temporary will be destroyed at the end of the expression, we need some way to get the data out of the temporary and into `arr2`

Usual thing to do is use copy semantics and make a potentially expensive copy
- What makes this case different thant he previous example is that the temporary is going to be destroyed anyways

The temporary doesn't need its data any more
- We don't need 2 sets of data to exist simultaneously
- Making a potential expensive copy and then destroying the original is suboptimal

### Introduction to move semantics

**Moved**: When ownership of data is transferred from one object to another
- Cost of such a move is typically trivial, which is way faster than copying an array of data

When the temporary was then destroyed at the end of the expression, it would no longer have any data to destroy
- We wouldn't have to pay that cost either

**Move Semantics**: Refers to the rules that determine how the data from one object is moved to another object
- When invoked, any data member that can be moved is moved, and any data member that can't is copied

### How move semantics is invoked

When all of the following are true, move semantics will be invoked instead of copy semantics:
- The type of the object supports move semantics
- The object is being initialized with an rvalue object of the same type
- The move isn't elided

Not many types support move semantics
- `std::vector` and `std::string` does support move semantics

### We can return move-capable types like `std::vector` by value

Because return by value returns an rvalue, if the return type supports move semantics, then the return value can be moved instead of copied into the destination object
- Makes return by value extremely inexpensive

### Expensive-to-copy types shouldn't be passed by value, but if they are move-capable they can be returned by value

One of the most common things we do in C++ is pass a value to some function, and get a different value back

When the passed values are class types, that process involves 4 steps:
1. Construct the value to be passed
2. Actually pass the value to the function
3. Construct the value to be returned
4. Actuall pass the return value back to the caller

```cpp
#include <iostream>
#include <vector>

std::vector<int> doSomething(std::vector<int> v2)
{
    std::vector v3 { v2[0] + v2[0] }; // 3 -- construct value to be returned to caller
    return v3; // 4 -- actually return value
}

int main()
{
    std::vector v1 { 5 }; // 1 -- construct value to be passed to function
    std::cout << doSomething(v1)[0] << '\n'; // 2 -- actually pass value

    std::cout << v1[0] << '\n';

    return 0;
}
```

Assume `std::vector` is not move-capable. In that case the above program makes 4 copies
1. Constructing the value to be passed copies the initializer list into `v1`
2. Actually passing the value to the function copies argument`v1` into function parameter `v2`
3. Constructing the value to be returned copies the initializer into `v3`
4. Actually returning the value to the caller copies `v3` back to the caller

We can't optimize copies 1 and 3 at all
- Need a `std::vector` to pass to the function
- And need a `std::vector` to return

Can affect copies 2 and 4

Copy 2 is made because we're passing by value from the caller to the call function. Other options:
- Pass by reference/address? Yes
- Copy be elided? No, elision only works when we're making a redundant copy/move
  - No redundant copy/move here
- Use an out parameter? No, passing a value to the function, not getting a value back
- Use move semantics? No, argument is an lvalue

Pass by const reference is our best option here

Copy 4 is made because we're passing by value from the called function back to the caller. Other options:
- Return by reference/address? No, object is created locally inside the funciton and will be destroyed
- Copy by elided? Yes, possibly. If the compiler is smart
  - By rewriting the code so that `v3` is constructed in the scope of the caller instead, we can avoid the copy that would otherwise be made when returning
- Out parameter? Yes, can construct an empty `std::vector` object in the scope of the caller, and pass it to the function by non-const reference
  - Function can fill this parameter with data
  - When returned, the object will still exists
  - Downsides and contraints: Ugly calling semantics, doesn't work with objects that don't support assignment, challenging to write such functions that can work with both lvalue and rvalue arguments
- Move semantics? Yes, `v3` is going to be destroyed, instead of copying `v3`, we can use move semantics

Elision is the best option here, but whether it happens is out of our control
- Next best option for move-capable types is move semantics

For move-capable types, we prefer to pass by const reference, and return by value

# 16.6 - Arrays and Loops

## Notes

## The variable scalability challenge, revisited
