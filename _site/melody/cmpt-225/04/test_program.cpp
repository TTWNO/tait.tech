//
//   Test Program for Basic Stack Class
//
#include <iostream> // for I/O facilities
using namespace std;
#include "MinimalStack.h" // basic_stackj declaration

int main(int argc, char* const argv[]){
  cout << "\n\nMinimalStack Template Class Test Proceedure - START\n\n";

  // Make some stacks, and verify that empty() says they are empty.
  MinimalStack<int> s1;
  MinimalStack<float> s2;

  cout<<"s1.isEmpty() = "<<s1.isEmpty()<<"\n";
  cout<<"s2.isEmpty() = "<<s2.isEmpty()<<"\n";

  // Put some things on them
  cout<<"s1.push("<<1<<")\n";
  s1.push(1);
  cout<<"s1.push("<<2<<")\n";
  s1.push(2);
  cout<<"s2.push("<<1.5<<")\n";
  s2.push(1.5);
  cout<<"s2.push("<<2.5<<")\n";
  s2.push(2.5);
  
  // Verify that isEmpty() reports that they are empty
  // and that the right things are on top
  cout<<"s1.isEmpty()="<<s1.isEmpty()<<"\n";
  cout<<"s1.top()="<<s1.top()<<"\n";
  cout<<"s2.isEmpty()="<<s2.isEmpty()<<"\n";
  cout<<"s2.top()="<<s2.top()<<"\n";
  
  // Empty them and verify that isEmpty() again reports that they are empty.
  while(!s1.isEmpty()){
    cout<<"s1.pop()="<<s1.pop()<<"\n";
  }
  cout<<"s1.isEmpty()="<<s1.isEmpty()<<"\n";
  while(!s2.isEmpty()){
    cout<<"s2.pop()="<<s2.pop()<<"\n";
  }
  // transcriber's note: the following lines are not contained on the slide, but I am assuming they are supposed to be there.
  cout<<"s2.isEmpty()="<<s2.isEmpty()<<"\n";
  return 0;
}
