/*
 * Solution by Prathik Gowda <gowdapra@grinnell.edu>
 *
 * I used man pages for help
 * 
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *trim(char *);

int
main(int argc, char **argv)
{
  /* checks to see whether we have the correct number of args */
  if (argc != 2)
    {
      fprintf(stderr, "usage: %s <file_name>.txt\n", argv[0]);
      return -1;
    }

  /* opens output for file for writing and checks for errors */
  FILE *out_fp = fopen(argv[1], "w");

  /* variables for getline */
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  /* read from stdin using getline in loop */
  while ((nread = getline(&line, &len, stdin)) != -1)
    {
      /* if user wants to quit, close file and exit */
      if (!strcmp(line, "quit\n") || !strcmp(line, "q\n"))
        {
          fclose(out_fp);
          return 0;
        }

      char *trimmed = trim(line);

      /* print to stdout and file */
      fprintf(stdout, "%s", trimmed);
      fprintf(out_fp, "%s", trimmed);
    }

  if (line != NULL)
    {
      free (line);
    }

  fclose(out_fp);
  return 0;
}

/* trims the given inp string and returns it */
char *
trim(char *inp)
{
  char *end = inp + strlen(inp) - 1; /* pointer to end of inp */

  /* while there is a space at end, move back by one char */
  while (end >= inp && isspace(*end))
    end--;

  /* 
   * when we have exited the loop, that means we hit a non-space. thus we can
   * put null character after to remove the spaces
   */
  *(end + 1) = '\n';
  *(end + 2) = '\0';

  return inp;
}

