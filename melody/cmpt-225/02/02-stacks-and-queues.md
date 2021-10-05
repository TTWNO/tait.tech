---
layout: simple
---

# Stacks & Queues - 1

CMPT 225, Fall 2021, Lecture 2

## Stack

* ADT that stores a collection of objects/values
* Insertions and removals follow last-in-first-out pattern
* Fundamental Operations:
  * push: inserts an element on the "top"
  * pop: removes + returns the top element

e.g.

Stack index|Value 

push a

Stack index|Value 
0|a

push b

Stack index|Value 
0|b
1|a

push c

Stack index|Value 
0|c
1|b
2|a

pop

Stack index|Value 
0|b
1|a

* conventient optional operations
  * size: return # of elements on stack // encapsulation
  * empty: check for emptiness // better than "size=0?"
  * top: return top element, but don't remove it // better than x = pop(); push(x) then use x

## Algorithm Applications

* parasing/evaluation/transformation of expressions
* speech recognition coding/decoding
* shared network access control
* programming languages & execution
  * Postscript, Forth, the call stack
* things we do daily with computers

## Parenthasies Checking

Parenthasies: `(()(((()())()()(()))`

A diagram showing:
For every left parenthasies, add one to a counter.
For every right parthenthasies, remove one from the counter.
If the counter is not zero by the end of the sequence, there are too many on one side of the parenthasies.

Can be done by counting unmached left parenthasies:

Successful example:

Character|Counter
|0
(|1
(|2
)|1
(|2
(|3
)|2
)|1
)|0
Yay!|0

Failed example:

Character|Country
|0
(|1
(|2
)|1
(|2
)|1
|Oh no it's not zero!

Another fail:

Character|Counter
|0
(|1
)|0
(|1
)|0
)|-1
|Negative 1 this time!

Do this one yourself:

Character|Counter
(|
)|
)|
(|

But consider multiple grouping symbols: `(\{\{)`, `(\{)\{`, `(\{[( ... ]`.
Counting is not enough.

## Parenthasies Checking

Diagram showing failure on the last character of this sequence: `(()((()()))()(())))`

Can be done by counting unmatched left parenthasies:

Character|Counter
(|1
(|2
)|1
(|2
(|3
)|2
)|1
)|0

Example 2:

Character|Counter
(|1
(|2
)|1
(|2
)|1

Example 3:

Character|Counter
(|1
)|0
(|1
)|0
)|-1

Example 4:

Character|Counter
(|1
)|0
)|-1
(|0

But consider multiple grouping symbols:

* sequence `(\{\})` will and should work
* sequence `(\{)\}` will work and should not
* sequence `(\{[( ...` ???

Counting is not enough.

## Stack-based Algorithm for Checking Grouping Symbols

Pseudo-code:

```
I is an input stream of symbols.
S is a new empty stack.

while there are signals to read from I {
  c is next symbol from I
  if c is a left grouping signal {
    push c on S
  } else if c is a right grouping signal{
    if s in empty { report error and stop }
    d is pop S
    if c and d do not match { report error and stop }
  endif // if c is not a grouping symbol, ignore it
end while

if S is not empty { report error and exit }
report ok
```

Diagram showing how each set of parenthasies are matched, innermost first torwards the outermost.

## Stack: Partially-Filled Array Implementation

Variables:

* A - an array of stack elements
* capacity - size of array
* top - index in array of top stack element
  * -1 if stack is empty


A starts out as:

Index|0|1|2|...|capacity-1
Value|a|b|c|...|

* Capacity = &lt;size of A&gt;
* top = 2

push e

A now equals

Index|0|1|2|3|4|...|capacity-1
Value|a|b|c|d|e|...|

* capacity = &lt;size of A&gt;
* top = 3

## The Queue ADT

A container that stores a collection of items with insertion and removal in "first-in-first-out" order.

Stack: a digram showing circled being placed on top of eachother, pushing circles into the tube, then popping them out from the same size (the top). Like a pringles can of elements.

Queue: a diagram showing circles being unqueued in on the left and dequeued on the right. Like waiting in line for food.

Basic operations:
* enqueue: add an item to the back of a list
* dequeue: remove & return the item at the front of the list

## Example: Palindrome Checking

Sequence `aba` should succeed.
Sequence `aab` should not.

In an array: a diagram showing the following pattern with the variable `i` set to the leftmost element and `j` set to the rightmost element.

Values|a|b|c|...|s|b|a

With a stack and queue:
1. read symbols, starting each in a stack and a queue
2. while the stack, queue are not empty:
  * pop and element from the stack + delete an element from the queue
  * if different -> not a palindrome
3. palindrome

## Queue: Array Implementations

Enqueue: a,b,c,d.
Front is now a, last is now d.

Values|a|b|c|d|...

Dequeue returns and deletes first element.
Front is now b, last is now d.

Values|?|b|c|d|...

Many enquques/dequeues later:

Values|s|...|m|n|o

Front element is now `m`, last element is now s.

Values|?|t|u|v|w|...

A similar slide is here, but I can't see the differnece.

Variables:
* array A is array of size capacity
* front is 0
* back is 0
* size is 0
* capacity = &lt;size of array&gt;

Pseudo-code:

```
array A = array of size capacity // holds queue contents
front = 0 // index in A of front element, if queue not empty
back = 0 // index where next unqueued element will go
size = 0 // number of elements in queue
capacity = <size of array> // ???(can't read) queue size supported

enqueue(x) { // adds x to the back of the queue
  // requires size<capacity>
  A[back] = x
  size = size + 1
  back = (back + 1) % capacity
}

dequeue() { // removes front element of queue and returns it
  // required size > 0
  temp = A[front]
  front = (front + 1) % capacity
  size = size - 1
  return temp
}
```

Is `size == front - back`?

Diagram showing only true if front and back haven't been switched around due to wrapping around back to the beginning o the array.

## "Circular Array" Queue Example

* size = 0
* front = 0
* back = 0

Values|empty|empty|empty|empty|empty|empty

enqueue: a,b,c,d

* front = 0
* back = 4

Values|a|b|c|d|empty|empty

dequque 3 times

* front = 3
* back = 4

Values|empty|empty|empty|d|empty|empty

enqueue e,f,g,h

* front = 3
* back = 2

Values|g|h|empty|d|e|f

unqueue j

* size = 6
* font = 3
* back = 3

Values|g|h|j|d|e|f

dequeue 3 times

* back = 3
* front = 0

Values|g|h|j|empty|empty|empty

dequeue 3 times

* back = 3
* front = 3

Values|empty|empty|empty|empty|empty|empty

## End
