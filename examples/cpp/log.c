#include <math.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  double num = 100;
  // scanf (argv[1], "%lf", &num);
  fprintf (stderr, "num = %lf\n", num);
  double result = log10(num);
  printf ("log10(%lf) = %lf\n", num, result);
} // main

