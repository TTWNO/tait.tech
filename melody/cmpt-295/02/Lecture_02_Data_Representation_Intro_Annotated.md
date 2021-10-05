---
layout: simple
---
# CMPT 295

Unit: Textbook Chapter 2 - Data Representation

Lecture 2 - Representing data in memory

Data = information = data, instructions (code, programs)


## CAL Volunteer Note-Taker Position [1]

* If you are taking lecture notes in CMPT 295 and your hand writing is you may be interested in applying for the following volunteer note-taker position:
  * The Centre for Accessible Learning (CAL) is looking for a CMPT 295 notetaker
  * CAL volunteer lecture note-takers are provided with a $100 credit applied to their student account in acknowledgment of their assistance
* Interested?
* Please see the email CAL has sent us
* Please feel free to call 778-782-3112 or email calexams@sfu.ca the Centre if
you have any questions


## Last Lecture [2]
* COVID Protocol
* What is CMPT 295?
  * What shall we learn in CMPT 295?
  * What should we already know?
  * Which resources do we have to help us learn all this?
* Activity
* Questions

## Feedback on Lecture 1 Activity [3]
* Thank you for participating in the Lecture 1 Activity!
* Feedback now posted on our course web site
* Check it out!

## Unit Objectives [4]

Chapter 2 of our textbook

* Understand how a computer represents (encodes) data in (fixed-size) memory
* Become aware of the impact this fixed size has on …
  * Range of values represented in memory
  * Results of arithmetic operations
* Become aware of ...
  * How one data type is converted to another
  * And the impact this conversion has on the values
* Bottom Line: allow software developers to write more reliable code

## Today’s Menu [5]
* Representing data in memory – Most of this is review
  * “Under the Hood” - Von Neumann architecture
  * Bits and bytes in memory
    * How to diagram memory -> Used in this course and other references
    * How to represent series of bits -> In binary, in hexadecimal (conversion)
    * What kind of information (data) do series of bits represent -> Encoding scheme
    * Order of bytes in memory -> Endian
  * Bit manipulation – bitwise operations
    * Boolean algebra + Shifting
* Representing integral numbers in memory
  * Unsigned and signed
  * Converting, expanding and truncating
  * Arithmetic operations
* Representing real numbers in memory
6
  * IEEE floating point representation
  * Floating point in C – casting, rounding, addition, …

## “Under the hood” Von Neumann architecture [6]

Architecture of most computers

Its features:
* CPU, memory,
input and ouput, bus
* (circled in red) Data and instructions
(code/programs) both stored in memory

* C programs (.c) -- How our code and data are represented in memory
* Assembly programs (.s) -- How a compiler transforms our code into machine executable code in several steps
* Object (.o) file an executable -- How a compiler optimizes (or not) our code
* *Computer executes it -- How a microprocessor is designed and how it executes our code*
* CPU, Memory -- How memory is designed

"Computer executes it" has a diagram attached.

Two I/O devices are shown (represented by a cylindar), one on the left, one one the right.
On the left is "input peripheral", on the right is "output peripheral".

A red box surrounds the two central nodes (represented by squares), labeled "motherboard".
It contains two items inside it.
On the left is the "Central Processing Unit (CPU)", which executes instructions.
On the right is "Memory", which is "volatile" and stores data and instructions.

An arrow points from the far left input peripheral to the CPU.
A bi-directional arrow points between the CPU and memory.
A final arrow points from memory to the output peripheral.

## How to diagram memory [7]
* Seen as a linear (contiguous) array of bytes
* 1 byte (8 bits) smallest addressable unit of memory
  * Each byte has a unique address
  * Byte-addressable memory
* Computer reads a word worth of bits at a time (=> word size)
* Questions:
  1. If word size is 8, how many bytes are read at a time from memory?
  Answer: (annotated) 1 byte
  2. If a computer can read 4 bytes at a time, its
  word size is (annotated) 32 bits.

Address|M[]
size−1|
...|
0x0008|
0x0007|
0x0006|
0x0005|
0x0004|
0x0003|
0x0002|
0x0001|
0x0000|1 byte

