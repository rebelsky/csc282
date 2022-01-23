/**
 * sizes.c
 *   Some experiments with finding sizes.
 *
 * <Insert FLOSS license here>
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// +---------+-------------------------------------------------------
// | Helpers |
// +---------+

/**
 * Print a bit of info.
 */
void
helper (char *name, char *str)
{
  printf ("helper: sizeof(%s) = %d\n", name, (int) sizeof (str));
  printf ("helper: strlen(%s) = %d\n", name, (int) strlen (str));
  printf ("\n");
} // helper (char *, char *)

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  char *s1 = malloc(128);
  char s2[64];
  char *s3 = "this is a string";
  char *s4 = s2;

  printf ("sizeof(s1) = %d\n", (int) sizeof (s1));
  printf ("strlen(s1) = %d\n", (int) strlen (s1));
  helper ("s1", s1);

  printf ("sizeof(s2) = %d\n", (int) sizeof (s2));
  printf ("strlen(s2) = %d\n", (int) strlen (s2));
  printf ("s2: \"%s\"\n", s2);
  helper ("s2", s2);

  printf ("sizeof(s3) = %d\n", (int) sizeof (s3));
  printf ("strlen(s3) = %d\n", (int) strlen (s3));
  helper ("s3", s3);

  printf ("sizeof(s4) = %d\n", (int) sizeof (s4));
  printf ("strlen(s4) = %d\n", (int) strlen (s4));
  helper ("s4", s4);


  return 0;
} // main(int, char*[])
