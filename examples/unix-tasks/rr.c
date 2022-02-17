/**
 * Strip all the \r's from a file.
 *
 * The CSC282 Collective.
 *
 * <Insert Arbitrary FLOSS license>
 */

#include <stdio.h>

int
main (int argc, char *argv[])
{
  int ch;
  while ((ch = fgetc (stdin)) != EOF)
    {
      if ('\r' != ch)
        fputc (ch, stdout);
    } // while
  return 0;
} // main
