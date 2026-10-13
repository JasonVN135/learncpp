# F.1 - Constexpr Functions

## Notes

`constexpr` keyword is used to create compile-time (symbolic) constants

Function call to a normal function are not allowed in constant expressions
- We cannot use such function calls anywhere a constant expression is required

```cpp
#include <iostream>

int main()
{
    constexpr double radius { 3.0 };
    constexpr double pi { 3.14159265359 };
    constexpr double circumference { 2.0 * radius * pi };

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```

```shell
Our circle has circumference 18.8496
```

Having a complex initializer for `circumference` isn't great

Let's make a function instead

```cpp
#include <iostream>

double calcCircumference(double radius)
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // compile error

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```

It doesn't compile. Variable `circumference` requires that its initializer is a constant expression.
- `calcCircumference()` isn't a constant expression

### Constexpr functions can be used in constant expressions

**Constexpr Function**: A function that is allowed to be called in a constant expression

Simply use the `constexpr` keyword in front of the function's return type.

```cpp
#include <iostream>

constexpr double calcCircumference(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // now compiles

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```

### Constexpr funtions can be evaluated at compile time

A constant expression is required to evaluate at compile-time
- If a required constant expression contains a constexpr function call, that constexpr function call must evaluate at compile time

The call to `calcCircumference(3.0)` is replaced with the result of the function call

```cpp
#include <iostream>

constexpr double calcCircumference(double radius)
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { 18.8496 };

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```

To evaluate at compile time, 2 other things must also be true:
- The call to the constexpr function must have arguments that are known at compile time
- All statements and expressions within the constexpr function must be evaluateable at compile-time

### Constexpr functions can also be evaluated at runtime

Constexpr functions call also be evaluated at runtime, in which case they will return a non-constexpr result

```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    int x{ 5 }; // not constexpr
    int y{ 6 }; // not constexpr

    std::cout << greater(x, y) << " is greater!\n"; // will be evaluated at runtime

    return 0;
}
```

Because argument `x` and `y` are not constant expressions, the function cannot be resolved at compile time
- The function can still be resolved at runtime

# F.2 - Constexpr functions (part 2)

## Notes

### Constexpr function calls in non-required constant expressions

```cpp
#include <iostream>

constexpr int getValue(int x)
{
    return x;
}

int main()
{
    int x { getValue(5) }; // may evaluate at runtime or compile-time

    return 0;
}
```

Because `getValue()` is a constexpr, the call `getValue(5)` is a constant expression.
- Because variable `x` is not a constexpr, idt does not require a constant e pression initializer
- Even though we've provided a constant expression initializer, the compiler is free to choose whether `getValue(5)` evaluates at runtime or compile time

### Diagnosis of constexpr functions in required constant expression

Compiler is `not` required to determine whether a constexpr functinon is evaluated at compile time until it is actually evaluated at compile-time

```cpp
#include <iostream>

int getValue(int x)
{
    return x;
}

// This function can be evaluated at runtime
// When evaluated at compile-time, the function will produce a compilation error
// because the call to getValue(x) cannot be resolved at compile-time
constexpr int foo(int x)
{
    if (x < 0) return 0; // needed prior to adoption of P2448R1 in C++23 (see note below)
    return getValue(x);  // call to non-constexpr function here
}

int main()
{
    int x { foo(5) };           // okay: will evaluate at runtime
    constexpr int y { foo(5) }; // compile error: foo(5) can't evaluate at compile-time

    return 0;
}
```

When writing a constexpr function, always explicitly test that it compiles when evaluated at compile time - Call it in a context where a constant expression is required, such as in the initialization of a constexpr variable

### Constexpr/consteval function parameters are not constexpr

The parameters of a constexpr function are not implicitly constexpr, nor may they be dclared as `constexpr`

Because such parameters are not constexpr, they cannot be used in constant expressions within the function

```cpp
consteval int goo(int c)    // c is not constexpr, and cannot be used in constant expressions
{
    return c;
}

constexpr int foo(int b)    // b is not constexpr, and cannot be used in constant expressions
{
    constexpr int b2 { b }; // compile error: constexpr variable requires constant expression initializer

    return goo(b);          // compile error: consteval function call requires constant expression argument
}

int main()
{
    constexpr int a { 5 };

    std::cout << foo(a); // okay: constant expression a can be used as argument to constexpr function foo()

    return 0;
}
```

The parameters of constexpr functions may be declared as `const`, in which case they are treated as runtime constants

### Constexpr functions are implicitly inline

When a constexpr function is evaluated at compile-time, the compiler must be able to see the full definition of the constexpr function prior to such function calls
- Forward declaration will not suffice in this case, even if the actual function definition appears later in the same compilation unit

A constexpr function call in multiple files needs to have its definition included into each translation unit
- Normally be a violation of the ODR
- Constexpr functions are implicitly inline, makes them exempt from the ODR

