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

### Spring break PSA


### Upcoming work

* Lots of reading.
* Optional: Practice making a makefile.

Background: Why `make`?
-----------------------

* SE context:
* Historical context:

Review: C compilation steps
---------------------------

_What happens between the C code and the executable?_

(We'll consider both traditional compilation and more modern compilation.)

Review: C project components
----------------------------

_What goes in a (non-trival) C project?_

### Project type 1: Library code

_Libraries are collections of code we expect to others to use in
their programs, or that we expect ourselves to use in other contexts.
Good programmers find or write libraries of things they want to
use._

Libraries in C are often loaded with -lNAME.

Have you built a library in C?

###  Probject type 2: Large program

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

Writing a sample Makefile
-------------------------

We’re building a sample math utilities package, which we can find in 
[`examples/srmath`](../examples/srmath/).

Right now, srmath presents one function, gcd (long, long).
srgcd.c contains the implementation of gcd
srmath.h is the general header file
We also have srtest to permit unit testing.
I’m not too worried about library files today.
I want to be able to build my test file (gcdtest) and a utility (gcd).

Adding standard targets
-----------------------

Adding variables
----------------

Adding automatic variables
--------------------------

$@ the target
$^ the dependencies
$< the first dependency

Using generic rules
-------------------

