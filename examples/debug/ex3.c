/**
 * example.c
 *   An example for our discussions.
 */

// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <assert.h>
#include <stdio.h>

// +---------+---------------------------------------------------------
// | Helpers |
// +---------+

/**
 * Allocate an array.
 */
void
vals (int *result[])
{ 
  int values[10];
  *result = values;
} // vals

/**
 * A function that fills in some values in an array.
 */
void
f (int n)
{ 
  int i;
  int values[10]; 
  for (i = 0; i < 10; i++)
    { 
      values[i] = n;
      assert(values[i] == n);
    } // for
} // f

// +------+------------------------------------------------------------
// | Main |
// +------+
int
main (void)
{
  int *stuff;
  vals (&stuff);
  stuff[0] = 42;
  f (5);
  assert (42 == stuff[0]);
  return 0;
} // main

