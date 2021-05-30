---
title: "EBoard 12: Queues, Memory, and More"
number: 12
section: eboards
held: 2021-05-13
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Preliminaries
    * Administrative stuff
    * Q&A
* Queue implementations
* Generalizing our queues, phase 1
* What are things that can go wrong?
* Testing
* Break?
* Generalizing our queues, phase 2
* Memory errors: Causes and diagnosis
* Examples

Administrative stuff
--------------------

### General Notes

* Happy Thursday!    Have a great weekend.

### Upcoming Activities

* Thursday at 5:00 p.m.: Advice and guidance for a data science career.
  <https://grinnellcollege.webex.com/grinnellcollege/j.php?MTID=mdce020bcd5f926a1549020e215edc659>
* Friday at 5:00 p.m.: SEPC Internship Panel
* Baseball Doubleheader Saturday at 11:00 a.m. and 1:30 p.m.
* Monday at noon: CS Table wrapup.
* Sunday at 2:30 or 3:00 weekly sunrise movement.  Webex.  Email
  appropriate student for info.
* Follow Men's Tennis to Nationals at WashU

### Work for Tuesday

* Read the man pages for `getopt` and `getopt_long`.
* Write an alternative to `cat`, that takes the following options.
    * `--version` or `-v`: Prints out the version and exits.
    * `--helper` or `-h`: Gives a succinct summary of the options.
    * `--outfile` or `-o`: Sends output to the given file.  (There
      may be many calls to `-o`.)
    * `--pipe` or `-p`: Also sends output to standard output.  (This
      is the default behavior; only overrriden by `-o`.)
    * `--verbose` or `-v`: Prints information about what's happening
      to stderr. 
    * `--stdin`: Reads from stdin in addition to from any files
      given on the command line.  (You can decide if you want
      this to be before all the files, after all the files, or in-between
      all of the files.)
    * `--safe` or `-s`: Does not overwrite any files specified by `-o`.
    * `--dryrun` or `-d`: Does not actually do the work, but does verify
      that it has permission to read and write all of the files.
    * A bunch of file names, which represent all of the files.
    * Any others you consider appropriate

Q&A
---

Queue implementations
---------------------

### Comment from Sam

* You should never have to implement queues in real life.  There are
  a lot of standard implementations around.
* In a job interview, someone might ask you to implement a linked structure.
* If you can't easily implement queues, you should practice doing so.
* You should also consider ways to ensure that your code is correct (or
  as correct as you can make it).
    * Think about common errors.
    * Test.
    * Implement in a verifiable language (hah)
* I'm using queues in this class
    * To give you practice
    * To reinforce some of the key issues in design (and things that
      go wrong)
    * To look once again at testing.
    * To consider memory errors.

### Basic strategy

```
struct sq
  {
    int size;   // Not everyone
    struct sq_node *front;
    struct sq_node *back;
  }

struct sq_node
  {
    char *contents;
    struct sq_node *next;
  } 
```

Design choice 1: Why use `size`?

* This makes the `size` procedure constant time rather than linear time.
* There is overhead to making sure that the `size` remains correct.
* `size` is a good way of checking whether or not the queue is empty.
* Relatively little space overhead; I would normally include it.

Design choice 2: Testing

* Writing the testing code may take as long or longer than writing
  the basic code.
* Sam spent five times as long (plus or minus) on his tests as he spent
  on the array-based implementation (which turned out to be seemingly
  bug-free).

Design choice 3: Dummy nodes

```
    siz hed tal
   +---+---+---+
   | 3 | * | *------------------\
   +---+-|-+---+                |
         v                      v
   +---+---+    +---+---+   +---+---+
   |   | *----> |   | *---> |   | / |
   +---+---+    +---+---+   +---+---+
```

Traditional problem with linked structures: You need special cases for
adding to the empty structure and removing the last element in the empty
the structure.

```
int 
sq_enqueue (SQ *q, char *contents)
{
  if (0 == q->size)
    {
      q->front = (struct sq_node *) malloc (sizeof (struct sq_node));
      if (q->front == NULL) return 0;
      q->front->contents = contents;
      q->front->next = NULL;
      q->back = q->front;
    }
  else
    {
      struct sq_node *tmp = (struct sq_node *) malloc (sizeof (struct sq_node));
      if (tmp == NULL) return 0;
      tmp->contents = contents;
      tmp->next = NULL;
      back->next = tmp;
    }
} // sq_enqueue

char * 
sq_dequeue(SQ *q)
{
  // Special case for the queue becoming empty
}
```

When you write special case code, you sometimes make mistakes.

