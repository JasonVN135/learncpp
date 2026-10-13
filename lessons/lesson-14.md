# 14.1 - Introduction to Object Oriented Programming

## Notes

### Procedural Programming

**Procedural Programming**: The focus is on creating "procedures" that implement our program logic
- Pass data objects to these functions
- Those functions perform operations on the data, then potentially return a result to be used by the caller

The functions and the data those functions operate on are separate entities

In programming properties are represented by objects, and behaviors are represented by functions
- Procedural programming represents reality fairly poorly

### What is object-oriented programming?

**Object-Oriented Programming**: The focus is on creating program-defined data types that contain both properties and a set of well-defined behaviors

Because the properties and behaviors are no longer separate, objects are easier to modularize
- Makes programs easier to write and understand, also provide a higher degree of code reusability
- Provide a more intuitive way to work with out data by allowing us to define how we interact with the object

### A procedural vs OOP-Like example

Procedural:

```cpp
#include <iostream>
#include <string_view>

enum AnimalType
{
    cat,
    dog,
    chicken,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    default:  return 0;
    }
}


int main()
{
    constexpr AnimalType animal{ cat };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

    return 0;
}
```

OOP Mindset

```cpp
#include <iostream>
#include <string_view>

struct Cat
{
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog
{
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken
{
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};

int main()
{
    constexpr Cat animal;
    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

    return 0;
}
```

If we wanted to update our animal to a snake, all we had to do is create a `Snake` type anduse it instead of `Cat`
- Very little existing code needs to be changed
- Less risk of breaking something that already works

### OOP Brings other benefits to the table

Best way to keep your code good is to keep it as modular as possible
- OOP also brings a number of useful concepts to the table
  - Inheritance
  - Encapsulation
  - Abstraction
  - Polymorphism

OOP Doesn't replace procedural programming
- It gives you additional tools in your programming tool belt to manage complexity when needed

### The term "object"

In traditional programming, an object is a piece of memory to store values, and that's it

In OOP, an "object" implies that it is both an object in the traditional programming sense, and that it combines both properties and behaviors

# 14.2 - Introduction to Classes

## Notes

### The class invariant problem

Structs do not provide an effective way to document and enforce class invariant

**Class Variant**: A condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state
- An object that has a violated class invariant is said to be in an **invalid state**, and unexpected or undefined behavior may result from further use of that object

```cpp
struct Fraction
{
    int numerator { 0 };
    int denominator { 1 };
};
```

Nothing prevents us from explicitly violating this class invariant
- We use aggregate initialization to explicitly initialize the denominator to `0`.
- Our object is now in an invalid state

### A more complex class invariant

```cpp
#include <string>

struct Employee
{
    std::string name { };
    char firstInitial { }; // should always hold first character of `name` (or `0`)
};
```

The user is responsible that `firstInitial` is updated properly whenever `name` gets updated
- We're relying on the user to be aware of and use these function that can help handle these problems

We'd love to bullet proof our class types so that an object either can't be put into an invalid state, or can signal immediately if it is 

### Introduction to Classes

**Class**: A program-defined compound type that can have many member variables with different types

### Defining a class

Because a class is a program-defined data type, it must be defined before it can be used
- Classes are defined similarly to struct, except we use the `class` keyword

```cpp
class Employee
{
    int m_id {};
    int m_age {};
    double m_wage {};
};
```

```cpp
#include <iostream>

class Date       // we changed struct to class
{
public:          // and added this line, which is called an access specifier
    int m_day{}; // and added "m_" prefixes to each of the member names
    int m_month{};
    int m_year{};
};

void printDate(const Date& date)
{
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
}

int main()
{
    Date date{ 4, 10, 21 };
    printDate(date);

    return 0;
}
```

### Most of the C++ standard library is classes

Both `std::string` and `std::string_view` are defined as classes
- Most of the non-aliased types in the standard library are defined as classes

# 14.3 - Member Functions

## Questions

1. Create a struct called IntPair that holds two integers. Add a member function named print that prints the value of the two integers.

The following program function should compile:

```cpp
#include <iostream>

// Provide the definition for IntPair and the print() member function here

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	return 0;
}
```

```shell
p1: Pair(1, 2)
p2: Pair(3, 4)
```

```cpp
struct IntPair
{

	int x {};
	int y {};

	void print()
	{
		std::cout << "Pair(" << x << ", " << y << ")\n";
	}
};
```

2. Add a new member function to IntPair named isEqual that returns a Boolean indicating whether one IntPair is equal to another.

The following program function should compile:

```cpp
#include <iostream>

// Provide the definition for IntPair and the member functions here

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}
```

```shell
p1: Pair(1, 2)
p2: Pair(3, 4)
p1 and p1 are equal
p1 and p2 are not equal 
```

```cpp
struct IntPair
{

	int x {};
	int y {};

	void print()
	{
		std::cout << "Pair(" << x << ", " << y << ")\n";
	}

	bool isEqual(const IntPair& pair)
	{
		return (x == pair.x) && (y == pair.y);
	}
};
```

## Notes

```cpp
#include <iostream>

struct Date
{
    // here are our member variables
    int year {};
    int month {};
    int day {};
};

void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    print(today);   // non-member function accessed using normal calling convention

    return 0;
}
```

### The separation of properties and actions

In programming, we represent properties with variables and actions with functions

While we could put both `Date` and `print()` into a namespace to make it clearer that the twi are meant to be packaged together, that adds more names into our program and more namespace prefixes

### Member Functions

**Member Functions**: Class types can also have their own functions\
**Non-Member Functions**: Functions that are not member functions

Member functions must be declared inside the class type definition, and can be defined inside or outside of the class type definition
- A definition is also a declaration, so if we define a member functoin inside the class, that counts as a declaration

### A member function example

```cpp
// Member function version
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}
```

This program compiles the same result

3 differences between the non-member and member example
1. Where we declare and define the `print()` function
2. How we call the `print()` function
3. How we access members inside the `print()` funciton

### Member functions are declared inside the class definition

In the non-member example, `print()` non-member functoin is defined outside of the `Data` struct in global namespace
- Has external linkage, it could be called from other source files

Member example, the `print()` member funciton is declared inside the `Data` struct definition
- `print()` is declared as part of the `Date`, this tells teh compiler `print()` is a member function
- Member functions defined inside the class type definition are implicitly inline
- They will not cause violations of the one-definition rule if the class type definition is included into multiple code files

### Calling member functions (and the implicit object)

In the non-member example, we call `print(today)`

In the member example, we call `today.print()`
- The syntax is consistent with how we access member variables (e.g. `today.day = 16`)

All (non-static) member funcitons must be called using an object of that class type
- The member function case, we don't need to pass `today` as an argument
- The object that a member function is called on is *implicitly* passed to the member function

**Implicit Object**: The object that a member function is called on

### Accessing members inside a member function using the implicit object

```cpp
void print() // defines a member function named print()
{
    std::cout << year << '/' << month << '/' << day;
}
```

In the member, example, we access the members as `year`, `month`, and `day`
- Inside a member function, any member identifier that is not prefixed with the member selection operator is associated with the implicit object
- When `today.print()` is called, `today` is our implicit object
  - `year`, `month`, and `day` evaluated to the values of `today.year`, `today.month`, and `today.day`

### Another member function example

```cpp
#include <iostream>
#include <string>

struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " kisses " << person.name << '\n';
    }
};

int main()
{
    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };

    joe.kisses(kate);

    return 0;
}
```

First we define 2 `Person` structs, then call `joe.kisses(kate)`
- `joe` is the implicit object here, and `kate` is passed as an explicit argument
- The identifier `name` doeesn't use the member selection operator, so it refers to the implicit object
- `person.name` uses the member selection operator, so it does not refere to the implicit object

### Member variables and functions can be defined in any order

The C++ compiler normally compils code from top to bottom. For each name encountered, the compiler determines whether it has already seen a declaration for that name

Non-members must be declared before they can be used, or the compiler will complain

```cpp
int x()
{
    return y(); // error: y not declared yet, so compiler doesn't know what it is
}

int y()
{
    return 5;
}
```

Inside a class definition, this restriction doesn't apply
- You can access member variables and member functions before they are declared
- You can define member variables and member functions in any order you like

```cpp
struct Foo
{
    int z() { return m_data; } // We can access data members before they are defined
    int x() { return y(); }    // We can access member functions before they are defined

    int m_data { y() };        // This even works in default member initializers (see warning below)
    int y() { return 5; }
};
```

Data members are initialized in order of declaration
- If the initialization of a data member accesses another data member that isn't declared until later, the initialization will result in undefined behavior

### Member functions can be overloaded

Member functons can be overloaded, so long as each member function can be differentiated

```cpp
#include <iostream>
#include <string_view>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }

    void print(std::string_view prefix)
    {
        std::cout << prefix << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 };

    today.print(); // calls Date::print()
    std::cout << '\n';

    today.print("The date is: "); // calls Date::print(std::string_view)
    std::cout << '\n';

    return 0;
}
```

```shell
2020/10/14
The date is: 2020/10/14
```

### Structs and member functions

In C, structs only have data members, not member functions

In C++, it is fine for structs to have member functions
- This excludes constructors, which are a special type of member function
- A class type with a constructor is on longer an aggregate, and we want our structs to remain aggregates

Best Practice: structs should avoid defining constructor member functions

### Class types with no data members

