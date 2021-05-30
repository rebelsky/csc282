/**
 * expmod-tail.c
 *   A new, tail-recursive, somewhat efficient implementation of expmod.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "expmod.h"
#include "logmath.h"

// +---------+-------------------------------------------------------
// | Helpers |
// +---------+

static long
expmod_helper (long x, long n, long m, long acc)
{
  if (0 == n)
    {
      return acc;
    } // base case
  else if (n % 2 == 0)
    {
      return expmod_helper ((x*x) % m, n/2, m, acc);
    } // even
  else
    {
      // x^(k+1) = x^k * x; k = n - 1
      // return (x * expmod (x, n-1, m)) % m;
      return expmod_helper (x, n-1, m, (x*acc) % m);
    } // odd
} // expmod_helper

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

long
expmod (long x, long n, long m)
{
  return expmod_helper (x, n, m, 1);
} // expmod (long x, long n, long m)

