/**
 * arguments.c
 *   A simple example of argument processing in C.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <string.h>

// +----------+------------------------------------------------------
// | Contants |
// +----------+

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
// | Helpers |
// +---------+

// Deal with strings that appear by themselves (e.g., representing
// the input file)
void
set_infile (char *str)
{
  if (! str)
    {
      fprintf (stderr, "Null string provided as input file.  Bad user.\n");
      ++errors;
    }
  else if (num_infiles >= MAX_INFILES)
    {
      fprintf (stderr, 
               "You cannot have that many infiles.  Discarding %s\n",
               str);
      ++errors;
    } 
  else
    infiles[num_infiles++] = str;
} // str

void
process_command_line (int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
    {
      char *argument = argv[i];
      // Sanity check: Make sure the argument is not null.
      if (! argument) continue;

      // Sanity check: Make sure the argument is not empty
      if (! argument[0]) continue;

      // Determine the type of the argument
      if ('-' == argument[0])
        {
          if ('-' == argument[1])
            {
              // Handle the word-based command-line flags, e.g., --help
              // We shouldn't use strings for switches.
              // Option 1: Do a switch with the first character
              // Option 2: Do a bunch of if statements.
              if (! strcmp (argument, "--help"))
                {
                  printf ("There is no help.\n");
                }
              else if (! strcmp (argument, "--version"))
                {
                  printf ("Version 3+4i\n");
                }
              else if (! strcmp (argument, "--verbose"))
                {
                  verbose = 1;
                }
              else 
                {
                  fprintf (stderr, 
                           "I have no idea what %s means.\n", 
                           argument);
                  ++errors;
                }

            }
          else if (! argument[1]) // same as (0 == argument[1])
            {
              // Handle the "-" command-line option, which we
              // often interpret as "the next thing is an input
              // file".
              set_infile (argv[++i]);
            } 
          else
            {
              // Handle the single-letter command-line flags
              // int s = strlen (argument);
              // for (int j = 1; j < s; j++)
              for (char *ch = argument+1; *ch; ++ch)
                {
                  switch (*ch)
                    {
                      case 'h':     // Help
                        printf ("This program is helpless\n");
                        break;
                      case 'i':     // Infile
                        if (i+1 == argc) 
                          {
                            fprintf (stderr, "-i flag w/o file\n");
                            ++errors;
                          }
                        else
                          {
                            // Note: We need to skip the next argument
                            set_infile (argv[++i]);
                          }
                        break;
                      case 'o':     // Outfile
                        break;
                      case 's':     // Strange
                        strange = 1;
                        break;
                      case 'v':     // Verbose
                        verbose = 1;
                        break;
                      default:
                        fprintf (stderr, "Unrecognized flag: %c\n", *ch);
                        ++errors;
                        break;
                    } // switch
                 } // for
            }
        }
      else // Not a dash argument
        {
          set_infile (argument);
        }
    } // for 
} // process_command_line

void
print_settings ()
{
  if (strange) 
    printf ("Strange mode\n");
  else
    printf ("Other mode\n");
  if (verbose) 
    printf ("Verbose mode\n");
  else
    printf ("Normal mode\n");
  for (int i = 0; i < num_infiles; i++)
    {
      printf ("Input file %d: %s\n", i, infiles[i]);
    }
  printf ("Outfile: %s\n", outfile);
  if (errors)
    {
      printf ("You idiot!  You had %d %s.\n", 
              errors,
              (1 == errors) ? "error" : "errors");
    }
} // print_settings

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
  process_command_line (argc, argv);
  print_settings ();

  // And we're done
  return 0;
} // main

