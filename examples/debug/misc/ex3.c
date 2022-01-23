/**
 * YA example.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>

// +---------+-------------------------------------------------------
// | Globals |
// +---------+

long *stuff;
long *more;

// +---------+-------------------------------------------------------
// | Helpers |
// +---------+

void
foo (int n)
{
  stuff = (long *) malloc (n * sizeof (long));
} // foo  

void
bar (int n)
{
  more = (long *) malloc (n * sizeof (long));
  for (int i = -10; i < 10; i++)
    more[i] = -1;
  free (more);
} // bar

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  foo (1024);
  bar (1024);
  free (stuff);
} // main
