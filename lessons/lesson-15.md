# 15.1 - The hidden "this" pointer and member function chaining

## Notes

When a member function is called, how does C++ keep track of which object it was called on?

```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << m_id; }
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}
```

When we call `simple.setID(2)`, C++ knows that function `setID()` should operate on object `simple`. `m_id` actually refers to `simple.m_id`

C++ utilizes a hidden pointer named `this`

### The hidden `this` pointer

**this**: Keyword for a constant pointer that holds the address of the current implicit object

```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << this->m_id; } // use `this` pointer to access the implicit object and operator-> to select member m_id
};

int main()
{
    Simple simple{ 1 };
    simple.setID(2);

    simple.print();

    return 0;
}
```

### how is `this` set?

```cpp
simple.setID(2);
```
Although the `setID(2)` looks like it only has 1 argument, it actually has 2
- When compiled, the compiler rewrites the expression as:

```cpp
Simple::setID(&simple, 2); // note that simple has been changed from an object prefix to a function argument!
```

This is now just a standard funciton call, and the object `simple` is now passed by address as an argument to the function

Since the function call now has an added argument, the member function definition also needs to be modified to accept this argument as a parameter

```cpp
static void setID(Simple* const this, int id) { this->m_id = id; }
```

Our `setId` function has a new leftmost parameter named `this`, which is a const pointer
- `m_id` member has also been rewritten as `this->m_id`

Putting it all together
1. When we call `simple-setID(2)`, the compiler actually calls `Simple::setID(&simple, 2)`, and `simple` is passed by address to the function
2. The function has a hidden parameter named `this` which receives the address of `simple`
3. Member variables inside `setID()` are prefixed with `this->`, which points to `simple`, When the compiler evaluates `this->m_id`, it's actually resolving to `simple.m_id`

### `this` always points to the object being operated on

Each member funciton has a single `this` pointer parameter that points to the implicit object

```cpp
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
```

`this` pointer alternately holds the address of object `a` or `b` depending on whether we've called a member funciton on object `a` or `b`

`this` is just a function parameter, it doesn't make instances of your class larger memory-wise

### Explicitly referencing `this`

Most of the time, you won't need to explicitly reference the `this` pointer
- There are a few occasions where doing so can be useful

If you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using `this`

```cpp
struct Something
{
    int data{}; // not using m_ prefix because this is a struct

    void setData(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```

Some developers prefer to explicitly add `this->` to all class members to make it clear that theya re referencing a member
- Using the "m_" prefix is a more concise way to differentiate private member variables from non-member variables

### Returning *this

Something that is useful is to have a member function return the implicit object as a return value

**Function Chaining** Allow member functions to be "chained" together, so several member functions can be called on the same object in a single expression

```cpp
(std::cout << "Hello, ") << userName;
```

`operator<<` uses `std::cout` and the string literal `"Hello, "` to print `"Hello, "` to the console.
- Since this part of an expression, `operator<<`, needs to return a value, it `operator<<` returned void, you'd end up with this as the partailly evaluated expression

```cpp
void{} << userName;
```

Instead `operator<<` returns the stream object that was passed in, which in this case is `std::cout`
- After the first `operator<<`, has been evaluated, we get:

```cpp
(std::cout) << userName;
```

We only need to specify `std::cout` once, and then we can chain as many pieces of text together using `operator<<`
- Each call returns `std::cout` so the next call uses `std::cout` as the left operand

```cpp
class Calc
{
private:
    int m_value{};

public:

    void add(int value) { m_value += value; }
    void sub(int value) { m_value -= value; }
    void mult(int value) { m_value *= value; }

    int getValue() const { return m_value; }
};
```

```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5); // returns void
    calc.sub(3); // returns void
    calc.mult(4); // returns void

    std::cout << calc.getValue() << '\n';

    return 0;
}
```

If we make each function return `*this` by reference, we can chain the calls together

```cpp
class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }
};
```

```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4); // method chaining

    std::cout << calc.getValue() << '\n';

    return 0;
}
```

### Resetting a class back to default state

If your class has a default constructor, you may be interested in providing a way to return an existing object back to its default state

Constructors are only for initialization of new objects, and should not be called directly
- Best way to reset a class back to a default state is to create a `reset()` member function
- Create a new object, and then assign that new object to the current implicit object

```cpp
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```

### `this` and const objects

For non-const member functions, `this` is a const pointer to a non-const value
- With const member functions, `this` is a const pointer to a const value

The errors generated from attempting to call a non-const member function on a const object can be a little cryptic

```shell
error C2662: 'int Something::getValue(void)': cannot convert 'this' pointer from 'const Something' to 'Something &'
error: passing 'const Something' as 'this' argument discards qualifiers [-fpermissive]
```

When we call a non-const member function on a const object, the implicit `this` funciton parameter is a const pointer to a non-const object
- Converting a pointer to a const object into a pointer to a non-const object requires discarding the const qualifier, which cannot be done implicitly

