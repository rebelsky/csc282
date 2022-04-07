---
title: "EBoard 08: Make and Makefiles"
number: 8
section: eboards
held: 2022-03-17
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Review
    * Why does Make exist?
    * The (approximate) stages of (C) compilation
    * Some standard C project components
    * The (basic) form of a Makefile
* A Make project
    * Doing without make
    * A basic Makefile
    * Adding variables
    * Adding automatic variables
    * Adding generic rules

Administrivia
-------------

* Sorry for last week (and the week before).
* I hope most of you are well.
* I own way too many copies of _Weapons of Math Destruction_ for Kindle.
  If you'd like one, let me know.

### Spring break PSA

* Please take of yourselves (and others).
* Moderation in all (except sleep).
* If possible, take time to relax.
* Consent is essential.
* Mask when you return.

### Upcoming work

* Some reading.
* Optional: Practice making a makefile.

Background: Why `make`?
-----------------------

SE context: 

* We tend to break big projects up into smaller pieces.
* We need instructions on how to assemble those small pieces.
* We have dependencies that we need to pay attention to
  (if X changes, I need to rebuild Y)

Historical context:

* Computer scientists like to automate.
* If we have a series of instructions and notes on dependencies, we should
  be able to automate the building of projects by putting those instructions
  and notes in a specified format, and having a program control it all.
* CC: If we do work by hand, we should be able to have the computer observe 
  us and build the appropriate series of instructions and notes on dependencies.
    * It will probably do better than we do.
* Part of the early C/Unix development included a program called "Make"
  that helps "automate" the building of larger programs (provided you
  provide the information in a particular format).
* There are newer build systems.
    * Ant/Maven were popular for Java
    * Many IDEs now include a build system (and a static analyzer)
* Nonetheless, Make remains useful.

Review: C compilation steps
---------------------------

_What happens between the C code and the executable?_

(We'll consider both traditional compilation and more modern compilation.)

We want to go from foo.c to the foo executable, paying attention to all
the steps.

* Step one, run the C preprocessor. (preprocessing)
    * Replaces `#define`'d names with the corresponding text.
    * Replaces macros with the corresponding macro text.
    * Inserts any file that has been `#include`'d
    * Handles `#ifdef` sections.
* Step two, turn the C program into assembly code. (translating or compiling)
* Step three, build the (relocatable) object file. (assembling)
    * object code is the basic code that a computer runs
    * relocatable object code makes easily modifiable references to
      memory addresses so that you can move it "anywhere" in memory.
* Step four, combine the object file with other object files and libraries
  to build an executable (linking, originally called "compiling")

What are libraries?

* Good C programmers don't reinvent the wheel (unless the wheel is bad).
    * Better C programmers own a collection of wheels
* In C, some libraries are linked automatically, such as stdlib and stdio.
* But there are oodles of libraries out there, so we may have to specify
  when we want additional ones.
    * `-lm` to include the math library.

Review: C project components
----------------------------

_What goes in a (non-trival) C project?_

### Project type 1: Library code

_Libraries are collections of code we expect to others to use in
their programs, or that we expect ourselves to use in other contexts.
Good programmers find or write libraries of things they want to
use._

Libraries in C are often loaded with -lNAME.

Have you built a library in C?  No.

Examples: Sam wants to build a library of a variety of math functions that 
Sam uses regularly.

* `gcd (long x, long y)`
* `expmod (long x, long n, long m)` compute `x^n mod m`

We will be building `srmath.so`, at least I think we will.

What files will we need or build.

* `srgcd.c` contains the code for the `gcd` function.
* `srgcd.o` with the object code for gcd.  Build with something like
  `cc -c srgcd.c -o srgcd.o`
* `srmath.h` declares all of the functions in the library.
* A way to test the gcd function to make sure we didn't screw it up.
    * `gcdtest.c`
    * `gcdtest.o`
* `gcd`, an excutable, because every function should also be a command you can type.
* `gcd.c`, the source code for the executable (not including the gcd function)
  includes the `main` routines.
* `gcd.o`
* `srmath.a` or `srmath.so` The library file that we will be creating
* `README` to provide guidance to those who come after us.
* `LICENSE` to indicate how the materials can be used.
* `Makefile` to remember all of the instructions.

###  Project type 2: Large program

_To ease shared development and to speed rebuilding, we regularly divide
larger projects into many files._

* In Java, we often express expectations for components through interfaces 
  (or through the public methods of a class).
* In C, we often express expectations through .h files.  (Ideally,
  you only rely on the .h file, and not the source code, of a separate
  file).

Make basics
-----------

Remember: Instructions for building the parts of a program and also for
determining what needs to be rebuilt when a file changes.

```
TARGET: PREREQUSITES
        INSTRUCTIONS
        INSTRUCTIONS
        INSTRUCTIONS
```

Writing a sample Makefile
-------------------------

We’re building a sample math utilities package, which we can find in 
[`examples/srmath`](../examples/srmath/).

Right now, srmath presents one function, gcd (long, long).

* srgcd.c contains the implementation of gcd
* srmath.h is the general header file
* We also have srtest to permit unit testing.
* I’m not too worried about library files today.
* I want to be able to build my test file (gcdtest) and a utility (gcd).

What we start with

```
$ ls
gcd.c  gcdtest.c  srgcd.c  srmath.h  srtest.c  srtest.h  testdemo.c
```

It appears that Sam made a bad design decision and temporarily put
`gcd(long long)` into both `srgcd.c` and `srmath.c`.  WE just got
rid of the latter.

* Note `gcd` is declared in `srmath.h`

Let's write instructions for building the gcd application.

How do we combine `gcd.c` and `srgcd.c` into the executable `gcd`?

* First build the corresponding .o files
    * `cc -c gcd.c -o gcd.o`
    * `cc -c srgcd.c -o srgcd.o`
* Combine them into an executable.
    * `cc gcd.o srgcd.o -o gcd`

And what dependencies exist?

```
gcd: gcd.o srgcd.o
        cc gcd.o srgcd.o -o gcd

gcd.o: gcd.c srmath.h
        cc -c gcd.c -o gcd.o

srgcd.o: srgcd.c srmath.h
        cc -c srgcd.c -o srgcd.o
```

```
$ make gcd
cc -c gcd.c -o gcd.o	
cc -c srgcd.c -o srgcd.o	
cc gcd.o srgcd.o -o gcd
```

Adding standard targets
-----------------------

Most makefiles have a standard set of targets.

* `default` (which should come first): The primary thing we want to
  build
* `clean`: Remove temporary files, keep built things that are likely
  useful (e.g., executables or the library).
* `distclean`: Remove temporary files and any other built things.
  (Clean up for distribution to others.)

Adding variables
----------------

Adding automatic variables
--------------------------

$@ the target
$^ the dependencies
$< the first dependency

Using generic rules
-------------------

