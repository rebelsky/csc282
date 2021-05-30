---
title: "EBoard 11: Memory and More"
number: 11
section: eboards
held: 2021-05-11
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Preliminaries
    * Administrative stuff
    * Q&A
* Review: Exponentiation (beating a dead horse)
* Counting operations
* Making the damn thing iterative
* Lessons
* _Break_
* Short detour: Queues
* Memory errors: Causes and diagnosis
* Examples

Administrative stuff
--------------------

### General Notes

* Happy Tuesday!  
* Those of you who aren't doing tasks will need to write a final reflection.
    * Details forthcoming.
    * Others can choose to write one, too.

### Upcoming Activities

* Wednesday at 7:00 p.m. Writers @ Grinnell Distinguished Author Lecture.
  <https://www.prairielights.com/live/alexander-chee-writers-grinnell-distinguished-author-event>
* Thursday at 5:00 p.m.: Advice and guidance for a data science career.
  <https://grinnellcollege.webex.com/grinnellcollege/j.php?MTID=mdce020bcd5f926a1549020e215edc659>

### Work for Thursday

* Implement queues

Q&A
---

Review: Exponentiation
----------------------

Goal: Compute `(x^n) mod m`, where `x`, `n`, and `m` are all non-negative long 
values.  

Rationale: Useful for encryption and decryption.

Assume: x < m and m < sqrt(LONG_MAX).

Iterative solution: Use a for loop.  Easy to verify correctness

Recursive solution 1:

* x^0 = 1
* x^(2k) = x^k * x^k
* x^(2k+1) = x * x^(2k)

* The recursive solution is a bit harder to prove correct, particularly
  since we don't quite have it in that form.
    * If we were in 208, we'd do a proof by some kind of induction.
* We wrote a variety of implementations, some correct, some incorrect.
* We implemented a timer, and a tester, and a command-line version.
* We discovered that a recursive solution was *much* faster than the
  "obvious" iterative solution.
* We had trouble measuring the growth because the growth was so slow.
    * We did not try using the nanosecond timer.
    * I have now tried.  On my machine, it only does increments of
      1000 nanoseconds, which is no more precise then microseconds.
      (See [time2-expmod.c](../examples/expmod/time2-expmod.c).
* We were attempting to find other ways of counting using macros.
  I was having difficulty with that.
    * Issue: How do we ensure that there's only one copy of the
      variables.  

Counting Calls
--------------

Idea: Instead of `*`, use `MULTIPLY`.  In normal situations,
`MULTIPLY(X,Y)` just gives `X*Y` (parenthesized appropriately).
When we want to count, we use something that increments a
counter and then returns `X*Y`.

```
#ifdef LOGMATH
extern long _MULTIPLICATIONS;
#define MULTIPLY(X,Y) ((_MULTIPLICATIONS++ * 0) + ((X)*(Y)))
#else
#define MULTIPLY(X,Y) ((X)*(Y))
#endif
```

How do we ensure that there's only one copy of the variables?

* Use `extern` in the header.  That says "It's not declared here."
    * The linker will have to fill in the address.
* Don't use modifiers in one of the files (I chose `logmath.c`).
* Cross your fingers.
* **Don't use `static`** (that's what I did wrong).
* **Don't initialize extern variables** (that's also something I did wrong).
* **Make sure to recompile all the .o files.**

Some examples

```
$ ./emr 11 1000 51
16
*: 15
/: 9
%: 30
$ ./emr 11 2000 51
1
*: 16
/: 10
%: 32
$ ^2^4
./emr 11 4000 51
1
*: 17
/: 11
%: 34
$ ^4^8
./emr 11 8000 51
1
*: 18
/: 12
%: 36
```

And we've learned ...?

* For large enough n, 11^(1000*n) mod 51 is 1.
* The recursive version is nice because it allows divide and conquer.
* The growth is logarithmic.  Yay!
* Counting was helpful in allowing us to see the growth.  (It
  required overhead for us.)