### Why `this` a pointer and not a reference

Since `this` pointer always points to the implicit object, why `this` is a pointer instead of a reference
- `this` was added to C++ when references didn't exist yet

# 15.2 - Classes and Header Files

## Questions

1. What is the purpose of defining member functions outside the class definition?
- To make the class definition shorter and easier to manage.
- To separate the public interface from the implementation details.
- When defined in a source file, to minimize recompilation times when an implementation detail changes.

2. How do you define a member function outside the class definition?
- Define the function with the class name prefixed using the scope resolution operator (::).

3. Where should the class definition be placed to facilitate reuse in multiple files or projects?
- In a separate header file with the same name as the class.

4. Which of the following is true about the one-definition rule for classes and member functions?
- Member functions defined inside the class definition are exempt from the one-definition rule.


## Notes

As classes get longer and more complicated, having all member funciton definitions inside the class can make the class harder to manage and work with

C++ allows us to separate the "declaration" portion of the class from the "implementation" portion by defining member functions outside of the class definition

```cpp
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // constructor declaration

    void print() const; // print function declaration

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const  { return m_day; }
};

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

int main()
{
    const Date d{ 2015, 10, 14 };
    d.print();

    return 0;
}
```

Member functions can be defined outside the class definition just like non-member functions
- We must prefix the member function names with the name of the class type so the compiler knows we're defining a member of that class type rather than a non-member

### Putting class definitions in a header file

If you define a class inside a source (.cpp) file, that class is only usable within that particular source file
- In larger programs, it's common that we'll want to use the classes we write in multiple source files

The compiler typically needs to see the full definition of a class (or any program-defined type) in order for the type to be used
- The compiler needs to understand how members are declared in order to ensure they are used properly

Our header files usually contain the full definition of a class rather than just a forward declaration of the class

### Naming your class header and code files

Classes are defined in header files of the same name as the class
- Any member functions defined outside fo the class are put in a .cpp file of the same name

```cpp
// Date.h
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

#endif
```

```cpp
// Date.cpp
#include "Date.h"

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
```

Now any other header or code file that wants to use the `Date` class can simply `#include "Date.h"`

### Doesn't defining a class in a header file violate the ODR if the header is #included more than once

Types are exempt form the part of the ODR that says you can only have 1 definition per program

Including a class definition more than once into a single translation unit is still an ODR violation
- Header guards or `#pragma once` will prevent his from happening

### Inline member functions

member functions are not exempt from the ODR
- How do we avoid ODr violations when member functions are defined in a header

Member functions defined inside the class definition are implicitly inline.
- Inline functions are exempt from the one definition per program part of the one definition rule

Member functions defined outside the class definition are not implicitly inline
- Such functions are usually defined in a code file

Alternatively, member functions defined outside the class definition can be left in the header file if they are made inline

```cpp
// Date.h
#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

inline Date::Date(int year, int month, int day) // now inline
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

inline void Date::print() const // now inline
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

#endif
```

### Inline expansion of member functions

The compiler must be able to see a full definition of a function in order to perform inline expansion
- Most often, such functions are defined inside the class definition
- If you want to define a member function outside the class definition, but still want it to be eligible for inline expansion
  - Can define it as an inline function just below the class definition

### So why not put everything in a header file?

Might be tempted to put all of your member function definitions into the header file, either inside the class definition, or as inline functions below the class definition

Downsides to oing so
- Defining members inside the class definition clutters up your class definitions
- If you change any of the code in the header, you'll need to recompile every file that includes that header
  - Can have a ripple effect, where 1 minor chnage causes the entire program to need to recompile
- If you change the code in a .cpp file, only that .cpp file needs to be recompile
  - Given the choice, it's generally better to put non-trivial code ina  .cpp file when you can

Few cases where it might make sense to violate the best practice of putting the class definition in a header and non-trivial member functions in a code file
1. For a small class that is used in only 1 code file and not intended for general reuse, may prefer to define the class directly in the single .cpp file
2. If a class only has a small number of non-trivial functions that are unlikely to change, creating a .cpp file that contains only 1-2 definitions may not be worth the effor
  - May be preferable to make the member functions `inline` and place them beneath the class definition in the header
3. In modern C++, classes/libraries are increasingly being distributed as "header-only",
  - All code for the class or library is placed in a header file
  - Primarily to make distributing and using such files easier
4. For template classes, template member functions defined outside the class are almost always defined inside the header file

### Default arguments for member functions

Because member functions are always declared as part of the class definition, the best practice for member functions is simple:
- Always put the default argument inside the class definition

### Libraries

The header files provide the declarations that the compiler requires in order to validate that the programs you're writing are syntactically correct
- Implementations for the classes that belong to the C++ standard library are contaiend in a precompiled file that is linked automatically at the link stage