```
             siz hed tal
            +---+---+---+
            | 3 | * | *------------------\
            +---+-|-+---+                |
                  v                      v
 +---+---+  +---+---+    +---+---+   +---+---+
 | / | *--->|   | *----> |   | *---> |   | *----+
 +---+---+  +---+---+    +---+---+   +---+---+  |
   ^                                            |
   |                                            |
   +--------------------------------------------+
```

Whoops!  Detour failed.  Dummy nodes won't help us.

Design choice 4: Where do we declare the structs?

* Option 1: In `sq.h`
    * Historical C ethos: Reveal details to your clients.
    * "It's what I was taught to do."
* Option 2: In `sq.c`
    * Encapsulation: Our client shouldn't need to know how we
      implement them.  (That means we can change.)
    * Allows us to change implementation.
    * Harder for clients to accidentally break.
    * Sam didn't have them there.
    * If we embrace open source, clients can still see how we've
      built things.

Changing our type?
------------------

What if we decide to go from a queue of strings to a queue of ints?

* Start with the same code.  Then copy, change
* Change the struct to have `int` rather `char *`
* Use `int` instead of `char *` for variables and parameters and ...
* Use `INT_MIN` as the error value rather than NULL.
* Change `sq` to `iq` and `SQ` to `IQ`

Problem: What if the original code was wrong?

* We'll need to go back and fix all the variants we made.
* Perhaps we want to do something other than manually copy/paste/change.
* We want parameteric polymorphism in C!

What might go wrong?
--------------------

* Don't ensure that `malloc` works correctly.
* Doesn't properly deallocate on `dequeue` or `free`.
* Doesn't initialize the struct in `new`.
* In some cases, the pointers might get mixed up.

Code review
-----------

We'll look at some issues.

### From `sq-d.c`

```
sq *
sq_new(){
  return malloc(sizeof(sq));
}
```

Assumes that `malloc` zeroes the memory.  But does it?

```
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sq.h"

int
main (int argc, char *argv[])
{
  SQ *q = sq_new ();
  assert (q);
  assert (0 == sq_size (q)); // 0
  assert(sq_enqueue (q, "Alpha"));
  assert(sq_enqueue (q, "Bravo"));
  sq_free (q);
  q = sq_new ();
  assert (q);
  assert (0 == sq_size (q)); // 0
} // main
```

Whoops!

Change to `calloc`.

### From `sq-a.c`

In `dequeue`, if the size is 1, we set `front` and `back` to `NULL`, 
but don't free the old node.  (Memory leak!)

```
  if (q->size == 1)
    {
      q->front = NULL;
      q->back  = NULL;
      q->size--;

      return first;
    }
```

It's good practice to cast the return value from `malloc`.  (But the
code should still work fine.)

Don't put `main` in your utility code!  Create two files that you link
together.

The following code is problematic.  If the malloc fails, 
assigning `new->string` or `new->next` will result in a seqfault.

```
  /* declares and initializes new node */
  struct node *new = malloc(sizeof(struct node));
  new->string      = str;
  new->next        = NULL;

  /* if malloc failed, return 0 */
  if (!new)
    {
      return 0;
    }
```

## From `sq-b.c`

Does not free the struct (misunderstanding)

```
void sq_free (SQ *q){
    // deQ until the q is empty.
    while(sq_dequeue(q));
    // the Q can be used after it is sq_freed, will just have 0 elements,
    // unless i want to free it here
}
```

Don't chain arrows, even with parens?

```
        return q->front->str;
```

Make sure that `malloc` succeeds.

```
    // Make space for a new node
    node_t* node = malloc(sizeof(node_t));

    // Fill the node with the string
    node->str = str;
```

Order of nodes matters.  For queues, we want front linking to a
series of nodes that link to back.  For stacks, we want top linking
to the prior nodes.

## From `sq-c.c`

Not valid C.

Testing
-------

Look at the code.

* Idea one: Randomly generate instructions and check their results.
* Idea two: Record those instructions so that you can replay them.
* Idea three: Generate a program you could run instead.

Changing our type, revisited (aka avoiding repetitive code)
-----------------------------------------------------------

### Detour: Meta-programming

Writing programs that generate code is called "meta-programming".

Instead of manually copy/paste/change for our different kinds of queues, 
we should write programs to generate our queues.

### Meta-programming with macros

In C, you can use macros to do some kinds of meta-programming (that
is, to generate code).

For example, if we wanted versions of `square` for different types
(e.g., `isquare` for `ints` and `dsquare` for doubles, etc.)

