---
title: "EBoard 08: The C Preprocessor and Macros"
number: 8
section: eboards
held: 2021-04-29
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Quick wrapup of Make (for the time being)
* The C Preprocessor, reviewed
* Constants
* Some side notes on including files
* Macro basics
* Break
* Macro cautions
* Sam's testing macros
* Exponentiation (if time)
* The silly #include example (maybe)

Administrative stuff
--------------------

### General Notes

* Happy Thursday!  I hope you have a wonderful weekend.
* Reminder: I do want to see you try the tasks, even if things don't
  go quite right.
* Sorry about the confusing "double include" assignment.  I sometimes
  choose things that push a little too far just to see what you come
  up with.  We'll either do an example today or you'll read about one
  for the next class (or both).
* If you are post-vaccine today and can't come to class, I understand.

### Upcoming Activities

* CS Extras TODAY at 5pm: Michael Spicer on
  Regulating the Internet and Machines: Creating Sustainable
  Social-Machine Relationships in the Digital Age.
  In the Events Channel on the CS Team.
* Mando Memorial Lecture TODAY at 7pm
  <https://www.prairielights.com/live/hanif-abdurraqib-armando-“mando”-alters-montaño-‘12-memorial-lecture-writers-grinnell>
* Convocation Thursday May 6th at noon: the STEM Pipeline

### Work for Tuesday