# 15.3 - Nested Types (member types)

## Notes

```cpp
#include <iostream>

enum class FruitType
{
	apple,
	banana,
	cherry
};

class Fruit
{
private:
	FruitType m_type { };
	int m_percentageEaten { 0 };

public:
	Fruit(FruitType type) :
		m_type { type }
	{
	}

	FruitType getType() { return m_type; }
	int getPercentageEaten() { return m_percentageEaten; }

	bool isCherry() { return m_type == FruitType::cherry; }

};

int main()
{
	Fruit apple { FruitType::apple };

	if (apple.getType() == FruitType::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```

Because `enum class FruitType` is meant to be used in conjunction with the `Fruit` class, having it exist independently of the class leaves us to infer how they are connected

### Nested Types (member types)

**Nested Types**: A type defined inside the class, under the appropriate access specifier

```cpp
#include <iostream>

class Fruit
{
public:
	// FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```

`FruitType` is now defined inside the class, where it has been renamed `Type`

Nested type `Type` has been defined at the top of the class
- Nested type names must be fully defined before they can be used, so theya re usually defined first

Nested types follow normal access rules `Type` is defined under the `public` access specifier

Class types act as a scope region for names declared within, just as namespaces do

We do not need to use the fully qualified name
- In member funciton `isCherry()`, we access the `cherry` enumerator without the `Fruit::` scope qualiifier

Outside the class, we must use the fully qualified name

We changed our enumerated type rom scoped to unscoped, since the class itself is now acting as a scoped region

### Nested typedefs and type aliases

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
```

```shell
John has id: 1
```

Inside the class we can just use `IDType`, but outside the class we must use the fully qualified name `Employee::IDType`

Very common for classes in C++ standard library to make use of nested typedefs

### Nested classes and access to outer class members

Fairly uncommon for classes to have other classes as a nested type, it is possible\
A nested class doesn't have access to the `this` pointer of the outer class
- Nested classes can not directly access the members of the outer class
- Nested classes can be instantiated independently of the outer class

Because nested classes are members of the outer class, they can access any private members of the outer class that are in scope

### Nested types and forward declaration

A nested type can be forward declared within the class that encloses it
- Can be defined later, either within the enclosing class, or outside of it

```cpp
#include <iostream>

class outer
{
public:
    class inner1;   // okay: forward declaration inside the enclosing class okay
    class inner1{}; // okay: definition of forward declared type inside the enclosing class
    class inner2;   // okay: forward declaration inside the enclosing class okay
};

class inner2 // okay: definition of forward declared type outside the enclosing class
{
};

int main()
{
    return 0;
}
```

A nested type cannot be forward declared prior to the definition of the enclosing class

```cpp
#include <iostream>

class outer;         // okay: can forward declare non-nested type
class outer::inner1; // error: can't forward declare nested type prior to outer class definition

class outer
{
public:
    class inner1{}; // note: nested type declared here
};

class outer::inner1; // okay (but redundant) since nested type has already been declared as part of outer class definition

int main()
{
    return 0;
}
```

While you can forward declare a nested type after the definition of the enclosing class, since the enclosing class will already contain a declaration for the nested type, doing so is redundant

# 15.4 - Introduction to Deestructors

## Notes

### The cleanup problem

Say you are writing a program that needs to send some data over a network
- However, establishing a connection to the server is expensive, so you want to collect a bunch of data and then send it all at once

```cpp
// This example won't compile because it is (intentionally) incomplete
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    n.sendData();

    return 0;
}
```

However, `NetworkData` has a potential issue
- Relies on `sendData()` being explicitly called before the program is shutdown
- If the user forgets to do this, the data will not be sent to the server, and will be lost when the program exits

Classes that use a resource often needs to be explicitly sent or closed before the class object using them is destroyed
- We may want to do some record-keeping prior to the destruction of the object, such as writing information to a log file, or sending a piece of telemetry to a server

### Destructors to the rescue

**Destructors**: Designed to allow a class to do any necessary clean up before an object of the class is destroyed

### Destructor naming

Destructors have specific naming rules:
1. Destructor must have the same name as the class preceded by a tilda (~)
2. The destructor can not take arguments
3. The destructor has no return type

A class can only have a single destructor

You shouldn't call a destructor explicitly

Destructors may safely call other member functions since the object isn't destroyed until after the destructor executes

### A destructor example

```cpp
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```

```shell
Constructing Simple 1
Constructing Simple 2
Destructing Simple 2
Destructing Simple 1
```

### Improving the NetworkData Program

```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	~NetworkData()
	{
		sendData(); // make sure all data is sent before object is destroyed
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    return 0;
}
```

### An implicit destructor

If a non-aggregate class type object has no user-declared destructor, the compiler will generate a destructor with an empty body
- This destructor is called an implicit destructor and is effectively a placeholder

### A warning about the `std::exit()` function

When the program is terminated immediately, the program just ends
- Local variables are not destroyed first
- No destructor will be called

# 15.5 - Class templates with member functions

## Questions

1. Write a class template named Triad that has 3 private data members with independent type template parameters. The class should have a constructor, access functions, and a print() member function that is defined outside the class.

The following program should compile and run:

```cpp
#include <iostream>
#include <string>

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}
```

```cpp
#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad
{
private:

	T m_x {};
	U m_y {};
	V m_z {};

public:

	Triad(const T& x, const U& y, const V& z) : m_x {x}, m_y {y}, m_z {z}
	{

	}

	const T& first()
	{
		return m_x;
	}

	const U& second()
	{
		return m_y;
	}

	const V& third()
	{
		return m_z;
	}

	void print() const;
};

