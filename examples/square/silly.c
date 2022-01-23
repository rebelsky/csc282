#include <stdio.h>


#define SILLY(X) ((X)-(X))

int 
main (int argc, char *argv[])
{
  int a, b, p, q;
  a = 1;
  p = SILLY(a++); // p = ((a++)-(a++))
  printf ("a=%d, p=%d\n", a, p);
  // Potential output? a=3, p=? -1,0,1
  b = 1;
  q = SILLY(++b); // q = ((++b)-(++b))
  printf ("b=%d, q=%d\n", b, q);
  // Potential output? b=3, q=?
  
} // main

