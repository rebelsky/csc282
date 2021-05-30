/**
 * srtest.c
 *   Implementation of SamR's simple testing utilities.
 *
 *   Copyright (c) 2013-21 Samuel A. Rebelsky.  All rights reserved.
 *
 *   This file is part of SRTest, SamR's simple testing utilities.
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


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>      // For fprintf, FILE, and such.

#include "srtest.h"     // Make sure that internal matches external.


// +-----------+-------------------------------------------------------
// | Variables |
// +-----------+

int sr_tests = 0;

int sr_errors = 0;


// +--------------------+----------------------------------------------
// | Exported Functions |
// +--------------------+

int 
sr_check_long (FILE *ERR, char *expstr, long exp, long val)
{
  ++sr_tests;
  if (exp == val)
    {
      return 1;
    } // if (exp == val)
  else
    {
      ++sr_errors;
      if (ERR)
        {
          fprintf (ERR, "For '%s', expected %ld, got %ld.\n",
                   expstr, val, exp);
        } // if there's a designated output.
      return 0;
    } // if (exp != val)
} // sr_check_long

int
sr_get_errors (void)
{
  return sr_errors;
} // sr_get_errors ()

void
sr_report (FILE *port)
{
  fprintf (port, "%d tests conducted; %d tests failed.\n",
           sr_tests, sr_errors);
} // sr_report(FILE *)

void
sr_reset ()
{
  sr_tests = 0;
  sr_errors = 0;
} // sr_reset
