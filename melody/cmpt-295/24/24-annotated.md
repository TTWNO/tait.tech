---
layout: simple
math: true
---

# CMPT 295 - Unit - Instruction Set Architecture

I do not like computer jokes...not one bit!

Lecture 24:

* MIPS

## Last Lecture

* Assembler (part of the compilation process):
  * Transforms assembly code (`movl %edi,%eax`) into machine code
(`0xf889 -> 1111100010001001`)
* Instruction Set Architecture (ISA) [Annotation: ...is an abstract model of a computer ...is an interface between software (and s/w developers) and hardware (hardware designers)
A formal specification (or agreement) of:
  * Registers and memory model, set of instructions (assembly-machine) [Annotation: main memory]
  * Conventions, model of computation [Annotation: data types, memory addressing modes]
  * etc...
* Design principles when creating instruction set (IS)
    1. Each instruction must have an unambiguous encoding
    2. Functionally complete (Turing complete)
    3. Machine instruction format: 1) as few of them as possible 2) of the
same length 3) fields that have the same purpose positioned in the
same location in the format
* Types of instruction sets: CISC and RISC

[Annotation: A realization of an ISA is called an implementation. An ISA permits multiple implementations.]

## Today’s Menu

* Instruction Set Architecture (ISA)
  * Definition of ISA
* Instruction Set design
  * Design guidelines
  * (highlighted) Example of an instruction set: MIPS
  * Create our own instruction sets
  * ISA evaluation
* Implementation of a microprocessor (CPU) based on an ISA
  * Execution of machine instructions (datapath)
  * Intro to logic design + Combinational logic + Sequential logic circuit
  * Sequential execution of machine instructions
  * Pipelined execution of machine instructions + Hazards

## Example of another ISA: MIPS

[Annotation: MIPS = microprocessor without interlocked pipelined stages.]

## Example of an ISA: MIPS

* Registers and Memory model
  * \# of registers -> 32 registers (each register is 32 bit wide) See Figure on next Slide [Annotation: 1]
  * Word size -> 32 bits [Annotation: 3]
  * Memory size -> $$2^{m} \times n = 2^{32} \times 8 \text{ bits}$$ [Annotation: 5]
  * Byte-addressable memory
