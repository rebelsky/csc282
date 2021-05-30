/**
 * expmod-bad.c
 *   A valiant attempt at an iterative expmod.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stddef.h>
#include "expmod.h"

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

long
expmod (long x, long n, long m)
{
  long result = 1;

  for (size_t i = 0; i < n; i++)
    {
      if (!(n % 2)) // n is even
        {
          long tmp = (result * x) % m; // calculate x^k 
          result = (tmp * tmp) % m;    // x^(2k) = x^k + x^k 
          n /= 2;                      // now we can halve n 
        } // n is even
      else // n is odd
        {
          result = (result * x) % m;
        } // n is odd
    } // for
  return result;
} // expmod

