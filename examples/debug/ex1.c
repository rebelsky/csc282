/**
 * ex1.c
 *   A very simple program that crashes.
 *
 *   Copyright (c) 2013-2021 Samuel A. Rebelsky.  All rights reserved.
 *
 *   This file was once part of the Glimmer Guide to GDB (G^3).
 */


// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>


// +---------+---------------------------------------------------------
// | Globals |
// +---------+

static int *ip;


// +-----------------+-------------------------------------------------
// | Predeclarations |
// +-----------------+

void qux (int i);
void baz (int i);


// +---------+---------------------------------------------------------
// | Helpers |
// +---------+

void
qux (int i)
{
  if ((i <= 1) || ((i % 2) == 1))
    baz (i - 1);
  else
    qux (i / 2);
} // qux

void
baz (int i)
{
  if ((i % 5) == 0)
    *ip = i;
  else
    qux (i);
} // baz


// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  baz (67);
  printf ("Result is %d\n", *ip);
  return 0;
} // main
