---
title: "EBoard 10: Exploring your code (or mine)"
number: 10
section: eboards
held: 2021-05-06
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Q&A (not on readings)
* `expmod`, our new example
* Questions on expmod
* Break
* Questions on readings
* More fun with macros

Administrative stuff
--------------------

### General Notes

* Happy Thursday!  I hope you have a wonderful weekend.
* Congrats to those of you who were elected to Phi Beta Kappa last
  year or this.  (Today was PBK induction.)
* Sometimes I hate my Macbook.  Why do reboots take 1+ hours?  It
  was getting close enough that was starting to set up my iPad for class.
    * Class is less prepped than normal.  Sorry.  Or maybe "differently
      prepped".
* Those of you who aren't doing tasks will probably need to write a
  final reflection.

### New Topics

We have four class sessions left.  In addition to some random
smallish topics, I have two big topics left to cover: Command-line
processing and debugging.  What else would you like to cover?  (Yes,
I have other things up my sleeve; I'd just like to give you some
options.)

* GitHub
* What errors have I encountered in recent years?
* Databases SQL/NoSQL [Not really related to this course.]
* Vim or Emacs.

### Upcoming Activities

* Getting your start-up from idea to reality.  7pm, tonight
  https://grinnellcollege.webex.com/grinnellcollege/j.php?MTID=md2e94b3aa4d52df5c00ecdc15e4ed812
* The Grinnellian is Saturday, 2-6pm (ish) on graduation stage?
* ISO Cultural Evening Sunday on graduation stage at 7pm.

### Work for Tuesday

* Make a collaborative list of what kinds of things you would look
  at in a program when you get a segfault.
    * Make sure to pay attention to crashes that are caused by
      incorrect code elsewhere.
* Read some code (to be posted) and be prepared to explain what is wrong 
  with it.

Q&A
---

Review: Exponentiation
----------------------

Goal: Compute `(x^n) mod m`, where `x`, `n`, and `m` are all non-negative long 
values.  

Assume: x < m and m < sqrt(LONG_MAX).

Obvious solution:

```
long
expmod(long x, long n, long m)
{
  long result = 1;
  for (i = 0; i < n; i++)
    {
      result = (result * x) % m;
    } // for
  return result;
} // expmod
```

* We want to do the `mod` each time through so that we don't overflow.

Can we do a more efficient solution?

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
      long tmp = expmod (x, n/2, m);       // x^(2k) = x^k * x^k
      return (tmp * tmp) % m;
    } // even
  else // odd
    {
      long tmp = expmod (x, n-1, m);       // x^(k+1) = x^k * x
      return (x * tmp) % m;
    } // odd
} // expmod
```

The project
-----------

Let's put things together into a project.  What files will you create?

* `expmod.h`, declares `long expmod (long x, long n, long m);`
* Implementations (Note: We can choose which one to link.)
    * `expmod-recursive.c`, declares our recursive version of `expmod`
    * `expmod-slow.c`, declares our iterative, correct, and slow version
      of `expmod.
    * `expmod-bad.c`, declares the incorrect iterative version.
    * `expmod-iterative.c`, declares the (not-yet-developed) correct iterative
      version.
* Test files.
    * Correctness
    * Efficiency
* Sample programs to run the code.
    * em.c - Generates emr, ems, emb, emi

Detour - Rant
-------------

Why doesn't Teams tell you it's downloading?

Checking for correctness
------------------------

How can we make sure that this code (or any code) is correct?

* With a good test suite, including some strange outliers.
* Write it in a different language that verifies code correctness.
* Manual traces.
* Proof?

Checking for efficiency
-----------------------

I've claimed this version is more efficient in terms of calls
to multiplication, division, and exponentation.  How can we
check that (other than just manually)?

* Claim: The recursive version is O(logn) multiplications
* If our test suite does enough tests, we might observe a difference.
  E.g., using the `time` command or graphing the time for different
  inputs.  
* Do it using recurrence relations (kind of like proof).
* Instrument the program to count multiplications.
* Write a program that generates data.
    * We did so.  Even with the largest possible exponent, it's
      still less than two microseconds on SamR's computer.

How do we define `MULTIPLY` so that it can both increment a counter
and return a value?

```
#define MULTIPLY(X,Y) do { ++MULTIPLICATIONS; ((X)*(Y)); } while (0)
```

Doesn't work because it doesn't return a value.

```
#define MULTIPLY(X,Y) ((++_MULTIPLICATIONS * 0) + ((X)*(Y)))
```

From recursive to iterative
---------------------------

How can we turn that wonderful recursive solution into a 
slightly-less-wonderful, but somewhat-more-efficient iterative
solution?

Here's an incorrect solution submitted by a student.

```
long
expmod_iterative(long x, long n, long m)
{
  long result = 1;
 
  for (size_t i = 0; i < n; i++) 
    {
      if (!(n % 2)) // n is even
        { 
          long tmp = (result * x) % m; // calculate x^k 
          result = (tmp * tmp) % m;    // x^(2k) = x^k + x^k 
          n /= 2;                      // now we can halve n 
        } // n is even
      else // n is odd
        {
          result = (result * x) % m;
        } // n is odd
    } // for
  return result;
} // expmod_iterative
```

How can we tell it's incorrect?  How can we fix it?

Manually use this to compute 2^8.

Initially

* i = 0, result = 1, x is 2, n is 8, m is 100000
    * Check that n is even
    * tmp gets 2
    * result gets 4
    * n gets 4
    * i gets 1
* i = 1, result = 4, x = 2, n = 4, m is 100000
    * Check that n is even
    * tmp gets 8 (2*4)
    * result = 64
    * n gets 2
    * i gets 2
* i = 2 //
    * Terminate the for loop
    * Whoops!  2^8 is not 64
* If n is odd, this is no longer a divide and conquer algorithm, so
  it will be O(n) rather than O(logn)

Maybe we'll try again next time.

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
      return expmod (x*x % m, n/2, m);     // x^(2k) = (x^2)^k;  k = n/2
    } // even
  else // odd
    {
      long tmp = expmod (x, n-1, m);       // x^(k+1) = x^k * x; k = n - 1
      return (x * tmp) % m;
    } // odd
} // expmod
```

Generalizing
------------

How would our code change if we just wanted to compute `x^n`, where `x`
is a double and `n` is a non-negative long value?

Q&A on Readings
---------------

* What, if anything, did you find confusing?
* What would you like me to spend class time on?
* What would you like to try to do during class?

Avoiding Repetitive Code
------------------------

### Detour: Meta-programming

### Meta-programming with macros

### Example, revisited

### Other examples

Parametric Polymorphism (Perhaps)
---------------------------------
