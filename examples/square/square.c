#include <stdio.h>


int square(int x) { return x*x; }
#define SQUARE(X) ((X)*(X))

int 
main (int argc, char *argv[])
{
  int a, b, p, q;
  a = 1;
  p = square(a++);
  printf ("a=%d, p=%d\n", a, p);
  b = 1;
  q = SQUARE(b++);
  printf ("b=%d, q=%d\n", b, q);

  a = 1;
  p = square(++a);
  printf ("a=%d, p=%d\n", a, p);
} // main

