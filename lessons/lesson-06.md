# 6.1 - Operator Precedence and Associativity

## Quiz

1. For this exercise, you are given a set of expressions that have no parentheses. Using the operator precedence and associativity rules in the table above, add parentheses to each expression to make it clear how the compiler will evaluate the expression.

- x = 3 + 4 + 5
  - x = ((3 + 4) + 5)
- x = y = z
  - x = (y = z)
- z *= ++y + 5
  - z *= ((++y) + 5)
- a || b && c || d;
  - (a || (b && c)) || d


## Notes

**Operation**: A mathematical process involving 0+ input values (**Operands**) that produces a new value
**Operator**: The specific operation to be performed is denoted by a construct symbol

### Evaluation of compound expressions

Using normal mathematical precedence rules, we know that `4 + 2 * 3` is the same as `4 + (2 * 3)`
- How does the compiler know
  - At compile time, the compiler must parse the expression and determine how operands are grouped with operators
    - Done via the precedence and associatevity rules
  - At compile or runtime, the operands are evaluated and operations executed to produce a result

### Operator Precedence

To assist with parsing a compound expression, all operators are assigned a level of precedence
- Operators with higher **precedence** levels are grouped with operands first

### Operator associativity

Would `(7 - 4 - 1)` be the same as `(7 - 4) - 1 = 2` or `7 - (4 - 1) = 4`?
- Since both subtraction operators have the same precedence level, the compiler can not use precedence alone to determine how this should be group

The operator's **sociateivity** tells the compiler whether to evaluate the operators from left to right or from right to left
- Operators in precedence level 6 (subtration and addition) have associativity of left to right

### Parenthesization

We can explicitly use parentheses to set the grouping of operands as we desire

### Use parenthesis to make compound expressions easier to understand

In order to reduce mistakes and make your code easier, it's a good idea to parenthesize any non-trivial compound expressions
- Parenthesize evertying, except addition, subtraction, multiplication, and division

```cpp
x = (y + z + w);   // instead of this
x = y + z + w;     // it's okay to do this

x = ((y || z) && w); // instead of this
x = (y || z) && w;   // it's okay to do this

x = (y *= z); // expressions with multiple assignments still benefit from parenthesis
```

The assignment operators have the second lowest precedence (only the comma operator is lower, and rarely used)

### Value computation of operations

**Value Computation**: The execution of operators in an expression to produce a value
- The precedence and association rules determine the order in which value compuation happens
- `4 + (2 * 3)` -> The value computation for `(2 * 3)` must happen first
  - So that value computation `(4 + 6)` can be completed

### Evaluation of operands

**Evaluation**: Refer to the evaluation of operands (not the evaluation of operators or expressions)
- Given `(a + b)`, `a` will be evaluated to produce some value, and `b` will be evaluated to produce some value
- These values can be then used as operands to `operator+` for value computation

### The order of evaluation of operands is mostly unspecified

We know from precedence and associativity rules that `a * b + c * d` will evaluate to  `(a * b) + (c * d) = 14`
- They do not tell us the orer in which the operands or subexpressions are evaluated
- Compiler is free to evalute the operands in any order

It is possible to write expressions where the order of evaluation does matter

```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z);
}

int main()
{
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous

    return 0;
}
```

The above program can be made unambiguous by making each function call to `getValue()` a separate statement


# 6.2 - Arithmetic operators

## Notes

### Unary arithmetic operators

2 Unary operators, plus (+) and minus (-). Only take 1 operand

**Unary minus**: Returns the operand multiplied by -1\
**Unary plus**: Returns the value of the operand, generally redundant

### Binary arithmetic operators

5 Binary arithmetic operators, take a left and right operand
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Remainder (%)

### Integer and floating point division

Divison operator has 2 different modes

**Floating point division**: Returns a floating point value, and the fraction is kept
**Integer Division**: Both operands are integers, drop any fractions and returns an integer value

### static_cast<> to do floating point division with integers

```cpp
#include <iostream>

int main()
{
    constexpr int x{ 7 };
    constexpr int y{ 4 };

    std::cout << "int / int = " << x / y << '\n';
    std::cout << "double / int = " << static_cast<double>(x) / y << '\n';
    std::cout << "int / double = " << x / static_cast<double>(y) << '\n';
    std::cout << "double / double = " << static_cast<double>(x) / static_cast<double>(y) << '\n';

    return 0;
}
```

