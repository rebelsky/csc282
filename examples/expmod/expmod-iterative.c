/**
 * expmod-iterative.c
 *   An iterative, somewhat efficient implementation of expmod.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "expmod.h"
#include "logmath.h"

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

long
expmod (long x, long n, long m)
{
  long result = 1;
  while (n > 0)
    {
      if (MOD(n,2) == 0)        // even
        {
          x = MOD(MULTIPLY(x,x),m);
          n = DIVIDE(n,2);
        }
      else 
        {
          result = MOD(MULTIPLY(result,x),m);
          n = n-1;
        }
    } // while
  return result;
} // expmod

