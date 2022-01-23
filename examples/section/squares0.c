/**
 * A silly example of writing similar functions.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>

// +-----------+-----------------------------------------------------
// | Utilities |
// +-----------+

int 
isquare (int x)
{
  return x*x;
} // isquare

double
dsquare (double x)
{  
  return x*x;
} // dsquare

long
lsquare (long x)
{
  return x*x;
} // lsquare

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  int i = isquare (5);
  double d = dsquare (5.5);
  long l = lsquare (5555555555);
  return 0;
} // main
