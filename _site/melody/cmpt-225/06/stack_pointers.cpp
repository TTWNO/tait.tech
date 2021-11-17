/* A program to demonstrate printing out partial contents of the call stack */

#include <iostream> /* Note: only "#include" shown in image */
#include <iomanip> /* Note: only "#include" shwon in image */

using namespace std;

int print_stack(int k, int j){
  cout << "print_stack() begins" << endl;
  cout << "argument k is at &k=" << &k << "   and k=" << k << endl;
  cout << "argument j is at &j=" << &j << "   and j=" << j << endl;

  int CCC[2] = {77777777, 88888888};
  cout << "Peeking from &j up, for the space of k ints" << endl;
  int *p = (&j)+k;
  for (int l=k; l>0; l--){
    cout << p << ": " << setw(8) << hex << *p << " =  " << setw(11) << dec << *p << endl;
    p-=j;// subtracts j from an int pointer sets it to the j-th previous int
  }
  cout << "End of: print_stack()" << endl;
}

int ffff(int fun_arg){
  cout << "fun() begins" << endl;
  cout << "fun_arg is at &fun_arg=" << &fun_arg << endl;
  int BBB[2] = {44444444,55555555};
  cout << "BBB is at BBB=" << BBB << endl;
  print_stack(40, +1);
  cout << "fun ends" << endl;
}

int main(){
  cout << "main() begins" << endl;
  int XXXX = 99999999;
  int AAAA[2] = {11111111,22222222};
  ffff(33333333);
  cout << "main() ends" << endl;
}
