# 0.1 - Bit flags and bit manipulation via std::bitset

## Notes

The smallest addressable unit of memory is a byte. Since all objects need to have unique memory addresses, this means objects must be at least one byte in size

For boolean variables, this is wasteful as they only need 1 bit
- Majority of cases, this is fine as we're usually not so hard-up for memory to care
- It could be useful to "pack" 8 individual boolean values into a single byte for starge

**Bit Manipulation**: Modifying individual bits within an object

### Bit flags

Instead of viewing objects as holding a single value, we treat each bit in the object as an independent Boolean value

**Bit Flags**: When individual bits of an object are used as boolean values
- A bit holding `0` is said to be `false` or `off`
- A bit holding `1` is said to be `true` or `on`

**Flag**: A value that signals when some condition exists in a program

To define a set of bit flags we'll typically use an unsigned integer of the appropriate size or `std::bitset`

```cpp
#include <bitset> // for std::bitset

std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
```

`std::bitset` is the easier way to do bit manipulation

### Bit numbering and bit position

**Bit Position**: Given a sequence of bits, we typically number the bits from right to left, starting with 0

```shell
76543210  Bit position
00000101  Bit sequence
```

### Manipulating bits via `std::bitset`

`std::bitset` provides 4 key member functions that are useful for doing bit manipulation
- `test()`: Query whether a bit is 0 or 1
- `set()`: Turn a bit on (Set to 1)
- `reset()`: Turn a bit off (Set to 0)
- `flip()`: Flip a bit vaue from 0 to 1 or vice versa

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3);   // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4);  // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << bits<< '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    return 0;
}
```

```shell
All the bits: 00001101
Bit 3 has value: 1
Bit 4 has value: 0
```

### What if we want to get or set multiple bits at once

`std::bitset` doesn't make this easy.
- Need to use a more traditional method

### The size of std::bitset

`std::bitset` is optimized for speed, not memory saving
- The size of a `std::bitset` is typically the number of bytes needed to hold the bits, rounded *up* to the nearest `sizeof(size_t)`, which is a 4 bytes on 32-bit machine and 8-bytes on 64-bit machine
- `std::bitset<8>` will typically use eiterh 4 or 8 bytes of memory
  - Even though it technically only needs 1 byte
  - Only useful for convenience, not memory

### Querying `std::bitset`

Other member functions
- `size()`: Return the number of bits in the bitset
- `count()`: Return the number of bits in the bitset that are set to `true`
- `all()`: Returns a boolean indicating whether all bits are set to `true`
- `any()`: Returns a boolean indicateing whether any bits are set to `true`
- `none()`: Returns a boolean indicating whether no bits are set to `true`

# O.2 - Bitwise Operators

## Questions

1. Answer the following

- What does 0110 >> 2 evaluated to in binary?
  - 0001
- What does the following evaluate to in binary: 0011 | 0101 ?
  - 0111
- What does the folowing evaluated to in binary: 0011 & 0101 ?
  - 0001
- What does the following evaluate to in binary (0011 | 0101) & 1001 ?
  - 0111 & 1001 = 0001

2. A bitwise rotation is like a bitwise shift, except that any bits shifted off one end are added back to the other end. For example 0b1001 << 1 would be 0b0010, but a left rotate by 1 would result in 0b0011 instead. Implement a function that does a left rotate on a std::bitset<4>. For this one, it’s okay to use test() and set().

```cpp
#include <bitset>
#include <iostream>

// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
// Your code here
}

int main()
{
	std::bitset<4> bits1{ 0b0001 };
	std::cout << rotl(bits1) << '\n';

	std::bitset<4> bits2{ 0b1001 };
	std::cout << rotl(bits2) << '\n';

	return 0;
}
```

```cpp
#include <bitset>
#include <iostream>

// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{

    return (bits << 1) | (bits >> 3);

}

