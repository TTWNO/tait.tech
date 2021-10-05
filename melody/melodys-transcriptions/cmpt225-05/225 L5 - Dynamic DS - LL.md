---
layout: simple
math: true
---

# Dynamic Data Structures - Linked Lists

Transcriber's note:
Each row in the Value\|Pointer/Link tables represents a node.
Despite the fact that the link/pointer takes you to the "value" column, in reality it is taking you to the node "row", it's not just a pointer to the value.

## Dynamic Data Structures

* Basic types (e.g. int, char, bool, ...), and arrays of these store a *fixed* amount of data.
* We want implementations of ADTs like stacks + queues to *grow & shrink* (their memory use) *as needed*.
  * e.g. like Vector, Array-something? (can't read), String classes

Basic Idea:

Store data in a collection of (simple) objects.
add/delete these as needed; link them all together to make the main object.

## Linked Lists

- A sequence of simple objects (nodes): each storing one datum (plus a link...) linked together in a chain
- E.g., to store the list &lt;3, 5, 7&gt;:

Datum|Link
---|---
<span id="z1">3</span>|[link](#z2)
<span id="z2">5</span>|[link](#z3)
<span id="z3">7</span>|link to nowhere

- These objects have no names, (in contrast to declared values)
  - we access them by following links
    - in Java, references (implemented as pointers)
    - in C++, pointers

Need one named place to start like so:

A normal variable of type "pointer to a node": [First](#y1)

Data|Link
---|---
<span id="y1">3</span>|[pointer](#y2)
<span id="y2">5</span>|[pointer](#y3)
<span id="y3">7</span>|null pointer

## Implementing a Stack with a Linked List (By example)

Code to run, followed by the current stack.

### <code>stack s;</code>

<label for="tof">top or front</label>
<span id="tof">node</span>

### <code>s.push(3)</code>

<a href="#x1">front</a>

Data|Pointer
---|---
<span id="x1">3</span>|null pointer

### etc...

...

### <code>s.push(5)</code>

[front](#w1)

Data|Pointer
---|---
<span id="w1">5</span>|[pointer](#w2)
<span id="w2">8</span>|[pointer](#w3)
<span id="w3">...</span>|... ([pointer](#w4))
<span id="w4">3</span>|null pointer

### <code>s.push(7)</code>

[front](#v1)

Value|Pointer
<span id="v1">7</span>|[pointer](#v2)
<span id="v2">5</span>|[pointer](#v3)
<span id="v3">8</span>|[pointer](#v4)
<span id="v4">...</span>|...

To perform the push(7):

1. Make a new node to store the 7
2. modify links to insert it correctly

Original:

[front](#u1)

Data|Pointer
---|---
<span id="u1">5</span>|[pointer](#u2)
<span id="u2">8</span>|...

After operation:

[front](#t1) now points at node with value 7; node with value 7's pointer now points to the [old front](#u1)

Value|Pointer
---|---
<span id="t1">7</span>|[pointer](#t2)
<span id="t2">5</span>|[pointer](#t3)
<span id="t3">8</span>|...

### <code>s.pop()</code>

[front](#s1)

Value|Pointer
---|---
<span id="s1">5</span>|[pointer](#s2)
<span id="s2">8</span>|...

How to perform the pop():
1. Change the "top" link
2. Return the old top node

Linked list after running operation (note that two links go to the same node):

[top](#r0) now points to second row

Value|Pointer
---|---
<span id="r1">7</span> (return this value)|[pointer](#r0)
<span id="r0">5</span>|[pointer](#r2)
<span id="r2">8</span>|...

* Caveat 1: don't lose the old top value
* Caveat 2: don't ignore the old top node (it still consumes space)

### "Improved" pop():

1. Store the old top value in "temp"
2. make *top* link to the new top node
3. *free* the space for the old top node
3. return temp

## The List Class (A doubly-linked list implementation of a list)

See <a href="./list.cpp">list.cpp</a>

&lt;...5,6,7,...&gt; in a double linked list:

Prev|Value|Next
---|---|---
...|<span id="d0">5</span>|[next](#d1)
[prev](#d0)|<span id="d1">6</span>|[next](#d2)
[prev](#d1)|<span id="d2">7</span>|...

## End
