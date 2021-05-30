/**
 * expmod-recursive.c
 *   A recursive, somewhat efficient implementation of expmod.
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
  if (0 == n)                               // x^0 = 1
    {
      return 1;
    }
  else if (MOD(n,2) == 0) // even
    { 
      long tmp = expmod (x, DIVIDE(n,2), m);       // x^(2k) = x^k * x^k
      return MOD(MULTIPLY(tmp,tmp),m);
    } // even
  else // odd
    {
      long tmp = expmod (x, n-1, m);       // x^(k+1) = x^k * x
      return MOD(MULTIPLY(x,tmp), m);
    } // odd
} // expmod