template <typename T, typename U, typename V>
void Triad<T, U, V>::print() const
{
	std::cout << "[" << m_x << ", " << m_y << ", " << m_z << "]";
}


int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}
```

2. If we remove the const from the print() function declaration and definition, the program will no longer compile. Why not?
- t2 is a const object, so only const member functions can be invoked on t2. If we make print() a non-const member function, then t2 is not allowed to call it. This is because a non-const member function could conceivably modify the implicit object, which would be a violation of the constness of the const object (t2 in this case).


## Notes

With a funciton template, we can define type template parameters and then use them as the type of our function parameter

```cpp
template <typename T> // this is the template parameter declaration
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```

Class templatesa llow us to use type template parameters for the type of our data members of class types

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (required in C++17 or older)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

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

### Type template parameters in member functions

Type template parameters defined as part of a class template parameter declaration can be used both as the type of data members and as the type of member function parameters

```cpp
#include <ios>       // for std::boolalpha
#include <iostream>

template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    // When we define a member function inside the class definition,
    // the template parameter declaration belonging to the class applies
    Pair(const T& first, const T& second)
        : m_first{ first }
        , m_second{ second }
    {
    }

    bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}
```

When we define a member funciton inside the class template definition, we don't need to provide a template parameter declaration for the member function
- Such member functions implicitly use the class template parameter declaration

We don't need deduction for CTAD to work with non-aggregate classes
- A matching constructor provides the compiler with the information it needs to deduce the template parameters from the initializers

```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

Since the member function definition is separate from the class template definition, we need to resupply a template parameter declaration so the compiler knows what `T` is
- When we define a member function outside of the class, we need to qualify the member function name with the fully templated name of the class template

### Injected class name

In our class template for `Pair<T>`, we named our constructor `Pair`, not `Pair<T>`

**Injected Class Name**: Within the scope of a class, the unqualified name of the class is called an injected class name, serves as shorthand for the fully templated name

`Pair` is the injected class name of `Pair<T>`, any use of `Pair` will be treated as if we had written `Pair<T>` instead

We can also define our `isEqual()` member like this:

```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair& pair) // note the parameter has type Pair, not Pair<T>
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

### Where to define member functions for class template outside the class

With member functions for class templates, teh compiler needs to see both the class definition and the template member function definition.
- We typically want to define both a class and its member function templates in the same location

When a member funciton template is defined *inside* the class definition, the template member function definition is part of the class definition
- Anywhere the class definition can be seen, the template member function definition can also be seen

When a member function template is defined *outside* the class definition, it should generally be defined immediately below the class definition
- Anywhere the class definition can be seen, the member funciton template definitions immediately below the class definition will also be seen

# 15.6 - Static member variables

## Notes

### Static member variables

Consider the following class

```cpp
#include <iostream>

struct Something
{
    int value{ 1 };
};

int main()
{
    Something first{};
    Something second{};

    first.value = 2;

    std::cout << first.value << '\n';
    std::cout << second.value << '\n';

    return 0;
}
```

Whenw e instantiate a class object, each object gets its own copy of all normal member variables

**Static Member Variables**: Shared by all objects of the class

```cpp
#include <iostream>

struct Something
{
    static int s_value; // declare s_value as static (initializer moved below)
};

int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)

int main()
{
    Something first{};
    Something second{};

    first.s_value = 2;

    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}
```

```shell
2
2
```

Because `s_value` is a static member variable, `s_value` is shared between all objects of the class

### Static Members are not associated with class objects

Although you can access static members through objects of the class, static members exist even if no object of the class have been instantiated

Static members are global variables that live inside the scoped region of the class
- Little difference betweence between a static member of a class and a normal variable inside a namespace

It can be accessed directly using the class name and the scope resolution operator

```cpp
class Something
{
public:
    static int s_value; // declare s_value as static
};

int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)

