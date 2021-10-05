---
layout: simple
---

# Memory & Pointers 1

CMPT-225, Fall 2021

## Computer Memory

* A sequence of locations
* Indexed by address: 0,1,2,...
* Each location stores a data *byte*
* Processor can *read* or *write* the byte at each address.
* Regions of memory are allocated to processes *as needed*, according to some scheme.

Diagram displaying "Code + Data for running part of OS" at the start of memory, "Free memory" in the middle, and "Code + Data for running user processes" and the end.

## Variables & Memory

A variable is (roughly) and names & tagged collection of bytes:

Diagram showing:
* "int x; x = 6" taking 4 bytes of memory,
* "char c; c = 'x';" taking 1 byte of memory
* "bool b; b = 'true';" taking 1 byte of memory

* So, *at run time*, each variable has an *address* in memory.
* In C, C++ we can:
  * access the address of a variable
  * access a variable or memory location by its address
  * declare variables by storing addresses (pointers).

## Addresses & Pointers - By Example

* "int i = 5;"
  * allocate space for an *int*,
  * name the space "i",
  * store 5 there
* "int \*p;"
  * allocate space for an address,
  * name it p,
  * record its type as "pointer to int"
* "p = &and;i;"
  * "&i" is the address of "i"
  * store &and;i in p
  * so, p becomes a *pointer to i*
* "cout << i;"
  * outputs the value stored in i, *5*
* "cout << p;"
  * outputs the address of i: 0xbffffbbc
* "cout << \*p;"
  * "\*" *dereferences* p. That is, \*p is the value *pointed to by p*. In this case *5*

Diagram of memory:

Address|Name|Value
...|...|...
<span id="point">254</span>|i|5
...|...|...
923|p|<a href="#point">254</a>

Second diagram of memory:

Address|Name|Value|Size
0x6fffbe|i|5|4 bytes
...|...|...|...
???|p|0x6fffbe|4 bytesa

Slide showing program code: see pointers.c

Slide showing output: see output.txt

Slide showing same program with different highlights.

Slide showing same output with different highlights.

## End