Best Practice:
- Constexpr/consteval functions used in a single source file (.cpp) should be defined in the source file above where they are used
- Constexpr/consteval functions used in multiple source files should be definedin a header file so they can be included into each source file

### Recap
  
- Marking a function as `constexpr` means it can be used in a constant expression
  - It does not mean "will evaluate at compile time"
- A constant expression is only required to evaluate at compile time in contexts where a constant expression is required
- In contexts that don't require a constant expression, the compiler may choose whether to evaluate a constant expression at compile time or at runtime
- A runtime expression will evaluate at runtime

# F.3 - Constexpr functions (part 3) and consteval

## Notes

### Forcing a constexpr function to be evaluated at compile-time

There is no way to tell the compiler that a constexpr function should prefer to evaluate at compile time whenever it can
- We can force a constexpr function that is eligible to be evaluated at compile-time to actually evaluate at compile-time by ensuring the return value is used where a constant expression is required.
- The most common way to do this is to use the return value to initialize a constexpr variable
  - This requires introducing a new variable into our program just to ensure compile-time evaluation

### Consteval C++20

**Consteval**: Used to indicate that a function **must** evaluate at compile time
- Otherwise a compile error will result
- Such functions are called **Immediate Functions**

```cpp
#include <iostream>

consteval int greater(int x, int y) // function is now consteval
{
    return (x > y ? x : y);
}

int main()
{
    constexpr int g { greater(5, 6) };              // ok: will evaluate at compile-time
    std::cout << g << '\n';

    std::cout << greater(5, 6) << " is greater!\n"; // ok: will evaluate at compile-time

    int x{ 5 }; // not constexpr
    std::cout << greater(x, 6) << " is greater!\n"; // error: consteval functions must evaluate at compile-time

    return 0;
}
```

C++ Doesn't currently provide any relabile mechanism to determine if a constexpr function call is evaluating at compile-time or runtime

### What about `std::is_constant_evaluated` or `if consteval`?

Neither tell you whether a function call is evaluating at compile time or runtime

`std::is_constant_evaluated()` returns a `bool` indicating whether the current function is executing in a constant-evaluated context

**Constant Evaluated Context**: One in which a constant expression is required
- In cases where the compiler is required to evaluate a constant expression at compile-time, `std::is_constant_evaluated()` will `true` as expected

```cpp
#include <type_traits> // for std::is_constant_evaluated()

constexpr int someFunction()
{
    if (std::is_constant_evaluated()) // if evaluating in constant context
        doSomething();
    else
        doSomethingElse();
}
```

The compiler may also choose to evaluate a constexpr function at compile-time in a context that doesn't require a constant expression

In C++23, `if consteval` is a replacement for `if (std::is_constant_evaluated())`, providing a nicer syntax and fixes some other issues

### Using consteval to make constexpr execute at compile-time C++20

Such functions can't evaluate at runtime, making them less flexible than constexpr functions
- Still be useful to have a convenient way to force constexpr functions to evaluate at compile-time

```cpp
#include <iostream>

#define CONSTEVAL(...) [] consteval { return __VA_ARGS__; }()               // C++20 version per Jan Scultke (https://stackoverflow.com/a/77107431/460250)
#define CONSTEVAL11(...) [] { constexpr auto _ = __VA_ARGS__; return _; }() // C++11 version per Justin (https://stackoverflow.com/a/63637573/460250)

// This function returns the greater of the two numbers if executing in a constant context
// and the lesser of the two numbers otherwise
constexpr int compare(int x, int y) // function is constexpr
{
    if (std::is_constant_evaluated())
        return (x > y ? x : y);
    else
        return (x < y ? x : y);
}

int main()
{
    int x { 5 };
    std::cout << compare(x, 6) << '\n';                  // will execute at runtime and return 5

    std::cout << compare(5, 6) << '\n';                  // may or may not execute at compile-time, but will always return 5
    std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will always execute at compile-time and return 6


    return 0;
}
```

# F.4 - Constexpr functions (part 4)

## Notes

### Constexpr/consteval functions can use non-const local variables

Within a constexpr or consteval function, we can use local variables that are not constexpr, and the value of these variables can be changed

```cpp
#include <iostream>

consteval int doSomething(int x, int y) // function is consteval
{
    x = x + 2;       // we can modify the value of non-const function parameters

    int z { x + y }; // we can instantiate non-const local variables
    if (x > y)
        z = z - 1;   // and then modify their values

    return z;
}

int main()
{
    constexpr int g { doSomething(5, 6) };
    std::cout << g << '\n';

    return 0;
}
```

When such functions are evaluated at compile time, the compiler will essentially "execute" the funciton and return the calculated state

### Constexpr/consteval functions can use function parameters and local variables as arguments in constexpr functions

A constexpr or consteval function can use its function parameters or even local variables (which may not be const at all) as arguments in a constexpr function call.