Other ways to analyze?

* Use performance analyzers, such as gperf.  (Ask Charlie!)

Detour: Can write OO programs in C?
-----------------------------------

* It depends on what you mean by Object-Oriented.
* You can certainly refer to code and variables in other .o files.
* You can certainly build structs that contain both data and 
  pointers to functions.  ("Encapsulation")
* Inheritance and Polymorphism (subtype and parameteric) with
  type checking can be hard.
* You can get can subtype polymorphism by using `(void *)` for your 
  parameters.
* You're better off using C++, the best name ever for a language.

From recursive to iterative
---------------------------

How can we turn that wonderful recursive solution into a 
slightly-less-wonderful, but somewhat-more-efficient iterative
solution?

* x^0 = 1
* x^(2k) = (x^2)^k
* x^(2k+1) = x * x^(2k)

```
long
expmod (long x, long n, long m)
{
  if (0 == n)                              // x^0 = 1
    {
      return 1;
    }
  else if ((n % 2) == 0) // even
    { 
      return expmod ((x*x) % m, n/2, m);   // x^(2k) = (x^2)^k;  k = n/2
    } // even
  else // odd
    {
      long tmp = expmod (x, n-1, m);       // x^(k+1) = x^k * x; k = n - 1
      return (x * tmp) % m;
    } // odd
} // expmod
```

### Strategies for turning recursive procedures into iterative procedures

* Try to do the same thing as the recursive procedure is doing, but
  by adding extra variables.
* Make it tail recursive and do the natural translation from tail
  recursion to iteration.
* Build your own stack.  (Not a great solution.)
* Dynamic programming!  Set up an array as a cache, and build it
  bottom up instead of top down.

### Tail recursion!

How do you make a procedure tail recursive?