int main()
{
    // note: we're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
```

Best Practice: Access static members using the class name and the scope resolution

### Defining and initializing static member variables

When we declare a static member variable inside a class type, we're telling the compiler about the existence of a static member variable, but not actually defining it
- Static member variables are essentially global variables, must explicitly define the static memberoutside of the class

```cpp
int Something::s_value{ 1 }; // define and initialize s_value to 1
```

- Instantiates the static member variable
- Initializes it

You can define and initialize the value even if it's declared as private in the class

For non-template classes, if the class is defined in a header file, the static member definition is usually placed in the associated code file for the class
- The member can also be defined as `inlin` and placed below the class definition i the header

If the class is defined in a source file, the static member definition is usually placed directly underneath the class
- Do not put static member definition in a header file

For template classes, the (templated) static member definition is typically placed directly underneath the template class definition in the header file

### Initialization of static member variables inside the class definition

Few shortcuts to the above
- When the static member is a constant integral type, or a const enum, the static member can be initialized inside the class definition

```cpp
class Whatever
{
public:
    static const int s_value{ 4 }; // a static const int can be defined and initialized directly
};
```

Because the static member variable is a const int, no explicit definition line is needed
- Allowed because these specific const types are compile-time constants

```cpp
class Whatever
{
public:
    static inline int s_value{ 4 }; // a static inline variable can be defined and initialized directly
};
```

Such variables can be initialized inside the class definition regardless of whether they are constant or not
- Preferred method of defining and initializing static members

Because `constexpr` members are implicitly inline (as of C++17), static `constexpr` members can also be initialized inside the class definition without explicit use of the `inline` keyword

```cpp
#include <string_view>

class Whatever
{
public:
    static constexpr double s_value{ 2.2 }; // ok
    static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
};
```

Best Practice: Make your static members `inline` or `constexpr` so they can be initialized inside the class definition

### An example of static member variables

Why use static variables inside classes? One use is to assign a unique ID to every instance of the class. Here’s an example

```cpp
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 };
    int m_id {};

public:
    // grab the next value from the id generator
    Something() : m_id { s_idGenerator++ }
    {
    }

    int getID() const { return m_id; }
};

int main()
{
    Something first{};
    Something second{};
    Something third{};

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
```

```shell
1
2
3
```

Gives each object a unique ID can help when debugging, as it can be used to differentiate objects that otherwise have identical data

Static member variables are also useful when the class needs to utilize a lookup tble

By making the lookup table static, only one copy exists for all objects, rather than making acopy for each object instantiated

### Only static members may use type deduction (`auto` and CTAD)

A static member may use `auto` to deduce its type from the initializer, or Class Template Argument Deduction (CTAD) to deduce template type arguments from the initializer

Non-static members may not use `auto` or CTAD

```cpp
#include <utility> // for std::pair<T, U>

class Foo
{
private:
    auto m_x { 5 };           // auto not allowed for non-static members
    std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members

    static inline auto s_x { 5 };           // auto allowed for static members
    static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members

public:
    Foo() {};
};

int main()
{
    Foo foo{};

    return 0;
}
```

# 15.7 - Static Member Functions

## Questions

1. Convert the Random namespace in the following example to a class with static members:

```cpp
#include <chrono>
#include <random>
#include <iostream>

namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}
}

int main()
{
	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 10; ++count)
		std::cout << Random::get(1, 6) << '\t';

	std::cout << '\n';

	return 0;
}
```

```cpp
#include <chrono>
#include <random>
#include <iostream>

class Random
{
private:
	static std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	static inline std::mt19937 mt{ generate() };

public:

	static inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}
};

int main()
{
	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 10; ++count)
		std::cout << Random::get(1, 6) << '\t';

	std::cout << '\n';

	return 0;
}
```

## Notes

Static member variables are member variables that belong to the class rather than the object

What happens if a static variable is private?

```cpp
#include <iostream>

class Something
{
private: // now private
    static inline int s_value { 1 };
};

int main()
{
    std::cout << Something::s_value; // error: s_value is private and can't be accessed directly outside the class
}
```

We can't access `Something::s_value` directly from `main()`

### Static member functions

Member functions can be made static as well

```cpp
#include <iostream>

class Something
{
private:
    static inline int s_value { 1 };

public:
    static int getValue() { return s_value; } // static member function
};

int main()
{
    std::cout << Something::getValue() << '\n';
}
```

Static member functions are not associated with a particular object
- They can be called directly using the (`Something::getValue()`)
- Can also be called through objects of the class type, though not recommended

### Static member functions have no `this` pointer

1. Static member functions have no `this` pointer
2. Static member functions can directly access other static members, but not non-static members

### Static members defined outside of the class definition

Static member functions can also be defined outside of the class declaration
- Works the same way as for normal member functions

```cpp
#include <iostream>

class IDGenerator
{
private:
    static inline int s_nextID { 1 };

public:
     static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; }