It is possible to create class types with no data members
- Also possible to instantiate objects of such a class type

```cpp
#include <iostream>

struct Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo f{};
    f.printHi(); // requires object to call

    return 0;
}
```

Using a class type with no data members is overkill, using a namespace is better

```cpp
#include <iostream>

namespace Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo::printHi(); // no object needed

    return 0;
}
```

# 14.4 - Const Class Objects and Const Member Functions

## Notes

All const variables must be initialized at time of creation

```cpp
const int x;      // compile error: not initialized
const int y{};    // ok: value initialized
const int z{ 5 }; // ok: list initialized
```

Class type objects (struct, class, unions) can also be made const by using the `const` keyword
- Must be initialized at the time of creation

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};

int main()
{
    const Date today { 2020, 10, 14 }; // const class type object

    return 0;
}
```

You'll generally want to make your class type objects const (or constexpr) when you need to ensure they aren't modified after creation

### Modifying the data members of const objects is disallowed

Once a const class type object has been iniitalized, any attempt to modify the data members of the object is disallowed
- It would violate the const-ness of the object
- Includes:
  - changing member variables directly
  - calling member functions that set the value of member variables

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object

    return 0;
}
```

### Const objects may not call non-const member functions

This code will cause a compilation error

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // compile error: can't call non-const member function

    return 0;
}
```

Even though `print()` doesn't try to modify a member variable, our call to `today.print()` is still a const violation. 
- This happens because the `print()` member function itself is not declared as a const
- Compiler won't let us call a non-const member function on a const object

### Const member functions

**Const Member Function**: A member function that guarantees it will not modify the object or call any non-const member functions

Making `print()` a const member function is easy - simply append the `const keyword to the function prototype after the parameter list, but before the function body

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // ok: const object can call const member function

    return 0;
}
```

A const member function that attempts to change a data member or call a non-const member function will cause a compiler error to occur

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay() const // made const
    {
        ++day; // compile error: const function can't modify member
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.incrementDay();

    return 0;
}
```

Const member functions can modify non-members and call non-member functions per usual

### Const member functions may be called on non-const objects

Const member functions may also be called on non-const objects

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // non-const

    today.print();  // ok: can call const member function on non-const object

    return 0;
}
```

Const member functions can be called on both const and non-const objects, if a member function doesn't modify the state of the object, it should be made const

Once a member function is made const, that function can be called on const objects
- Removal of `const` on a member function will break any code that calls that member function on a const object

### Const objects via pass by const reference

Although instantiating const local variables is 1 way to create const objects, a more common way to get a const object is by passing an object to a function by const reference

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // non-const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

Inside of the `doSomething()` function, `date` is treated as a const object
- With that const `date`, we're calling a non const member function
- We can't call non-const member functions on const objects, this will cause a compiler error

Simply make `print()` const:

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

### Member function const and non-const overloading

Although it is not done very often, it is possible to overload a member function to have a const and non-const version of the same funcion
- Works because the const qualifier is considered part of the function's signature
- 2 functions which differ only in their const-ness are considered distinct

```cpp
#include <iostream>

struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

int main()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const

    return 0;
}
```

```shell
non-const
const
```

Only typically done when the return value needs to differ in constness.
- Pretty rare

# 14.5 - Public and private member and access specifiers

## Questions

1. 
a. What is a public member?
- A public member is a member of a class that can be accessed by anyone, including other members of the same class and the public.
b. What is a private member?
- A private member is a member of a class that can only be accessed by other members of the class.
c. What is an access specifier?
- An access specifier determines who has access to the members that follow the specifier.
d. How many access specifiers are there, and what are they?
- 3, `public:`, `private:`, and `protected:`

2. 
a. Write a class named Point3d. The class should contain:

Three private member variables of type int named m_x, m_y, and m_z;
A public member function named setValues() that allows you to set values for m_x, m_y, and m_z.
A public member function named print() that prints the Point in the following format: <m_x, m_y, m_z>

```cpp
int main()
{
    Point3d point;
    point.setValues(1, 2, 3);

    point.print();
    std::cout << '\n';

    return 0;
}
```

```shell
<1, 2, 3>
```

```cpp
#include <iostream>

class Point3d
{
private:
	int m_x {};
	int m_y {};
	int m_z {};

public:
	void setValues(int x, int y, int z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void print()
	{
		std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">";
	}
};
```

b. Add a function named isEqual() to your Point3d class. The following code should run correctly:

```cpp
int main()
{
	Point3d point1{};
	point1.setValues(1, 2, 3);

	Point3d point2{};
	point2.setValues(1, 2, 3);

	std::cout << "point 1 and point 2 are" << (point1.isEqual(point2) ? "" : " not") << " equal\n";

	Point3d point3{};
	point3.setValues(3, 4, 5);

	std::cout << "point 1 and point 3 are" << (point1.isEqual(point3) ? "" : " not") << " equal\n";

	return 0;
}
```

```shell
point 1 and point 2 are equal
point 1 and point 3 are not equal
```

```cpp
class Point3d
{
private:
	int m_x {};
	int m_y {};
	int m_z {};

public:
	void setValues(int x, int y, int z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void print()
	{
		std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">";
	}

	bool isEqual(const Point3d& point)
	{
		return (m_x == point.m_x) && (m_y == point.m_y) && (m_z == point.m_z);
	}
};
```

## Notes

### Member Access

**Access Level**: Each member of a class type has a property that determines who can access that member

C++ has 3 levels: public, private, and protected

Whenever a member is accessed, the compiler checks whether the access level of the member permits that member to be accessed
- If the access is not permitted, the compiler will generate a compilation error

**Access Control**: The access level system that permits or stops access

### The members of a struct are public by default

**Public Members**: Members of a class type that do not have any restrictions on how they can be accessed
- Public members can be accessed by anyone as long as they are in scope

Public members can be accessed by other members of the same class
- Can also be accessed by **The Public**, what we call code that exists outside the members of a given class type
- Include non-member functions, as well as the members of other class types

All members of a struct are public members

```cpp
#include <iostream>

struct Date
{
    // struct members are public by default, can be accessed by anyone
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        // public members can be accessed in member functions of the class type
        std::cout << year << '/' << month << '/' << day;
    }
};

// non-member function main is part of "the public"
int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    // public members can be accessed by the public
    today.day = 16; // okay: the day member is public
    today.print();  // okay: the print() member function is public

    return 0;
}
```

Members are accessed in 3 places
- Within member function `print()`, we acess the `year`, `month`, and `day` members of the implicit objects
- In `main()`, we directly access `today.day` to set its value
- In `main()`, we call member function `today.print()`

All are allowed because public members can be accessed from anywhere

`main()` is not a meber of `Date`, it is considered to be part of the public
- Because the public has access to public members, `main()` can directly access the members of `Date`

### The members of a class are private by default

**Private Members**: Members of a class type that can only be accessed by other members of the same class

```cpp
#include <iostream>

class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private

    return 0;
}
```

Members are accessed in the same 3 places;
- Within members function `print()`, we access the `m_year`, `m_month`, and `m_day` members of the implicit object
- In `main()`, we directly access `today.m_day` to set its value
- In `main()`, we call member function `today.print()`

If you compile this program, you will note that 3 compilation errors are generated

The statements `today.m_day = 16` and `today.print()` now both generate compilation errors

Within `print()`, access to members `m_year`, `m_month` and `m_day` is allowed
- Because `print()` is a member of the class and members of the class are allowed to access private members

The iniitalization of `today` now causes a compilation error
- Our `Date` class has private data members, so our `Date` class does not qualify as an aggregate
- Can not use aggregate initialziation to initialize it any more

### Naming your private members variables

In C++, it is a common convention to name private data members starting with an "m_" prefix

```cpp
// Some member function that sets private member m_name to the value of the name parameter
void setName(std::string_view name)
{
    m_name = name;
}
```

The "m_" prefix allows us to easily differentiate data members from function parameters or local variables within a member function
- Can easily see that "m_name" is a member, and "name" is not
- Makes it clear that this function is changing the state of the class

Same reason we recommend using "s_" prefixes for local static variables and "g_" prefixes for globals

If we had named our private member `name` isntead of `m_name`:
- Our `name` funciton parameter would have shadowed the `name` private data member
- If we had a member function named `name`, we'd get a compile error due to a redefinition of idnetifier `name`

### Setting access levels via access specifiers

**Access Specifiers**: An access specifier sets the access level of all members that follow the specifier

C++ provides 3 access speicifers: `public`, `private`, and `protected`

```cpp
class Date
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
```  

`print()` is a public member due to the `public:` access specifier

Because we have private members, we can not aggregate initialize `d`
- We're using default member initialization instead

Since classes default to private access, you can omit a leading `private:` access specifier

Because classes and structs have different access level defaults, many developers prefer to be explicit

```cpp
class Foo
{
private: // redundant, but makes it clear that what follows is private
    int m_something {};  // private by default
};
```

### Access Level Summary

Access Level Public:
- Access Specifier: `public:`
- Member Access: yes
- Derived Class Access: yes
- Public Access: Yes
Access Level Private:
- Access Specifier: `private:`
- Member Access: Yes
- Derived Class Access: Yes
- Public Access: Yes
Access Level Protected:
- Access Specifier: `protected:`
- Member Access: Yes
- Derived Class Access: No
- Public Access: No

### Access Level Best Practices for Structs and Classes

Structs should avoid access specifiers altogether, meaning all struct members will be public be default
- We want structs to be aggregates, and aggregates can only have public members

Classes should generally only have private data members\
Classes normally have public member functions
- Occassionally member functions are made private if they are not intended to be used by the public

### Access levels work on a per-class basis

Access to members is defined on a per class basis, not a per-object basis

Member functions can directly access private members
- Because access levels are per-class, not per-object, a member function can also directly access the private members of ANY other object ont he same class type that is in scope

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name{};

public:
    void kisses(const Person& p) const
    {
        std::cout << m_name << " kisses " << p.m_name << '\n';
    }

    void setName(std::string_view name)
    {
        m_name = name;
    }
};

int main()
{
    Person joe;
    joe.setName("Joe");

    Person kate;
    kate.setName("Kate");

    joe.kisses(kate);

    return 0;
}
```

