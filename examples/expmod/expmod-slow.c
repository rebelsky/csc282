/**
 * expmod-recursive.c
 *   A recursive, somewhat efficient implementation of expmod.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "expmod.h"

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

long
expmod(long x, long n, long m)
{
  long result = 1;
  for (long i = 0; i < n; i++)
    {
      result = (result * x) % m;
    } // for
  return result;
} // expmod

