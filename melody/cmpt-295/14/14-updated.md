---
layout: simple
math: true
---

# CMPT 295

* Unit - Machine-Level Programming
* Lecture 14
  * Assembly language
  * Program Control
  * Function Call and Stack
  * Passing Control

## Last Lecture

* In x86-64 assembly, there are no iterative statements
* To alter the execution flow, compiler generates code sequence
that implements these iterative statements (while, do-while
and for loops) using branching method:
  * cmp\* instruction
  * jX instructions (jump)
* 2 loop patterns:
  * “coding the false condition first” -> while loops (hence for loops)
  * “jump-in-middle” -> while, do-while (hence for loops)

## While loop – Question from last lecture “coding the false condition first” (updated)

in C:

```
while(x<y){ // 1
  //stmts
}
```

Cases:

* $$y-x >0 \implies y>x$$: loops, g
* $$y-x <0 \implies y< x$$: exits loop, l
* $$y-x =0 \implies y=x$$: exists loops, e

in assembly: # x in %edi, y in %esi

```
loop:
  cmpl %edi, %esi #2
  jl endloop
  # stmts
  jmp loop
endloop:
  ret
```

Loop Pattern 1

```
loop:
  if cond false
    goto done:
  stmts
  goto loop:
done:
```

Would this assembly code be the equivalent of our C code?

Not quite! We need `jle`

## Demo: alternative way of implementing `if/else` in assembly language (updated)

Lecture 12 – ifelse.c and ifelse.s

We shall have a look at this code during lecture 15, our review lecture!

## For loop - Homework

In C:

```
format: for(initialization;condition testing;increment){
for(i=0;i<;i++){
  // stmts
}
return;
```

Becomes:

```
i=0; //initialization
while(i<n){//condition
  //stmts
  i++; //increment
}
return;
```

In Assembly:

```
  xorl %ecx, %ecx #initialization: %ecx (i) <- 0
loop:
  cmpl %edi, %ecx #i-n?0 testing
  jge endloop #i-n>=0 false condition
  #stmts
  incl %ecx #i++ increment
  jmp loop #loop again
endloop:
  ret
```

## Today’s Menu

* Introduction
  * C program -> assembly code -> machine level code
* Assembly language basics: data, move operation
  * Memory addressing modes
* Operation leaq and Arithmetic & logical operations
* Conditional Statement – Condition Code + cmovX
* Loops
* (highlighted) Function call – Stack
  * (highlighted) Overview of Function Call
  * (highlighted) Memory Layout and Stack - x86-64 instructions and registers
  * (highlighted) Passing control
  * Passing data – Calling Conventions
  * Managing local data
  * Recursion
* Array
* Buffer Overflow
* Floating-point operations

## What happens when a function (caller) calls another function (callee)?

1. Control is passed (PC is set) …
  * To the beginning of the code in callee function
  * Back to where callee function was called in caller function
2. Data is passed …
  * To callee function via function parameter(s)
  * Back to caller function via return value
3. Memory is …
  * Allocated during callee function execution
  * Deallocated upon return to caller function

Code example 1:

```
void who(...) {
  int sum = 0;
  ...
  y = amI(x);
  sum = x + y;
  return;
}
```

Code example 2:

```
int amI(int i)
{
  int t = 3*i;
  int v[10];
  ...
  return v[t];
}
```

Above mechanisms implemented with machine code instructions and described as a set of conventions (ISA)

## Remember from Lecture 2: Closer look at memory

* Seen as a linear array of bytes
* 1 byte (8 bits) smallest addressable
unit of memory
  * Byte-addressable
* Each byte has a unique address
* Computer reads a “word size” worth
of bits at a time
* Compressed view of memory

Compressed view of memory w/ addresses in cells:

<table>
  <thead>
    <tr>
      <th>Address</th>
      <th colspan="8">M[]</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>size-8</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
      <td>...</td>
    </tr>
    <tr>
      <td>0x0018</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>0x0010</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>0x0008</td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
      <td></td>
    </tr>
    <tr>
      <td>0x0000</td>
      <td>0x0001</td>
      <td>0x0002</td>
      <td>0x0003</td>
      <td>0x0004</td>
      <td>0x0005</td>
      <td>0x0006</td>
      <td>0x0007</td>
      <td>0x0008</td>
    </tr>
  </tbody>
</table>
  

## Memory Layout

Segments:

* Stack
  * Runtime stack, e. g., local variables
* Heap
  * Dynamically allocated as needed, explicitly released (freed)
  * When call malloc(), free(), new(), delete, ...
* Data
  * Statically allocated data, e.g., global vars, static vars, string constants
* Text
  * Executable machine instructions
  * Read-only
* Shared Libraries
  * Executable machine instructions
  * Read-only

Address|M[]
---|---
0x00007FFFFFFFFFFF|Stack (down arrow)
...|...
|Shared Libraries
...|...
|Heap (up arrow)
|Data
0x0000000000400000|Text
0x0000000000000000|

## Memory Allocation Example

Where does everything go?

```
#include ...
char hugeArray[1 << 31]; /* 231 = 2GB */
int global = 0;
int useless(){ return 0; }
int main ()
{
  void *ptr1, *ptr2;
  int local = 0;
  ptr1 = malloc(1 << 28); /* 228 = 256 MB*/
  ptr2 = malloc(1 << 8); /* 28 = 256 B*/

  /* Some print statements ... */
}
```

