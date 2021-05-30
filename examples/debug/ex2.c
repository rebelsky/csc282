#include <stdlib.h>

void
f (int *ip)
{
  int i = *ip;
  free (ip);
  ip = malloc (sizeof (int));
  *ip = i + 1;
}

int 
main (int argc, char *argv[])
{
  int *stuff;
  stuff = malloc (sizeof (int));
  *stuff = 5;
  f (stuff);
  assert (6 == *stuff);
  *stuff = 1;
  assert (1 == *stuff);
  free (stuff);
  return 0;
} // main
