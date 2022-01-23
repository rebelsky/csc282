/**
 * bs.c
 *   A simple binary search library.
 *
 * Authors: Anonymized to protect the awesome
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "bs.h"
#include <stdio.h>

// +---------------+-------------------------------------------------
// | Local Helpers |
// +---------------+


int
binary_search_ints_helper (int v, int a[], int lb, int ub)
{
  fprintf (stderr, "binary_search_ints_helper (%d, a[], %d, %d)\n",
           v, lb, ub);

  int index = (lb+ub) / 2;

  if (lb == ub)
  {
    return -1;
  }
  if (a[index] == v )
  {
    return index;
  }
  else if (v > a[index]) 
  {
    return binary_search_ints_helper(v, a, index, ub);
  }
  else 
  {
    return binary_search_ints_helper(v, a, lb, index);
  }
} // binary_search_ints_helper

// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

int
binary_search_ints (int v, int a[], int n)
{
  fprintf (stderr, "v is %d, n is %d\n", v, n);
  return binary_search_ints_helper(v, a, 0, n);
} // binary_search_ints