### The technical and practical difference between structs and classes

The only difference is that class defaults its members to private while structs defaults its members to public

Use a struct when all of the following are true:
- You have a simple collection of data that doesn't benefit from restricting access
- Aggregate initialzation is sufficient
- You have no class invariatns, setup needs, or cleanup needs

Use a class otherwise

# 14.6 - Access Functions

## Notes

### Access Functions

**Access Functions**: A trivial public member function whose job is to retrieve or change the value of a private member variable

Comes in 2 flavors:
- **Getters**: Public member functions that return the vlue of a private member variable
- **Setters**: Public member functions that set the value of a private member variable

Getters are usually made const, so they can be called on both const and non-const objects\
Setters should be non-const, so they can modify the data members

```cpp
#include <iostream>

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year

    int getMonth() const  { return m_month; }     // getter for month
    void setMonth(int month) { m_month = month; } // setter for month

    int getDay() const { return m_day; }          // getter for day
    void setDay(int day) { m_day = day; }         // setter for day
};

int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
```

```shell
The year is : 2021
```

### Access function naming

There is no common convention for naming acess funcitons
- Few naming conventions that are more popular than others

Prefix with "get" and "set"

```cpp
int getDay() const { return m_day; }  // getter
void setDay(int day) { m_day = day; } // setter
```

No prefix

```cpp
int day() const { return m_day; }  // getter
void day(int day) { m_day = day; } // setter
```

The no-prefix convention is not particularly obvious that this is setting hte value of the day member

"set" prefix only

```cpp
int day() const { return m_day; }     // getter
void setDay(int day) { m_day = day; } // setter
```

Highly recommend using the "set" prefix for setters\
Getters can use either a "get" prefix or no prefix

### Getters should geturn by value or by const lvalue reference

Getters should provide "read-only" access to data
- Best practice is that they should return by either value or by const lvalue reference (making a copy of the member is expensive)

### Access functions concerns

Many developers would argue that use of access funcitons violates good class design

Recommend a pragmatic approach. As you create your classes, consider the following:
- If your class has no invariants and requires a lot of access funcitons, consider using a struct and providing direct access to members instead
- Prefer implementating behaviors or actions instead of access functions
  - Instead of `setAlive(booL)`, use `kill()` or `revive()`
- Only provide access functions in cases where the public would reasonably need to get or set the value of an individual member

# 14.7 - Member functions returning references to data members

## Notes 

Member functions can also return by reference, and they follow the same rules for when it is safe to return by reference as non-member functions
- Member functions have 1 additional case we need to discuss: member functions that return data members by reference

### Returning data members by value can be expensive

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
```

`getName()` access functions returns `std::string m_name` by value
- An expensive copy of `m_name` will be made every time
- Generally not the best choice

### Returning data members by lvalue reference

Member functions can also return data members by (const) lvalue reference\
Data members have the same llifetime as the object containing them

Generally safe for a member function to return a data member by (const) lvalue reference

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```

### The return type of a member function returning a reference to a data member should match the data member's type

In general, the return type of a member function returning by reference should match the type of the data member being returned

In the above example, returning `std::string_view` would require a temporary `std::string_view` to be created and returned every time the function was called
- If the caller wants a `std::string_view`, they can do the conversion themselves

For getters, using `auto` to have the compiler deduce the return type from the member being returned is a useful way to ensure that no conversions occur

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const auto& getName() const { return m_name; } // uses `auto` to deduce return type from m_name
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```

However, using an `auto` return type obscures the return type of the getter from a documentation perspective

### Rvalue implicit objects and return by reference

What if our implicit object is an raalue instead (such as the return value of some function that returns by value)?
- Rvalue objects are destroyed at the end of the full expression in which they are created
- When an rvalue objectis destroyed, any references to members of that rvalue will be invalidated and left dangling

A reference to a member of an rvalue object can only be safely used within the full expression where the rvalue object is created

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

	return 0;
}
```

### Using member functions that return by reference safely

It is conventional for getters to return types that are expensive to copy by const reference, not by value

How we can use the return values from such functions safely. 3 cases in the example above illustrate the 3 key points:
- Prefer to use the return value of a member function that returns by reference immediately, since this works with both lvalue and rvalue objects, if you always do this, you will avoid trouble
- Do not "save" a returned reference to use later, unless you are sure the implicit object is an lvalue
  - If you do this with an rvalue implicit object, undefined behavior will result when you use the now-dangling reference
- If you do need to persist a returned reference for use later and aren't sure that the implicit object is an lvalue

Best Practice: Prefer to use the return value of a member function that returns by reference immediately, to avoid issues with dangling references when the implicit object is an rvalue

### Do not return non-const references to private data members

Because a reference acts just like the object being referenced, a member function that returns a non-const reference provides direct access to that member (even if the member is private)

```cpp
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value(); // prints 5

    return 0;
}
```

Because `value()` returns a non-const refrence to `m_value`, the caller is able to use that reference to directly access and change the value of `m_value`

### Const member functions can't return non-const references to data members

A const member funciton is not allowed to return a non-const reference to members
- A const member function is not allowed to modify the state of the object
- Nor is it allowed to call functions that would modify the state of the object

If a const member function is allowed to return a non-const reference to a member, it would be handling the caller a way to directly modify that member

# 14.8 - The benefits of data hiding

## Notes

### Implementaiton and Interfaces in Class Types

The separation of interface and implementation is useful in programming
- Let's define what we mean by interface and implementation with regards to class type

**Interface**: Defines how a user of the class type will interact with objects of the class type
- The public members of a class type form its interface

**Public Interface**: An interface composed of public members

An interface is an implicit contract between the author of a class and the user of a class

**implementation**: The implementation of a class type consists of the code that actually makes the class behave as intended
- Includes both the member variables that store data, and the bodies of the member functions that contain the program logic and manipulate the member variables

### Data hiding

**Data Hiding**: A technique used to enforce the separation of interface and implementation by hiding the implementation of a program-defined data type from users

First, we ensure the data members of the class type are private
- The statement inside the bodies of member functions are already not directly accessible to users
- We don't need to do anything else there

Next, ensure the member functions are public, so that the user can cal them

We force the user of a class type to manipulate objects using the public interface, and preven thtme from directly accessing implementation details

Doing so provides a large number of useful benefits that help encourage class reusability and maintainability

Structs should not use data hiding

### Data hiding make classes easier to use, and reduces complexity

```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view sv{ "Hello, world!" };
    std::cout << sv.length();

    return 0;
}
```

The details of how `std::string_view` is implemented is not exposed to us
- We don't get to see how many data members a `std::string_view` has, what they are named, or what type they are
- We don't know how the `length()` member function is returning the length of the string being viewed

All we need to know is how to initialize an object of type `std::string_view` and what the `length()` member function returns

### Data hiding allows us to maintain invariatns

```cpp
#include <iostream>
#include <string>

struct Employee // members are public by default
{
    std::string name{ "John" };
    char firstInitial{ 'J' }; // should match first initial of name

    void print() const
    {
        std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John" and 'J'
    e.print();

    e.name = "Mark"; // change employee's name to "Mark"
    e.print(); // prints wrong initial

    return 0;
}
```

This program prints:

```shell
John has first initial J
Mark has first initial J
```

Our `Employee` struct has a class invariant that `firstInitial` should always equal the first character of `name`

The `name` member is public, the code in `main()` is able to set `e.name` to `"Mark"`, and the `firstInitial` member is not updated

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee // members are private by default
{
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name)
    {
        m_name = name;
        m_firstInitial = name.front(); // use std::string::front() to get first letter of `name`
    }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
    }
};

int main()
{
    Employee e{};
    e.setName("John");
    e.print();

    e.setName("Mark");
    e.print();

    return 0;
}
```

```shell
John has first initial J
Mark has first initial M
```

The only change from the user's perspective is that instead of assigning `name` a value directly, they're calling member function `setName()`, which does the job of setting both `m_name` and `m_firstInitial`

### data hiding allows us to do better error detection (and handling)

```cpp
#include <iostream>
#include <string>

class Employee
{
    std::string m_name{ "John" };

public:
    void setName(std::string_view name)
    {
        m_name = name;
    }

    // use std::string::front() to get first letter of `m_name`
    char firstInitial() const { return m_name.front(); }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << firstInitial() << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John"
    e.setName("Mark");
    e.print();

