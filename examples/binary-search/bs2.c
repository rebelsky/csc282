/**
 * bs.c
 *   A simple binary search library.
 *
 * Authors: <YOUR NAMES HERE>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "bs.h"
#include <stdio.h>

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

int
binary_search_ints (int v, int a[], int n)
{
  int lower = 0;
  int upper = n;
  int middle;

#ifdef DEBUG
  fprintf (stderr, "binary_search_ints (%d, a[], %d)\n", v, n);
#endif

  // Problem v = 1, a = { 0 }, n = 1 

  // goes through first check comparison
  do
  {
    middle = (upper + lower) / 2;
#ifdef DEBUG
    fprintf (stderr, "middle: %d, lower: %d, upper: %d\n", middle, lower, upper);
#endif

    if (upper <= lower)
    {
      break; // exit loop
    }
    else if (a[middle] == v)
    {
      return middle; // position of answer
    }
    else if (a[middle] < v)
    {
      lower = middle + 1; // new lower bound, inclusive
    }
    else
    {
      upper = middle;     // new upper bound, but exclusive
    }
  } // end of loop
  while (1);
  
  return -1;  
} // binary_search_ints} // binary_search_ints