so address resolution -> n = 8 bits [Annotation: 4]
  * Size of memory address (# of bits) -> 32 bits; m = 32 [Annotation: 2]
* So, there are $$2^{32}$$ distinct addressable memory “chunks”
(or “locations”) and each of these addressable memory
“chunks” (or “locations”) has 8 bits See Figure on next next Slide [Annotation: 6]

### FIGURE A.6.1 MIPS registers and usage conventions.

Register name|Number|Usage
---|---|---
`$zero`|0|constant 0
`$at`|1|reserved for assembler
`$v0`|2|expression evaluation and results of a function
`$v1`|3|expression evaluation and results of a function
`$a0`|4|argument 1
`$a1`|5|argument 2
`$a2`|6|argument 3
`$a3`|7|argument 4
`$t0`|8|temporary (not preserved across call)
`$t1`|9|temporary (not preserved across call)
`$t2`|10|temporary (not preserved across call)
`$t3`|11|temporary (not preserved across call)
`$t5`|12|temporary (not preserved across call)
`$t6`|13|temporary (not preserved across call)
`$t7`|14|temporary (not preserved across call)
`$s0`|15|saved temporary (preserved across call)
`$s1`|16|saved temporary (preserved across call)
`$s2`|17|saved temporary (preserved across call)
`$s3`|18|saved temporary (preserved across call)
`$s4`|19|saved temporary (preserved across call)
`$s5`|20|saved temporary (preserved across call)
`$s6`|21|saved temporary (preserved across call)
`$s7`|22|saved temporary (preserved across call)
`$t8`|24|temporary (not preserved across call)
`$t9`|25|temporary (not preserved across call)
`$k0`|26|reserved for OS kernel
`$k1`|27|reserved for OS kernel
`$gp`|28|pointer to global area
`$sp`|29|stack pointer
`$fp`|30|frame pointer
`$ra`|31|return address (used by function call)

Source: Page A-24 in Patterson and Hennessy

## MIPS Memory Model

### FIGURE 2.13 -- The MIPS memory allocation for program and data

These addresses are only a software convention,
and not part of the MIPS architecture.
The stack pointer is initialized to $$\text{7fff fffc}_{\text{hex}}$$ and grows down toward the segment.<!--_-->
At the other end, the program code ("text") starts at $$\text{0040 0000}_{\text{hex}}$$. <!--_-->
The static data starts at $$\text{1000 0000}_{\text{hex}}$$. <!--_-->
Dynamic data, allocated by `malloc` in C and by `new` in Java, is next.
It grows up toward the stack and in an area called the heap.
The global pointer: `$gp`, is set to an address to make it easy to access data.
It is initialized to $$\text{1000 8000}_{\text{hex}}$$<!--_-->
so it can access from $$\text{1000 000}_{\text{hex}}$$ to $$\text{1000 ffff}_{\text{hex}}$$ using the positive and negative 16-bit offsets from `$gp`.
The information is also found in Column 4 of the MIPS Reference Data Card at the front of the book.

Source: Page 104 in Patterson and Hennessy

Register/Address|Label
(top) `$sp` -> $$\text{7fff ffff}_{\text{hex}}$$|Stack (arrow pointing down)
|Dynamic data (arrow pointing up) [Annotation: heap]
(between Static Data and Text) `$gp` -> $$\text{1000 8000}_{\text{hex}}$$, $$\text{1000 0000}_{\text{hex}}$$|Static Data
(bottom) `$pc` -> $$\text{0040 0000}_{\text{hex}}$$|Text
(bottom) 0|Reserved

## Example of an ISA: MIPS

* Instruction set
  * MIPS assembly language notation
    * `add a, b, c`, Meaning: a = b+c
  * 3 operand assembly language
    * Requiring all instructions to have 3 operands would
keep the design of the microprocessor hardware
simple
    * Hardware for a variable number of operands is
more complicated

## Activity

* If we want to write an assembly program that sums
four variables b, c , d and e, how many MIPS add
instructions would we need?

* Solution:

```
add a,b,c # a = b+c
add a,a,d # a = b+c+d
add a,a,e # a = b+c+d+e
```

$$\therefore$$ make your comments as "self contained" as possible, to be self contained, the reader does not have to refer back to other commands to understand current comment!

## Example of an ISA: MIPS

(Sub)set of instructions:

MIPS assembly language instructions|Semantic (i.e., Meaning)|Corresponding MIPS machine instructions
---|---|---
`lw $s1, 20($s2)` [A](#A)|`$s1 = M[$s2 + 20]`|?
`sw $s1, 20($s2)` [A](#A)|`M[$s2 + 20] = $s1`|?
`add $s1, $s2, $s3`|`$s1 = $s2 + $s3`|?
`sub $s1, $s2, $s3`|`$s1 = $s2 - $s3`|?
`beq $s1, $s2, 25`|`if ($s1 == $s2) go to PC + 4 + 100` [Annotation: PC+4 done as part of loop fetch-decode-execute]|?
`j 2500`|`go to 10000 (2500 * 4 bytes)`|?
`jal 2500`|`$ra = PC + 4; go to 10000`|?

* <span id="A">Memory addressing modes -> Direct (absolute),
base + displacement and Indirect</span>
* Operand model ->
* Format/syntax of corresponding MIPS machine instructions?
  * Length of machine instruction -> 32 bits (4 bytes)
  * Size of opcode? Size of other fields? Order of operands?

Format/syntax of these bit patterns are all the question marks.

## A closer look at MIPS’ add instruction

* MIPS assembly language instruction:
  * add <span id="As0">$s0</span>, <span id="Aal">$al</span>, <span id="At7">$t7</span>
* Corresponding MIPS machine instruction:
  * 0x00af8020
  * Binary: 0000 0000 1010 1111 1000 0000 0010 0000
  * Breakdown: Label|Binary|Meaning|Bits
---|---|---|---
opcode|000000|operation of the instruction|6 bits
rs (`$al` in `add $s0,$al,$t7`)|00101|first register source operand|5 bits
rt (`$t7` in `add $s0,$al,$t7`)|01111|second register source operand|5 bits
rd (`$s0` in `add $s0,$al,$t7`)|10000|register destination operand (contains result of operation)|5 bits
shamt|00000|shift amount|5 bits
func|100000|function -- often called function code, which indicates the specific variant of the operation in the `opcode` field|6 bits

[Annotation: Why 5 bits for `rs`, `rt` and `rd`?
$$2^{5} =32$$ registers -> need 5 bits to uniquely identify 32 registers]

Total: 32 bits

## Let’s examine an ISA: MIPS (3 of 3)

* Function call conventions
  * caller saved registers (4-15, 24, 25)
  * callee saved registers (16-23, 30, 31)

Register name|Number|Usage
---|---|---
`$zero`|0|constant 0
`$at`|1|reserved for assembler
`$v0`|2|expression evaluation and results of a function
`$v1`|3|expression evaluation and results of a function
`$a0`|4|argument 1
`$a1`|5|argument 2
`$a2`|6|argument 3
`$a3`|7|argument 4
`$t0`|8|temporary (not preserved across call)
`$t1`|9|temporary (not preserved across call)
`$t2`|10|temporary (not preserved across call)
`$t3`|11|temporary (not preserved across call)
`$t5`|12|temporary (not preserved across call)
`$t6`|13|temporary (not preserved across call)
`$t7`|14|temporary (not preserved across call)
`$s0`|15|saved temporary (preserved across call)
`$s1`|16|saved temporary (preserved across call)
`$s2`|17|saved temporary (preserved across call)
`$s3`|18|saved temporary (preserved across call)
`$s4`|19|saved temporary (preserved across call)
`$s5`|20|saved temporary (preserved across call)
`$s6`|21|saved temporary (preserved across call)
`$s7`|22|saved temporary (preserved across call)
`$t8`|24|temporary (not preserved across call)
`$t9`|25|temporary (not preserved across call)
`$k0`|26|reserved for OS kernel
`$k1`|27|reserved for OS kernel
`$gp`|28|pointer to global area
`$sp`|29|stack pointer
`$fp`|30|frame pointer
`$ra`|31|return address (used by function call)

## MIPS - Design guidelines

* opcode
* rs
* rt
* rd
* shamt
* func

3) In terms of machine instruction format:
    1. Create as few of them as possible
    2. Have them all of the same length and same format!
    3. If we have in different machine instruction formats, then position the
fields that have the same purpose in the same location in the format
  * Can all MIPS machine instructions have the same length and same
format?
    * For example: `lw $s1, 20($s2)`
    * When designing its corresponding machine instruction …
      * Must specify source register using 5 bits -> OK!
      * Must specify destination register using 5 bits -> OK!
      * Must specify a constant using 5 bits -> Hum…
        * Value of constant limited to [0..25-1]
        * Often use to access array elements
so needs to be $$> 2^{5} = 32$$

## MIPS ISA designers compromise

* Keep all machine instructions format the same length
* Consequence -> different formats for different kinds of MIPS
instructions
  * R-format for register
    * Label|Size
---|---
opcode|6 bits
rs|5 bits
rt|5 bits
shamt|5 bits
func|6 bits
  * I-format for immediate
    * Label|Size
---|---
opcode|6 bits
rs|5 bits
rt|5 bits
Address/immediate|16 bits
  * J-format for jump
    * Label|Size
---|---
opcode|6 bits
Target address|26 bits

* opcode indicates the format of the instruction
  * This way, the hardware knows whether to treat the last half of the
instruction as 3 fields (R-format) or as 1 field (I-format)
  * Also, position of fields with same purpose are in the same location
in the 3 formats &#x263a;

## Summary

* Types of instruction sets: CISC and RISC
* Looked at an example of a RISC instruction set: MIPS
  * Registers and Memory model
  * (Sub)set of instructions (assembly + machine instructions)
  * Function call conventions
  * Model of computation
* MIPS design principles
    1. Unambiguous binary encoding of instruction
    2. (highlighted) IS functionally complete (“Turing complete”)
    3. Machine instruction format -> only 3 of same length but of different format!
      * R-format for register
      * I-format for immediate
      * J-format for jump
* Also, position of fields with same purpose are in the same location in the 3
formats &#x263a;

## Next lecture

* Instruction Set Architecture (ISA)
  * Definition of ISA
* Instruction Set design
  * Design guidelines
  * Example of an instruction set: MIPS
  * (highlighted) Create our own instruction sets
  * (highlighted) ISA evaluation
* Implementation of a microprocessor (CPU) based on an ISA
  * Execution of machine instructions (datapath)
  * Intro to logic design + Combinational logic + Sequential logic circuit
  * Sequential execution of machine instructions
  * Pipelined execution of machine instructions + Hazards