    return 0;
}
```

This program has another class invariant
- `m_name` shouldn't be an empty string.
- If `m_name` is set to an empty string, nothing bad will happen immediately, but if `firstInitial()` is then called the `front()` member of `std:;string` will not work

We like to prevent `m_name` from ever being empty

Because we're forcing the user to set `m_name` through the public interface function `setName()`, we can have `setName()` validate that the user has passed in a valid name
- If the name is non-empty, then we can assign it to `m_name`, else, we can do a number of things
  - Ignore the request to set the name to "" and return to the caller
  - Assert out
  - Throw an exception

### Data hiding makes it possible to change implementation details without breaking existing programs

```cpp
#include <iostream>

struct Something
{
    int value1 {};
    int value2 {};
    int value3 {};
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```

What would happen if we decided if we decided to change the implementation details of the class

```cpp
#include <iostream>

struct Something
{
    int value[3] {}; // uses an array of 3 values
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```

The program no longer compiles because the member named `value1` no longer exists, and a statement in `main()` is still using that identifier

Data hiding gives us the ability to change how classes are implemented without breaking the programs that use them

```cpp
#include <iostream>

class Something
{
private:
    int m_value[3]; // note: we changed the implementation of this class!

public:
    // We have to update any member functions to reflect the new implementation
    void setValue1(int value) { m_value[0] = value; }
    int getValue1() const { return m_value[0]; }
};

int main()
{
    // But our programs that use the class do not need to be updated!
    Something something;
    something.setValue1(5);
    std::cout << something.getValue1() << '\n';
}
```

Because we did not change the public interface of the class, our program that uses that interface did not need to change at all, and still functions identically

### Classes with interfaces are easier to debug

Encapsulation can help you debug a program when something goes wrong
- Often when a program doesn't work correctl, it is because one of our member variables has been given an incorrect value
- If everyone is able to set the member variable directly, tracking down which piece of code actually modified the member variable to the wrong value can be difficult

If a member can only be changed through a single member function, then you can simply breakpoint that single function and watch as each caller changes the value

### Prefer non-member functions to member functions

In C++, if a function can be reasonably implemented as a non-member function, prefer to implement it as a non-member function instead of a member function

Benefits:
- Non-member functions are not part of the interface of your class. The interface of your class will be smaller and more straightforward, making the class easier to understand
- Non-member functions enforce encapsulation, as such functions must work through the public interface of the class. There is no temptation to access the implementation directly just because it is convenient
- Non-member function don't need to be considered when making changes to the implementation of a class
- Non-member functions tend to be easier to debug
- Non-member functions containing application specific data and logic can be separated from the reusable portions of the class

Best Practice: Prefer implementing functions as non-members when possible (especially functions that contain application specific data or logic)

### The order of class member declaration

We can order our members in any order we like

There are 2 schools of thought on ordering
- List your private members first, and then list your public member functions
  - Follows the traditional style of declare-before-use
  - Anybody looking at your class code will see how you've defined your data members before they are used, which can make reading through and understanding implementation details easier
- List your public members first, and put your private members down at the bottom.
  - because someone who uses your class is interested in the public interface, putting your public members first makes the information they need up top, and puts the implementation details last

Modern C++, Public first is more commonly recommended, especially for code that will be shared with other developers

# 14.9 - Introduction to Constructors

## Notes

How do we initialize a class with private member variables? We must use a matching constructor

### Constructors

**Constructor**: A special member function that is automatically called after a non-aggregate class type object is created

When a non-aggregate class type object is defined, the compiler looks to see if it can find an accessible constructor that is a match for the initialization values provided by the caller
- If an accessible constructor is found, memory for the object is allocated, then the constructor function is called
- If no accessible matching constructor can be found, a compilation error will be generated

Constructors generally perform 2 functions:
- Typically perform initialization of any member variables
- They may perform other setup functions
  - Might include things such as error checking, opening files and databases, etc.

### Naming Constructor

Constructors have specific rules for how they must be named:
- Must have the same name as the class
  - For template classes, this name excludes the template parameters
- Constructors have no return type (not even Void)

### A basic constructor example

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
```

### Constructor implicit conversion of arguments

Compiler will perform implicit conversion of arguments ina function call in order to match a function definition where the parameters are a different type

No different for constructors

```cpp
class Foo
{
public:
    Foo(int x, int y)
    {
    }
};

int main()
{
    Foo foo{ 'a', true }; // will match Foo(int, int) constructor

    return 0;
}
```

### Constructors should not be const

A constructor needs to be able to initialize the object being constructed, a constructor must not be const

```cpp
#include <iostream>

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}
```

### Constructors vs setters

Constructors are designed to initialize an entire object at the point of instantiation\
Setters are designed to assign a value to a single member of an existing object

# 14.10 - Constructor member initializer lists

## Questions

1. Write a class named Ball. Ball should have two private member variables, one to hold a color, and one to hold a radius. Also write a function to print out the color and radius of the ball.

The following sample program should compile:

```cpp
int main()
{
	Ball blue { "blue", 10.0 };
	print(blue);

	Ball red { "red", 12.0 };
	print(red);

	return 0;
}
```

```shell
Ball(blue, 10)
Ball(red, 12)
```

```cpp
class Ball
{
private:
	std::string m_name {};
	double m_radius {};

public:
	Ball(std::string_view name, double radius) :
		m_name {name}, m_radius {radius}
	{

	}

	const std::string& getName() const
	{
		return m_name;
	}

	double getRadius() const
	{
		return m_radius;
	}
};

void print(const Ball& ball)
{
	std::cout << "Ball(" << ball.getName() << ", " << ball.getRadius() << ")\n";
}
```

## Notes

### Member initialization via a member initialization list

**Member Initializer List**: To have a constructor initialize members

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```

Member initializer list is defined after the constructor parameters
- Begins with a colon (:), and then lists each member to initialize along with the initialization value for that variable, separated by commas
- Must use a direct form of initialization here
- Copy doesn't work

```shell
Foo(6, 7) constructed
Foo(6, 7)
```

When `Foo` is instantiated, the members in the initialization list are initialized with the specified initialization values

### Member Initializer list formatting

C++ provides a lot of freedom to format your member initializer lists as you prefer

The following are valid

```cpp
Foo(int x, int y) : m_x { x }, m_y { y }
{
}

Foo(int x, int y) :
    m_x { x },
    m_y { y }
{
}

Foo(int x, int y)
    : m_x { x }
    , m_y { y }
{
}
```

recommended to use the third style

If the member initialization list is short/trivial, all initializers can go on one line

```cpp
Foo(int x, int y)
    : m_x { x }, m_y { y }
{
}
```

### Member initialization order

Because the C++ standard says so, the members in a member initializer list are always initialized in the order in which they are defined inside the class

```cpp
#include <algorithm> // for std::max
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```

The following is printed

```cpp
Foo(-858993460, 7)
```

Because `m_x` is defined first in the class, `m_x` gets initialized firs
- `m_x` gets initialized to the value of `m_y` which hasn't been initialized yet

Best Practice: Member variables in a member initializer list should be listed in order that they are defined in the class

### Member initializer list vs default member initializers

If a member has both a default member initializer and is listed in the member initializer list for the construct, the member initializer list value takes precedence

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};    // default member initializer (will be ignored)
    int m_y { 2 }; // default member initializer (will be used)
    int m_z;      // no initializer

public:
    Foo(int x)
        : m_x { x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

int main()
{
    Foo foo { 6 };
    foo.print();

    return 0;
}
```

```shell
Foo constructed
Foo(6, 2, -858993460)
```

### Constructor function bodies

The bodies of constructors functions are most often left empty
- Primarily use constructor for initialization

Because the statements in the body of the constructor execute after the member initializer list has executed
- We can add statements to do any other setup tasks required

New programmers sometimes use the body of the constructor to assign values to members
- In cases where members are required to be initialized, assignment won't work

```cpp
#include <iostream>

class Foo
{
private:
    int m_x { 0 };
    int m_y { 1 };

public:
    Foo(int x, int y)
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```

Best Practice: use the member initializer list to initialize your members over assigning values in the body of the constructor

### Detecting and handling invalid arguments to constructors

```cpp
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator }
    {
    }
};
```

The denominator of the fraction cannot be zero
- This class has an invariant that `m_denominator` cannot be `0`

Inside the member initializer list, our tools for detecting and handling errors are quite limited
- We can use the conditional operator to detet an error, but then what?

```cpp
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator != 0.0 ? denominator : ??? } // what do we do here?
    {
    }
}
```

Inside the body of the constructor, we can use statements, so we have more options for detecting and handling errors
- Good place to `assert` or `static_assert` that the arguments passed in are semantically valid
- Doesn't actually handle runtime errors in a porduction build

### When constructors fail (Prelude)

4 Strategies for dealing with errors:
- Resolve the error within the function
- Pass the error back to the caller to deal with
- Halt the program
- Throw an exception

Most cases, we don't have enough info to resolve such issues entirely within the constructor

With non-member and non-special member functions, we can pass an error back to the caller to deal with
- But constructors have no return value

We can add an `isValid()` member function that returns whether to obeject is dcurrently in a valid state or not
- Means the caller has to remember to actually call the function any time a new Fraction is created

Certain types of programs, we can just halt the entire program and let the user rerun the program
- Most cases, that's not acceptable

Exceptions abort the construction process entirely, which means the user never gets access to a semantically invalid object
- Throwing an exception is the best thing to do in these situations

# 14.11 - Default constructors and default arguments

## Notes

**Default Constructor**: A constructor that accepts no arguments
- A constructor that has been defined with no parameters

```cpp
#include <iostream>

class Foo
{
public:
    Foo() // default constructor
    {
        std::cout << "Foo default constructed\n";
    }
};

int main()
{
    Foo foo{}; // No initialization values, calls Foo's default constructor

    return 0;
}
```

### Value initialization vs default initialization for class types

If a class type has a default constructor, both value initialization and default initialization will call the default construtor

For a class such as `Foo`, the following are equivalent

```cpp
Foo foo{}; // value initialization, calls Foo() default constructor
Foo foo2;  // default initialization, calls Foo() default constructor
```

Best Practice: Prefer value initialization over default initialization for all class types

### Constructors with default arguments

The rightmost parameters of constructors can have default arguments

```cpp
#include <iostream>

class Foo
{
private:
    int m_x { };
    int m_y { };

public:
    Foo(int x=0, int y=0) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // calls Foo(int, int) constructor using default arguments
    Foo foo2{6, 7}; // calls Foo(int, int) constructor

    return 0;
}
```

If all of the parameters in a constructor have default arguments, the constructor is a default constructor

### Overloaded constructors

Constructors can be overloaded. We can have multiple constructors so that we can construct objects in different ways

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x, int y) // non-default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // Calls Foo() constructor
    Foo foo2{6, 7}; // Calls Foo(int, int) constructor

