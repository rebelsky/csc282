/**
 * ex3.c
 *  Yet another debugging or memory exercise.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  int *ip = (int *) malloc (sizeof (int));
  int *jp = ip;
  *jp = 5;
  // free (ip);
  assert (5 == *jp);
  ip = (int *) malloc (sizeof (int));
  *ip = 11;
  assert (5 == *jp);
  return 0;
} // main 
