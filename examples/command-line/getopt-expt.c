/**
 * A simple experiment to help us understand how `getopt` functions.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <unistd.h>

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#ifndef MAX_INFILES
#define MAX_INFILES 4
#endif

// +---------+-------------------------------------------------------
// | Globals |
// +---------+

static int verbose = 0;         // -v or --verbose
static int strange = 0;         // -s or --strange
static char *outfile = NULL;    // -o or --output
static char *infiles[MAX_INFILES];
static int num_infiles = 0;
static int errors = 0;

// +---------+-------------------------------------------------------
// | Victims |
// +---------+

/*
"Erik D. Nelson" <nelsoner@grinnell.edu>
"Justin Richard" <richardj@grinnell.edu>
"Brady Zheng" <zhengyun@grinnell.edu>
"Marty S. Allen" <allenmar2@grinnell.edu>
"Moiz A. Yousufi" <yousufim@grinnell.edu>
"Ben P. Mikek" <mikekben@grinnell.edu>
"Nèd Watson" <learned.watson@protonmail.com>
"Amisha Pershad" <pershada@grinnell.edu> 
"Priyank R. Shah" <shahpriy@grinnell.edu>
*/

// +-----------+-----------------------------------------------------
// | Utilities |
// +-----------+

void
getopt_dump ()
{
  printf ("  optarg: %s, optind: %d, optopt: %d, opterr: %d, optreset: %d\n",
          optarg, optind, optopt, opterr, optreset);
}

void
process (int argc, char *argv[], char *options)
{
  opterr = 0;
  int result;
  do
    {
      result = getopt (argc, argv, options);
      printf ("  getopt returned %d\n", result);
      getopt_dump();
    }
  while (-1 != result);
} // process

void 
reset()
{
  optind = 1;
  optreset = 1;
}

void
printargs (int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    printf ("%2d: %s\n", i, argv[i]);
} // printargs

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  char *fakeargv[] = { "fake", "-i", "other", "-v", "-f", "pizza", "-s" };
  int fakeargc = sizeof (fakeargv) / sizeof (char *);

  printf ("Fake arguments\n");
  printargs (fakeargc, fakeargv);
  printf ("Real arguments\n");
  printargs (argc, argv);

  char *paramses[] = { "f", "fx", "svi:ho:" };
  int num_paramses = sizeof (paramses) / sizeof (char *);

  getopt_dump();

  for (int i = 0; i < num_paramses; i++)
    {
      char *params = paramses[i];

      reset ();
      printf ("\nProcessing original arguments with only %s\n", params);
      process (argc, argv, params);

      reset ();
      printf ("\nProcessing fake arguments with only %s\n", params);
      process (fakeargc, fakeargv, params);
    }

  // And we're done
  return 0;
} // main