    return 0;
}
```

A corollary of the above is that a class should only have one default constructor
- 1 more than 1 default constructor is provided, the compiler will be unable to disambiguate which should be used

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x=1, int y=2) // default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // compile error: ambiguous constructor function call

    return 0;
}
```

## An implicit default constructor

**Implicit Default Constructor**: If a non-aggregate class type object has no user-declared constructors, the compiler will generate a public default constructor

```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

    // Note: no constructors declared
};

int main()
{
    Foo foo{};

    return 0;
}
```

This class has no user-declared constructors, so the compiler will generate an implicit default constructor for us

The implicit default constructor is equivalent to a constructor that has no parameters, no member initializer list, and no statemetns in the body of the constructor

```cpp
public:
    Foo() // implicitly generated default constructor
    {
    }
```

### Using `= default` to generate an explicit defaulted default constructor

**Explicitly Defaulted Default Constructor**: Cases where we would write a default constructor that is equivalent to the implicitly generated default constructor, we can instead tell the compiler to generate a default constructor for us

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() = default; // generates an explicitly defaulted default constructor

    Foo(int x, int y)
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // calls Foo() default constructor

    return 0;
}
```

Since we have declared `Foo(int x, int y)`, an implicit default constructor would not normally be generated

Best Practice: Prefer an explicitly defaulted default constructor over a default constructor with an empty body

### Explicitly defaulted default constructor vs empty user-defined constructor

2 cases where the explicitly defaulted default constructors behaves differently than an empty user-defined constructor
1. Value initializing a class, if the class has a user-defined default constructor, the object will be default initialized
    - If the class has a default constructor that is not user-provided (implicitly defined or `= default`), the object will be zero-initialized before being default initialized

```cpp
#include <iostream>

class User
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    User() {} // user-defined empty constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

class Default
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    Default() = default; // explicitly defaulted default constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

class Implicit
{
private:
    int m_a; // note: no default initialization value
    int m_b {};

public:
    // implicit default constructor

    int a() const { return m_a; }
    int b() const { return m_b; }
};

int main()
{
    User user{}; // default initialized
    std::cout << user.a() << ' ' << user.b() << '\n';

    Default def{}; // zero initialized, then default initialized
    std::cout << def.a() << ' ' << def.b() << '\n';

    Implicit imp{}; // zero initialized, then default initialized
    std::cout << imp.a() << ' ' << imp.b() << '\n';

    return 0;
}
```

```shell
782510864 0
0 0
0 0
```

2. Prior to C++20, a class with a user defined default constructor makes the class a non-aggregate
    - An explicitly defaulted default constructor doesn't
    - The former will cause the class to use list initialization instead of aggregate initialization
    - C++20 and onward, this inconsistency was addressed

### Only create a default constructor when it makes sense

A class should only provide a default constructor when it makes sense for objects of a class type to be created using all default values

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction() = default;
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f1 {3, 5};
    f1.print();

    Fraction f2 {}; // will get Fraction 0/1
    f2.print();

    return 0;
}
```

This would make sense, giving the user a default fraction of `0/1`

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{ };
    int m_id{ };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }
        , m_id{ id }
    {
    }

    void print() const
    {
        std::cout << "Employee(" << m_name << ", " << m_id << ")\n";
    }
};

int main()
{
    Employee e1 { "Joe", 1 };
    e1.print();

    Employee e2 {}; // compile error: no matching constructor
    e2.print();

    return 0;
}
```

To represent employees, it doesn't make sense to allow creation of employees with no names

# 14.12 - Delegating Constructors

## Questions

1. Write a class named Ball. Ball should have two private member variables, one to hold a color (default value: black), and one to hold a radius (default value: 10.0). Add 4 constructors, one to handle each case below:

```cpp
int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };

    return 0;
}
```

```shell
Ball(black, 10)
Ball(blue, 10)
Ball(black, 20)
Ball(blue, 20)
```

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
	std::string m_color{ "black" };
	double m_radius{ 10.0 };

public:
	// Default constructor (color and radius will use default value)
	Ball()
	{
            print();
	}

	// Constructor with only radius parameter (color will use default value)
	Ball(double radius)
		: m_radius{ radius }
	{
            print();
	}

	// Constructor with only color parameter (radius will use default value)
	Ball(std::string_view color)
		: m_color{ color }
	{
            print();
	}

	// Constructor with both color and radius parameters
	Ball(std::string_view color, double radius)
		: m_color{ color }
		, m_radius{ radius }
	{
            print();
	}

    void print() const
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
    }
};

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };

    return 0;
}
```

2. Reduce the number of constructors in the above program by using default arguments and delegating constructors.

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
	std::string m_color{ "black" };
	double m_radius{ 10.0 };

public:
	// Handles Ball(radius)
	Ball(double radius)
		: Ball{ "black", radius } // delegate to the other constructor
	{
		// We don't need to call print() here since it will be called by
		// the constructor we delegate to
	}

	// Handles Ball(color, radius), Ball(color), and Ball()
	Ball(std::string_view color="black", double radius=10.0)
		: m_color{ color }
		, m_radius{ radius }
	{
		print();
	}

	void print() const
	{
		std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
	}
};

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };

    return 0;
}
```

## Notes

When a class contains multiple constructors, it's extremely common for the code in each constructor to be similar if not identical with lots of repetition

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id) // Employees must have a name and an id
        : m_name{ name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }

    Employee(std::string_view name, int id, bool isManager) // They can optionally be a manager
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James", 7 };
    Employee e2{ "Dave", 42, true };
}
```

Constructors are allowed to call other functions including other member functions of the class, we can refactor:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id{ 0 };
    bool m_isManager { false };

    void printCreated() const // our new helper function
    {
        std::cout << "Employee " << m_name << " created\n";
    }

public:
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id }
    {
        printCreated(); // we call it here
    }

    Employee(std::string_view name, int id, bool isManager)
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    {
        printCreated(); // and here
    }
};

int main()
{
    Employee e1{ "James", 7 };
    Employee e2{ "Dave", 42, true };
}
```

It requires introduction of a new function, and our 2 constructors are also both initializing `m_name` and `m_id`
- Want to remove redundancy

### Calling a constructor in the body of a function creates a temporary object

We would think to call `Employee(std::string_view, int)` constructor from the body of `Employee(std::string_view, int, bool)` in order to iniitalize `m_name` and `m_id`

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // this constructor initializes name and id
    {
        std::cout << "Employee " << m_name << " created\n"; // our print statement is back here
    }

    Employee(std::string_view name, int id, bool isManager)
        : m_isManager { isManager } // this constructor initializes m_isManager
    {
        // Call Employee(std::string_view, int) to initialize m_name and m_id
        Employee(name, id); // this doesn't work as expected!
    }

    const std::string& getName() const { return m_name; }
};

int main()
{
    Employee e2{ "Dave", 42, true };
    std::cout << "e2 has name: " << e2.getName() << "\n"; // print e2.m_name
}
```

This doesn't work correctly as the output is as follows

```shell
Employee Dave created
e2 has name: ???
```

Initialization of the class object is finished once the member initializer list has finished executing.
- By the time we begin executing the constructor's body it's too late to do more intiailization

What looks like a function call to a constructor usually creates and direct-initializes a temporary object

Best Practice: Constructors should not be called directly from the body of another function

### Delegating Constructors

**Constructor Chaining/Delegating Constructors**: Constructors are allowed to delegate initialization to another constructor from the same class type

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };

public:
    Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }

    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // actually initializes the members
    {
        std::cout << "Employee " << m_name << " created\n";
    }

};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

Downside of this method is that it sometimes requires duplication of initialization values
- We need an initialization value for the `int` parameter.
- Had to hardcode literal `0`, as there is no way to reference the default member initializer

A constructor that delegates to another constructor is not allowed to do any member initialization itself, so your constructors can delegate or initialize, but not both

It's possible for one constructor to delegate to another constructor, which delegates back to the first constructor, creating an infinite loop

### Reducing constructors using default arguments

Default values can also sometimes be used to reduce multiple constructors into fewer constructors

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};
    int m_id{ 0 }; // default member initializer

public:

    Employee(std::string_view name, int id = 0) // default argument for id
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