int main()
{
	std::bitset<4> bits1{ 0b0001 };
	std::cout << rotl(bits1) << '\n';

	std::bitset<4> bits2{ 0b1001 };
	std::cout << rotl(bits2) << '\n';

	return 0;
}
```

## Notes

### Bitwise Operators

**Bitwise Operators**: C++ Bit manipulation operators

- Left shift - << - x << n - bits from `x` are shifted left by `n` positions, new bits are 0
- Right shift - >> - x >> n - bits from `x` are shifted right by `n` positions, new bits are 0
- bitwise NOT - ~ - ~x - each bit from `x` is flipped
- bitwise AND - & - x & y - each bit is set when both corresponding bits in `x` and `y` are 1
- bitwise OR - | - x | y - each bit is set when either corresponding bit in `x` and `y` is 1
- bitwise XOR - ^ - x ^ y - each bit is set when the corresponding bits in `x` and `y` are different

The bitwise operators are defined for integral types and `std::bitset`.

Avoid using the bitwise operators with signed integral operands
- Easily avoided by using unsigned operand or `std::bitset`

### Bitwise left shift (<<) and bitwise right shift (>>) operators

**Bitwise left shift**: Shifts bits to the left
- Provides the initial bit sequence
- The right operand is an integer number that specifies the number of bit positions to move

`0110` << 1 is `1100`\
`0110` << 2 is `1000`

Notice we shifted a `1` bit off the end of the number
- Bits that are shifted off are lost forever

**Bitwise right shift**: Shifts bits to the right

`0110` >> 1 is `0011`\
`0110` >> 2 is `0001`

### Aren't operator << and  >> used for input and output?

Yes, they are.

Programs today don't make much use of the bitwise shift operators. They are more often used for `std::cout`

The `<<` operator knows what to do by looking at the type of the operands.
- If the left operand is an integral, it uses the bit shift.
- If its an output stream, it knows it should output instead

Using bit shift and output on the same line requires parentheses

### Bitwise NOT

**Bitwise NOT**: Flips each bit from `0` to `1` and vice versa

`~0011` is `1100`
`~1010` is `0101`
`~0000 1010` is `1111 0101`

### Bitwise OR

**Bitwise OR**: Sets each bit if one of each bit is true

`0011 | 1010` is `1011`
`0000 | 1111` is `1111`
`0010 | 1000 | 0001` is `1011`

### Bitwise AND

**Bitwise AND**: For each pair of bits in the operand, Bitwise AND set the result to 1 if both paired bits are 1

`0011 | 1010` is `0010`
`0000 | 1111` is `0000`
`0001 | 0011 | 0111` is `0001`

### Bitwise XOR

**Bitwise XOR**: Exclusive OR

`0110` ^ `0011` is `0101`
`0011` ^ `1100` is `1111`
`0101` ^ `1110` is `1011`

### Bitwise assignment operators

To assign the outcome of each bitwise operator, you can add `=` to the end of each operator

- x <<= n
- x >>= n
- x &= y
- x |= y
- x ^= y

Avoid bit shifting on integral types smaller than `int`

# O.3 - Bit manipulation with bitwise operators and bit masks

## Questions

1. Given the following program:

```cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t option_viewed{ 0x01 }; // 0000 0001
    [[maybe_unused]] constexpr std::uint8_t option_edited{ 0x02 }; // 0000 0010
    [[maybe_unused]] constexpr std::uint8_t option_favorited{ 0x04 }; // 0000 0100
    [[maybe_unused]] constexpr std::uint8_t option_shared{ 0x08 }; // 0000 1000
    [[maybe_unused]] constexpr std::uint8_t option_deleted{ 0x10 }; // 0001 0000

    std::uint8_t myArticleFlags{ option_favorited };

    // Place all lines of code for the following quiz here

    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    return 0;
}
```

Add a line of code to set the article as viewed.

```shell
0000'0101
```

```cpp
myArticleFlags |= option_viewed;
```


Add a line of code to check if the article was deleted.

```cpp
std::cout << static_cast<bool>(myArticleFlags & option_deleted) << "\n";
```

Add a line of code to clear the article as a favorite.

```cpp
myArticleFlags &= static_cast<std::uint8_t>(-option_favorited);
```

```shell
00000001
```

Extra credit: why are the following two lines identical?

```cpp
myflags &= ~(option4 | option5); // turn options 4 and 5 off
myflags &= ~option4 & ~option5; // turn options 4 and 5 off
```

`~(option4 | option5)` is `~(0001 1000)` is `(1110 0111)
`~option4 & ~option5` is `(1111 0111) & (1110 1111)` is `1110 0111`

