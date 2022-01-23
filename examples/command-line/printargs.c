/**
 * printargs.c
 *   Print out the arguments.  Whee!
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>

// +---------+-------------------------------------------------------
// | Helpers |
// +---------+

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    {
      printf ("%2d: %s\n", i, argv[i]);
    } // for i

  // And we're done
  return 0;
} // main

