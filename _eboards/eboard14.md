---
title: "EBoard 14: Wrapping up"
number: 14
section: eboards
held: 2021-05-20
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Preliminaries
    * Administrative stuff
    * Q&A
* `getopt`
* Break
* `getopt_long`
* Time to fill out evaluations. (4:30-4:45)
* Final notes

Administrative stuff
--------------------

### General Notes

* Happy Thursday!  We're almost done!  It's almost the last class of
  the term.
* I've turned in grades for the class.  You all pass.  Congrats.
* Things I forgot to mention: Alfred Aho, who wrote the original
  version of `egrep` and whose research stimulated `lex` and `yacc`,
  won the 2020 Turing award.  He also worked on `awk`.  (Jeff Ullman,
  who worked with him on the research, shared the award with him.)
* I was sharing my screen yesterday and someone asked "Why does it
  say 'You idiot' repeatedly in that terminal window in the background?"

### Upcoming Activities

* Recording of Teach-in on Myanmar
  <https://www.youtube.com/watch?v=FPvOBSU5-rM>
* Thursday CS Extra: A constrained K-Means clustering algorithm for 
  improving the energy efficiency of many-core systems.
  In the CS Events channel immediately after class.

### Work for the future

* Write your own `malloc`
* Keep playing
* Keep experimenting
* Build your toolkits
* Send email (or whatever)

Q&A
---

Accumulated Side Notes
----------------------

Our program from last time is deficient in that we sometimes have
multiple blocks of code responding to "the same flag" (or at least
the same meaing of flag).

In C programs, `extern` means "this is a variable that exists
somewhere in memory, but I'm not declaring it in this file."  The
linker is responsible for figuring out where it is (where to put
it) and updating the reference.

    file1.c
        int x;
        static int y;

    file2.c
        extern int x;
        static int y;

    +-----+ The Stack
    |     | 
    +-----+
    |     |
    +-----+
    |     |
    +-----+
    |     |
    +-----+
    |     |

    |     |
    +-----+
    |     |
    +-----+ The Heap
    |     |


    |     |
    +-----+
    |     |
    +-----+
    |     | file2.y
    +-----+
    |     | file1.y
    +-----+ 
    |     | x
    +-----+
    |     |
    +-----+
    |     |
    +-----+ "Fixed memory"

Given `char *fakeargv[] = { "-i", "other", "-v", "-f", "-s" };`, how
do we find out how many things are in the array?

> Put a `null` at the end and iterate the array.

> Do it manually.

> In this context, it knows the size of fakeargv, so you can write
  `char *fakeargv[] = { "-i", "other", "-v", "-f", "-s" };`

How does that work?

        char *strs = [ "a", "alphabet", "b" ];
   
    001c|b0   |
        +-----+
    0018|0    |
        +-----+ 
    0014|abet |
        +-----+
    0010|alph |
        +-----+ 
    000c|a0   |
        +-----+
    0008|001c |
        +-----+ 
    0004|0010 |
        +-----+
    0000|000c | arr
        +-----+ "Fixed memory"

`arr` stores three pointers, the length of what they point to is
irrelevant in the calculation.  The amount of memory allocated to
the array is just the three pointers.  (In some languages, the size
of the array is also stored somewhere, often at arr[-1].)

Command-line processing with libraries
--------------------------------------

* Don't reinvent the wheel!
* Even if the language doesn't include a library for it, some group
  will often develop one and it becomes common use.
* Some overly opinionated people, like SamR, object to the design of
  common libraries and design their own.

### Design decisions

* Does the library process all the command line at once, or just "the
  next part of the command line"?
* How do we convey information about what we expect on the command line
  to the library?
    * When you see this flag/these flags, call this code?
    * When you see this flag/these flags, fill in this variable?
    * ....
* How does the library convey information back to the programmer.
* How do we deal with flag arguments?  `-i infile` (`-iinfile`)
* What command-line behavior do we expect?  Do we believe that we
  should be able to pull arguments into one big `-asdfdasdf`?
* Some designers might attempt to support multiple techniques.
* Most focus on a few particular approaches.

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