int main()
{
    for (int count{ 0 }; count < 5; ++count)
        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

    return 0;
}
```

```shell
The next ID is: 1
The next ID is: 2
The next ID is: 3
The next ID is: 4
The next ID is: 5
```

Because all the data and functions int he class are static, we don't need to instantiate an object of the class to make use of its functionality

Member functions defined inside the class definition are implicitly inline
- Member functions defined outside the class definition are not implicitly inline, but can be made inline

### A word of warning about classes with all static members

"Pure static classes" also called "monostates" can be useful, they have some downsides
1. Because all static members are instantied only once, there is no way to have multiple copies of a pure static class
2. Because all of the members belong to the class, and class declarations usually have global scope, a pure static class is essentially the equivalent of declaring functions and global variables in a globally accessible namespace
    - Has all the downsides of global variables

### Pure static classes vs namespaces

Pure static classes have a lot of overlap with namespaces

One significant difference is that class have access controls while namespaces do not

A static class is preferable when you have static data members and/or need access control

### C++ does not support static constructor

If you can initalize normal member variables via a constructor, then by extension it makes sense that you should be able to initalize static member variables via a static constructor

```cpp
#include <iostream>

struct Chars
{
    char first{};
    char second{};
    char third{};
    char fourth{};
    char fifth{};
};

struct MyClass
{
	static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
};

int main()
{
    std::cout << MyClass::s_mychars.third; // print i

    return 0;
}
```

If iniitalizing your static member variables requires executing code, there are many different ways to do it

One way is to use a function to create an object, fill it with data, and return it to the caller

```cpp
#include <iostream>

struct Chars
{
    char first{};
    char second{};
    char third{};
    char fourth{};
    char fifth{};
};

class MyClass
{
private:
    static Chars generate()
    {
        Chars c{}; // create an object
        c.first = 'a'; // fill it with values however you like
        c.second = 'e';
        c.third = 'i';
        c.fourth = 'o';
        c.fifth = 'u';

        return c; // return the object
    }

public:
	static inline Chars s_mychars { generate() }; // copy the returned object into s_mychars
};

int main()
{
    std::cout << MyClass::s_mychars.third; // print i

    return 0;
}
```

# 15.8 - Friend non-member functions

## Notes

There are situations where access contorl is either not sufficient or not ideal

Need a way to subvert the access control system on a case by case basis

### Friendship is magic

**Friend Declaration**: `friend` keyword, can be used to tell the compiler that some other class or function is now a friend

**Friend**: A class/function that has been granted full access to the private and protected members of another class
- A class can selectively give other classes or functions full access to their members without impacting anything else

Friend declaration is not affected by access control, it doesn't matter where within the class boydy it is placed

### Friend non-member functions

**Friend Function**: A function that can access the private and protected members of a class as though it were a member of that class
- Other regards, the friend funciton is a normal function

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    // Because print() is a friend of Accumulator
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```

Declared a non-member function named `print(0)` that takes an object of class `Accumulator`

Because `print()` is not a member of the Accumulator class, it would normally not be able to access private members
- The Accumulator class has a friend declaration, access is now allowed

`print()` is a non-member function, we must explicitly pass an `Accumulator` object to `print()` to work with

### Defining a friend non-member inside a class

Much like member funcitons can be defined inside a class if desired, friend non-member functions can also be defined inside a class

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Friend functions defined inside a class are non-member functions
    friend void print(const Accumulator& accumulator)
    {
        // Because print() is a friend of Accumulator
        // it can access the private members of Accumulator
        std::cout << accumulator.m_value;
    }
};

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```

Becuase `print()` is defined as a friend, it is instead treated as a non-member function

### Syntactically preferring a friend non-member function

There were times we might prefer to use a non-member function over a member function

```cpp
#include <iostream>

class Value
{
private:
    int m_value{};

public:
    explicit Value(int v): m_value { v }  { }

    bool isEqualToMember(const Value& v) const;
    friend bool isEqualToNonmember(const Value& v1, const Value& v2);
};

bool Value::isEqualToMember(const Value& v) const
{
    return m_value == v.m_value;
}

bool isEqualToNonmember(const Value& v1, const Value& v2)
{
    return v1.m_value == v2.m_value;
}

int main()
{
    Value v1 { 5 };
    Value v2 { 6 };

    std::cout << v1.isEqualToMember(v2) << '\n';
    std::cout << isEqualToNonmember(v1, v2) << '\n';

    return 0;
}
```

We defined 2 similar functions that check whether 2 `Value` objects are equal

`isEqualToMember()` is a member function, `isEqualToNonMember()` is a non-member function

`isEqualToMember()`, we're passing one object implicitly and the other explicitly
- We have to mentally reconcile that `m_value` belongs to the implicit object whereas `v.m_value` belongs to the explicit parameter

`isEqualToNonMember()`, both objects are passed explicitly
- Leads to better parallelism in the implementation of the function
- `m_value` is always explicitly prefixed with an explicit parameter

### Multiple Friends

A function can be a friend of more than one class at the same time

```cpp
#include <iostream>

