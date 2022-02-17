#include <stdio.h>

int
main (int argc, char *argv[])
{
  int ch;
  while ((ch = fgetc (stdin)) != EOF)
    {
      if (('a' <= ch) && (ch <= 'z'))
        fputc (ch-32, stdout);
      else
        fputc (ch, stdout);
    } // while
  return 0;
} // main