```
#define SQUARE_FUN(NAME, TYPE) \
  TYPE  \
  NAME (TYPE X) \
  { \
    print ("Squaring"); \
    return X*X; \
  }
```

We can do something similar to generalize queues.  See old reading.

When you find yourself programming by copy/paste/change, you should
find a way to avoid that.  Sometimes writing programs that generate
your code is the way to go.

See <https://rebelsky.cs.grinnell.edu/musings/cnix-macros-generics>

Memory Errors
-------------

_We'll consider some issues and their effects._

### Use after freeing

Example 

    int *ip = (int *) malloc (sizeof (int));
    int *jp = ip;
    *jp = 5;
    free (ip);
    printf ("%d\n", *jp);
    *ip = (int *) malloc (sizeof (int));
    *ip = 11;
    printf ("%d\n", *jp);

Effects?  What do you see happening if you try to use memory after
you've freed it?

* Freeing doesn't clear memory, so you might still use it.
* The next time someone calls `malloc`, they may get that memory,
  change it, and your value will change unexpectedly.

How do you know if your code inadvertently uses memory that has
been freed (other than, "Hmmm, my value changed inadvertently.")

* Use a program that looks at your program, such as the Google
  performance analyzer.
    * Old answer, on Linux: Use `valgrind`.
    * New straightforward answer on most clang systems is ot use
      address sanitizer.

Why doesn't C have a garbage collector?

* C was designed long before good garbage collectors existed.
  At the time C was designed, most languages assumed that the
  programmer would manage memory (and should manage memory).
* Until a decade or so ago, all production garbage collectors seemed
  to do bulk collection, which stops the program.  That's not generally
  acceptable for C programs, which are traditionally written for 
  to be fast and "predictable".
* Java was an attempt to add objects + garbage collection to C.
    * [Other issues with Java]
* Rust may also be C plus garbage collection.
* Memory is also much cheaper these days.

### Out-of-bounds memory access

Examples

Effects?

* Similar to using freed memory (You won't notice immediate effects.)
* Valgrind or Address Sanitizer are great ways to figure this out.

### Dereferencing a null pointer

Examples

Effects?

### Too much recursion (stack overflow)

Examples

Effects?

### Passing pointers to functions without specifying limits

Examples

Effects?

### Mis-typing things

Examples

Effects?

### Diagnosing

_How do we diagnose these errors?_

An example
----------

```
/**
 * example.c
 *   An example for our discussions.
 */

// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <assert.h>
#include <stdio.h>

// +---------+---------------------------------------------------------
// | Helpers |
// +---------+

/**
 * Allocate an array.
 */
void
vals (int *result[])
{
  int values[10];
  *result = values;
} // vals

/**
 * A function that fills in some values in an array.
 */
void
f (int n)
{
  int i;
  int values[10];
  for (i = 0; i < 10; i++)
    {
      values[i] = n;
      assert(values[i] == n);
    } // for
} // f

// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (void)
{
  int *stuff;
  vals (&stuff);
  stuff[0] = 42;
  f (5);
  assert (42 = stuff[0]);
  return 0;
} // main
```

Another example
---------------

```
#include <stdlib.h>
#include <stdio.h>
void
f (int *ip)
{
  int i = *ip;
  free (ip);
  ip = malloc (sizeof (int));
  *ip = i + 1;
}
int
main (int argc, char *argv[])
{
  int *stuff;
  stuff = malloc (sizeof (int));
  *stuff = 5;
  f (stuff);
  assert (6 == *stuff);
  *stuff = 1;
  assert (1 == *stuff);
  free (stuff);
  return 0;
} // main
```

Another example
---------------

```
/**
 * example.c
 *   An example for our discussion of lldb and such.
 */

// +---------+---------------------------------------------------------
// | Headers |
// +---------+

#include <assert.h>
#include <stdio.h>

// +---------+---------------------------------------------------------
// | Helpers |
// +---------+

/**
 * Allocate an array.
 */

void
vals (int *result[])
{
  int values[10];
  *result = values;
} // vals

/**
 * A function that fills in some values in an array.
 */
void
f (int n)
{
  int i;
  int values[10];
  for (i = 0; i < 10; i++)
    {
      values[i] = n;
      assert(values[i] == n);
    } // for
} // f

// +------+------------------------------------------------------------
// | Main |
// +------+

int
main (void)
{
  int *stuff;
  vals (&stuff);
  stuff[0] = 42;
  f (5);
  assert (stuff[0] == 42);
  return 0;
} // main
```

Parametric Polymorphism (Perhaps)
---------------------------------
