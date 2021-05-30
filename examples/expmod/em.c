/**
 * em.c
 *   A simple command-line version of expmod.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>
#include "expmod.h"
#include "logmath.h"

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  if (argc != 4)
    {
      fprintf (stderr, "Usage: %s x n m\n", argv[0]);
      return 1;
    }
  else
    {
      long x = atol (argv[1]);
      long n = atol (argv[2]);
      long m = atol (argv[3]);
      long result = expmod (x, n, m);
#ifdef VERBOSE
      fprintf (stdout, "(%ld^%ld) %% %ld = %ld\n", x, n, m, result);
#else
      fprintf (stdout, "%ld\n", result);
#endif
#ifdef LOGMATH
      fprintf (stdout, "*: %ld\n", _MULTIPLICATIONS);
      fprintf (stdout, "/: %ld\n", _DIVISIONS);
      fprintf (stdout, "%%: %ld\n", _MODS);
#endif
      return 0;
    }
} // main

