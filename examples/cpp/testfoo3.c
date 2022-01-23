#include "foo.h"
#include "foo.c"
#include <stdio.h>

int
main (int argc, char *argv[])
{
  double d = 99.5;
  int i = foo(d);
  printf ("foo (%lf) = %d\n", d, i);
  return 0;
} // int