* Read lots of things (see [the schedule](../schedule))
* Do task 9a or 9b on our Teams channel
    * [Task 09a](https://teams.microsoft.com/l/channel/19%3ae114631658e84764b72b80c75bb70c55%40thread.tacv2/Task%252009a%2520-%2520Groking%2520utstack%2520(due%25202021-05-04)?groupId=32394573-b837-4c0f-b7b5-aeec3e347a0b&tenantId=524f9e3e-faca-4f64-b3ec-adb2baee8807):
      Explain [`utstack.h`](https://raw.githubusercontent.com/troydhanson/uthash/master/src/utstack.h)
    * [Task 09b](https://teams.microsoft.com/l/channel/19%3a88df62dbac2347eab28abb27a0549463%40thread.tacv2/Task%252009b%2520-%2520Using%2520uthash%2520(due%25202021-05-04)?groupId=32394573-b837-4c0f-b7b5-aeec3e347a0b&tenantId=524f9e3e-faca-4f64-b3ec-adb2baee8807)
      Use uthash.h to implement a simple dictionary.

Q&A
---

Wrapping up `make` for the time being
-------------------------------------

### Summary from last class

* Almost every nontrivial project requires a sequence of commands.
* When you find yourself needing to remember sequences of commands,
  put 'em in a Makefile.
    * It preserves them.
    * It allows other people to use them.
    * It may make rebuilding more efficient.
* Learn to use the automatic variables in the Makefile.
    * Knowing how to read automatic variables eases the reading of
      most real Makefiles.  (`$@`, `$^`, and `$<` are the big ones).
* Have fun with Make

### Other issues

* I skipped annotations, such as `.PHONY`.  These provide information
  to Make about a variety of issues, in this case, targets that aren't
  themselves files (e.g., `all` or `check`).
* For portable software, many designers have started relying on
  Automake, which builds platform-specific Makefiles (and more).
* We have just scratched the surface of Make.  As time progresses,
  you'll find more command-line flags to do, more options, etc.
  Here are some lines I never remember but find useful.

        md := $(shell ls *.md 2>/dev/null)      # Lists all files matching *.md
                                                # sending error messages to /dev/null
        html := $(md:%.md=%.html)               # Converts .md to .html
        default: $(html)

### Questions

With some references, do you think you can write your own Makefiles?

> Yeah, maybe.  Or I'll ask Sam for help.

The C Preprocessor
------------------

Our goal: List many of the important things that the C preprocessor
does and *why* that feature might be included.

Five minutes in small groups, then back to the class as a whole.

Feature / purpose.

Note: If we want to see what the C preprocessor does, we can use 
`cc -E`.

### Replaces #defined constants with values

E.g.,

    #define STRLEN 32
    char str[STRLEN];

becomes

    char str[32];

This is useful because?

* It makes it easier to update if we change our mind about what
  the "constant" should be.
* It avoids the overhead of remembering which of those values mean
  "STRLEN" and which mean something else.
* Compared to a variable, this may be more efficient.  We can avoid
  memory lookups.  Yay!
* #defined constants can be easier to read.

Note: There are predefined constant.  __DATE__ gives you the current date
in some horrendous form.  The date is translated at compile time.

Detour: `const int STRLEN = 32` is also a constant.

### Replaces macros with their bodies

E.g.,

    #define DOUBLE(X) 2*(X)
    y = DOUBLE(3);

becomes

    y = 2*(3);

Why have macros?

* Macros are like functions but perhaps more efficient.
    * Executing code directly requires fewer instructions than
      "push parameters on stack, jump to this procedure, do the
      instructions, place the return value somewhere, return,
      copy the value back"
* Macros can be more readable.

### Include other files with `#include`

E.g.,

        # foo.h
        int foo (double bar);

        # baz.c
        #include "foo.h"
        ....

Becomes

        #baz.c
        # 1 foo.h 1
        int foo (double bar);
        # 2 baz.c 2

Why?

* Don't have to copy and paste the code yourself.
* Consistency across files / no need to update everywhere.
* Note: We don't normally include compiled.

### Conditional inclusion of code

For example,

        #ifdef DEBUG
          fprintf (stderr, "I reached point 42 of the code\n");
        #endif

Becomes nothing if DEBUG is not defined

        # line 100

Becomes what's in the ifdef if DEBUG is defined

          fprintf (stderr, "I reached point 42 of the code\n");

Where do those variables come from?

* We define them ourselves.
* We define them in the environment (maybe)
* We defined them in the Makefile or other build instructions
    * Automake does this for us.

Detour: Dates
-------------

Sam dislikes "MMMM DD, YYY" because it's medium / small / large.

Sam really dislikes "MM/DD/YYY" because it's ambigious.  Most of
Europe uses "DD/MM/YYYY"  What is 3/12/2021?

Sam prefers YYYY-MM-DD because it's unambiguous and it sorts nicely.

        class-2020-05-12.txt
        class-2021-03-04.txt
        class-2021-04-29.txt

Break
-----

This break inserted at its approximate location.  Its precise location
will depend on a variety of other factors.

Constants
---------

### Defined within the file

    #define CONSTANT value

### Defined during compilation

    cc -DCONSTANT=value;

### A hybrid (good practice)

    #ifndef STRLEN
    #define STRLEN 32
    #endif

This is good practice because it lets the program work "as is", but
also allows someone to easily reconfigure it for their special
circumstances.

Note that the compilation flags are often done in the makefile

    CFLAGS = -DCONSTANT=value

Some side notes on `#include`
-----------------------------

### What does include do?

Takes a given file and shoves its contents into your code.

For .h files, those are normally declarations.

For .c files, those are normally code.

### Include vs Link

Header files are *not* libraries.  Although the `#include <math.h>` tells us
to include the *declarations* of the math libraries, it does not 
(necessarily) tell the C compiler to include their code.

This is `testfoo.c`.

```
#include "foo.h"
#include <stdio.h>

int
main (int argc, char *argv[])
{
  double d = 99.5;
  int i = foo(d);
  printf ("foo (%lf) = %d\n", d, i);
  return 0;
} // int
```

This is `foo.h`

```
int foo (double bar);
```

This is `foo.c`

```
#include "foo.h"

int
foo (double bar)
{
  return (int) bar;
} // foo
```

What happens if I type the following?

```
$ cc testfoo.c -o testfoo
```

* When run, it will print out something like "foo (99.5) = 99".
* It won't compile, let alone run.

```
$ $ cc testfoo.c -o testfoo
Undefined symbols for architecture x86_64:
  "_foo", referenced from:
      _main in testfoo-9c357b.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

What does this error message mean?

* The compiler can't find the `foo` function because it's not in
  `testfoo.c` nor any of the "standard" places it looks for library
  code.
* Solution: We need to link both testfoo.o and foo.o to build our
  final program.

NOTE: Even though I did an include of foo.h, I did not get access\
to the code in foo.c.

TRADITIONALLY, including `<math.h>` didn't give you access to libmath.
You had to add the -lm flag.

### Including `.c` vs `.h` files.

* `.h` files are almost always just declarations
* `.c` files can be code.

The following compiles directly because it includes the *code* for
the `foo` function.

```
#include "foo.c"
#include <stdio.h>

int
main (int argc, char *argv[])
{
  double d = 99.5;
  int i = foo(d);
  printf ("foo (%lf) = %d\n", d, i);
  return 0;
} // int
```

Why not include a `.c` file?

* If two files include the same `.c` file, we'll likely get a conflict.
* We don't generally include `.c` files unless we are doing clever hacks.

### A note about including headers

This is `testfoo3.c`

```
#include "foo.h"
#include "foo.c"
#include <stdio.h>

int
main (int argc, char *argv[])
{
  double d = 99.5;
  int i = foo(d);
  printf ("foo (%lf) = %d\n", d, i);
  return 0;
} // int
```

This is `foo.c`

```
#include "foo.h"

int
foo (double bar)
{
  return (int) bar;
} // foo
```

What will happen when we try to compile and run testfoo3.c?

* We've included `foo.h` twice, once directly and once indirectly.
* That *might* stop things from working correctly.
* However, right now it looks like the compiler does not complain
  about identical declarations of the same function.

So I'm going to change `foo.h` slightly, adding a type declaration.

```
int foo (double bar);

typedef struct pair
  {
    int x;
    int y;
  } pair;
```

### Detour

What types did I just name or create?

* `pair`
* `struct pair`

If I had written

```
typedef struct pear
  {
    int x;
    int y;
  } apple;
```

I would have created

* `struct pear`
* `apple`

### Back to the problem

If we include the new `foo.h` twice, we have two identical type 
declaration.  The C compiler generally does not like that.

```
$ cc testfoo3.c -o testfoo
In file included from testfoo3.c:2:
In file included from ./foo.c:1:
./foo.h:6:16: error: redefinition of 'pair'
typedef struct pair
               ^
testfoo3.c:1:10: note: './foo.h' included multiple times, additional include site here
#include "foo.h"
         ^
./foo.c:1:10: note: './foo.h' included multiple times, additional include site here
#include "foo.h"
         ^
./foo.h:6:16: note: unguarded header; consider using #ifdef guards or #pragma once
typedef struct pair
               ^
In file included from testfoo3.c:2:
In file included from ./foo.c:1:
./foo.h:10:5: error: typedef redefinition with different types ('struct (anonymous
      struct at ./foo.h:6:16)' vs 'struct pair')
  } pair;
    ^
testfoo3.c:1:10: note: './foo.h' included multiple times, additional include site here
#include "foo.h"
         ^
./foo.c:1:10: note: './foo.h' included multiple times, additional include site here
#include "foo.h"
         ^
./foo.h:10:5: note: unguarded header; consider using #ifdef guards or #pragma once
  } pair;
    ^
2 errors generated.
```

We sometimes inadvertently include the same header file more than once,
and we should try avoid that.

### Standard header file format

```
#ifndef __HEADER_H__
#define __HEADER_H__

#endf // __HEADER_H__
```

The preprocessor is not smart about includes, so we have to be
smarter about includes.

Macro basics
------------

A macro is an instruction for the preprocessor that gives a pattern
and a replacement.

We have constant macros

        #define STRLEN 32

We also have function macros, which are parameterized

        #define DOUBLE(X) X*2

The preprocessor takes the the *text* of the parameter to a function
macro and substitutes it into the body of that macro, putting that
new code into the place of the MACRO "call".

```
#define DOUBLE(X) 2*X

#include <stdio.h>

int
main (int argc, char *argv[])
{
  printf ("double (3) is %d\n", DOUBLE (3));
  return 0;
} // main
```

After preprocessing

```
int
main (int argc, char *argv[])
{
  printf ("double (3) is %d\n", 2*3);
  return 0;
}
```

If I compile and run, I should get "double (3) is 6"  And I do.

Modified

```
#define DOUBLE(X) 2*X

#include <stdio.h>

int
main (int argc, char *argv[])
{
  printf ("double (2+1) is %d\n", DOUBLE(2+1));
  return 0;
} // main
```

What's the output going to be?

```
double (2+1) is 5
```

Why?

```
double (1+2) is 4
```

Macro issues
------------

### Ben's parens

### Macros vs. functions

### Multi-line macros

### Multi-line macros, revisited

Detour: Exponentiation
----------------------

Goal: Compute x^n mod m.  Assume x < m and m < sqrt(LONG_MAX).

Obvious solution:

Can we do a more efficient solution?
