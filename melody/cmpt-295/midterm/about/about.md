---
layout: simple
---

# CMPT 295 -- About our Midterm 1

## Midterm 1

* When: Friday, Oct. 15 9:30am – 10:20am
* Where: same classroom
* Duration: 45 minutes (+ 5 minutes to organize ourselves)

## What to study?

Everything we covered up until (and including)
our lecture on Friday, Oct. 8 is subject to
examination

* All material from Lecture 1 until and including Lecture 14 (partial
lecture notes + annotated lecture notes + your own lecture
notes + recorded lectures)
* Labs 1 to 3, Assignments 1, 2, 3 and 4 (even though Assignment 4
is due after our Midterm 1)
* All demo code posted on our course web site
* Textbook Readings + Practice Problems:
  * Chapter 2, Section 2.1 to 2.4 (skip 2.3.7) + Practice Problems 2.1 to 2.34, 2. 38 to 2.41, 2.44, 2.45, 2.47, 2.48, 2.50, 2.52, 2. 54
  * Chapter 3, Section 3.2 to 3.6 (skip 3.4.4 for now, skip 3.5.5 and 3.6.8) + Practice Problems 3.1 to 3.11, 3.13 to 3.16 B. (not A.), 3.18, 3.20,
3.21 to 3.26, 3.28

## Format of Midterm 1

* First section: questions that require short answers.  For example:
  * “Yes/no” or
  * “fill in the blank” or
  * a few words
  * etc…
* Second section: questions that require written answers. For example:
  * Calculating – we always show every step of our work
  * Writing/completing C or assembly code
  * Hand tracing code
  * Writing an answer (in English)
  * etc…

## Appendix

As part of Midterm 1’s appendix, we will
be given the following information:

Table of x86-64 Jumps:

Instruction|Condition|Description
---|---|---
`jmp`|always|Unconditional jump
`je`/`jz`|ZF|Jump if equal / zero
`jne`/`jnz`|~ZF|Jump if not equal / not zero
`js`|SF|Jump if negative
`jns`|~SF|Jump if nonnegative
`jo`|OF|Jump if overflow
`jno`|~OF|Jump if not overflow
`jq`/`jnle`|~(SF ^ OF) & ~ZF|Jump if greater (signed >)
`jge`/`jnl`|~(SF ^ OF)|Jump if greater or equal (signed >=)
`jl`/`jnge`|SF ^ OF|Jump if less (signed <)
`jle`/`jng`|(SF ^ OF) \| ZF|Jump if less or equal (signed <=)
`ja`/`jnbe`|~CF & ~ZF|JumP if greater (unsigned >)
`jae`/`jnb`|~CF|Jump if greater or equal (unsigned >=)
`jb`/`jnae`/`jc`|CF|Jump if less (unsigned <)
`jbe`/`jna`/`jnc`|CF \| ZF|Jump if less or equal (unsigned <=)

Table of x86-64 Registers

64-bit (quad)|32-bit (double)|16-bit (word)|8-bit (byte)|8-bit (byte)|
63..0|31..0|15..0|15..8|7..0|
---|---|---|---|---|---
rax|eax|ax|ah|al|Return value
rbx|ebx|bx|bh|bl|Callee served
rcx|ecx|cx|ch|cl|4th arg
rdx|edx|dx|dh|dl|3rd arg
rsi|esi|si||sil|2nd arg
rdi|edi|di||dil|1st arg
rbp|ebp|bp||bpl|Callee served
rsp|esp|sp||spl|Stack position
r8|r8d|r8w||r8b|5th arg
r9|r9d|r9w||r9b|6th arg
r10|r10d|r10w||r10b|Callee served
r11|r11d|r11w||r11b|Callee served
r12|r12d|r12w||r12b|Callee served
r13|r13d|r13w||r13b|Callee served
r14|r14d|r14w||r14b|Callee served
r15|r15d|r15w||r15b|Callee served

and the powers of 2 from $$2^{-10}$$ to $$2^{10}$$ in decimal

## Exam Seating Arrangement

* S represents a student seated at a seat
* X represents a vacant seat

Front of classroom is the bottom of the table:

S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S
S|X|S|X|S|X|S

EVERYTHING HERE (the front of the class) (included cell phones, computer and calculator)!
Keep pens, pencils, eraser with you!

## Before the midterm

* Once you have received your midterm, leave the midterm face up on your table
* Read its instructions on its first page
* Please, do not touch, leaf through, or write your name on the midterm
  * Why? Because it is unfair to all other students who have not yet received a midterm
* When all students have received a midterm, you will be instructed to start the midterm

## During the midterm

If you have a question

1. Have a look at the instructions on Page 1 for an answer
2. If the answer to your question is not on Page 1,
raise your hand and the instructor will attend to
your question – the instructor is the only
person answering questions (TAs will not be
answering questions)

## At the end of midterm

When you are told to: Please, stop writing!
please, do stop writing and hand in our
midterm as instructed

Why? If you continue writing, it is unfair to all
other students who have stopped writing

## Questions?

