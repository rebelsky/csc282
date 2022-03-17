/**
 * testdemo.c
 *   A simple demo of SamR's testing utilities.
 *
 *   Copyright (c) 2013-2022 Samuel A. Rebelsky.  All rights reserved.
 *
 *   This file is part of SRTest, SamR's simple testing library.
 *
 *   SRTest is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   SRTest is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with SRTest.  If not, see <http://www.gnu.org/licenses/>.
 */


// +-------+-----------------------------------------------------------
// | Notes |
// +-------+


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include "srtest.h"


// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  sr_reset();

  // A few simple tests
  SR_CHECK_LONG (stderr, 2+3, 5);
  SR_CHECK_LONG (stderr, 2+4, 6);
  SR_CHECK_LONG (stderr, 2*4, 8);

  // Incorrect tests (intended as a demo)
  // SR_CHECK_LONG (stderr, 2+3, 6);

  // Look at the results
  if (sr_get_errors() != 0)
    {
      sr_report (stderr);
      return 1;
    } // if (sr_errors != 0)

  // And we're done
  return 0;
} // main
