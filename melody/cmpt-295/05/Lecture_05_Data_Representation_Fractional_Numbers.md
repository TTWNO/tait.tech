---
layout: simple
math: true
---

# CMPT 295: Unit - Data Representation

## Lecture 5

* Representing fractional numbers in memory
* IEEE floating point representation

## Last Lecture
* Demo of size and sign conversion in C: code and results posted!
* Addition:
  * Unsigned/signed:
    * Behave the same way at the bit level
    * Interpretation of resulting bit vector (sum) may differ
  * Unsigned addition -> true sum may overflow its w bits in memory (annotation with diagram of unisnged overflows, see lecture 04 to see full description of diagram)
    * If so, then actual sum = $$(x + y) \mod 2^{w}$$ (equivalent to subtracting $$2^{w}$$ from true sum $$(x + y)$$)
  * Signed addition -> true sum may overflow its w bits in memory (annotation attached displaying diagram of negative and positive overflows, see Lecture 04 for detailed description of diagram)
    * If so then …
      * actual sum = $$\text{U2T}_{w}[(x + y) \mod 2^{w}]$$
      * true sum may be too +ve -> positive overflow OR too –ve -> negative overflow
* Subtraction
  * Becomes an addition where the 2nd operand is transformed into its additive inverse in two’s complement
* Multiplication:
  * Unsigned: actual product = $$(x \times y) \mod 2^{w}$$
  * Signed: actual product = $$\text{U2T}_{w}[(x \times y) \mod 2^{w}]$$ <!--_ -->
  * Can be replaced by additions and shifts

Conclusion: the same bit pattern is interpreted differently.

## Questions

* Why are we learning this?
* What can we do in our program when we suspect that overflow may occur?

## Demo – Looking at integer additions in C
* What does the demo illustrate?
  * Unsigned addition
    * Without overflow
    * With overflow
    * Can overflow be predicted?
  * Signed addition
    * Without overflow
    * With positive overflow and negative overflow
    * Can overflow be predicted?
* This demo (code and results) posted on our course web site
4

## Today’s Menu
* (greyed out) Representing data in memory – Most of this is review
  * (greyed out) “Under the Hood” - Von Neumann architecture
  * (greyed out) Bits and bytes in memory
    * (greyed out) How to diagram memory -> Used in this course and other references
    * (greyed out) How to represent series of bits -> In binary, in hexadecimal (conversion)
    * (greyed out) What kind of information (data) do series of bits represent -> Encoding scheme
    * (greyed out) Order of bytes in memory -> Endian
  * (greyed out) Bit manipulation – bitwise operations
    * (greyed out) Boolean algebra + Shifting
* (greyed out) Representing integral numbers in memory
  * (greyed out) Unsigned and signed
  * (greyed out) Converting, expanding and truncating
  * (greyed out) Arithmetic operations
*  (highlighted) Representing real numbers in memory
  * (highlighted) IEEE floating point representation
  * (greyed out) Floating point in C – casting, rounding, addition, …

We’ll illustrate what we covered today by having a demo!

## Converting a fractional decimal number into a binary number (bit vector) [R2B(X)]

* How would 346.625 ($$346 \frac{5}{8}$$) be represented as a binary number?
* Expanding the subtraction method we have already seen:

Starting number: 346.625

Whole:

Value|Attempted Addition (subtraction) value|Result|Binary Implication|Note
346|-256|90|$$1 \times 2^{8}$$|MSb
90|-128|&#9785;|$$0 \times 2^{7}$$|
90|-64|26|$$1 \times 2^{6}$$|
26|-32|&#9785;|$$0 \times 2^{5}$$|
26|-16|10|$$1 \times 2^{4}$$|
10|-8|2|$$1 \times 2^{3}$$|
2|-4|&#9785;|$$0 \times 2^{2}$$|
2|-2|0|$$1 \times 2^{1}$$|
0|-1|&#9785;|$$0 \times 2^{1}$$|LSb

Fractional:

Value|Attempted addition (subtraction) value|result|binary implication|notes
.625|-0.5|.125|$$1 \times 2^{-1}$$|MSb
.125|-0.25|&#9785;|$$0 \times 2^{-2}$$|
.125|-0.125|0|$$1 \times 2^{-3}$$|LSb


Binary representation is: $$\text{101011010.101}_{2}$$

