#include <stdio.h>

/**
 * matrix.c
 *   A simple problem to illustrate some issues with matrices
 *   in C, or something like that.
 *
 * <Insert FLOSS license.>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#define COLS 5
#define ROWS 4

// +---------+-------------------------------------------------------
// | Helpers |
// +---------+

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[]) 
{
  int M[ROWS][COLS];

  for (int i = 0; i < ROWS; i++)
  for (int j = 0; j < COLS; j++)
  M[i][j] = (i/j)*(j/i);

  return 0;
} // main