### Dividing by 0 and 0.0

Integer divison with a divisor of `0` will cause undefined behavior, as the results are mathematically undefined!

The result of dividing by floating point value 0.0 is implementation defined.
- Behavior is determined by the compiler/architecture
- IEEE754 returns `Nan` or `Inf`, other architectures return undefined behavior

### Arithmetic assignemtn operators

- Additon assignment (+=)
- Subtraction assignemnt (-=)
- Multiplication assignemnt (*=)
- Division assignment (/=)
- Remainder assignment (%=)

### Modifying and non-modifying operators

**Modifying Operators**: An operator that can modify the value of one of its operands
- +=, -=, *=, /=, %=
- Bitwise assignment: <<=, >>=, &= |= and ^=

# 6.3 - Remainder and Exponentiation

## Questions

1. What does the following expression evaluate to? `6 + 5 * 4 % 3`
- 8

2. Write a program that asks the user to input an integer, and tells the user whether the number is even or odd. Write a constexpr function called isEven() that returns true if an integer passed to it is even, and false otherwise. Use the remainder operator to test whether the integer parameter is even. Make sure isEven() works with both positive and negative numbers.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int getNumber()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    return x;
}

bool isEven(const int x)
{
    if (x % 2 == 0) {
        return true;
    }
    return false;
}

int main()
{
    const int x{getNumber()};
    bool isNumberEven{isEven(x)};

    if (isNumberEven) {
        std::cout << x << " is even\n";
    }
    else {
        std::cout << x << " is odd\n";
    }
    return 0;
}
```

## Notes

### The remainder operator

**Remainder Operator** (**Modulo Operator**) An operator that returns the remainder after doing an integer division

```cpp
#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	std::cout << "Enter another integer: ";
	int y{};
	std::cin >> y;

	std::cout << "The remainder is: " << x % y << '\n';

	if ((x % y) == 0)
		std::cout << x << " is evenly divisible by " << y << '\n';
	else
		std::cout << x << " is not evenly divisible by " << y << '\n';

	return 0;
}
```

### Remainder with negative numbers

The remainder will take the sign of the first operand

```shell
Enter an integer: -6
Enter another integer: 4
The remainder is: -2
-6 is not evenly divisible by 4

Enter an integer: 6
Enter another integer: -4
The remainder is: 2
6 is not evenly divisible by -4
```

### Where's the exponent operator

C++ does not include an exponent operator\
To do exponents, `#include <cmath>` and use the `pow()` function
- There may be rounding errors
If you want to do integer exponentation, you're better off using your own function to do so

```cpp
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>

// note: exp must be non-negative
// note: does not perform range/overflow checking, use with caution
constexpr std::int64_t powint(std::int64_t base, int exp)
{
	assert(exp >= 0 && "powint: exp parameter has negative value");

	// Handle 0 case
	if (base == 0)
		return (exp == 0) ? 1 : 0;

	std::int64_t result{ 1 };
	while (exp > 0)
	{
		if (exp & 1)  // if exp is odd
			result *= base;
		exp /= 2;
		base *= base;
	}

	return result;
}

int main()
{
	std::cout << powint(7, 12) << '\n'; // 7 to the 12th power

	return 0;
}
```

Safer version that checks overflow

