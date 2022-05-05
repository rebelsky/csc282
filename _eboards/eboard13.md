---
title: "EBoard 13: C as interface / Command-line processing"
number: 13
section: eboards
held: 2022-05-05
link: true
---
# {{ page.title }}

* This class will not be recorded, at least not by me.

_Approximate overview_

* Administrative stuff
* C isn't a language
* Command-line processing

Administrivia
-------------

* Happy Thursday!  Also Happy May 5!
* Updates on various department issues.
    * Fingers crossed that something works out.

C isn't (just) a language
-------------------------

_TPS_

<https://gankra.github.io/blah/c-isnt-a-language/>

Who is the audience?

* Teenage hackers?
* Younger (20's) (opinionated) programmers, who like informality
  and profanity.

What are the main points of the article (and, perhaps, any related
articles you read)?

Point one: ABIs

* More than anything, C is an ABI (Application Binary Inteface, duh!)
    * Zeroes and ones
    * Kind of like an API (Application Programmer Interface, the
      list of procedures/objects in a library), but for 
      assemblers/compilers.
    * Agreements on ...
        * How you organize data (e.g., in a struct).
        * How you pass data to a procedure (which registers do I use,
          what order of parameters on the stack, etc.): These depend
          on the type passed.
        * How you get data back from a procedure.
* Because most systems have C hidden somewhere in the dark corners, most
  system calls have a C interface.
* Therefore, whatever language you use has to "understand" the C ABI.

Once upon a time, thoughtful/forward-looking designers could have dealt
with this.  Now so much is ingrained that it's too late to fix things.
We are screwed.

In the end, most language designers end up relying on a hidden C/C++
backend because (a) parsing C sucks and (b) C is used everywhere and
(c) every architecture/C compiler pair may make different decisions
on ABI issues (and there are 176 or so "common" pairs/triplets).

You can't make big changes because (a) there's too much legacy code
out there that you can't break; (b) programmers are slow to update.

So ...

No matter what you have to do, at some time you have to understand some C.

Command-line processing
-----------------------

_TPS_

What is command-line processing?

* When you run a program (command) on the command line, all the things that
  come after the command

What common flags do you know about?  (Are there any common flags?)

* `-o` and a file name, which may represent an output file
    * `foo -ooutput.txt` ; short, no space
    * `foo -o output.txt` ; short, with a space
    * `foo --output output.txt` ; verbose, preferred by non-C folks
* `-a` (for "all", in GitHub, ls, perhaps more)
* `-l` (for "list", if that makes sense in context)
* `-r` (for "recursive", e.g., on directories)
* `-f` (for "force")
* `-v` (for "version" or "verbose")
* `-h` (for "help")
* `-g` (for "guess this means something")

Conclusion: Unix sucks for standardized UI design.

What complications do you anticipate in parsing the command line?

* User can enter things we don't expect.  In those situations, we shold
  probably print an error message and stop.
* Newline characters might be an issue.  `foo -t "a\nb"`
* Too many ways to write the same thing (e.g., -ofoo and -o foo).
* long arguments (the ones with the two dashes and a string).
* Optional parameters
* Combining parameters, as in `tar -xvf`
* Where do we store the information, particularly when it's variable-length
  information?

Historical approaches to command-line processing
------------------------------------------------

Do it by hand (using `argc` and `argv`)!

Task: Write a program that has 

* an optional flag, `-v`, for verbose mode.
* an optional flag, `-o FILE`, for an output file.  (If there is no
  input file, writes to standard output.)
* an optional flag, `-c CHARS`, for a number of characters.  (If `-c` is not 
  specified, use 1.)
* an optional flag, `-h`, which prints out a help message and stops.
* files (0 or more)

Your program should then read all the other files specified on the
command line and print the first CHARS characters of each file to the
specified output file (or standard output, if it exists).

### Breaking up the program.

Normal program template

```
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{

  exit (EXIT_SUCCESS);
} // main
```

Declare setting variables and set defaults

```
  int chars = 1;
  char *outfile = 0;
  int verbose = 0;
```

Validate argc

```
if (argc < 2) 
  {
    fprintf (stderr, "You idiot!  I need more command-line arguments.\n");
    help (argv[0]);
    exit (EXIT_FAILURE);
  }
```

Read the command line

```
for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
      {
        // Optional : Validate number of characters in flag
        // Make a decision based on the character
        switch (argv[i][1])
          {
            case 'v':           // Verbose
              verbose = 1;
              break;
            case 'c':
              chars = atoi (argv[++i]);         // EEECH! 
              // Todo: Add a sanity check that ++i is okay
              // Todo: Make sure that argv[++i] is only digits
              break;
            default:
              fprintf ("Thank you for that helpful parameter which I do not understand, '%s'\n", argv[i]);
              help (argv[0]);
              exit (EXIT_FAILURE);
          } // switch
      } // if
    else
      {
        // We've run out of arguments, break out of the loop
        // Or skip over them
        // Or ...
      } // else
  } // for
```

Question: What if we wanted to support `-c 5` and `-c5`?

```
            case 'c':
              if (argv[i][2] == 0)
                {
                  chars = atoi (argv[++i]);
                }
              else
                {
                  chars = atoi (argv[i] + 2);
                }
              break;
```

Building standardized libraries
-------------------------------

* At some point, most language designers decided to add some way of 
    * (a) accessing the values entered on the command line (e.g., `argc`
      and `argv` in C) and
    * (b) providing information to process the command line.
* In C, `getopt` is the primary library and `getopt_long` is an extended
  version of it.

Here's the declaration of `getopt`

```
int getopt(int argc, char * const argv[],
           const char *optstring);

extern char *optarg;
extern int optind, opterr, optopt;
```

What's going on here?

A sample `getopt` program
-------------------------

Stolen from the `getopt` man page.

```
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  int flags, opt;
  int nsecs, tfnd;

  nsecs = 0;
  tfnd = 0;
  flags = 0;
  while ((opt = getopt (argc, argv, "nt:")) != -1) 
    {
      switch (opt) 
        {
          case 'n':
            flags = 1;
            break;
          case 't':
            nsecs = atoi (optarg);
            tfnd = 1;
            break;
          default: /* '?' */
            fprintf (stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
            exit (EXIT_FAILURE);
        } // switch
    } // while

  printf ("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",
         flags, tfnd, nsecs, optind);

  if (optind >= argc) 
    {
      fprintf (stderr, "Expected argument after options\n");
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
} // main
```
