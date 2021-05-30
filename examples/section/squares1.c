/**
 * A silly example of writing similar functions.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>

// +---------+-------------------------------------------------------
// | Globals |
// +---------+

int squareCount = 0;

// +-----------+-----------------------------------------------------
// | Utilities |
// +-----------+

#define TYPE int
#define NAME isquare
#include "square.c"
#undef TYPE
#undef NAME

#define TYPE double
#define NAME dsquare
#include "square.c"
#undef TYPE
#undef NAME

#define TYPE long
#define NAME lsquare
#include "square.c"
#undef TYPE
#undef NAME


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