You can also apply demorgans law, distributing the not and flipping OR to AND

## Notes

### Bit Masks

We need some way to identify the specific bits we want to manipulate

**Bit mask**: A predefined set of bits that is used to select which specific bits will be modified by subsequent operations
- Blocks the bitwise operators from touching bits we don't want modified, and allows access to the ones we do want modified

### Defining bit masks in C++14

Simplest set of bit masks is to define one bit mask for each bit position
- Although bit masks can be literals, they're often defined as symbolic constants so they can be given a meaningful name and easily reused

```cpp
#include <cstdint>

constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7
```

### Defining bit masks in C++11 or eariler

C++ doesn't support binary literals, 2 good approaches

Hexadecimal literals
```cpp
constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
constexpr std::uint8_t mask1{ 0x02 }; // hex for 0000 0010
constexpr std::uint8_t mask2{ 0x04 }; // hex for 0000 0100
constexpr std::uint8_t mask3{ 0x08 }; // hex for 0000 1000
constexpr std::uint8_t mask4{ 0x10 }; // hex for 0001 0000
constexpr std::uint8_t mask5{ 0x20 }; // hex for 0010 0000
constexpr std::uint8_t mask6{ 0x40 }; // hex for 0100 0000
constexpr std::uint8_t mask7{ 0x80 }; // hex for 1000 0000
```

Easier method is with left-shift operator

```cpp
constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000
```

### Testing a bit

To determine if a bit is on or off, we use bitwise AND (&)

```cpp
#include <cstdint>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

	std::cout << "bit 0 is " << (static_cast<bool>(flags & mask0) ? "on\n" : "off\n");
	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	return 0;
}
```

```shell
bit 0 is on
bit 1 is off
```


### Setting a bit

To turn on a bit, we use bitwise OR equals (|=) with the bit mask.

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    flags |= mask1; // turn on bit 1

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    return 0;
}
```

```shell
bit 1 is off
bit 1 is on
```

You can turn on multiple bits at the same time using Bitwise OR

```cpp
flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time
```

### Resetting a bit

To reset a bit to 0, we use Bitwise AND and Bitwise NOT together

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    flags &= ~mask2; // turn off bit 2

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```

```shell
bit 2 is on
bit 2 is off
```

You can turn off multiple bits at the same time with bitwise OR

```cpp
flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time
```

Some compilers will complain about a sign conversion with:

```cpp
flags &= -mask2;
```

Because the type of `mask2` is smaller than `int`, `operator-` causes operand `mask2` to undergo integral promotion to type `int`. The compiler complains that we're trying to use `operator&=` when the left is unsigned, and the right is signed

Instead you can do:

```cpp
flags &= static_cast<std::uint8_t>(~mask2);
```

### Flipping a bit

To flip a bit, use Bitwise XOR

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```

You can flip multiple bits simultaneously

```cpp
flags ^= (mask4 | mask5);
```

### Bit masks and std::bitset

std::bitset supports the full set of bitwise operators

### Making bit masks meaningful

A best practice is to give your bit masks useful names as a way to document the meaning of your bit flags

```cpp
#include <cstdint>
#include <iostream>

