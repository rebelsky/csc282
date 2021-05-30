---
title: "EBoard 13: Command-line processing"
number: 13
section: eboards
held: 2021-05-18
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Preliminaries
    * Administrative stuff
    * Q&A
* Command-line processing
* Conventions 
* Using libraries
    * getopt
    * getopt_long

Administrative stuff
--------------------

### General Notes

* Happy Tuesday!  Only one more class to go.  (Or at least only one
  more session of CSC-282 to go.)
* Since only two of you attempted the assignment (or at least submitted
  something), we'll be spending class time writing examples to help us
  better understand the libraries.

### Upcoming Activities

* Recording of Teach-in on Myanmar
  <https://www.youtube.com/watch?v=FPvOBSU5-rM>
* Thursday CS Extra: A constrained K-Means clustering algorithm for 
  improving the energy efficiency of many-core systems.
  In the CS Events channel.

### Work for Thursday

* Read ["Learn Vim for the Last Time"](https://danielmiessler.com/study/vim/)
    * I don't necessarily agree with everything Miessler says.
    * You may want to practice, too.
* Consider finding an XKCD about Vim.

Q&A
---

Command-line processing
-----------------------

* In the beginning was the command line.
* In most cases, humans interacted with "interactive" computers by
  typing commands at a terminal and the computer responded in the
  same terminal.
* We do that in Linux all the time.
* When we run a program in Linux (or other command-line interface),
  we may want to convey configuration options to the program.
    * Option 1: The program could prompt us
    * Option 2: The information could be stored in a file.
    * Option 3: We can type the configuration information after the command
    * Option 4: Combinations of the above
    * Option 5: Other things
* The designers of Unix generally favored a combination of options 2
  (general configuration) and 3 (to specify what should happen in the
  particular run).
* Taking input on the command line is better than interactive input in
  many situations.
    * It allows you to run scripts without human intervention
    * For testing, you can give a set of commands to work with a data
      structurees.
    * It's Unix, you can also put all the input in a file and pipe it
      through the program.
* Since C was built to build Unix programs, it needed to provide
  support for command-line processing.

Command-line conventions
------------------------

* The early days were "the Wild West" of Unix command-line interface design
    * Do we use -r or -R for "recursive" (in a program that might recurr)?
    * Do we even use dashes?  Why?
    * How do we address files that start with a dash?
* But conventions have evolved over time.
* Early days, flags would traditionally start with a dash (to distinguish
  them from other kinds of information) and other kinds would not.
    * That creates problems when a filename, for example, starts with
      a dash.
* Unix programmers are lazy, they would rather type -rmf than -r -m -f
* Over time, clarity became a priority over concision.  New practices
  arose.
    * --flag as a way of signalling a flag, rather than, -f or -r or whatever
    * Some folks like `-wordflag` with only one dash.
* We're now in a world which is still a bit wild (and still oriented towards
  the global west)
* Nonetheless, most new programs now support single dash flags, single
  dash compound flags, and double-dash word flags.

What flags have you become accustomed to using / seeing?

* `-v` or `--verbose`: Report information while the program is running
  (frequently to help with tracing problems or errors).
* `-o file` or `--output file`: Name the/an output file
* `-i file` or `--input file`: Name the/an input file.
    * A lot of programs treat any remaining words on the command line
      as the input files.
* `-a`: "All", depending on what all means in the particular context.
* `--version`: Give the version number.  Whoops.  Overlaps verbose.
* `-h` or `--help`: Give help or options.

And some less common ones

* `-p` or `--pipe`: Print to standard output

Command-line processing in C
----------------------------

```
int
main (int argc, char *argv[])
{
} // main
```

* `argc` is the number of command-line parameters (including the command)
* `argv` is the parameters themselves as strings

```
int
main (int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    {
      printf ("%2d: %s\n", i, argv[i]);
    } // for i

  // And we're done
  return 0;
} // main
```

```
$ ./printargs -r hello world -f 23
```

How big is argc?  6!

```
$ ls H*
Hello world     Hi
```

How big is argc?  3

What do you expect the output to be?

        0: ./printargs
        1: Hello world
        2: Hi

Possibility

        0: ./printargs
        1: H*

We got

```
$ ./printargs H*
 0: ./printargs
 1: Hello world
 2: Hi
```

Note: the H* is expanded by the shell and the different file names are
passed to the printargs procedures as separate "arguments".

* Sam occasionally gets glitches in his programs where the files with
  spaces get separated.

Detours
-------

Many C programmers write the test as `(CONSTANT == EXP)` rather than than
`(EXP == CONSTANT)` because history suggests that we sometimes forget an
equals sign, and, say, `(x = 2)` is a legal test.  However, `(2 = x)` is
invalid and the compiler tells you that.

In C, && is processed left to right and does short-circuit evaluation,
so we can safely write.

Many people write `(! var)` rather than `(0 != var)` or `(NULL != var)`.

`for (int j = 1; j < strlen (argument); j++)` is inefficient, since it
requires us to call `strlen` multiple times.

Processing the command line
---------------------------

See our sample code in [`examples/command-line/arguments.c`](../examples/command-line/arguments.c).

It was not possible to record the design discussions.

Command-line processing with libraries
--------------------------------------

* Don't reinvent the wheel!

### Design decisions

`getopt`
--------

From the man page ...

     #include <unistd.h>

     extern char *optarg;
     extern int optind;
     extern int optopt;
     extern int opterr;
     extern int optreset;

     int
     getopt(int argc, char * const argv[], const char *optstring);

### Questions:

If "The getopt() function returns the next known option character in
optstring", why does `getopt` return an `int` rather than a `char`?

As Schemers, we believe that "the same function call with the same
arguments should produce the same result".  Clearly, that shouldn't
happen with `getopt`.  How do we control / understand state?

### Understanding getopt

Sam believes we best understand libraries by writing programs that
use them.  We'll start with some simple programs that let us explore
`getopt`.

Break
-----

Sam assumes we'll need a break about now.  We may have to continue
the `getopt` example after break.

`getopt-long`
-------------

Not as much of a standard

From the man page

     #include <getopt.h>

     extern char *optarg;
     extern int optind;
     extern int optopt;
     extern int opterr;
     extern int optreset;

     int
     getopt_long(int argc, char * const *argv, const char *optstring,

     const struct option *longopts, int *longindex);

       struct option {
           char *name;
           int has_arg;
           int *flag;
           int val;
       };

