/**
 * time-expmod.c
 *   A quick and dirty hack to help us check the efficiency of expmod.
 */

/* Victims
*/

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
#include "expmod.h"

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  struct timeval start;
  struct timeval finish;

  for (long expt = 1; expt < LONG_MAX/2; expt *= 2)
    {
      // Start the timer
      if (gettimeofday (&start, NULL)) 
        { 
          fprintf (stderr, "Could not get start time.\n");
          return 1;
        }
      // Do the calculation
      long result;
      for (int i = 0; i < 100; i++)
        {
          result = expmod (13, expt, 612131675);
        }
      // End the time
      if (gettimeofday (&finish, NULL)) 
        { 
          fprintf (stderr, "Could not get end time.\n");
          return 2;
        }
      // Compute the difference
      long elapsed = 1000000*(finish.tv_sec - start.tv_sec) +
                     (finish.tv_usec - start.tv_usec);
      // Print the info
      fprintf (stdout, "%ld,%ld,%ld\n", expt, elapsed, result);
    } // for

  return 0;     // Success!
} // main