```cpp
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>
#include <limits> // for std::numeric_limits

// A safer (but slower) version of powint() that checks for overflow
// note: exp must be non-negative
// Returns std::numeric_limits<std::int64_t>::max() if overflow occurs
constexpr std::int64_t powint_safe(std::int64_t base, int exp)
{
    assert(exp >= 0 && "powint_safe: exp parameter has negative value");

    // Handle 0 case
    if (base == 0)
        return (exp == 0) ? 1 : 0;

    std::int64_t result { 1 };

    // To make the range checks easier, we'll ensure base is positive
    // We'll flip the result at the end if needed
    bool negativeResult{ false };

    if (base < 0)
    {
        base = -base;
        negativeResult = (exp & 1);
    }

    while (exp > 0)
    {
        if (exp & 1) // if exp is odd
        {
            // Check if result will overflow when multiplied by base
            if (result > std::numeric_limits<std::int64_t>::max() / base)
            {
                std::cerr << "powint_safe(): result overflowed\n";
                return std::numeric_limits<std::int64_t>::max();
            }

            result *= base;
        }

        exp /= 2;

        // If we're done, get out here
        if (exp <= 0)
            break;

        // The following only needs to execute if we're going to iterate again

        // Check if base will overflow when multiplied by base
        if (base > std::numeric_limits<std::int64_t>::max() / base)
        {
            std::cerr << "powint_safe(): base overflowed\n";
            return std::numeric_limits<std::int64_t>::max();
        }

        base *= base;
    }

    if (negativeResult)
        return -result;

    return result;
}

int main()
{
	std::cout << powint_safe(7, 12) << '\n'; // 7 to the 12th power
	std::cout << powint_safe(70, 12) << '\n'; // 70 to the 12th power (will return the max 64-bit int value)

	return 0;
}
```

# 6.4 - Increment/Decrement operators, and side effects

## Notes

### Incrementing and decrementing variables

- Prefix increment (pre-increment) - ++x - increment x, then return x
- Prefix decrement (pre-decrement) - --x - decrement x, then return x
- Postfix increment (post-increment) - x++ - copy x, then increment x, then return the copy
- Postfix decrement (post-decrement) - x-- - copy x, then decrement x, then return the copy

### Prefix increment and decrement

First the operand is incremented or decremented, then expression evaluates the value of the operand

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { ++x }; // x is incremented to 6, x is evaluated to the value 6, and 6 is assigned to y

    std::cout << x << ' ' << y << '\n';
    return 0;
}
```

```shell
6 6
```

### Postfix increment and decrement

First copy the operand, then the operand is incremented/decremented, then the copy is evaluated

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { x++ }; // x is incremented to 6, copy of original x is evaluated to the value 5, and 5 is assigned to y

    std::cout << x << ' ' << y << '\n';
    return 0;
}
```

```shell
6 5
```

### When to use prefix vs postfix

In many cases, the prefix and postfix operators produce the same behavior
- Prefer the prefix versions, as they are generally more performant, and less likely to cause surprises

Use postfix when doing so produces significantly more concise or understandable code than the equivalent code written using the prefix versions

### Side Effects

**Side effects**: Function has a side effect if it has some observable effect beyond producing a return value


### Side effects can cause order of evaluation issues

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int x { 5 };
    int value{ add(x, ++x) }; // undefined behavior: is this 5 + 6, or 6 + 6?
    // It depends on what order your compiler evaluates the function arguments in

    std::cout << value << '\n'; // value could be 11 or 12, depending on how the above line evaluates!

    return 0;
}
```

### The sequence of side effects

In many cases, C++ doesn't specify when the side effects of operators must be applied
- Lead to undefined behavior

C++ does not define the order of evaluation for function arguments or the operands of operators

Don't use a variable that has a side effect applied to it more than once in a given statement

# 6.5 - The comma operator

Comma - , - x, y - Evaluate x then y, returns value of y

**Comma Operator**: Allows you to evaluated multiple expressions wherever a single xpression is allowed

```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand

    return 0;
}
```

The left operand is evaluated, increments `x` from `1` to `2`.
- Next the right operand is evaluated, increments `y` from `2` to `3`
- `3` is printed in the console

Comma has the lowest precedence of all operators, even assignments

```cpp
z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
```

A statement written using the comma operator would be better written as separate statements\
Most programmers don't use commas, unless inside for-loops

### Comma as a separator

The comma symbol is often used as a separator, these uses do not invoke the comma operator

```cpp
void foo(int x, int y) // Separator comma used to separate parameters in function definition
{
    add(x, y); // Separator comma used to separate arguments in function call
    constexpr int z{ 3 }, w{ 5 }; // Separator comma used to separate multiple variables being defined on the same line (don't do this)
}
```

# 6.6 The conditional operator

## Notes

**Conditional Operator (?:)**: (**Arithmetic if**), a ternary operator (3 operands).
- Provides a shorthand method for doing a particular type of if-else statement

```shell
condition ? expression1 : expression2;
```

### Example

```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    int x { getValue() };
    int y { getValue() };
    int max { (x > y) ? x : y };
    std::cout << "The max of " << x <<" and " << y << " is " << max << ".\n";

    return 0;
}
```

If `x > y` is true, `max` is set to `x`, else, `max` is set to `y`

### Conditional operator evaluates as part of an expression

Since the conditional operator is evaluated as part of an expression, it can be used anywhere an expression is accepted.

The conditional operator can be used in a constant expressions, allowing the conditional operator to be used in place where statements cannot be used.

```cpp
#include <iostream>