First, last binary digit *before* the period are MSb, LSb respectively.
First, last binary digit *after* the period are also MSb, LSb respectively.

Negative Powers of 2:

* $$2^{-1}$$ = 0.5
* $$2^{−2}$$ = 0.25
* $$2^{−3}$$ = 0.125
* $$2^{−4}$$ = 0.0625
* $$2^{−5}$$ = 0.03125

## Converting a binary number into a fractional decimal number [R2B(X)]

* How would $$\text{1011.101}_{2}$$ be represented as a fractional decimal number?

## Review: Fractional decimal numbers

Positional notation:

Notation|Value
$$d_{i}$$|$$\text{10}^{i}$$
$$d_{i-1}$$|$$\text{10}^{i-1}$$
...|...
$$d_{2}$$|100
$$d_{1}$$|10
$$d_{0}$$|1
$$d_{-1}$$|$$\frac{1}{10}$$
$$d_{-2}$$|$$\frac{1}{100}$$
$$d_{-3}$$|$$\frac{1}{1000}$$
...|...
$$d_{-j}$$|$$\text{10}^{-j}$$

Example: 2.345

Digit in number|Note
2|$$\text{10}^{0}$$
.|
3|$$\text{10}^{-1}$$
4|$$\text{10}^{-2}$$
5|$$\text{10}^{-3}$$

{% katex display %}
2.345 = 2 \times \text{10}^{0} + 3 \times \text{10}^{−1} + 4 \times \text{10}^{−2} + 5 \times \text{10}^{−3}
{% endkatex %}

## Converting a binary number into a fractional decimal number [B2R(X)]

Positional notation: can this be a possible encoding scheme?

$$b_{i}$$|$$2^{i}$$
$$b_{i-1}$$|$$2^{i-1}$$
...|...
$$b_{2}$$|4
$$b_{1}$$|2
$$b_{0}$$|1
$$b_{-1}$$|$$\frac{1}{2}$$
$$b_{-2}$$|$$\frac{1}{4}$$
$$b_{-3}$$|$$\frac{1}{8}$$
...|...
$$b_{-j}$$|$$2^{-j}$$

## Converting a binary number into a fractional decimal number [B2R(X)]

* How would $$\text{1011.101}_{2}$$ be represented as a fractional decimal number?
* Using the positional encoding scheme:

{% katex display %}
\begin{aligned}
&\text{1011.101}_{2} = \\
&(\text{1011}_{2} = 1 \times 2^{3} + 1 \times 2^{1} + 1 \times 2^{0} = \text{11}_{10}) +\\
&(\text{.101}_{2} = 1 \times 2^{-1} + 1 \times 2^{-3} = 0.5 + 0.125 = \text{0.625}_{10})
\end{aligned}
{% endkatex %}

Result: \_\_\_\_

Negative Powers of 2

$$2^{−1}$$|0.5
$$2^{−2}$$|0.25
$$2^{−3}$$|0.125
$$2^{−4}$$|0.0625
$$2^{−5}$$|0.03125
$$2^{−6}$$|0.015625
$$2^{−7}$$|0.0078125
$$2^{−8}$$|0.00390625

## Positional notation as encoding scheme?

* One way to answer this question is to investigate whether the encoding scheme allows for arithmetic operations
* Let’s see: Using the positional notation as an encoding scheme produces fractional binary numbers that can be
  * added
  * multiplied by 2 by shifting left
  * divided by 2 by shifting right (unsigned)

Example:

Operand|Binary|Fraction|Makeup
|$$\text{1011.101}_{2}$$|$$11\frac{5}{8}$$|$$8 + 2 + 1 + \frac{1}{2} + \frac{1}{8}$$
Divide by 2|$$\text{101.1101}_{2}$$|$$5\frac{13}{16}$$|$$4 + 1 + \frac{1}{2} + \frac{1}{4} + \frac{1}{16}$$
Divide by 2|$$\text{10.11101}_{2}$$|$$2\frac{29}{32}$$|$$2 + \frac{1}{2} + \frac{1}{4} + \frac{1}{8} + \frac{1}{32}$$
Multiply by 4|$$\text{1011.101}_{2}$$|$$11\frac{5}{8}$$|$$8 + 2 + 1 + \frac{1}{2} + \frac{1}{8}$$
Multiply by 2|$$\text{10111.01}_{2}$$|$$23\frac{1}{4}$$|$$16 + 4 + 2 + 1 + \frac{1}{4}$$