Best Practice: Members for which the user must provide initialization values should be defined first
- Members for which the user can optionally provide initiailization values should be defined second

###  A conundrum: Redundant constructors vs redundant default values

There is currently no way to specify that a delegating constructor or default argument should use the default member initializer value

Usually more straightforward to have fewer constructors, even if it results in duplication of initialization values

# 14.13 - Temporary Class Objects

## Notes

In most cases where a variable is used only once, we actually don't need a variable
- Instead, we can substitute in the expression used to initialize the variable where the variable would have been used

### Temporary class objects

```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p); // prints (3, 4)

    return 0;
}
```

In case 1, we're instantiating variable `IntPair p` and then passing `p` to function `print()`
- `p` is only used once, there is really no reason to define a variable here

**Temporary Object**: An object that has no name and exists only for the duration of a single expression

```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const{ return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p);

    // Case 2: Construct temporary IntPair and pass to function
    print(IntPair { 5, 6 } );

    // Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
    print( { 7, 8 } );

    return 0;
}
```

Case 2: WE're telling the compiler to construct an `IntPair` object, and initializing it with `{5, 6}`
- No name means temporary
- The temporary object is passed, when the function returns, the temporary object is destroyed

Case 3: Creating a temporary object. Because we have not explicitly specified what type to construct, the compiler will deduce the necessary type

### Creating Temporary objects via direct initialization

You can create temporary objects using direct initialization

```cpp
Foo (1, 2); //  temporary Foo, direct-initialized with (1, 2) (similar to `Foo { 1, 2 }`)
```

This produces the same result as `Foo {1, 2}`

What about cases without any arguments

```cpp
Foo();     // temporary Foo, value-initialized (identical to `Foo {}`)

```

This syntax has a completely different meaning when used with a named variable

```cpp
Foo bar{}; // definition of variable bar, value-initialized
Foo bar(); // declaration of function bar that has no parameters and returns a Foo (inconsistent with `Foo bar{}` and `Foo()`)
```

```cpp
Foo(1);    // Function-style cast of literal 1, returns temporary Foo (similar to `Foo { 1 }`)
Foo(bar);  // Defines variable bar of type Foo (inconsistent with `Foo { bar }` and `Foo(1)`)
```

- The version with literal `1` in parentheses behaves consistenly with all the other versions of this syntax that create temporary objects
- The version with identifier `bar` in parentheses defines a vaariable named `bar`. If `bar` is already defined, this will cause a redefinition compile-error

### Temporary Objects and Return By Value

When a function returns by value, the object that is returned is a temporary object

```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

// Case 1: Create named variable and return
IntPair ret1()
{
    IntPair p { 3, 4 };
    return p; // returns temporary object (initialized using p)
}

// Case 2: Create temporary IntPair and return
IntPair ret2()
{
    return IntPair { 5, 6 }; // returns temporary object (initialized using another temporary object)
}

// Case 3: implicitly convert { 7, 8 } to IntPair and return
IntPair ret3()
{
    return { 7, 8 }; // returns temporary object (initialized using another temporary object)
}

int main()
{
    print(ret1());
    print(ret2());
    print(ret3());

    return 0;
}
```

### A few notes

Just as i the case of an `int`, when used in an expression, a temporary class object is an rvalue
- Such objects can only be used where rvalue expressions are accepted

Temporary objects are created at the point of definition, and destroyed at the end of the full expression in which they are defined
- A full expression is an expression that is not a subexpression

### `static_cast` vs explicit instantiation of a temporary object

We often have the option to use either `static_cast` or explicit instantiation of a temporary object

```cpp
#include <iostream>

int main()
{
    char c { 'a' };

    std::cout << static_cast<int>( c ) << '\n'; // static_cast returns a temporary int direct-initialized with value of c
    std::cout << int { c } << '\n';             // explicitly creates a temporary int list-initialized with value c

    return 0;
}
```

Best Practice: Prefer `static_cast` when converting to a fundamental type, and a list-initialized temporary when converting to a class type

Prefer `static_cast` when to create a temporary object when any of the following are true:
- We need to perform a narrowing conversion
- We want to make it really obvious that we're converting to a type that will result in some different behavior
- We want ot use direct-initialization for some reason

Prefer creating a new object (using list iniitialization) to create a temporary object when any of the following are true:
- We want to use list-initialization
- We need to provide additional arguments to a constructor to facilitate the conversion

# 14.14 - Introduction to the copy constructor

## Questions

1. In the lesson above, we noted that the parameter for a copy constructor must be a (const) reference. Why aren’t we allowed to use pass by value?
- Pass by value of another Class can be expensive

## Notes

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?

    f.print();
    fCopy.print();

    return 0;
}
```

This program compiles just fine and produces the result

```shell
Fraction(5, 3)
Fraction(5, 3)
```

This is done with Copy Constructor

### The copy constructor

**Copy Constructor**: A constructor that is used to initialize an object with an existing object of the same type
- After the copy constructor executes, the newly created object should be a copy of the object passed in as the initiator

### Implicit Copy Constructor

**Implicit Copy Constructor**: If you do not provide a copy constructor for your classes, C++ will create one
- The statement `Fraction fCopy {f}` is invoking the implicit copy constructor to initialize `fCopy`

The implicit copy constructor will do memberwise initialization

After the copy constructor has executed, the members of `f` and `fCopy` have the same values, so `fCopy` is a copy of `f`

### Defining your own copy constructor

Can also explicitly define our own copy constructor

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

    f.print();
    fCopy.print();

    return 0;
}
```

The copy constructor we defined above is functionally equivalent to the one we'd get by default
- We've added an output statement to prove the copy constructor is actually being called

A copy constructor should not do anything other than copy an object
- If you are relying on the copy constructor for some behavior other than just copying, that behavior may or may not occur

### Prefer the implicit copy constructor

The memberwise initialization performed by the implicit copy constructor is usally exactly what we want
- In most cases, using the implicit copy constructor is perfectly fine

### The copy constructor's parameter must be a reference

It is required that the parameter of a copy constructor be an lvalue reference or const lvalue reference
- Copy constructor shouldn't be modifying the parameter, using a const lvalue reference is preferred

### Pass by value and the copy constructor

When an object is pass by value, the argument is copied into the parameter
- when the argument and parameter are the same class type, the copy is made by implicitly invoking the copy constructor

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

int main()
{
    Fraction f{ 5, 3 };

    printFraction(f); // f is copied into the function parameter using copy constructor

    return 0;
}
```

```shell
Copy constructor called
Fraction(5, 3)
```

### Return by value and the copy constructor

When the return type and the return value are the same class type, the temporary object is initialized by implicitly inovking the copy constructor

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

Fraction generateFraction(int n, int d)
{
    Fraction f{ n, d };
    return f;
}

int main()
{
    Fraction f2 { generateFraction(1, 2) }; // Fraction is returned using copy constructor

    printFraction(f2); // f2 is copied into the function parameter using copy constructor

    return 0;
}
```

When `generateFraction` returns a `Fraction` back to `main`, a temporary `Fraction` object is created and initialized using the copy constructor
- This temporary is used to initialize `Fraction f2`, this invokes the copy constructor again to copy the temporary into `f2`
- When `f2` is passed to `printFraction`, the copy constructor is called a third time

```shell
Copy constructor called
Copy constructor called
Copy constructor called
Fraction(1, 2)
```

### Using `= default` to generate a default copy construction

If a class has no copy constructor, the compiler will implicitly generate one for us

If we prefer, we can explicitly request the compiler create a default copy constructor for us suing the `= default` syntax

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Explicitly request default copy constructor
    Fraction(const Fraction& fraction) = default;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f };

    f.print();
    fCopy.print();

    return 0;
}
```

### Using `= delete` to preven copies

Occasionally we run into cases where we don't want objects of a certain class to be copyable
- Can prevent this by marking the copy constructor function as deleted, using `= delete`

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Delete the copy constructor so no copies can be made
    Fraction(const Fraction& fraction) = delete;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f }; // compile error: copy constructor has been deleted

    return 0;
}
```

# 14.15 - Class Initialization and Copy Elision

## Notes

6 basic types of initialization for objects with fundamental types

```cpp
int a;         // no initializer (default initialization)
int b = 5;     // initializer after equals sign (copy initialization)
int c( 6 );    // initializer in parentheses (direct initialization)

// List initialization methods (C++11)
int d { 7 };   // initializer in braces (direct list initialization)
int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
int f {};      // initializer is empty braces (value initialization)
```

All are valid for objects with class types

Certain forms of initialization are disallwed

### Unnecessary copies

```cpp
#include <iostream>

class Something
{
    int m_x{};

public:
    Something(int x)
        : m_x{ x }
    {
        std::cout << "Normal constructor\n";
    }

    Something(const Something& s)
        : m_x { s.m_x }
    {
        std::cout << "Copy constructor\n";
    }

    void print() const { std::cout << "Something(" << m_x << ")\n"; }
};

int main()
{
    Something s { Something { 5 } }; // focus on this line
    s.print();

    return 0;
}
```

```shell
Normal constructor
Copy constructor
Something(5)
```

This program is needlessly inefficient, as we've had to make two constructor calls
- The end result is the same as if we had written the following

```cpp
Something s { 5 }; // only invokes Something(int), no copy constructor
```

### Copy Elision

The compiler can treat `Something s{ Something{5}}` as if it was written as `Something s{5}`

**Copy Elision**: A compiler optimization technique that allows the compiler to remove unnecessary copying of objects