When a constexpr or consteval function is being evaluated at compile time, the value of all function parameters and local variables must be known to the compiler
- In specific context, C++ allows these values to be used as arguments in a call to a constexpr function, and that constexpr function call can still be evaulated at compile time

```cpp
#include <iostream>

constexpr int goo(int c) // goo() is now constexpr
{
    return c;
}

constexpr int foo(int b) // b is not a constant expression within foo()
{
    return goo(b);       // if foo() is resolved at compile-time, then `goo(b)` can also be resolved at compile-time
}

int main()
{
    std::cout << foo(5);

    return 0;
}
```

### Can a constexpr function call a non-constexpr function?

Yes, but only when the constexpr funciton is being evaluated in a non-constant context.
- A non-constexpr function may not be called when a constexpr function is evaluating in a constant context
- Doing so will produce a compilation error

Calling a non-constexpr function is allowed so that a constexpr function can do something like this:

```cpp
#include <type_traits> // for std::is_constant_evaluated

constexpr int someFunction()
{
    if (std::is_constant_evaluated()) // if evaluating in constant context
        return someConstexprFcn();
    else
        return someNonConstexprFcn();
}
```

Consider this variant

```cpp
constexpr int someFunction(bool b)
{
    if (b)
        return someConstexprFcn();
    else
        return someNonConstexprFcn();
}
```

This is legal as long as `someFunction(false)` is never called in a constant expression

Best results:
- Avoid calling non-constexpr functions from within a constexpr function if possible
- If your constexpr function requires different behavior for constant and non-constant context, conditionalize the behavior with `if (std::is_constant_evaluated())` in C++20
  - `if consteval` in C++23
- Always test your constexpr functions in a constant context, as they may work when called in a non-constant context but fail in a constant context

### When Should i constexpr a function?

If a function ca be evaluated as part of a required constant expression, it should be made `constexpr`

**Pure Function**: A function that meets the following criteria:
- The function always returnst he same return result when given the same arguments
- The function as no side effects (doesn't change the value of static local or global variables, doesn't do input or output, etc.)

Pure functions should generally be made constexpr

### Why not constexpr every function

1. `constexpr` signals that a function can be used in a constant expression. If your function cannot be evaluated as part of a constant expression, it should not be marked as `constexpr`
2. `constexpr` is part of the interface of a function. Once made constexpr, it can be called by other constexpr functions or used in contexts that require constant expressions. Removing the `constexpr` later will break such code
3. `constexpr` functions can be harder to debug since you can't breakpoint or step through them in a debugger

### Why constexpr a function when it is not actually evaluated at compile-time?

1. Little downside to using constexpr, may help the compiler optimize your program to be smaller and faster
2. Just because you're not calling the function in a compile time evaluatable context now doesn't mean you won't later
3. Repetition helps ingrain best practice 

# F.x - Chapter F summary and quiz

## Notes

- **constexpr Function**: A function that is allowed to be called in a constant expression
- **consteval Function**: A function that must evaluate at compile time

## Quiz

1. Add `const` and/or `constexpr` to the following program

```cpp
#include <iostream>

// gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns ball height from ground after "seconds" seconds
double calculateBallHeight(double towerHeight, int seconds)
{
	double gravity{ 9.8 };

	// Using formula: [ s = u * t + (a * t^2) / 2 ], here u(initial velocity) = 0
	double distanceFallen{ (gravity * (seconds * seconds)) / 2.0 };
	double currentHeight{ towerHeight - distanceFallen };

	return currentHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
void printCalculatedBallHeight(double towerHeight, int seconds)
{
	double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	double towerHeight{ getTowerHeight() };

	printCalculatedBallHeight(towerHeight, 0);
	printCalculatedBallHeight(towerHeight, 1);
	printCalculatedBallHeight(towerHeight, 2);
	printCalculatedBallHeight(towerHeight, 3);
	printCalculatedBallHeight(towerHeight, 4);
	printCalculatedBallHeight(towerHeight, 5);

	return 0;
}
```

```cpp
#include <iostream>

// gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns ball height from ground after "seconds" seconds
constexpr double calculateBallHeight(double towerHeight, int seconds)
{
	constexpr double gravity{ 9.8 };

	// Using formula: [ s = u * t + (a * t^2) / 2 ], here u(initial velocity) = 0
	const double distanceFallen{ (gravity * (seconds * seconds)) / 2.0 };
	const double currentHeight{ towerHeight - distanceFallen };

	return currentHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
void printCalculatedBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	const double towerHeight{ getTowerHeight() };

	printCalculatedBallHeight(towerHeight, 0);
	printCalculatedBallHeight(towerHeight, 1);
	printCalculatedBallHeight(towerHeight, 2);
	printCalculatedBallHeight(towerHeight, 3);
	printCalculatedBallHeight(towerHeight, 4);
	printCalculatedBallHeight(towerHeight, 5);

	return 0;
}
```