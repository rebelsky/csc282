#define DOUBLE(X) 2*X

#include <stdio.h>

int
main (int argc, char *argv[])
{
  printf ("double (1+2) is %d\n", DOUBLE(1+2));
  return 0;
} // main
