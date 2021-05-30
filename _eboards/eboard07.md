---
title: "EBoard 07: Fun with Make"
number: 7
section: eboards
held: 2021-04-27
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Review 
    * Why does Make exist?
    * Some standard C project components
    * The (approximate) stages of (C) compilation
    * The (basic) form of a Makefile
* Break?
* A Make project
    * The project
    * Doing without `make`
    * A basic `Makefile`
    * Adding variables
    * Adding automatic variables
    * Adding generic rules
* Other random topics

Administrative stuff
--------------------

### General Notes

* Happy Tuesday!
* Reminder: I do want to see you try the tasks, even if things don't
  go quite right.
* Today's class repeats some things from the readings.  I hope
  that's okay.  I may go quickly; feel free to slow me down.
* If you are post-vaccine on Thursday and can't come to class, I understand.

### Upcoming Activities

* Alissa Nutting & Dean Bakopoulos on "Made for Love".  Wednesday at
  7 p.m.
  <https://www.prairielights.com/live/alissa-nutting-christina-lee-and-dean-bakopoulos-writers-grinnell>
* CS Extras Thursday at 5pm: Michael Spicer on
  Regulating the Internet and Machines: Creating Sustainable
  Social-Machine Relationships in the Digital Age.
  In the Events Channel on the CS Team.
* Mando Memorial Lecture Thursday at 7pm
  <https://www.prairielights.com/live/hanif-abdurraqib-armando-“mando”-alters-montaño-‘12-memorial-lecture-writers-grinnell>
* Convocation Thursday May 6th at noon: the STEM Pipeline

### Work for Thursday

