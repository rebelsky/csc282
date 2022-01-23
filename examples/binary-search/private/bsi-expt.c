/**
 * bsi-expt.c
 *   A quick experiment with binary search of integer arrays.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "bs.h"
#include <stdio.h>      // For printf
#include <stdlib.h>     // For atoi

// +-----------------+-----------------------------------------------
// | Local utilities |
// +-----------------+

void
print_ints (int a[], int n)
{
  printf ("[");
  if (n > 0) 
    {
      printf ("%d", a[0]);
      for (int i = 1; i < n; i++) 
        {
          printf (", %d", a[i]);
        } // for i
    } // if (n > 0)
  printf ("]");
} // print_ints (int[], n)

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  int v;
  int a[argc-2];
  int n = argc - 2;

  // Grab the value.  (No error checking.)
  v = atoi (argv[1]);

  // Grab the array.  (No error checking.)
  for (int i = 2; i < argc; i++) 
    {
      a[i-2] = atoi (argv[i]);
    } // for i

  // Do the search
  int pos = binary_search_ints (v, a, n);
  if (pos == -1) 
    {
      printf ("The value %d could not be found in the array ", v);
      print_ints (a, n);
      printf ("\n");
      return 1;
    } // if (result == -1)
  
  else 
    {
      printf ("%d appears at position %d in ", v, pos);
      print_ints (a, n);
      printf ("\n");
    } // if (result != -1)

  return 0;
} // main(int, char**)
