#include "dsexception.h" // transcriber's note: I have no idea where this file is or what it does???
#include "List.h"

using namespace std;

int main()
{
  const int N = 5;
  List<int> lst;
  for (int i=N-1; i>0; --i)
  {
    lst.push_forward(i);
  }
  return 0;
}
