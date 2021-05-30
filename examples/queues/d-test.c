#include <stdio.h>
#include <assert.h>
#include "sq.h"

int
main (int argc, char *argv[])
{
  SQ *q = sq_new ();
  assert (0 == sq_size (q));
  assert (sq_enqueue (q, "Alpha"));
  assert (sq_enqueue (q, "Beta"));
  sq_free (q);
  q = sq_new ();
  printf ("size of new queue is %d\n", sq_size (q));
  assert (0 == sq_size (q));
  return 0;
} // main
