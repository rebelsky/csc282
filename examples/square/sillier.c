#include <stdio.h>


int silly(x,y)
{
  return x-y;
}

#define SILLY(X) silly(X,X);

int 
main (int argc, char *argv[])
{
  int a, b, p, q;
  a = 1;
  p = SILLY(a++); 
  printf ("a=%d, p=%d\n", a, p);
  // Potential output? a=3, p=? -1,0,1
  b = 1;
  q = SILLY(++b); 
  printf ("b=%d, q=%d\n", b, q);
  // Potential output? b=3, q=?
  
} // main

