/* a small program to demonstrate C++ addresses, pointers and arrays */

#include <iostream> /* Tait: missing name for import */
#include <iomanip> /* Tait: missing name from import */
using namespace std;

int main(){
  cout << "main() begin\n";

  int XXXX = 111111111;
  cout << "XXXX = " << XXXX << endl;
  cout << "XXXX is stored at &XXXX = " << &XXXX << endl;

  int * YYYY = &XXXX;
  cout << "YYYY is a pointer to XXXX: YYYY = " << YYYY << endl;
  cout << "* dereferences the pointer: *YYYY = " << *YYYY << endl;

  int AAAA[3] = { 222222222, 333333333, 444444444 };
  cout << "Array AAAA can be accessed with array notaions: " << endl;
  cout << "       AAAA[0] = " << AAAA[0] << endl;
  cout << "       AAAA[1] = " << AAAA[1] << endl;
  cout << "       AAAA[2] = " << AAAA[2] << endl << endl;
  
  cout << "Array variable AAAA is a pointer to A[0]: AAAA = " << AAAA << endl;
  cout << "So, dereferencing AAAA should give us A[0]: *AAAA = " << *AAAA << endl << endl;
  
  cout << "Adding 1 to an int pointer makes it point to the next int" << endl;
  cout << "AAAA = " << AAAA << endl;
  cout << "AAAA+1 = " << (AAAA+1) << endl;
  cout << "*(AAAA+1) = " << *(AAAA+1) << endl << endl;
  
  cout << "We can look at contents of a chunk of memory:" << endl;
  cout << "Peeking at the memory in the neighbourhood of &XXXX, we see: " << endl << endl;
  cout << "Address       Contents in Hex         Contents in Decimal " << endl;
  int * p = (&XXXX)+7;

  for (int i = 0; i < 15; i++) {
    cout << p << ": " << setw(8) << hex << *p << " =  " << setw(11) << dec << *p << endl;
    p -= 1;
  }

  cout << "main() ends" << endl;
}
