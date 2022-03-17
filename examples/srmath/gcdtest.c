/**
 * gcdtest.c
 *   A simple test of the gcd function in SamR's gcd library.
 *
 *   Copyright (c) 2013-22 Samuel A. Rebelsky.  All rights reserved.
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


// +-------+-----------------------------------------------------------
// | Notes |
// +-------+


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include "srmath.h"
#include "srtest.h"


// +--------+----------------------------------------------------------
// | Macros |
// +--------+


// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  int i;        // Generic counter variable

  sr_reset();

  // Check that the gcd of some things and 0 is 0.
  SR_CHECK_LONG (stderr, gcd (5, 0), 0);
  SR_CHECK_LONG (stderr, gcd (0, 5), 0);
  SR_CHECK_LONG (stderr, gcd (-3, 0), 0);
  SR_CHECK_LONG (stderr, gcd (0, -3), 0);
  SR_CHECK_LONG (stderr, gcd (0, 0), 0);

  // Check that the gcd of X and X is abs(X) for various prime and
  // compound X's
  SR_CHECK_LONG (stderr, gcd (-6, -6), 6);
  SR_CHECK_LONG (stderr, gcd (-5, -5), 5);
  SR_CHECK_LONG (stderr, gcd (-1, -1), 1);
  SR_CHECK_LONG (stderr, gcd (1, 1), 1);
  SR_CHECK_LONG (stderr, gcd (5, 5), 5);
  SR_CHECK_LONG (stderr, gcd (6, 6), 6);

  // Check relatively prime numbers
  SR_CHECK_LONG (stderr, gcd (5, 7), 1);
  SR_CHECK_LONG (stderr, gcd (7, 5), 1);
  SR_CHECK_LONG (stderr, gcd (6, 35), 1);
  SR_CHECK_LONG (stderr, gcd (35, 6), 1);

  // Check cases in which the gcd is a simple prime
  SR_CHECK_LONG (stderr, gcd (3, 6), 3);
  SR_CHECK_LONG (stderr, gcd (6, 3), 3);
  SR_CHECK_LONG (stderr, gcd (3, 9), 3);
  SR_CHECK_LONG (stderr, gcd (9, 3), 3);
  SR_CHECK_LONG (stderr, gcd (3, 15), 3);
  SR_CHECK_LONG (stderr, gcd (15, 3), 3);
  SR_CHECK_LONG (stderr, gcd (9, 15), 3);
  SR_CHECK_LONG (stderr, gcd (15, 9), 3);

  // Check cases in which the result is a compound number
  SR_CHECK_LONG (stderr, gcd (120, 70), 10);
  SR_CHECK_LONG (stderr, gcd (70, 120), 10);
  SR_CHECK_LONG (stderr, gcd (33 * 21, 33 * 40), 33);
  SR_CHECK_LONG (stderr, gcd (33 * 40, 33 * 21), 33);

  // Check a few more negative numbers
  SR_CHECK_LONG (stderr, gcd (-6, 35), 1);
  SR_CHECK_LONG (stderr, gcd (6, -35), 1);
  SR_CHECK_LONG (stderr, gcd (-6, -35), 1);
  SR_CHECK_LONG (stderr, gcd (-35, 6), 1);
  SR_CHECK_LONG (stderr, gcd (35, -6), 1);
  SR_CHECK_LONG (stderr, gcd (-35, -6), 1);
  SR_CHECK_LONG (stderr, gcd (-9, 15), 3);
  SR_CHECK_LONG (stderr, gcd (9, -15), 3);
  SR_CHECK_LONG (stderr, gcd (-9, -15), 3);
  SR_CHECK_LONG (stderr, gcd (-15, 9), 3);
  SR_CHECK_LONG (stderr, gcd (15, -9), 3);
  SR_CHECK_LONG (stderr, gcd (-15, -9), 3);

  // Check things that I seem to have screwed up
  SR_CHECK_LONG (stderr, gcd (64, 48), 16);
  SR_CHECK_LONG (stderr, gcd (48, 64), 16);

  // Incorrect tests (intended as a demo)
  // SR_CHECK_LONG (stderr, 2+3, 6);
  // SR_CHECK_LONG (stderr, gcd(1, 7), 11);

  // Look at the results
  if (sr_get_errors() != 0)
    {
      sr_report (stderr);
      return 1;
    } // if (sr_errors != 0)

  // And we're done
  return 0;
} // main
