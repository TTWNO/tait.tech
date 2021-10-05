/*
Transcriber's note: In the slide, the order of the functions is: main, f, g
But I have reordered them g, f, main to allow compilation.
*/
int g(int i){
  return 2*i;
} // return control to f

int f(int c){
  int d=3;
  int e=g(4); // go to g
  return e;
} // return control to main

int main(){
  int a=1;
  int b=f(2); // go to function f
  return 0;
} // return from program
