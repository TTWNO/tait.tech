#include "TVector.h"
#include <iostream>
using namespace std;

int main()
{
  const int N = 20;
  
  TVector<int> v; // make an int vector
  v.display(); // prints its contents

  // Stores N ints in the Vector
  for (int i=0; i<N; ++i)
  {
    v.push_back(i);
  }
  
  // print the contents
  v.display();

  return 0;
}
