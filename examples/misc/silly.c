/**
 * Sample code to examine stuff.
 */

#include <stdio.h>

int 
main (int argc, char *argv[])
{
#ifdef GREET
  /* Print a greeting. */
  printf ("Hello\n");
#endif

  /* Print a goodbye. */
  printf ("Bye\n");
} // main