int main()
{
    constexpr bool inBigClassroom { false };
    constexpr int classSize { inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```

There's no direct if-else replacement for this.

To try and use if-else:

```cpp
#include <iostream>

int getClassSize(bool inBigClassroom)
{
    if (inBigClassroom)
        return 30;
    else
        return 20;
}

int main()
{
    const int classSize { getClassSize(false) };
    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```

### Parenthesizing the conditional operator

Because C++ prioritizes the evaluation of most operators above the evaluation of the conditional operator, it's quite easy to write expressions using the ocnditional operator that don't evaluate as expected.

To avoid evaluation prioritization issues, the conditional operator should be parenthesized as follows:
- Parenthesize the entire conditional operation when used in a compound expression
- For readability, consider parenthesizing the condition if it contains any operators

```cpp
return isStunned ? 0 : movesLeft;           // not used in compound expression, condition contains no operators
int z { (x > y) ? x : y };                  // not used in compound expression, condition contains operators
std::cout << (isAfternoon() ? "PM" : "AM"); // used in compound expression, condition contains no operators (function call operator excluded)
std::cout << ((x > y) ? x : y);             // used in compound expression, condition contains operators
```

### The type of the expressions must match or be convertible

One of the following must be true:
- The type of the second and third operand must match
- The compiler must be able to find a way to convert one or both of the operands to matching types

```cpp
#include <iostream>

int main()
{
    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int

    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double

    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range

    return 0;
}
```

If either operand is not a fundamental type, it's generally best to explicitly convert one or both operands to a matching type yourself so you know exactly what you'll get

If the compiler can't convert either operands, a compile error will result

### When should you use the conditional operator?

Doing one of the following:
- Initializing an object with 1 of 2 values
- Assigning 1 of 2 values to an object
- Passing 1 of 2 values to a function
- Returning 1 of 2 values from a function
- Printing 1 of 2 values

# 6.7 - Relational operators and floating point comparisons

## Notes

**Relational operators**: Operators that let you compare 2 values
- Greater than - >
- Less than - <
- Greater than or equals - >=
- Less than or equals - <=
- Equality - ==
- Inequality - !=

### Boolean conditional values

Conditions in an *if statement* or *conditional operator* evaluate as Boolean values

```cpp
if (b1 == true)

if (b1) // same thing
```

```cpp
if (b1 == false)

if (!b1) // same thing
```

### Comparison of calculated floating point values can be problematic

```cpp
#include <iostream>

int main()
{
    constexpr double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
    constexpr double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';

    return 0;
}
```

Both values should be equal, but sometimes they are not.\
Floating point values are not precise, and small rounding errors may cause them to be slightly smaller or larger than expected

### Floating point less-than and greater-than

<, >, <=, and >= are reliable with floating point values.
- If the operands are almost identical, these operators should be considered unreliable

If the consequence of getting a wrong answer when the operands are similar is acceptable, then using these operators can be acceptable.

### Floating point equality and inequality

== and != are more trouble some, as they evaluate when exactly equal.

One exception is it is safe to compare a floating point literal with a variable of the same type that has been initialized with a literal of the same type.

We can also compare a const or constexpr floating point variable that was initialized with a literal value

```cpp
constexpr double gravity { 9.8 };
if (gravity == 9.8) // okay if gravity was initialized with a literal
    // we're on earth
```

# 6.8 - Logical Operators

## Questions

1. Evaluate the following expressions.

Note: in the following answers, we “explain our work” by showing you the steps taken to get to the final answer. The steps are separated by a => symbol. Expressions that were ignored due to the short circuit rules are placed in square brackets.

- (true && true) || false
  - true
- (false && true) || true
  - true
- (false && true) || false || true
  - true
- (5 > 6 || 4 > 3) && (7 > 8)
  - false
- !(7 > 6 || 3 > 4)
  - false

2. Rewrite this function using operator! instead of operator==.

```cpp
#include <iostream>

bool isEven(int x)
{
    // if x % 2 == 0, 2 divides evenly into our number, which means it must be an even number
    return (x % 2) == 0;
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (isEven(x))
        std::cout << x << " is even\n";
    else
        std::cout << x << " is odd\n";

    return 0;
}
```

```cpp
#include <iostream>

bool isEven(int x)
{
    // if x % 2 == 0, 2 divides evenly into our number, which means it must be an even number
    return !(x % 2);
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (isEven(x))
        std::cout << x << " is even\n";
    else
        std::cout << x << " is odd\n";

    return 0;
}
```

## Notes

Logical operators provide capabilities to test multiple conditions
- Logical NOT - ! - !x
- Logical AND - && - x && y
- Logical Or - || - x || y

**Logical Not**: !true -> false, !false -> true

```cpp
bool tooLarge { x > 100 }; // tooLarge is true if x > 100
if (!tooLarge)
    // do something with x
else
    // print an error
```

If logical NOT is intended to operate on the result of other operators, the other operators and their operands need to be enclosed in parenthese

### Logical OR

The logical OR is used to test whether either of two conditions is true
- true || true => true
- true || false => true
- false || true => true
- false || false => false

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int value {};
    std::cin >> value;

    if (value == 0 || value == 1)
        std::cout << "You picked 0 or 1\n";
    else
        std::cout << "You did not pick 0 or 1\n";
    return 0;
}
```

You can string together many logical OR statements:

```cpp
if (value == 0 || value == 1 || value == 2 || value == 3)
     std::cout << "You picked 0, 1, 2, or 3\n";
```

### Logical AND

Logical AND is used to test whether both operands is true
- false && false => false
- true && false => false
- false && true => false
- true && true => true

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int value {};
    std::cin >> value;

    if (value > 10 && value < 20)
        std::cout << "Your value is between 10 and 20\n";
    else
        std::cout << "Your value is not between 10 and 20\n";
    return 0;
}
```

You can string multiple logical AND statements

```cpp
if (value > 10 && value < 20 && value != 16)
    // do something
else
    // do something else
```

If all conditions are true, the if statement will execute.

### Short Circuit evaluation

**Short Circuit Evaluation**: The logical AND will not evaluate the right side if the left side is false. It will immediately return false if the left is already false, without checking the right.

### Mixing ANDs and ORs

logical AND has higher precedence than logical OR.
- Logical AND will be evaluated ahead of logical OR operators

### De Morgan's Law

`!(x && y) => (!x || !y)`
`!(x || y) => (!x && !y)`

### Where's the logical exclusive or (XOR) operator?

Logical XOR is a logical operator provided in some languages that is used to test whether an odd number of conditions is true
- false XOR false => false
- true XOR false => true
- false XOR true => true
- true XOR true => false

C++ doesn't provide an explicit logical XOR operator

`!=` produces the same results as logical XOR

### Alternative operator representation

C++ supports an alternative set of keywods for the operators that use words instead of symbols
- && => and
- || => or
- ! => not

# 6.x - Chapter 6 summary and quiz

## Review

- **Conditional operator (?:)**: a ternary operator. Given condition c, if c evaluates true, the x is evaluated, else y is evaluated

## Quiz

1. Complete the folowing program:

```cpp
#include <iostream>

// Write the function getQuantityPhrase() here

// Write the function getApplesPluralized() here

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}
```

Sample output:

```shell
Mary has a few apples.
How many apples do you have? 1
You have a single apple.
```

getQuantityPhrase() should take a single int parameter representing the quantity of something and return the following descriptor:

- < 0 = “negative”
- 0 = “no”
- 1 = “a single”
- 2 = “a couple of”
- 3 = “a few”
- > 3 = “many”

getApplesPluralized() should take a single int parameter parameter representing the quantity of apples and return the following:

- 1 = “apple”
- otherwise = “apples”