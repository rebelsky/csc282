/**
 * sq-example-00
 *   A simple example of string queues.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include "sq.h"

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  SQ *q = sq_new ();
  for (int i = 1; i < argc; i++)
    {
      if (! sq_enqueue (q, argv[i]))
        {
          fprintf (stderr, "Could not enqueue element %d: '%s'\n", i, argv[i]);
        }
    } // for
  printf ("There are now %d elements in the queue.\n", sq_size (q));
  char *str;
  while ((str = sq_dequeue (q)))
    {
      printf ("Removed '%s'\n", str);
      printf ("  %d elements remain.\n", sq_size (q));
    } // while
  sq_free (q);
} // main