A bit different than what you normally see.  Normally you just get
"This is what to include" and "This is the signature".  Here, we also
see a list of shared/global variables.

     The getopt() function incrementally parses a command line argument list
     argv and returns the next known option character.  An option character is
     known if it has been specified in the string of accepted option charac-
     ters, optstring.

### Questions:

If "The getopt() function returns the next known option character in
optstring", why does `getopt` return an `int` rather than a `char`?

> It's a custom in C to have some functions return `int` rather than
  `char`, such as `getchar` and `getc`.  That way, we can return -1
  as a value that says "No such character!"

> `getopt` should return -1 to suggest "did not find any specified
  command-line flags"

```
$ ./getopt-expt 
getopt returned -1
$ ./getopt-expt -f
./getopt-expt: illegal option -- f
getopt returned 63
$ ./getopt-expt -v
getopt returned 118
```

What are the 63 and 118?

> ASCII codes for `?` (63) and `v` (118)

```
$ ./getopt-expt -g
./getopt-expt: illegal option -- g
getopt returned 63
```

> It appears we get 63 (`?`) for "illegal option"


What are all those other variables?

     extern char *optarg;

"On return from getopt(), optarg points to an option argument, if it is
anticipated"

     extern int optind;

"the variable optind contains the index to the next argv argument
for a subsequent call to getopt()"

The variables opterr and optind are both initialized to 1.  The optind
variable may be set to another value before a set of calls to getopt() in
order to skip over more or less argv entries.

     extern int optopt;

"The variable optopt saves the last known option character returned
by getopt()"

     extern int opterr;

"If the getopt() function encounters a character not found in the string
optstring or detects a missing option argument it writes an error message
to the stderr and returns `?'.  Setting opterr to a zero will disable
these error messages.  If optstring has a leading `:' then a missing
option argument causes a `:' to be returned in addition to suppressing
any error messages."

opterr is a way of communicating to the `getopt` function *without adding
a parameter* to `getopt`.

Without changing `opterr`

    $ ./getopt-expt -x
    ./getopt-expt: illegal option -- x
    getopt returned 63

After setting `opterr` to 0.

    $ ./getopt-expt -x
    getopt returned 63

On to our last parameter ...

    extern int optreset;

"In order to use getopt() to evaluate multiple sets of arguments, or to
evaluate a single set of arguments multiple times, the variable optreset
must be set to 1 before the second and each additional set of calls to
getopt(), and the variable optind must be reinitialized."

Problem: `getopt` has internal state to keep track of where in the
argument list it is.  We use `optreset` to communicate to it to 
start again.

As Schemers, we believe that "the same function call with the same
arguments should produce the same result".  Clearly, that shouldn't
happen with `getopt`.  How do we control / understand state?

> We seem to have learned from our first experiments that `getopt`
  maintains an internal state that we don't quite understand.


Break
-----

Sam assumes we'll need a break about now.  

Understanding `getopt`
----------------------

Sam believes we best understand libraries by writing programs that
use them.  We'll start with a simple program that let us explore
`getopt` on the side.

Look in [`examples/command-line/getopt-expt.c`](../examples/command-line/getopt-expt.c)

```
Fake arguments
 0: fake
 1: -i
 2: other
 3: -v
 4: -f
 5: pizza
 6: -s
```

```
Processing fake arguments with only svi:ho:
  getopt returned 105   ; -i, store other
  optarg: other, optind: 3, optopt: 105, opterr: 0, optreset: 0
  getopt returned 118   ; -v
  optarg: (null), optind: 4, optopt: 118, opterr: 0, optreset: 0
  getopt returned 63    ; -f (invalid)
  optarg: (null), optind: 5, optopt: 102, opterr: 0, optreset: 0
  getopt returned -1    ; Done
  optarg: (null), optind: 5, optopt: 102, opterr: 0, optreset: 0
```

We don't have an easy way to identify the pizza or the -s.  If we
want to process other things differently, we may have to manually
keep track of what is valid and what is not.

Evaluations
-----------

Fill out at `grinnell.smartevals.com`.

Final thoughts
--------------

1. This class was special.  Thank you.

2. Teacher/student relationships.  Drop me a note from time to time.
Or read my musings.  Or both.

3.

