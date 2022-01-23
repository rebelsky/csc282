/**
 * expmod-new.c
 *   A new, recursive, somewhat efficient implementation of expmod.
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
      // x^(2k) = (x^2)^k;  k = n/2
      return expmod(MOD(MULTIPLY(x,x),m), DIVIDE(n,2), m);  
    } // even
  else // odd
    {
      long tmp = expmod (x, n-1, m);       // x^(k+1) = x^k * x
      return MOD(MULTIPLY(x,tmp), m);
    } // odd
} // expmod