So far so good!

## Positional notation as encoding scheme?

* Advantage (so far):
  * Straightforward arithmetic: can shift to multiply and divide, convert
* Disadvantage:
  * Cannot encode all fractional numbers:
    * Can only represent numbers of the form $$x \div 2^{k}$$ (what about $$\frac{1}{5}$$ or -34.8)
  * Only one setting of binary point within the w bits -> this limits the range of possible values
    * What is this range?
      * Example: w = 32 bits and binary point located at 16th bit:
        * Whole number range: [0 ... 65535]
        * Fraction range: [0 ... 1 - ε]
        * $$1 - \text{bits} = \epsilon$$
        * Range: [0.0 ... 65535.99998]

Not so good anymore!

## Representing fractional numbers in memory

* Here is another possible encoding scheme: IEEE floating point representation (IEEE Standard 754)
* Overview:
  * Binary Numerical Form: $$V = \text{(–1)}^{s} M 2^{E}$$
    * s – Sign bit -> determines whether number is negative or positive
    * M – Significand (or Mantissa) -> fractional part of number
    * E – Exponent
* Form of bit pattern (number of items not important, focus on scale): `[s|eee|fffffffffffff]`
  * Most significant bit (MSb) s (similar to sign-magnitude encoding)
  * exp (e) field encodes E (but is not equal to E)
  * frac (f) field encodes M (but is not equal to M)

## IEEE Floating Point Representation -- Precision options

* Single precision: 32 bits ≈ 7 decimal digits, range:10±38 (in C: float)
  * In C: diagram of memory showing:
    * 1 sign bit
    * 8 exp bits
    * 23 frac bits
* Double precision: 64 bits ≈ 16 decimal digits, range:10±308 (in C: double)
  * In C: diagram of memory showing:
    * 1 sign bit
    * 11 exp bits
    * 52 frac bits

## IEEE Floating Point Representation -- Three “kinds” of values

Numerical Form: $$V = \text{(–1)}^{s} M 2^{E}$$

* 1 sign bit
* `k` exp bits
  * denormalized: 00...00 (all 0's)
  * normalized: exp != 0 and exp != 11..11
  * special cases: 11...11 (all 1's)
* `n` frac bits  

* E = exp - bias, bias = $$2^{k-1} -1$$
* M = 1 + frac

Why is E biased? Using single precision as an example:

* exp range: [00000001 .. 11111110] and bias = $$2^{8-1} – 1$$
* E range: [-126 .. 127]
* If no bias: E range: [1 .. 254] => $$2^{1}$$ to $$2^{254}$$

Why adding 1 to frac? Because number V is first normalized before it is converted.

## Review: Scientific Notation and normalization

* From Wikipedia:
  * Scientific notation is a way of expressing numbers that are too large or too small (usually would result a long string of digits) to be conveniently written in decimal form.
  * In scientific notation, nonzero numbers are written in the form
  * In normalized notation, the exponent n is chosen so that the absolute value of the significand m is at least 1 but less than 10.

* Examples:
  * A proton's mass is 0.0000000000000000000000000016726 kg -> $$1.6726 \times \text{10}^{−27}$$kg
  * Speed of light is 299,792,458 m/s -> $$2.99792,458 \times \text{10}^{8}$$ m/s

Syntax:

Notation|Name
+/−|sign
$$d_{0}$$, $$d_{-1}$$, $$d_{-2}$$, $$d_{-3}$$ ... $$d_{-n}$$|significand
&times;|times
b|base
$$^{exp}$$|exponent

Let’s try: $$\text{101011010.101}_{2}$$ = \_\_\_\_

## Summary

* Representing integral numbers (signed/unsigned) in memory:
  * Encode schemes allow for small range of values exactly
* Representing fractional numbers in memory:
  1. Positional notation (advantages and disadvantages)
  2. IEEE floating point representation: wider range, mostly approximately
* Overview of IEEE Floating Point representation
* $$V = \text{(-1)}^{s} \times M \times 2^{E}$$
* Precision options
* 3 kinds: normalized, denormalized and special values

## Today’s Menu
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
18
  * IEEE floating point representation
  * Floating point in C – casting, rounding, addition, …
