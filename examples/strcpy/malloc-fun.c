/**
 * malloc-fun.c
 *   Some experiments with malloc and free.
 *
 * <Insert FLOSS license here>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  char *s1;

  s1 = malloc (128);
  strcpy (s1, "once upon a time");
  printf ("s1: '%s'\n", s1);
  free(s1);
  s1 = malloc (128);
  printf ("s1: '%s'\n", s1);

  return 0;
} // main(int, char*[])