int main()
{
        // Define a bunch of physical/emotional states
	[[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

	std::uint8_t me{}; // all flags/options turned off to start
	me |= (isHappy | isLaughing); // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing

	// Query a few states
	// (we'll use static_cast<bool> to interpret the results as a boolean value)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n';
	std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

	return 0;
}
```

### When are bit flags most useful

Bit flags make the most sense when you have many identical flag variables. 

You can also use bits to simplify function parameters taking multiple booleans

```cpp
void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8, bool option9, bool option10, bool option11, bool option12, bool option13, bool option14, bool option15, bool option16, bool option17, bool option18, bool option19, bool option20, bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27, bool option28, bool option29, bool option30, bool option31, bool option32);
```

```cpp
void someFunction(std::bitset<32> options);
```

# O.4 - Converting integers between binary and decimal representation

## Questions

1. Convert 0100 1101 to decimal
  - 64 + 8 + 4 + 1 = `77`
2. Convert 93 to an 8-bit unsigned binary number
  - 93 - 64 = 29, 29 - 16 = 13, 13 - 8 = 5, 5 - 4 = 1, 1 - 1 = 0
  - `0101 1101`
3. Convert -93 to an 8-bit signed binary number (using two’s complement).
  - 0101 1101 -> 1010 0010
  - 1010 0010 + 0000 0001 = `1010 0011`
4. Convert 1010 0010 to an unsigned decimal number
  - 128 + 32 + 2 = 162
5. Convert 1010 0010 to a signed decimal number
  - 1010 0010 => 0101 1101
  - 0101 1101 + 0000 0001 = 0101 1110
  - 0101 1110 = 64 + 16 + 8 + 4 + 2 = 94
  - 94 => -94
6. Write a program that asks the user to input a number between 0 and 255. Print this number as an 8-bit binary number (of the form #### ####). Don’t use any bitwise operators. Don’t use std::bitset.



## Notes

Consider a decimal integer (5623) We know what each value place is

Binary works the same way with only 2 digits


### Conveting Binary to decimal

Binary 0101 1110 = (0 * 128) + (1 * 64) + (0 * 32) + (1 * 16) + (1 * 8) + (1 * 4) + (1 * 2) + (0 * 1) = 94

### Converting Decimal to Binary

Given a number 148, we start with the largest power of 2 possible?

148 >= 128? Yes so 128 bit is 1, 148 - 128 = 20\
20 >= 64? No so 64 bit is 0\
20 >= 32? No so 32 bit is 0\
20 >= 16? Yes so 16 bit is 1, 20 - 16 = 4\
4 >= 8? No so 8 bit is 0\
4 >= 4? Yes so 4 bit is 1, 4 - 4 = 0\
There is nothing left so 2 bit and 1 bit are 0\

The bit is 1001 0100

### Adding in Binary

Consider 2 small binary numbers
- 0110 (6) + 0111 (7)

```shell
0 1 1 0
0 1 1 1
-------
      1

  1
0 1 1 0
0 1 1 1
-------
    0 1

1 1
0 1 1 0
0 1 1 1
-------
  1 0 1

1 1
0 1 1 0
0 1 1 1
-------
1 1 0 1 = 8 + 4 + 1 = 13
```

### Signed numbers and two's complement

We've dealt solely with unsigned integers

Signed integers are typically stored using a method known as two's complement\
**Two's Complement**: The leftmost bit is used as the sign bit.
- A 0 sign bit means the number is positive
- A 1 sign bit means the number is negative

### Converting decimal to binary

how to represent -5:

5: 0000 0101
- Invert the bits: 1111 1010
- Then add 1: 1111 1011

Convert -76 to binary: 0100 1100
- Invert the bits: 1011 0011
- Then add 1: 1011 0100

### Converting binary (two's complement) to decimal

If the sign is 0, just convert for unsigned numbers

If the sign is 1, then we invert the bits, add 1, then convert to decimal. Then make it negative

1001 1110
- Invert: 0110 0001
- Add 1: 0110 0010
- Convert to number: 64 + 32 + 2 = 98
- Add negative: -98

### Why types matter

A value of 1011 0100 would be 180 if it was unsigned, but -76 if it was signed

The type of the variable determines both how a variable's value is encoded and decoded

### What about converting floating point to/from binary?

A lot more complicated
