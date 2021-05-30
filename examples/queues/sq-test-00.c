/**
 * sq-test-00
 *   A simple test of string queues.
 *   If provided with an argument like "eedespd", it executes it
 *     as a series of commands (and prints out a program for
 *     the script, because I believe in overkill)..
 *   If not provided with such an argument, it generates a randomized
 *     series of commands and attempts to execute them.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sq.h"
#include "sample-strings.h"

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

#define MAX_COMMANDS 128

// +--------+--------------------------------------------------------
// | Macros |
// +--------+

#define GIVE_UP(VAL)                                            \
  do                                                            \
    {                                                           \
      commands[cmd] = 0;                                        \
      if (verbose) { fprintf (stdout, "}\n"); }                 \
      fprintf (stderr, "%s %s\n", argv[0], commands);           \
      return VAL;                                               \
    }                                                           \
  while (0)

// +------+----------------------------------------------------------
// | Main |
// +------+

int
main (int argc, char *argv[])
{
#ifdef VERBOSE
  int verbose = 1;
#else
  int verbose = 0;
#endif // verbose

  int len = sizeof (STRINGS) / sizeof (char *);
  int next = 0;         // Index of next string to add
  int expected = 0;     // Index of the next string we expect
  int cmd = 0;          // Which command are we executing?
  char commands[MAX_COMMANDS+1];
  int max_commands = MAX_COMMANDS;

  // Special case: We have a list of commands to execute (argv[1])
  if (argc > 1) 
    { 
      max_commands = strlen (argv[1]); 
      verbose = 1;
      fprintf (stdout, "// Test program for %s\n", argv[1]);
      fprintf (stdout, "#include <stdio.h>\n");
      fprintf (stdout, "#include <assert.h>\n");
      fprintf (stdout, "#include <stdlib.h>\n");
      fprintf (stdout, "#include \"sq.h\"\n");
      fprintf (stdout, "\n");
      fprintf (stdout, "int\n");
      fprintf (stdout, "main (int argc, char *argv[])\n");
      fprintf (stdout, "{\n");
      fprintf (stdout, "  SQ *q = sq_new ();\n");
      fprintf (stdout, "  assert (q);\n");
    } // if

  srandomdev();

  // Initialize the queue
  SQ *q = sq_new ();
  if (!q)
    {
      fprintf (stderr, "Could not set up the queue.\n");
      return 1;
    }

  // Keep going as long as we can do things
  while ((next < len) && (cmd < max_commands))
    {
      // Get the next command
      char command;
      if (argc > 1) 
        { 
          command = argv[1][cmd];  
        }
      else
        {
          int r = random() % 5;
          command = "eespd"[r];
        }
      commands[cmd++] = command;

      // Execute the command
      int size = next - expected;
      char *str;
      int tmp;

      switch (command) 
        {
          case 'c':     // Clear
            if (verbose)
              {
                fprintf (stdout, "  sq_free (q);\n");
                fprintf (stdout, "  q = sq_new ();\n");
                fprintf (stdout, "  assert (q);\n");
              }  
            sq_free (q);
            expected = next;
            q = sq_new ();
            if (! q)
              {
                fprintf (stderr, "Could not create a new queue.\n");
                GIVE_UP (1);
              }
            break;

          case 'e':     // Enqueue
            str = (char *) STRINGS[next++];     
            if (verbose) 
              {
                fprintf (stdout, 
                         "  assert(sq_enqueue (q, \"%s\"));\n", 
                         str);
              }
            if (! sq_enqueue (q, str))
              {
                fprintf (stderr, "Failed to enqueue \"%s\"\n", str);
                GIVE_UP (2);
              } // if
            break;

          case 's':     // Size
            tmp = sq_size (q);
            if (verbose) 
              {
                fprintf (stdout, 
                         "  assert (%d == sq_size (q)); // %d\n", 
                         size, tmp);
              }
            if (tmp != size)
              {
                fprintf (stderr, "Incorrect size: Expected %d, got %d\n",
                         size, tmp);
                GIVE_UP (3);
              }
            break;
            
          case 'p':     // Peek
            str = sq_peek (q);
            if (verbose) 
              {
                if (size)
                  {
                    fprintf (stdout, 
                             "  assert (! strcmp (\"%s\", sq_peek (q))); // %s\n", 
                             STRINGS[expected], str);
                  }
                else
                  {
                    fprintf (stdout,
                             "  assert (NULL == sq_peek (q)); // %s\n",
                             str);
                  } // else
              }
            if ((size > 0) && (!str))
              {
                fprintf (stderr, "Peek unexpectedly returned NULL\n");
                GIVE_UP (4);
              }
            if ((size == 0) && str)
              {
                fprintf (stderr, 
                         "Peek unexpectedly returned non-NULL (%s)\n",
                         str);
                GIVE_UP (5);
              }
            if ((size > 0) && (strcmp (str, STRINGS[expected])))
              {
                fprintf (stderr, "Peek failed: Expected %s, got %s\n",
                         str, STRINGS[expected]);
                GIVE_UP (6);
              }
            break;

          case 'd':       // Dequeue
            str = sq_dequeue (q);
            if (verbose) 
              {
                if (size)
                  {
                    fprintf (stdout, 
                             "  assert (! strcmp (\"%s\", sq_dequeue (q))); // %s\n", 
                             STRINGS[expected], str);
                  }
                else
                  {
                    fprintf (stdout,
                             "  assert (NULL == sq_dequeue (q)); // %s\n",
                             str);
                  } // else
              }
            if ((size > 0) && (!str))
              {
                fprintf (stderr, "Dequeue unexpectedly returned NULL\n");
                GIVE_UP (7);
              }
            if ((size == 0) && str)
              {
                fprintf (stderr, 
                         "Dequeue unexpectedly returned non-NULL (%s)\n",
                         str);
                GIVE_UP (8);
              }
            if ((size > 0) && (strcmp (str, STRINGS[expected])))
              {
                fprintf (stderr, "Dequeue failed: Expected %s, got %s\n",
                         str, STRINGS[expected]);
                GIVE_UP (9);
              }
            if (size > 0) ++expected;
            break;

          default:
            fprintf (stderr, "Invalid command: %c\n", command);
            break;
        } // switch
    } // while

  if (verbose) fprintf (stdout, "} // main\n");

  sq_free (q);

  return 0;
} // main
