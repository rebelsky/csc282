---
title: "EBoard 09: Make and Makefiles, continued (+ Macros)"
number: 9
section: eboards
held: 2022-03-17
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Reminder of where we were
* Our Make project, continued
    * Cleanup
    * Adding a second utility function
    * Adding variables
    * Adding automatic variables
    * Adding generic rules
* The C Preprocessor (if there's time)

Administrivia
-------------

* Happy Thursday!
* I hope you all had amazing breaks.
* Non-seniors: 
    * We do have another special topics course in the spring.
    * If we hire a visitor, we'll have more offerings.
* For next week, skim the GNU C preprocessor manual.
* Note: Until you write your own Makefiles (or whatever), you won't
  retain much of this info.  But you'll know what's possible, which
  will help you look for things.
* We miss all of you who are absent.

Where we were
-------------

* We were building a Makefile for a simple math library.
* The library is in [`examples/srmath`](../examples/srmath)
* In addition to the library, we were building tests and an executable.
* After writing some basic instructions, we also added some default targets.

```
# SRMath's not-so-amazing Makefile

# gcd.c gcdtest.c Makefile srgcd.c srmath.h srtest.c srtest.h testdemo.c

default: executables library

clean:
        rm -f *.o

distclean: clean
        rm -f libsrmath.so gcd gcdtest

# +---------+--------------------------------------------------------
# | Library |
# +---------+

library: srmath.so

srmath.so: srgcd.o
        cc srgcd.o -shared -o libsrmath.so

# +-------------+----------------------------------------------------
# | Executables |
# +-------------+

executables: gcdtest gcd

gcdtest: gcdtest.o srgcd.o srtest.o
        cc gcdtest.o srgcd.o srtest.o -o gcdtest

gcd: gcd.o srgcd.o
        cc gcd.o srgcd.o -o gcd

# +--------------+---------------------------------------------------
# | Object Files |
# +--------------+

gcd.o: gcd.c srmath.h
        cc -c gcd.c -o gcd.o    

srgcd.o: srgcd.c srmath.h
        cc -c srgcd.c -o srgcd.o        

gcdtest.o: gcdtest.c srmath.h srtest.h
        cc -c gcdtest.c -o gcdtest.o    

srtest.o: srtest.c srtest.h
        cc -c srtest.c -o srtest.o
```

Cleaning up our code
--------------------

Adding a second utility function
--------------------------------

Suppose we wanted a second utility function.  We're going to build
`expmod(long x, int n, long m)`, which computes `(x^n modulo m)`.

Who knows how to write that procedure?

Adding variables
----------------

Suppose we wanted to set the flags for the C compiler.  How many
lines do we have to change?

What else about the Makefile makes you cringe a bit?

Adding automatic variables
--------------------------

$@ the target
$^ the dependencies
$< the first dependency

Using generic rules
-------------------

How do we say "To build a .o file from a .c file, do the following"?  (or
anything similar)

Macros
------

* Somewhat like functions, except that they work at compile time, with
  program text, rather that an run time, with real values.
* `#define NAME(PARAMS) CODE`

