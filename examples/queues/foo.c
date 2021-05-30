// Test program for eeedeeecdd
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sq.h"

int
main (int argc, char *argv[])
{
  SQ *q = sq_new ();
  assert (q);
  assert(sq_enqueue (q, "Alpha"));
  assert(sq_enqueue (q, "Bravo"));
  assert(sq_enqueue (q, "Charlie"));
  assert (! strcmp ("Alpha", sq_dequeue (q))); // Alpha
  assert(sq_enqueue (q, "Delta"));
  assert(sq_enqueue (q, "Echo"));
  assert(sq_enqueue (q, "Foxtrot"));
  sq_free (q);
  q = sq_new ();
  assert (q);
  assert (NULL == sq_dequeue (q)); // (null)
  assert (NULL == sq_dequeue (q)); // (null)
} // main