**Elided**: When the compiler optimizes away a call to the copy constructor, we say the constructor has been elided

Copy Elision is exempt form the "as-if" rule
- Allowed to elide the copy constructor even if the copy constructor has side effects
- Copy constructors should not have side effects other than copying

If the compiler elides the call of the copy constructor, the side effects won't execute, and the observable behavior of the program will change

### Copy Elision in pass by value and return by value 

The copy constructor is normally called when an argument of the same type as the parameter is passed by value or returned by value is used
- In certain cases, these copies may be elided

```cpp
#include <iostream>

class Something
{
public:
	Something() = default;
	Something(const Something&)
	{
		std::cout << "Copy constructor called\n";
	}
};

Something rvo()
{
	return Something{}; // calls Something() and copy constructor
}

Something nrvo()
{
	Something s{}; // calls Something()
	return s;      // calls copy constructor
}

int main()
{
	std::cout << "Initializing s1\n";
	Something s1 { rvo() }; // calls copy constructor

	std::cout << "Initializing s2\n";
	Something s2 { nrvo() }; // calls copy constructor

        return 0;
}
```

In C++14 with copy elision disabled, the program will call the copy constructor 4 times

Due to elision, it's likely that your compiler will elide most or all of these copy constructor calls

# 14.16 - Converting constructrs and the explicit keyword

## Notes

### User-defined conversions

```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
public:
    Foo(int x)
        : m_x{ x }
    {
    }

    int getX() const { return m_x; }
};

void printFoo(Foo f) // has a Foo parameter
{
    std::cout << f.getX();
}

int main()
{
    printFoo(5); // we're supplying an int argument

    return 0;
}
```

The compiler will try to implicitly convert int value `5` into a `Foo`
- One of our types is a program-defined type
- C++ standard doesn't have specific rules that thells the compiler how to convert values to/from a program defined type

**User Defined Conversions**: Compiler will look to see if we have defined some function that it can use to perform such a conversion

### Converting constructors

The compiler will find a function that lets it convert int value `5` into a `Foo` object
- That function is the `Foo(int)` constructor

We've typically used constructors to explicitly construct objects

```cpp
Foo x { 5 }; // Explicitly convert int value 5 to a Foo
```

In the context of a function call, we're trying to solve the same problem

```cpp
printFoo(5); // Implicitly convert int value 5 into a Foo
```

Providing `int 5`, and we want a `Foo` object in return
- `Foo(int)` constructor was designed for exactly that

When `printFoo(5)` is called, parameter `f` is copy initialized using the `Foo(int)` constructor with `5` as an argument

**Converting Constructor**: A constructor that can be used to perform an implicit conversion

### Only one user-defined conversion may be applied

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};

public:
    Employee(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e) // has an Employee parameter
{
    std::cout << e.getName();
}

int main()
{
    printEmployee("Joe"); // we're supplying an string literal argument

    return 0;
}
```

We swapped out our `Foo` class for an `Employee` class
- `printEmployee` has an `Employee` parameter, we're passing in a C-style string literal
- Converting constructor `Employee(std::string_view)`

This version doesn't compile
- Only one user-defined conversion may be applied to perform an implicit conversion
- This requires 2, C-style literal convert to `std::string_view`, then `std::string_view` convert to `Employee`

2 Ways to make this work:
- Use a `std::string_view` literal

```cpp
int main()
{
    using namespace std::literals;
    printEmployee( "Joe"sv); // now a std::string_view literal

    return 0;
}
```

- Explicitly construct an `Employee` rather than implicitly create one

```cpp
int main()
{
    printEmployee(Employee{ "Joe" });

    return 0;
}
```

### When converting constructors go wrong

```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    Dollars(int d)
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5);

    return 0;
}
```

When we call `print(5)`, the `Dollars(int)` converting constructor will occur printing `$5`
- It is hard to tell what the caller's intent was because the caller did not provide any indication that this is what they actually wanted
- Possible that the caller assumed this would print just `5`

In a larger/more complex program, it's fairly easy to be surprised by the compiler performing some implicit conversions that you don't expect

Would be better if `print(Dollars)` would only be called with a `Dollars` object

### Explicit Keyword

**Explicit Keyword**: Tell the compiler that a constructor should not be used as a converting constructor

Making a constructor `explicit` has 2 noticable consequences:
- An explicit constructor cannot be used to do copy initialization or copy list initialization
- An explicit constructor cannot be used to do implicit conversions

```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    explicit Dollars(int d) // now explicit
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5); // compilation error because Dollars(int) is explicit

    return 0;
}
```

### Explicit constructors can be used for direct and direct list initialization

An explicit constructor can still be used for direct and direct list initialization

```cpp
// Assume Dollars(int) is explicit
int main()
{
    Dollars d1(5); // ok
    Dollars d2{5}; // ok
}
```

The following generates a compiler error

```cpp
print(5); // compilation error because Dollars(int) is explicit
```

What if we actually want to call `print()` with `int` value `5` but the constructor is explicit
- Instead of having the compiler implicitly convert `5` into a `Dollars` we can explicitly define the `Dollars` object ourselves

```cpp
print(Dollars{5}); // ok: explicitly create a Dollars
```

Also better documents our intent

Note that `static_cast` returns an object that is direct-initialized, so it will consider explicit constructors while performing the conversion

```cpp
print(static_cast<Dollars>(5)); // ok: static_cast will use explicit constructors
```

### Return by value and explicit constructors

When we return a value from a function, if that value doesn't match the return type of the function, an implicit conversion will cocur.
- Such conversions cannot use explicit constructors

```cpp
#include <iostream>

class Foo
{
public:
    explicit Foo() // note: explicit (just for sake of example)
    {
    }

    explicit Foo(int x) // note: explicit
    {
    }
};

Foo getFoo()
{
    // explicit Foo() cases
    return Foo{ };   // ok
    return { };      // error: can't implicitly convert initializer list to Foo

    // explicit Foo(int) cases
    return 5;        // error: can't implicitly convert int to Foo
    return Foo{ 5 }; // ok
    return { 5 };    // error: can't implicitly convert initializer list to Foo
}

int main()
{
    return 0;
}
```

### Best Practice for use of `explicit`

Make any constructor that will accept a single argument `explicit` by default
- Includes constructors with multiple parameters where most or all of them have default values
- Disallow the compiler from using the constructor for implicit conversions

If such a conversion is actually desired in a particular case, it is trivial to convert the implicit conversion into an explicit definition using direct list initialiation

**Should Not** Be made explicit:
- Copy and move constructors
**Are not typically** made explicit
- Default constructors with no parameters
- Constructors that only accept multiple arguments

If you prefer, the above can be marked as explicit to prevent implicit conversions with empty and multiple argument lists

Following **should usually** be made explicit
- Constructors that take a single parameter

Some occassions when it does make sense to make a single argument constructor non-explicit. This can be useful when all of the following are true
- The constructed object is semantically equivalent to teh argument value
- The conversion is performant

Ex: `std::string_view` constructor that accepts C-style string argument is not explicit
- There is unlikely to be a case where we wouldn't be okay with a C-style string being treated as `std::string_view`

# 14.17 - Constexpr aggregates and classes

## Notes

Constexpr functions, functions that may be evaluated at either compile time or runtime

```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    std::cout << greater(5, 6) << '\n'; // greater(5, 6) may be evaluated at compile-time or runtime

    constexpr int g { greater(5, 6) };  // greater(5, 6) must be evaluated at compile-time
    std::cout << g << '\n';             // prints 6

    return 0;
}
```

`greater()` is a constexpr function
- `greater(5, 6) is a constant expression, may be evaluated at either compile time or runtim
- Compiler is free to choose whether to evaluate at compile time or runtime

```cpp
#include <iostream>

struct Pair
{
    int m_x {};
    int m_y {};

    int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    Pair p { 5, 6 };                  // inputs are constexpr values
    std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime

    constexpr int g { p.greater() };  // compile error: greater() not constexpr
    std::cout << g << '\n';

    return 0;
}
```

We have an aggregate struct named `Pair`, `greater()` is now a member function
- Because member function `greater()` is not constexpr, `p.greater()` is not a constant expression

### Constexpr member functions

Member functions can be made constexpr via use of the `constexpr` keyword

```cpp
#include <iostream>

struct Pair
{
    int m_x {};
    int m_y {};

    constexpr int greater() const // can evaluate at either compile-time or runtime
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    Pair p { 5, 6 };
    std::cout << p.greater() << '\n'; // okay: p.greater() evaluates at runtime

    constexpr int g { p.greater() };  // compile error: p not constexpr
    std::cout << g << '\n';

    return 0;
}
```

We've made `greater()` a constexpr function, the compiler cna evalute at either runtime or compile-time
- When we call `p.greater()` in runtime expression `std::cout << p.greater()`, it evaluates at runtime

When `p.greater()` is used to initalize constexpr variable `g`, we get a compiler error
- Although `greater()` is now constexpr, `p` is still not constexpr
- `p.greater()` is not a constant expression

### Constexpr aggregates

If we need `p` to be constexpr, just make it constexpr

```cpp
#include <iostream>

struct Pair // Pair is an aggregate
{
    int m_x {};
    int m_y {};

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };        // now constexpr
    std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime or compile-time

    constexpr int g { p.greater() };  // p.greater() must evaluate at compile-time
    std::cout << g << '\n';

    return 0;
}
```

