---
layout: simple
---

# Participation Activity 4

Last name: <input type="text" name="lname">

First name: <input type="text" name="fname">

Std#: <input type="text" name="stdnum">

## Memory Allocation Example:

Where does eveything go?

Indicate with an arrow in which memory segment the content of each box will be found one we start executing the program.

Code (box is indicated as a comment):

```
#include ... // cyan box (shared libraries; header files and associated code.)

char hugeArray[1 << 31]; /* 2^31 = 2GB */ // purple box  (Data)
int global = 0; // purple box (Data)

int useless(){ return 0; } // (text; function code)

int main()
{
  void *ptr1, *ptr2; // red box (Stack)
  int local = 0; // red box (Stack)
  ptr1 = malloc(1 << 28); /* 2^28 = 256 MB */ // blue box (Heap)
  ptr2 = malloc(1 << 8); /* 2^8 = 256 B*/ // blue box (Heap)
/* some print statements */
}
```

<table>
  <thead>
    <tr>
      <th>M[]</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Kernel</td>
    </tr>
    <tr>
      <td>Stack (arrow pointing down)</td>
    </tr>
    <tr>
      <td>...</td>
    </tr>
    <tr>
      <td>Shared Libraries</td>
    </tr>
    <tr>
      <td>...</td>
    </tr>
    <tr>
      <td>Heap (arrow pointing up)</td>
    </tr>
    <tr>
      <td>Data</td>
    </tr>
    <tr>
      <td>Text</td>
    </tr>
    <tr>
      <td>...</td>
    </tr>
  </tbody>
</table>