class Humidity; // forward declaration of Humidity

class Temperature
{
private:
    int m_temp { 0 };
public:
    explicit Temperature(int temp) : m_temp { temp } { }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
};

class Humidity
{
private:
    int m_humidity { 0 };
public:
    explicit Humidity(int humidity) : m_humidity { humidity } {  }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
    std::cout << "The temperature is " << temperature.m_temp <<
       " and the humidity is " << humidity.m_humidity << '\n';
}

int main()
{
    Humidity hum { 10 };
    Temperature temp { 12 };

    printWeather(temp, hum);

    return 0;
}
```

3 things worth noting:
- `printWeather()` uses both `Humidity` and `Temperature` equally
    - Doesn't really make sense to have it be a member of either
- Because `printWeahter()` is a friend of both `Humidity` and `Temperature`, it can access the private data from objects of both classes

```cpp
class Humidity;
```

This is a forward declaration for `class Humidity`. Class forward declarations serve the same role as funciton forward declarations
- Tell the compiler about an identifier that will be defined later
- Unlike functions, classes have no return type or parameters, so class forward declarations are always simply `class ClassName`

### Doesn't friendship violate the principle of data hiding

No, Friendship is granted by the class doing the data hiding with the expectation that the friend will access its private members

Friendship can make a program more maintainable by allowing functionality to be separated when it makes sense from a design perspective
- Or when it makes more sense to use a non-member function instead of a member function

Because friends have direct access to the implementation of a class, changes to the implementation of the class will typically necessitate changes to the friends as well
- If a class has many friends, this can lead to a ripple effect

Best Practice: A friend function should prefer to use the class interface over direct access whenever possible

### Prefer non-friend functions to friend functions

We should prefer non-friend functions over friend functions

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 }; // if we rename this

public:
    void add(int value) { m_value += value; } // we need to modify this

    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    std::cout << accumulator.m_value; // and we need to modify this
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```

A better idea is as follows:

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }
    int value() const { return m_value; } // added this reasonable access function
};

void print(const Accumulator& accumulator) // no longer a friend of Accumulator
{
    std::cout << accumulator.value(); // use access function instead of direct access
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}

```

Best Practice: Prefer to implement a funciton as a non-friend when possible and reasonable

# 15.9 - Friend classes and friend member functions

## Questions

1. In geometry, a point is a position in space. We can define a point in 3d-space as the set of coordinates x, y, and z. For example, Point { 2.0, 1.0, 0.0 } would be the point at coordinate space x=2.0, y=1.0, and z=0.0.

In physics, a vector is a quantity that has a magnitude (length) and a direction (but no position). We can define a vector in 3d-space as an x, y, and z value representing the direction of the vector along the x, y, and z axis (the length can be derived from these). For example, Vector { 2.0, 0.0, 0.0 } would be a vector representing a direction along the positive x-axis (only), with length 2.0.

A Vector can be applied to a Point to move the Point to a new position. This is done by adding the vector’s direction to the point’s position to yield a new position. For example, Point { 2.0, 1.0, 0.0 } + Vector { 2.0, 0.0, 0.0 } would yield Point { 4.0, 1.0, 0.0 }.

Such points and vectors are often used in computer graphics (with points representing the vertices of a shape, and vectors represent movement of the shape).

```cpp
#include <iostream>

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x, double y, double z)
		: m_x{x}, m_y{y}, m_z{z}
	{
	}

	void print() const
	{
		std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}
};

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z)
		: m_x{x}, m_y{y}, m_z{z}
	{ }

	void print() const
	{
		std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
	}

	void moveByVector(const Vector3d& v)
	{
		// implement this function as a friend of class Vector3d
	}
};

int main()
{
	Point3d p { 1.0, 2.0, 3.0 };
	Vector3d v { 2.0, 2.0, -3.0 };

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}
```

## Notes

### Friend Classes

**Friend Class**: A class that can access the private and protected members of another class

```cpp
#include <iostream>

class Storage
{
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue)
       : m_nValue { nValue }, m_dValue { dValue }
    { }

    // Make the Display class a friend of Storage
    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst {};

public:
    Display(bool displayIntFirst)
         : m_displayIntFirst { displayIntFirst }
    {
    }

    // Because Display is a friend of Storage, Display members can access the private members of Storage
    void displayStorage(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else // display double first
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }

    void setDisplayIntFirst(bool b)
    {
         m_displayIntFirst = b;
    }
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayStorage(storage);

    display.setDisplayIntFirst(true);
    display.displayStorage(storage);

    return 0;
}
```

Because the `Display` class is a friend of `Storage`, `Display` members can access the private members of any `Storage` object they have access to 

```shell
6.7 5
5 6.7
```

Even though `Display` is a friend of `Storage`, `Display` has no access to the `*this` pointer of `Storage` objects

Friendship is not reciprocal, just because `Display` is a friend of `Storage` doesn't mean `Storage` is also a friend of `Display`

Class friendship is also not transitive
- If class A is friend of B, and B is a friend of C, doesn't mean A is friend of C

A friend class declaration acts as a forward declaration for the class being friended.
- We don't need to frward declare the class being friended before friending it

### Friend member functions

Instead of making an entire class a friend, you can make a single member function a friend.
- Done similarly to making a non-member function a friend, except the name of the member function is used instead

In actuality, this can be a little trickier than expected

```cpp
#include <iostream>