### Constexpr class objects and constexpr constructors

Making `Pair` a non-aggregate

```cpp
#include <iostream>

class Pair // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };       // compile error: p is not a literal type
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
```

Almost identical to the prior one, except `Pair` is no longer an aggregate
- We get a compiler error about `Pair` not being a "literal type"

**Literal Type**: Any type for which it might be possible to create an object within a constant expression
- An object can't be constexpr unless the type qualifies as a literal type

Definition of a literal type is complex, worth noting that literal types include
- Scalar types
- Reference types
- Most aggregates
- Classes that have a constexpr constructor

When a class object is instantiated, the compiler will call the constructor function to initialize the object
- The constructor function in our `Pair` class is not constexpr, so it can't be invoked at compile-time

Just make our constructor `constexpr` as well

```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
```

Implicitly defined construcotrs are constexpr if they can be defined as such. Explicitly defaulted constructors must be explicitly defined as constexpr

### Constexpr members may be needed with non-constexpr/non-const objects

Since the initializer if constexpr variable `g` must be a constant expression, it's clear that `pgreater()` must be a constant expression
- `p`, the `Pair` constrcutor, and `greater()` must all be constepxr

If we replace `p.greater()` with a constexpr function, things get a little less obvious

```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

constexpr int init()
{
    Pair p { 5, 6 };    // requires constructor to be constexpr when evaluated at compile-time
    return p.greater(); // requires greater() to be constexpr when evaluated at compile-time
}

int main()
{
    constexpr int g { init() }; // init() evaluated in compile-time context
    std::cout << g << '\n';

    return 0;
}
```

A constexpr function can evaluate at either runtime or compile time
- When a constexpr funciton evaluates at compile time, it can only call functions capable of evaluating at compile-time

Sing `g` is constexpr, `init()` must be evaluated at compile-time
- we define `p` as non-constexpr/non-const
- Even though `p` is not defined as constexpr, `p` still needs to be created at compile time
- Requires a constexpr `Pair` constructor

### Constexpr member functions may be const or non-const C++14

Constexpr member functions are no longer implicitly const.
- If you want a constexpr funciton to be a const funciton, you must explicitly mark it as such

# 14.x - Chapter 14 summary and quiz

## Review

- **Procedural Programming**: The focus on creating "procedures" that implement our program logic
- **Object-Oriented Programming**: The focus on creating program-defined data types that contain both properties and a set of well-defined behaviors
- **Class invariant**: A condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state
- **Invalid State**: An object that has a violated class invariant
- **Class**: A program-defined compound type that bundles both data and functions that work on that data
- **Member Functions**: Functions that belong to a class type
- **Implicit Object**: The object that a member funciton is called on
- **Non-Member Functions**: Functions that are not member functions
- **Const Member Functions**: A member function that guarantees it will not modify the object or call non-const member functions
- **Access Level**: Determines who can access that member
- **Access Constrol**: The access level system informal name
- **Public Members**: members of a class type that do not have any restrictions on how they can be accessed
- **The Public**: What we call code that exists outside the members of a given class type
- **Private Members**: Members of a class type that can only be accessed by other members of the same class
- **Access Specifier**: Explicitly set the access level of our members
- **Access Function**: Trivial public member function whose job is to retrieve or change the value of a private member variable
- **Getters**: Public member functions that return the value of a private member variables
- **Setters**: Public member functions that set the value of a private member variable
- **Interface**: Defines how a user of the class type will interact with objects of the class type
- **Public Interface**: An interface composed of public members
- **Implementation**: Consists of the code that actually makes the class behave as intended
- **Data Hiding**: Technique used to enforce the separation of interface and implementation by hiding the implementation of a program-defined data type from users
- **Encapsulation**: Used to refer to data hiding, also used to refer to the bundling of data and funcitons together
- **Constructor**: A special member function that is used to initialize class type objects
- **Member Initializer List**: Allows you to initialize your member variables from within a constructor
- **Default Constructor**: A constructor that takes no parameters
- **Implicit Default Constructor**: If a non-aggregate class type object has no user-declared constructors, the compiler will generate a default constructor
- **Constructor Chaining**: Constructors are allowed to delegate initialization to another constructor from the same class type
- **Delegating Constructors**: Constructors that perform constructor chaining
- **Temporary Object**: An object that has no name and exists only for the duration of the single expression
- **Copy Constructor**: A constructor that is used to initialize an object with an existing object of the same type
- **Implicit Copy Constructor**: C++ will create an implicit copy constructor that performs memberwise initalization
- **As If Rule**: The compiler can modify a program however it likes in order to produce more optimzied code, so long as those modifications do not affect a programls "observable behavior"
- **Copy Elision**: A compiler optimization technique that allows the compiler to remove unnecessary copying of objects
- **user-Defined Conversions**: A function that we've written to convert a value to or from a program defined type
- **Converting Constructor**: A constructor that can be used to perform an implicit conversion
- **Explicit**: A keyword to tell the compiler that a constructor should not be used as a converting constructor

## Quiz

1. 
a) Write a class named Point2d. Point2d should contain two member variables of type double: m_x, and m_y, both defaulted to 0.0.

Provide a constructor and a print() function.

The following program should run:

```cpp
#include <iostream>

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print();
    second.print();

    return 0;
}
```

```shell
Point2d(0, 0)
Point2d(3, 4)
```

```cpp
class Point2d
{
private:
	double m_x {0.0};
	double m_y {0.0};

public:

	Point2d(double x = 0.0, double y = 0.0) : m_x {x}, m_y {y}
	{
	}

	void print()
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}
};
```

b) Now add a member function named distanceTo() that takes another Point2d as a parameter, and calculates the distance between them. Given two points (x1, y1) and (x2, y2), the distance between them can be calculated using the formula std::sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)). The std::sqrt function lives in header cmath.

The following program should run:

```cpp
#include <cmath>
#include <iostream>

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

    return 0;
}
```

```shell
Point2d(0, 0)
Point2d(3, 4)
Distance between two points: 5
```

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <cmath>

class Point2d
{
private:
	double m_x {0.0};
	double m_y {0.0};

public:

	Point2d(double x = 0.0, double y = 0.0) : m_x {x}, m_y {y}
	{
	}

	void print()
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}

	double distanceTo(Point2d& target)
	{
		return std::sqrt((m_x - target.m_x) * (m_x - target.m_x) + (m_y - target.m_y) * (m_y - target.m_y));
	}
};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

    return 0;
}
```

2. Convert Fraction from a struct to a class. Convert all of the functions to (non-static) member functions.

```cpp
#include <iostream>

struct Fraction
{
    int numerator{ 0 };
    int denominator{ 1 };
};

Fraction getFraction()
{
    Fraction temp{};
    std::cout << "Enter a value for numerator: ";
    std::cin >> temp.numerator;
    std::cout << "Enter a value for denominator: ";
    std::cin >> temp.denominator;
    std::cout << '\n';

    return temp;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
    return { f1.numerator * f2.numerator, f1.denominator * f2.denominator };
}

void printFraction(const Fraction& f)
{
    std::cout << f.numerator << '/' << f.denominator << '\n';
}

int main()
{
    Fraction f1{ getFraction() };
    Fraction f2{ getFraction() };

    std::cout << "Your fractions multiplied together: ";

    printFraction(multiply(f1, f2));

    return 0;
}
````

```cpp
#include <iostream>

class Fraction
{
private:
	int m_numerator{ 0 };
	int m_denominator{ 0 };

public:

	explicit Fraction(int numerator = 0, int denominator = 0) : m_numerator { numerator }, m_denominator { denominator }
	{
	}

	void getFraction()
	{
		std::cout << "Enter a value for numerator: ";
		std::cin >> m_numerator;
		std::cout << "Enter a value for denominator: ";
		std::cin >> m_denominator;
		std::cout << '\n';
	}

	Fraction multiply(const Fraction& other) const
	{
		return Fraction{ m_numerator * other.m_numerator, m_denominator * other.m_denominator };
	}

	void print()
	{
		std::cout << m_numerator << '/' << m_denominator << '\n';
	}
};


int main()
{
    Fraction f1{  };
	f1.getFraction();
    Fraction f2{  };
	f2.getFraction();

    std::cout << "Your fractions multiplied together: ";

	Fraction f3 {f1.multiply(f2)};
    f3.print();

    return 0;
}
```

3. In the prior quiz solution, why was the Fraction constructor made explicit?
- Making the constructor explicit prevents it from being used to create a Fraction via an implicit conversion with a single value. This helps prevent nonsense like f1.multiply(true).

f1.multiply(true) requires that true be implicitly converted to a Fraction. Normally the compiler would use Fraction(int numerator=0, int denominator=1) for this, but if we make that constructor explicit, it is not eligible to be used for implicit conversions. Since the compiler will then be unable to find a way to convert true into a Fraction, it will emit a compilation error.

4. In the prior quiz question, why might it be better to leave getFraction() and print() as non-members?
- With the non-member version of getFraction(), we can define and initialize a Fraction in a single step. The member version requires two steps, as we must first create an object and then call the member function on it. It also prints application-specific text prompts for the user to follow.

By moving print() to be a non-member (and using access functions to access the members), we remove the function from the interface of the class, making the core functionality of the class less cluttered. It also means that if the implementation of the class is ever changed, we don’t need to consider whether print() needs to be updated, so long as the interface isn’t changed (since we know it can’t access any data members directly).

