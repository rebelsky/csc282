#include <stdio.h>

int
fib (int n)
{
  int result;

#ifdef DEBUG
  fprintf (stderr, "fib (%d)\n", n);
#endif

  if (n <= 1)
    result = n;
  else
    result = fib(n-1) + fib(n-2);
  return result;
}

int
main (int argc, char *argv[])
{
  printf ("fib (10) = %d\n", fib (10));
  return 0;
} // main 