class Display; // forward declaration for class Display

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	friend void Display::displayStorage(const Storage& storage); // error: Storage hasn't seen the full definition of class Display
};

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage)
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}
```

This won't work, in order to make a single member function a friend, the compiler has to have seen the full definition for the class of the friend member funciton.
- Since class `Storage` hasn't seen the full definition for class `Display` yet, the compiler will error at the point where we try to make the member function a friend

Easily resolved by moving the definition of class `Display` before the definition of class `Storage`

```cpp
#include <iostream>

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage) // compile error: compiler doesn't know what a Storage is
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}
};

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	friend void Display::displayStorage(const Storage& storage); // okay now
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}
```

We now have another problem. Because member function `Display::displayStorage()` uses `Storage` as a reference parameter, and we just moved the definition of `Storage` below the definition of `Display`

Compiler will complain it doesn't know what a `Storage` is

We can add `class Storage` as a forward declaration so the compiler will be okay with a reference to `Storage` before it has seen the full definition of the class

We can move the definition of `Display::displayStorage()` out of the class, after the full definition of `Storage` class

```cpp
#include <iostream>

class Storage; // forward declaration for class Storage

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage); // forward declaration for Storage needed for reference here
};

class Storage // full definition of Storage class
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	// Requires seeing the full definition of class Display (as displayStorage is a member)
	friend void Display::displayStorage(const Storage& storage);
};

// Now we can define Display::displayStorage
// Requires seeing the full definition of class Storage (as we access Storage members)
void Display::displayStorage(const Storage& storage)
{
	if (m_displayIntFirst)
		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
	else // display double first
		std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}
```

# 15.10 - Ref Qualifiers

## Notes

### Ref Qualifiers

**Ref-Qualifiers**: Allows us to overload a member function based on whether it is being called on an lvalue or an rvalue implicit object

Can create 2 versions of `getName()` - one for the case where our implicit object is an lvalue, and one for the case where our implicit object is an rvalue

To ref-qualify a function, we add a `&` qualifier to the overload that will match only lvalue implicit objects
- `&&` qualifiers to the overload that will match only rvalue implicit objects

```cpp
const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects, returns by reference
std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects, returns by value
```

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
	std::string m_name{};

public:
	Employee(std::string_view name): m_name { name } {}

	const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects
	std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e { name };
	return e;
}

int main()
{
	Employee joe { "Joe" };
	std::cout << joe.getName() << '\n'; // Joe is an lvalue, so this calls std::string& getName() & (returns a reference)

	std::cout << createEmployee("Frank").getName() << '\n'; // Frank is an rvalue, so this calls std::string getName() && (makes a copy)

	return 0;
}
```

Allows us to do the performant thing when our implicit object is an lvalue, and the safe thing when our implicit object is an rvalue

### Some notes about ref-qualified member functions

- For a given funciton, non-ref-qualified overloads and ref-qualified overloads cannot coexist. Use 1 or the other
- Similar to how a const lvalue reference can bind to an rvalue, if only a const lvalue-qualified function exists, it will accept either lvalue or rvalue implicit objects
- Either qualified overload can be explicitly deleted (using `= delete`), which prevents calls to that function.
  - Example: Deleting the rvalue-qualified version prevents use of the funciton with rvalue implicit objects

### So why don't we recommend using ref-qualifiers?

Downsides:
- Adding rvalue overloads to every getter that returns a reference adds clutter to the class
- Having an rvalue overload return by value means we have to pay for the cost of a copy (or more) even in cases where we could have used a reference safely
- Most C++ developers are not aware of ths feature
- The standard library typically does not make use of this feature

# 15.x - Chapter 15 summary and quiz

## Review

- `this`: The keyword that is a const pointer that holds the address  of the current implicit object
- **Method Chaning**: Several member functions can be called on the same object in a single expression
- **Nested Type**: A type that is defined inside a class type
- **Static Member Variables**: Static duration members that are shared by all objects of the class
- **Static Member Functions**: Member functions that can be called with no object
- **Friend Declaration**: Using the `friend` keyword, can be used to tell the compiler that some other class or funciton is now a friend
- **Friend**: A class/function that has been granted full access to the private and protected members of another class
- **Friend Function**: A function that can access the private and protected members of a class as though it were a member of that class
- **Friend Class**: A class that can access the private and protected members of another class