## Closer look at memory [8]

Typically, in a diagram, we represent memory (memory content) as a series of memory “cells” (or bits) in which one of two possible values (‘0’ and ‘1’) is stored

Address|M[]
size−1|
...|
0x0008|
0x0007|
0x0006|
0x0005|
0x0004|
0x0003|
0x0002|
0x0001|
0x0000|01000000

`0x0000` is labled as "1 memory cell"

## Compressed view of memory [9]

Address|M[]
size−1|
...|
0x0008|
0x0007|7
0x0006|6
0x0005|5
0x0004|4
0x0003|3
0x0002|2
0x0001|1
0x0000|0

Address|M[]
size−8||||||||
...||||||||
0x0018||||||||
0x0010 (annotation: why is this not `0x0016)||||||||
0x0008||||||||
0x0000|0|1|2|3|4|5|6|7

Each cell, no matter which diagram is used, represents 1 byte, or 8 bits.
`0x0000` to `0x0008` is eight bytes, or 64 bits.

## Why can only two possible values be stored in a memory “cell”?

* As electronic machines, computers use two voltage levels
  * Transmitted on noisy wires -> value of two voltage levels vary over a range
  * These ranges are abstracted using “0” and “1”

A diagram shows two horizontal green bars.
Bar one has a minimum of 0.0V, and a maximum of 0.2V. "0"
Bar two has a minimum of 0.9V, and a maximum of 1.1V. "1"
A wiggly line jiggles around somewhat randomly within the confines of the lower "0" bar--moving to the right with time, it moves up, temporarily traversing the whitespace between the two bars before settling back down in its jiggly pattern within the "1" bar.
It then reverses this step, through the whitespace back to the "0" bar where it started. 

* Back to the question Why can only two possible values be stored in a
memory “cell”?
  * Because computers manipulate two-valued information

## A bit of history [11]

ENIAC: Electronic Numerical Integrator And Calculator
* U. Penn by Eckert + Mauchly (1946)
* Data: 20 × 10-digit regs + ~18,000 vacuum tubes
* To code: manually set switches and plugged cables
  * Debugging was manual
  * No method to save program for later use
  * Separated code from the data

Source: [https://en.wikipedia.org/wiki/ENIAC#/media/File:ENIAC_Penn1.jpg](https://en.wikipedia.org/wiki/ENIAC#/media/File:ENIAC_Penn1.jpg)

## Review [12] -- Back to our bits -- How to represent series of bits
* From binary numeral system
* Base: 2
* Bit values: 0 and 1
* Possible bit patterns in a byte: 000000002 to 111111112
* Drawback of manipulating binary numbers?
  * What number is this?
    * 1001100 11001001 01000101 01001000<sub>2</sub>
  * Lengthy to write -> not very compact
  * Difficult to read

Annotation: "Error prone!" encompasses "lengthy to write" and "difficult to read".

## Review -- A solution: hexadecimal numbers

Decimal|Binary|Hexidecimal
0|0000|0
1|0001|1
2|0010|2
3|0011 (circled in annotation)|3
4|0100|4
5|0101 (circled in annotation)|5
6|0110|6
7|0111|7
8|1000|8
9|1001|9
10|1010|A
11|1011|B
12|1100|C
13|1101 (circled in annotation)|D
14|1110|E
15|1111 (circled in annotation)|F

* Base: 16
* Values: 0, 1, 2, …, 9, A, B, C, D, E, F
* Possible patterns in a byte: 0016 to FF16
* Conversion binary -> hex (hex is in annotation, binary numbers grouped by 4 by green lines)
  * e.g.: 0100(0x4) 1100(0xC) 1100(0xC) 1001(0x9) 0100(0x4) 0101(0x5) 0100(0x4) 1000(0xB)
  * annotation: conversion algorithm?
* Conversion hex -> binary (binary in annotation, an arrow points off from each hex character to the binary sequence representing it)
  * e.g.: 3(0011) D(1101) 5(0101) F(1111) (in C: 0x3D5F)
  * annotation: conversion algorithm?


## What could these 32 bits represent? -- What kind of information could they encode?

01100010011010010111010001110011<sub>2</sub>

Answer:
* Integer
* string of cleartexts
* colour

## What kind of information (data) do series of bits represent?

Encoding Scheme

Bit pattern:
`01100010 01101001
01110100 01110011`<sub>2</sub>

An arrow pointing to a box labeled "encoding schemes":

* ASCII character
* Unsigned integer
* Two’s complement (signed) integer
* Floating point
* Memory Address
* Assembly language
* RGB
* MP3
* …

An arrow pointing to the following list:

* Letters and symbols
* Positive numbers
* Negative numbers
* Real numbers
* C pointers
* Machine-level instructions
* Colour
* Audio/Sound
* …

Definition: An encoding scheme is an interpretation (representation) of a series of bits

Bottom line: Which encoding scheme is used to interpret a series of bits depends on the application currently executing (the “context”) not the computer

## Endian – Order of bytes in memory
* It is straight forward to store a byte in memory
  * All we need is the byte (series of bits) and a memory address
  * For example, let’s store byte `01110011`<sub>2</sub> at address `0x0000`

Address|M[]
size−1|
...|
0x0003|
0x0002|
0x0001|
0x0000|01110011<sub>2</sub>

## Endian – Order of bytes in memory

Question: But how do we store several bytes in memory?
* For example, let’s store these 4 bytes starting at address 0x0000

`01000010 01101001 01110100 01110011`<sub>2</sub>

<aside>Trick: (L)ittle-endian, (L)SB, (L)owest address number</aside>

Way 1: Little endian
Address|M[]|Hex (filled out as annotation)
size-1||
...||
0x0003|01000010|42
0x0002|01101001|69
0x0001|01110100|74
0x0000|01110011|73

Way 2: Big endian

Address|M[]|Hex
size−1||
...||
0x0003|01110011|73
0x0002|01110100|74
0x0001|01101001|69
0x0000|01000010|42

### Compressed view of memory:

Little-endian:

Address||||||||
size-8||||||||
...||||||||
0x0008||||||||
0x0000|73|74|69|42||||

Big-endian:

Address||||||||
...||||||||
0x0008||||||||
0x0000|42|69|74|73||||


## Review Bit -- Bit Manipulation - Boolean algebra

No matter what a series of bits represent, they can be manipulated using bit-level operations:
* Boolean algebra
* Shifting

* Developed by George Boole in 19th Century
  * Algebraic representation of logic
    * Encode “True” as 1 and “False” as 0

AND -> A&B = 1 when both A=1 and B=1

&|0|1
0|0|0
1|0|1

NOT -> ~A = 1 when A=0

~|
0|1
1|0

OR -> A|B = 1 when either A=1 or B=1

\||0|1
0|0|1
1|1|1

XOR (Exclusive-Or) -> A^B = 1 when either A=1 or B=1, but not both

^|0|1
0|0|1
1|1|0


## Interesting fact about Boolean algebra and digital logic

* Claude Shannon – 1937 master’s thesis
* Made connection between Boolean algebra and digital logic
  * Boolean algebra could be applied to design and analysis of digital
systems (digital circuits)

* Example:

Diagram of an AND gate.

Two lines go into a black box.
One is 1/high, one is 0/low.
An output comes out the other side: 0/low.

## Review (annotation: HW2)

Let’s try some Boolean algebra!

* Operations applied bitwise -> to each bit
* Spot the error(s):

<pre>
  01101001
& 01010101
= 01000001
</pre>

<pre>
  01101001
| 01010101
= 01111101
</pre>

<pre>
  01101001
^ 01010101
= 00111100

(notation on 2nd last bit of equals: error!)
</pre>

<pre>
~ 01010101
= 10101010
</pre>

## Useful bit manipulations
* Using a binary mask (or bit mask) as an operand
  1. AND: Extracts particular bit(s) so we can test whether they are set. Example:
<pre>
  10110011 <- some value x
& 00000001 <- binary mask
  00000001
</pre>
  The result tells us that the least significant bit (LSb) is set.
  2. XOR: Toggle specific bits
  Example: The result tells us that the least significant bit (LSb) of x is set
<pre>
  10110011 <- some value x
^ 00011100 <- binary mask
= 10101111 We get a toggled version of the 3 original bits (of x) that
</pre>
(red square around bits 4-6): "We get a toggled version of the three original bits (of x) that corresponds to the 3 set bits of the binary mask."
* Using two operands
  1. OR: Merge all set bits of operands
    * Example:
<pre>
  10110011 <- some value x
| 00011100 <- some value y
= 10111111
</pre>
The result contains all the set bits of x and y.

## Bit Manipulation - Shift operations

* LSb: least significant bit is the rightmost bit of a series of bits (or bit vector)
* MSb: most significant bit is the leftmost bit of a series of bits (or bit vector)

* Left Shift: x << y
  * Shift bit vector (a series of bits) `x` left `y` positions.
    * Effect:
      * Throw away y most significant bits (MSb) of x on left
      * Fill x with y 0’s on right
* Right Shift: x >> y
  * Shift bit vector `x` right `y` positions
  * Effect:
    * Throw away y least significant bits (LSb) of x on right
  * Logical shift: Fill x with y 0’s on left
  * Arithmetic shift: Fill x with y copies of x‘s sign bit on left
  * Sign bit: most significant bit (MSb) of x (before shifting occurred)

## Bit Manipulation - Shift operations – Let’s try! (HW3)

* Left Shift: 10111001 << 4 = 10010000
* Left Shift: 10111001 << 2 = 11100100

* Right Shift (logical): 00111001 >> 4 = 00000011
* Right Shift (arithmatic): 10111001 >> 4 = 11111011
* Right Shift (logical/arithmatic): 10111001 >> 2 = 00101110/11101110

## Summary

* Von Neumann architecture
  * Architecture of most computers
  * Its components: CPU, memory, input and ouput, bus
  * One of its characteristics: Data and code (programs) both stored in memory
* A look at memory: defined byte-addressable memory, diagram of (compressed) memory
  * Word size (w): size of a series of bits (or bit vector) we manipulate, also size of machine words (see Section 2.1.2)
* A look at bits in memory
  * Why binary numeral system (0 and 1 -> two values) is used to represent information in memory
  * Algorithm for converting binary to hexadecimal (hex)
    1. Partition bit vector into groups of 4 bits, starting from right, i.e., least significant byte (LSB)
      * If most significant “byte” (MSB) does not have 8 bits, pad it: add 0’s to its left
    2. Translate each group of 4 bits into its hex value
  * What do bits represent? Encoding scheme gives meaning to bits
  * Order of bytes in memory: little endian versus big endian
* Bit manipulation – regardless of what bit vectors represent
  * Boolean algebra: bitwise operations => AND (&), OR (|), XOR (^), NOT (~)
  * Shift operations: left shift, right logical shift and right arithmetic shift
    * Logical shift: Fill x with y 0’s on left
    * Arithmetic shift: Fill x with y copies of x‘s sign bit on left
    * Sign bit: Most significant bit (MSb) before shifting occurred

NOTE: C logical operators and C bitwise (bit-level) operators behave differently! Watch out for && versus &, || versus |, …

## Next Lecture
* Representing data in memory – Most of this is review
  * “Under the Hood” - Von Neumann architecture
  * Bits and bytes in memory
    * How to diagram memory -> Used in this course and other references
    * How to represent series of bits -> In binary, in hexadecimal (conversion)
    * What kind of information (data) do series of bits represent -> Encoding scheme
    * Order of bytes in memory -> Endian
  * Bit manipulation – bitwise operations
    * Boolean algebra + Shifting
* Representing integral numbers in memory
  * Unsigned and signed
  * Converting, expanding and truncating
  * Arithmetic operations
* Representing real numbers in memory
  * IEEE floating point representation
  * Floating point in C – casting, rounding, addition, …
