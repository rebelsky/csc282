/**
 * time2-expmod.c
 *   A quick and dirty hack to help us check the efficiency of expmod.
 */

/* Victims
*/

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <sys/time.h>   // struct timespec
#include <time.h>       // clock_gettime()
#include <stdio.h>
#include <limits.h>
#include "expmod.h"

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#define BASE 13
#define MODULUS 61213675

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  struct timespec start;
  struct timespec finish;

  for (long expt = 1; expt < LONG_MAX/2; expt *= 2)
    {
      // Start the timer
      if (clock_gettime (CLOCK_MONOTONIC, &start))
        { 
          fprintf (stderr, "Could not get start time.\n");
          return 1;
        }
      // Do the calculation
      long result;
      result = expmod (BASE, expt, MODULUS);
      // End the time
      if (clock_gettime (CLOCK_MONOTONIC, &finish))
        { 
          fprintf (stderr, "Could not get end time.\n");
          return 2;
        }
      // Compute the difference
      long elapsed = 1000000000*(finish.tv_sec - start.tv_sec) +
                     (finish.tv_nsec - start.tv_nsec);
      // Print the info
      fprintf (stdout, "%ld,%ld,%ld\n", expt, elapsed, result);
    } // for

  return 0;     // Success!
} // main