* Add an extra parameter (we'll call that the accumulator) `so-far`
* Take the operation that you normally do to the recusive call and
  move it inside, applying it to the accumulator.
* The accumulator's initial value is usually the base case value.

```
long
expmod (long x, long n, long m)
{
  return expmod_helper (x, n, m, 1);
} // expmod (long x, long n, long m)

long
expmod_helper (long x, long n, long m, long acc)
{
  if (0 == n)
    {
      return acc;
    } // base case
  else if (n % 2 == 0) 
    {
      return expmod_helper ((x*x) % m, n/2, m, acc);
    } // even
  else
    {
      // x^(k+1) = x^k * x; k = n - 1
      // return (x * expmod (x, n-1, m)) % m;
      return expmod_helper (x, n-1, m, (x*acc)%m);
    } // odd
} // expmod_helper
```

```
(define expmod
  (lambda (x n m)
    (letrec ([helper 
              (lambda (x n m so-far)
                (cond
                  [(zero? n)
                   so-far]
                  [(even? n)
                   (helper (* x x) (/ n 2) m so-far)]
                  [else ; n is odd
                   (helper x (- n 1) m (* x so-far))]))])
      (helper x n m 1))))
```

Whoo!  It looks fast.  And it works.  And that's probably the wrong
order to look at things.

### Let's trace it

```
emh (x, n, m, acc)
emh (2, 11, LARGE, 1) // Our initial call
  // n is odd
emh (2, 10, LARGE, 2*1)
  // n is even
emh (4, 5, LARGE, 2*1)  // x is 2^2
  // n is odd
emh (4, 4, LARGE, 4*2*1)
  // n is even
emh (16, 2, LARGE, 4*2*1) // x is 2^4
  // n is even
emh (256, 1, LARGE, 4*2*1) // x is 2^8
  // n is odd
emh (256, 0, LARGE, 256*4*2*1) // acc 2^8 * 2^2 * 2^1 * 1 = 2^11
  // n is zero
return acc // 2^11
```

### Our solution

```
long
expmod (long x, long n, long m)
{
  long result = 1;
  while (n > 0)
    {
      if (MOD(n,2) == 0)        // even
        {
          x = MOD(MULTIPLY(x,x),m);
          n = DIVIDE(n,2);
        }
      else
        {
          result = MOD(MULTIPLY(result,x),m);
          n = n-1;
        }
    } // while
  return result;
} // expmod
```

Damn!  We didn't save all that much.  But we did save 10% or so.

Note: We can make this a bit tighter.

Break
-----

_Our break came before turning the TR version into an iterative one._

Lessons
-------

* UM - Use Math [+1]
* Tracing is an important way to understand your code (when it works,
  when it doesn't work).
    * Debugging strategy, too.
    * When you have thorny problems, compare what you expect with what
      happens.
* Review of tail recursion (and its relation to iteration). [+2]
* "I'm better at StackOverflow than Sam."
* There's a performance analyzer from Google that we didn't learn how
  to use.
* Getting code right can take some time.
* Macros can help us avoid some duplication.
* Recursion to iteration can be a weird process; it depends on how the
  recursive algorithm is written.
    * It's good to practice.
    * Warning!  Not every recursive algorithm has a stack-free
      iterative equivalent.  (E.g., Quicksort may be impossible to
      do iteratively w/o a stack.)
* Don't optimize prematurely.
* Use Github or some other version control system.
* Makefiles can be helpful (and not too bad to write)
* C is fun(ny). 

Things Sam hoped were reinforced (in addition to the above)

* Tests help, particularly if you expect to evolve your code!
* Look for big improvements (n steps -> logn steps) before small.
* Code cross products.  Linking files in different ways can give
  you power.
* Macros allow you to do clever things, like turn counting on and off.
* Even experienced C programmers get things wrong.
    * And don't worry too much when they do.
* You have a responsibility to at least think about why your code
  might be correct.

Speaking of big improvements: Are there constant-time ways to
compute x^n, if we're okay with approximations?

WAG: Find the biggest power of 2 that's close and bit shift it.
Whoops.  That may be logarithmic.

Let's assume we can find log_e(x) in constant time.  Take a look
at the math.

x^n = e^(log_e(x))^n = e^(log_e(x)*n)

If you can do e^k quickly and log_e quickly, you can approximate
x^n quickly.

Before there were computers, you looked them up in books.
I don't know how log and e work right now.

Queues
------

Queues of strings.

Interface?

```
#ifndef __SQ_H__
#define __SQ_H__

// +------------------+----------------------------------------------
// | Type Definitions |
// +------------------+

typedef struct sq {
} sq;

// +-------------------+---------------------------------------------
// | Utility Functions |
// +-------------------+

/**
 * Add str to the queue, provided we haven't reached the limit.
 * If we reach the limit, returns 0.  Otherwise, returns 1.
 *
 * We allocate space for a copy of the string.
 */
int sq_enqueue (sq *q, char *str);

/**
 * Remove something from the queue, provided the queue is not empty.
 *
 * The client is responsible for freeing this string.
 */
char *sq_dequeue (sq *q);

/**
 * Check if the queue is empty
 */
? sq_empty (?);

/**
 * Check the front element (if the queue is nonempty)
 */
? sq_peek (?);

/**
 * Determine the size of the queue
 */
? sq_size (?)

#endif __SQ_H__
```

Implementation: Your task for next class.

Memory Errors
-------------

_We'll consider some issues and their effects._

### Use after freeing

Example 

    int *ip = (int *) malloc (sizeof (int));
    int *jp = ip;
    *ip = 5;
    free (ip);
    printf ("%d\n", *jp);
    *ip = (int *) malloc (sizeof (int));
    *ip = 42;
    printf ("%d\n", *jp);

Effects?

Other ways to "use memory after freeing"?

### Out-of-bounds memory access

Examples

Effects?

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

Avoiding Repetitive Code
------------------------

_For next class.  Left here to remind me._

### Detour: Meta-programming

### Meta-programming with macros

### Example, revisited

### Other examples

Parametric Polymorphism (Perhaps)
---------------------------------
