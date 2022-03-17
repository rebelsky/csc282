/**
 * srgcd.c
 *   An implementation of the GCD function for SamR's simple math library.
 *
 *   Copyright (c) 2013-2022 Samuel A. Rebelsky.  All rights reserved.
 *
 *   This file is part of SRMath, SamR's simple math library.
 *
 *   SRMath is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   SRMath is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with SRMath.  If not, see <http://www.gnu.org/licenses/>.
 */


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <stdlib.h>

#include "srmath.h"
#include "srtest.h"


// +--------------------+----------------------------------------------
// | Exported Functions |
// +--------------------+

long
gcd (long x, long y)
{
  long tmp;
  // Note: We're using Euclid's GCD algorithm, or at least SamR's
  // vague memory of Euclid's GCD algorithm.

  // Euclid's GCD algorithm works best with non-negative numbers.
  x = labs (x);
  y = labs (y);

  // Sanity check: If either value is 0, the gcd is 0.
  if ((x == 0) || (y == 0))
    {
      return 0;
    } // if either value is 0

  // Time to do the main work.  Repeatedly take the remainder until the
  // remainder is 0.
  while (y != 0)
    {
      tmp = x % y;
      x = y;
      y = tmp;
    } // while
  
  // The last nonzero divisor is the gcd
  return x;
} // gcd