* Read/skim [The C Preprocessor](https://gcc.gnu.org/onlinedocs/cpp/)
* Do tasks 8a and 8b on our Teams channel
    * [Task 08a](https://teams.microsoft.com/l/channel/19%3af31451429d71416ca14848a5172515aa%40thread.tacv2/Task%252008a%2520-%2520Including%2520files%2520(due%25202021-04-29)?groupId=32394573-b837-4c0f-b7b5-aeec3e347a0b&tenantId=524f9e3e-faca-4f64-b3ec-adb2baee8807): Find or write a file that you would reasonably include more than once in the same C file.  Explain why/how you would include it more than once.
    * [Task 08b](https://teams.microsoft.com/l/channel/19%3aaf60fd3fa24c4d649b2f2cb30a465687%40thread.tacv2/Task%252008b%2520-%2520Useful%2520macros%2520(due%25202021-04-29)?groupId=32394573-b837-4c0f-b7b5-aeec3e347a0b&tenantId=524f9e3e-faca-4f64-b3ec-adb2baee8807): Find or write a macro you would expect to regularly use in your C programming.

### Work for Tuesday

* TBD

Q&A
---

Background: Why `make`?
-----------------------

* Basic idea in Make is that we regularly have to build software systems
  AND building software systems usually requires a lot of commands.
* You could write all of those commands down on a piece of paper (digital).
* If you're writing them down digitally, you should be able to execute them.
* However, ...
    * Building software is slow (or used to be slow).
    * Even just five years ago, it took an hour to build GIMP (the GNU
      Image Manipulation Program) from scratch.
    * If something goes wrong along the way, you don't want to rebuild the
      whole thing each time; just what depends on what you fix.
* Figuring out where to continue is a hard problem.
    * Curtsinger research: Gather information by observing and create a
      "rebuild script" automatically.
    * Makefile approach: Write down dependencies and let the computer
      trace the graph.
    * Make has evolved a bit, but not much, over the years.
* Make was designed primarily for C projects, but has spread to any
  kind of project that fits in the "multiple steps with dependencies"
  millieux.
* It's a great hammer.  It can hit lots of things.

Review: C Project Components
----------------------------

_What goes in a (non-trival) C project?_

### Type 1: Library

_Code we expect to others to use in their programs, or that we expect
ourselves to use in other contexts.  Good programmers write or find
libraries of things they want to use._

Libraries in C usually have the form libNAME.a or libNAME.so.  When
developing those libraries, we usually work with .o files from the
individual C programs that compose the libraries.

We're going to build a library of useful Math utilities.

* `gcd (long x, long y)` finds the gcd of x and y.
* `exptmod (long base, long expt, long modulus)` - computes
  (base^expt) mod modulus.  (We have a separate function to do
  this because base^expt might overflow.

What are the source files we want?

* A `.c` file: `mymath.c` (source code)
    * Or `mygcd-lib.c` and `myexptmod-lib.c` (Sam likes to split independent
      things into separate `.c` files to ease development and recompliation.)
* An `.h` file  `mymath.h` (header file)
* Other C files: 
    * `mymathtest.c` (test file)
    * Or ... `mygcdtest.c` and `myexpmodtest.c` 
    * `mygcd.c` and `myexptmod` - Command-line versions of these procedures.
        * I could write the tests as shell scripts.
* Other files:
    * `Makefile`
    * Information from development, such as a logfile.
    * A `README.txt`
    * A `LICENSE`
    * Installation instructions

We'll be building .o files, the libraries, maybe some executables.

### Type 2: Larger program

_To ease sharing and to speed rebuilding, we often divide large
projects into many many many files._

In this case, we're probably doing some .h files (especially if we
split up the program into independing parts), a bunch of .c files,
some tests (also C files or shell scripts), and executables.

Detour: C Compilation Steps
---------------------------

Checking in ... do you know the (implicit) steps in going from
.c file to executable?  [Sam will attempt a survey.]

Variants of the cc command let you do each of these steps.

* .c files give the source code to the program.
* Preprocessor gives you new .c files.
    * Strips all the comments.
    * Handles the macro and constant definitions
    * Deals with the includes
    * Etc.
* Behind the scenes, not usually available to programmer: Lexing
  (divide the program into lexical pieces) and parsing (understand
  the broader structure, including nesting)
* Translate into a simpler intermediate language.  "Generic assembly"
* (Optionally): Optimize the generic assembly
* Translate the generic assembly into machine-specific assembly (`.s`)
* (Optionally): Optimize the machine-specific assembly.
* Assemble the assembly into
  .o file contains "object code", relocatable executable code.
* We link .o files (plus library files) into an executable file that we can run
    * Shove all the code together.
    * Make them work in the same address space.
    * Interestingly, this last step used to be called "compilation"; it
      became the term for all of the steps.

Optimization

* Move variables from memory to registers
* Pre-compute some operations (e.g., x+3 and we know x is 0, use 3)
* Unroll loops.
* Write code that takes both branches and throws one away.

Make basics
-----------

Recall: Our goal is to express a sequence of commands necessary to
create a program and to express the dependencies along the way.  "If
X changes, this has to be rebuilt."

We express this information using a series of "rules".  (Plus
additional stuff.)

    TARGET: PREREQUISITES
            INSTRUCTIONS

Let's try doing this for our sample project.

A sample project
----------------

We're building a sample math utilities package, which we can find
in [`examples/srmath`](../examples/srmath).

* Right now, `srmath` presents one function, `gcd (long, long)`.
    * `srgcd.c` contains the implementation of `gcd`
    * `srmath.h` is the general header file
* We also have `srtest` to permit unit testing.
* I'm not too worried about library files today.
* I want to be able to build my test file (`gcdtest`) and a
  utility (`gcd`).

Files

```
gcd.c           srgcd.c         srtest.c        testdemo.c
gcdtest.c       srmath.h        srtest.h
```

How do I build `gcd`?

    cc -c gcd.c -o gcd.o
    cc -c srgcd.c -o srgcd.o
    cc gcd.o srgcd.o -o gcd

How do I build gcdtest

    cc -c srgcd.c -o srgcd.o
    cc -c gcdtest.c -o gcdtest.o
    cc -c srtest.c -o srtest.o
    cc srgcd.o gcdtest.o srtest.o -o gcdtest

Suppose we just changed gcdtest.c.  Which of those steps do we need to redo?

    cc -c gcdtest.c -o gcdtest.o
    cc srgcd.o gcdtest.o srtest.o -o gcdtest

We shouldn't have to remember that!

Detour!
-------

If Sam types `!s` in his terminal window, what will happen?

Ignore the following

```
jet: engine
        type-in-chat
```

A Makefile for our project
--------------------------

Pattern

```
TARGET: DEPENDENCIES
        INSTRUCTIONS
```

```
# All those awesome .o files
gcd.o: gcd.c srmath.h
        cc -c gcd.c -o gcd.o
srgcd.o: srgcd.c srmath.h
        cc -c srgcd.c -o srgcd.o
srtest.o: srtest.c srtest.h
        cc -c srtest.c -o srtest.o
gcdtest.o: gcdtest.c srmath.h srtest.h
        cc -c gcdtest.c -o gcdtest.o

# Executables
gcd: gcd.o srgcd.o
        cc gcd.o srgcd.o -o gcd
gcdtest: srgcd.o gcdtest.o srtest.o 
        cc srgcd.o gcdtest.o srtest.o -o gcdtest
```

Let's try make

```
$ make gcd
cc -c gcd.c -o gcd.o
cc -c srgcd.c -o srgcd.o
cc gcd.o srgcd.o -o gcd
```

If we don't use tabs

```
$ make gcd
Makefile:13: *** missing separator (did you mean TAB instead of 8 spaces?).  Stop.
```

Making gcdtest

```
$ make gcdtest
cc -c srgcd.c -o srgcd.o
cc -c gcdtest.c -o gcdtest.o
cc -c srtest.c -o srtest.o
cc srgcd.o gcdtest.o srtest.o -o gcdtest
```

After changing gcdtest.c

```
$ make gcdtest
cc -c gcdtest.c -o gcdtest.o
cc srgcd.o gcdtest.o srtest.o -o gcdtest
```

Basically, make follows the dependencies, asking if any of them 
targets are older than the dependencies.  If so, it re-executes
the associated instructions.

Our Makefile has lots of things that we might want to fix/change/generalize.

* Meet standards!
* Write cleaner code.
* Make it easy to adapt.

Adding standard targets
-----------------------

Question: If I just type `make`, with a Makefile but without an explicit 
target, what should it build?

* It builds the first target

Standard targets

* `default`, the default thing.  Should appear first (or see the next
  standard target).
* `all`, appears first, what your goals are.  When you just type `make`,
  make attempts to make the target of the first specific rule.
* `check` (or `test`), run your test programs
* `install`, installs your program / you may not write
* `clean`, remove cruft
* `distclean`, remove cruft and anything you built
* `dist`, make a Tarball (or `zip` for a zipfile)

Note: Using `@` is a sign not to print out the command.

```
default:
        @echo "Please specify what to make!"
```

Here are some samples

```
all: gcd srmathlib.so

check: gcdtest
        ./gcdtest

install: srmathlib.so
        install srmathlib.so /usr/local/lib

clean:
        rm -f *.o

distclean:
        rm -f *.o *.so gcdtest gcd
```

Use these if you're planning on writing code you share with other people.

We use `clean` and `distclean` relatively rarely.

Detour: Libraries
-----------------

.a vs .so vs .dylib (Mac?) vs .dll

* Code from `.a` libraries is in the memory space of your program.  If
  lots of programs use the same library, we get one copy in *each* program.
* Code from `.so` (and other dynamicly linked librareis) get their own
  memory space.  If lots of programs use the same library, we got one
  copy total.  (Yay!  Save memory.  Boo!  Dangers.)

Adding variables
----------------

When we repeat ourselves, we try to avoid doing so.

Adding automatic variables
--------------------------

* `$@` the target
* `$^` the dependencies
* `$<` the first dependency
* A bunch of less common ones (see <https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html>)

```
# Executables
gcd: gcd.o srgcd.o
        $(CC) $(CFLAGS) $^ -o $@
gcdtest: srgcd.o gcdtest.o srtest.o
        $(CC) $(CFLAGS) $^ -o $@

# Libraries
srmathlib.so: srgcd.o
        $(CC) $(CFLAGS) -shared srgcd.o -o srmathlib.so

# All those awesome .o files
gcd.o: gcd.c srmath.h
        $(CC) $(CFLAGS) -c $< -o $@
srgcd.o: srgcd.c srmath.h
        $(CC) $(CFLAGS) -c $< -o $@
srtest.o: srtest.c srtest.h srmath.h
        $(CC) $(CFLAGS) -c $< -o $@
gcdtest.o: gcdtest.c srmath.h srtest.h
        $(CC) $(CFLAGS) -c $< -o $@
```

Using generic rules
-------------------

Use `%` for "Something"

E.g.,

```
CC = clang
CFLAGS = -g -Wall
%.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@
``` 

Note: You get a new automatic variable: `$*`, which is the stem of a rule.

Other Make Topics
-----------------

Exponentiation (if there's time)
--------------------------------