<table>
  <thead>
    <tr><th>M[]</th></tr>
  </thead>
  <tbody>
    <tr><td>Stack (down arrow)</td></tr>
    <tr><td>...</td></tr>
    <tr><td>Shared Libraries</td></tr>
    <tr><td>...</td></tr>
    <tr><td>Heap (up arrow)</td></tr>
    <tr><td>Data</td></tr>
    <tr><td>Text</td></tr>
  </tbody>
</table>

## Closer look at function call pattern

A function may call a function, which may call a function, which may call a function, …

Code example 1:

```
who(...) {
  ...
  ...
  are();
  ...
  ...
}
```

Code example 2:

```
are(...) {
  ...
  you();
  ...
  you();
  ...
}
```

Example 3:

```
you(...) {
  ...
  ...
  ...
  ...
  ...
}
```

* When a function (callee) terminates and returns, its most
recent caller resumes which eventually terminates and returns
and its most recent caller resumes …
* Does this pattern remind you of anything?

## Stack

Definition: A stack is a last-in-first-out (LIFO) data structure with two characteristic operations:

* push(data)
* data = pop() or pop(&data)

Do not have access to anything except what is on (at) top.

Image of stack of dinner plates.

## Closer look at stack

* x86-64 assembly language has stack-specific
* %rsp
  * Points to address of last used byte on stack
  * Initialized to “top of stack” at startup
  * Stack grows towards low memory address
* pushq src
* popq dest

Diagram of stack:
at the top of the stack is `%rsp`; the stack grows down.
Memory addresses decreese as they go down the stack.

## x86-64 stack instruction: push

* pushq src
  * Fetch value of operand src
  * Decrement %rsp by 8
  * Write value at address given by %rsp

Diagram of stack after 3 pushes (transcriber's note: these diagrams are probably wrong, but I need to describe what is there):

Register|M[] Stack|Name
---|---
%rsp||Top
...|...|...

## x86-64 stack instruction: pop

… we pop once.

* popq dest
  * Read value at %rsp (address) and store it in operand dest (must be register)
  * Increment %rsp by 8

After we pop once:

Register|M[] stack|Name
---|---
|data|
|data|
%rsp|data|Top
...|...

## Passing control mechanism x86-64 instruction: call and ret

* call func
  * push PC
  * jmp func (set PC to func)

Effect: return address, i.e., the
address of the instruction after
call func (held in PC) is
pushed onto the stack

Register|M[] Stack|Name
---|---|---
%rsp||Top
...|...|...

## Passing control mechanism x86-64 instruction: call and ret


* ret
  * popq PC
  * jmp PC

Effect: return address, i.e., the
address of instruction after
call func, is pop’ed from
the stack and stored in PC

After returning from the call …

Register|M[] Stack|Name
---|---|---
|data|
%rsp||Top

## Example

Example pt. 1, in C:

```
void multstore(long x, long y, long *dest) {
  long t = mult2(x, y);
  *dest = t;
  return;
}
```

Example pt. 1, in Assembly:

```
0000000000400540 <multistore>:
  400540: push %rbx #Save %rbx
  400541: mov %rdx,%rbx #save Dest
  400544: callq 400550 <mult2> #mult2(x,y)
  400549: mov %rax,(%rbx) #save as dest
  40054c: pop %rbx #restore %rbx
  40054d: retq #return
```

Example pt. 2, in C:

```
long mult2(long a, long b) {
  long s = a * b;
  return s;
}
```

Example pt. 2, in Assembly:

```
0000000000400550 <mult2>:
  400550: mov %rdi,%rax #a
  400553: imul %rsi,%rax #a*b
  400557: retq #return
```

## Example – Steps 1 and 2

Stack:

Register|M[] Stack|Name
---|---|---
|ret address|
%rsp||Top

Registers:

Register|Value
---|---
%rbx|
%rsp|0x120
%rax|
%rip|0x400540
%rdi|
%rsi|
%rdx|

## Example – Steps 3 and 4

Stack:

Register|M[] Stack|Name
---|---|---
|ret address|
|%rbx|
%rsp||Top
...|...|...

Registers:

Register|Value
%rbx|
%rsp|0x118
%rax|
%rip|400544
%rdi|
%rsi|
%rdx|

## Example – Steps 5 and 6

Stack:

Register|M[] Stack|Name
---|---|---
|ret address|
|%rbx|
|0x400549|
%rsp||Top

Registers:

Register|Value
---|---
%rbx|
%rsp|0x110
%rax|
%rip|0x400553
%rdi|
%rsi|
%rdx|

## Example – Steps 7, 8 and 9

Stack:

Register|M[] Stack|Name
|ret address|
|%rbx|
%rsp||Top
...|...|...

Registers:

Register|Value
%rbx|
%rsp|0x118
%rax|
%rip|0x400549
%rdi|
%rsi|
%rdx|

## Summary

* Function call mechanisms: passing control and data, managing memory
* Memory layout
  * Stack (local variables …)
  * Heap (dynamically allocated data)
  * Data (statically allocated data)
  * Text / Shared Libraries (program code)
* “Stack” is the data structure used for function call / return
  * If multstore calls mult2, then mult2 returns before multstore
* x86-64 stack register and instructions: stack pointer rsp, push and pop
* x86-64 function call instructions: call and ret

## Next Lecture

* Introduction
  * C program -> assembly code -> machine level code
* Assembly language basics: data, move operation
  * Memory addressing modes
* Operation leaq and Arithmetic & logical operations
* Conditional Statement – Condition Code + cmovX
* Loops
* Function call – Stack
  * Overview of Function Call
  * Memory Layout and Stack - x86-64 instructions and registers
  * (highlighted) Passing control
  * Passing data – Calling Conventions
  * Managing local data
  * Recursion
* Array
* Buffer Overflow
* Floating-point operations
