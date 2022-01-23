/**
 * gcd.c
 *   Compute the gcd of numbers entered on the command line.
 *
 *   Copyright (c) 2013-21 Samuel A. Rebelsky.  All rights reserved.
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

/*

 o The program does not currently verify that the values entered on the
   command line are integers.  It should do so.

 */


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <stdlib.h>             // For atol
#include <stdio.h>              // For printf and such

#include "srmath.h"


// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  long result;          // The computed gcd
  int i;                // Generic counter variable

  // Sanity check
  if (argc <= 1)
    {
      fprintf (stderr, "Usage: gcd VAL1 VAL2 ... VALN\n");
      return 1;
    }

  // If there's only one value, that value is the gcd.
  result = atol (argv[1]);

  // Scan through the command line, computing the gcd.
  for (i = 2; i < argc; i++)
    {
      result = gcd (result, atol (argv[i]));
    } // for

  // Report the result
  printf ("%ld\n", result);

  // And we're done.
  return 0;
} // main
