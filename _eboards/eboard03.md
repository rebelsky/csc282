---
title: "EBoard 03: Software development in C"
number: 3
section: eboards
held: 2021-04-13
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff.
* A motivating problem.
* Building C library code.
* Testing a C function.
* Work time.
* Break.
* Testing a C function, revisited.
* Thinking in C, once again.

Administrative stuff
--------------------

### General Notes

* Hi, I'm still Sam (or SamR).
* The class Web site is still at
  <https://rebelsky.cs.grinnell.edu/Courses/CSC282/2021SpT2/>.
* Sorry for the delay in posting things.  I had thought that the
  rough notes in the eboard would suffice, but it is clear that 
  they did not.
    * The assignments for today will be moved to Thursday.
    * I have time assigned to getting more on the site tomorrow.
    * The class Web site is (always) a work in progress.
* I'm giving up on the survey about background knowledge.
* Things I keep forgetting to say: _This course falls into the
  "What you put into it is what you get out of it" model._  That
  is, although you will pass as long as you try, you'll get the
  most out of it by engaging actively and taking risks.

### Upcoming Activities

* Convo, Thursday, Karla Erickson on I/Robot.

### Work for Thursday

* Generalize `top-five` to `top-n`.  **You _may_ limit the line size, but
  not the number of lines.**
* Write a program `pipe-to-file fname` that reads from stdin and puts
  output both to the given file and to stdout.
* Write a C program that strips spaces from the end of the line.
  **You may not rely on some arbitrary line size!**
* Readings based on what we might have learned today.

Q&A
---

Will you punish us for doing no work this past week?

> Nope.  That's my fault.

Why doesn't `indent` work the way you promised?

> It's the wrong `indent`.  You need GNU indent.  Not old BSD indent.

> For now, you may have to do it by hand.

For updating top-5 to top-n.  How much do we have to keep?

> Up to you.

Motivating example
------------------

*Many ideas in this example are borrowed from Jon Bentley's
_Programming Pearls_*

Today's motivating example: Suppose we are writing a binary search
routine that we expect to make available as part of a library.

    /**
     * Find an index of v in a, which is sorted in non-decreasing
     * order.  If v does not appear in a, returns -1.
     *
     * Pre: For all i, 0 < i < n, a[i-1] <= a[i].
     * Post: Let j = binarySearch(v, a, n).  If j == -1, then there 
     *   does not exist an i s.t. v = a[i].  Otherwise, v == a[j].
     */
    int binary_search_ints (int v, int a[], int n);

* What files do you expect to create (by hand or via code) as you 
  develop your library?  
* What tests would you write?  (High level or in C)

Files for the project
---------------------

`Makefile`
  : To help us put things together

`bs.h`
  : Information for the client

`bs.c`
  : Implement the procedure

`bs.3` or `README.txt`
  : Man page!

`bsi-test.c`
  : Some sort of testing

`libbs.so`
  : The shared library we want to build

`libbs.a`
  : A different kind of shared library

`bsi.c`
  : A simple application to use with the procedure, perhaps for testing.

Tests
-----

Generally, testing provides correct inputs to verify that that procedure provides correct outputs.

### Using hand-written C.

    /**
     * bsi-test.c
     *   The CSC-282-01 Spring Term 2 tests for binary_search_ints
     */
    #include "bs.h"

    int tests = 0;
    int failures = 0;

    void
    test (char *msg, int v, int a[], int n, int expected)
    {
      ++tests;
      if (binary_search_ints (v, a, n) != expected) {
        printf ("FAILED: %s\n", msg);
        ++failures;
      }
    } // test

    int 
    main (int argc, char *argv[])
    {
      // Not in the array
      int five[] = { 1, 2, 3, 4, 5 };
      test ("zero in five", 0, five, 5, -1);

      // In the array, including least, greatest, middle, ...
      // Maybe using for loops for efficiency.
      test ("three in five", 3, five, 5, 2);
      test ("one in five", 1, five, 5, 0);
      test ("four in five", 4, five, 5, 3);
      test ("two in five", 2, five, 5, 1);
      test ("five in five", 5, five, 5, 4);

      // Empty array
      ++tests;
      int empty[0];
      test ("empty array", 0, empty, 0, -1);

      // Some special arrays and special positions

      // Finish
      printf ("Failed %d of %d tests.\n", failures, tests);
      return failures;
    } // main

### A broader conceptual approach

Instead of writing a few particular examples, write a general testing thing.

    for each array size from 0 to 33
      fill the array with even integers from 0 to 2*(n-1)
      for each i from 0 to n-1, 
        ensure that binary search finds 2*i at position i
        ensure that binary-search does not find 2*i-1 
      ensure that binary search does not find 2*n
      note: If we can count steps, we should also assess the run time

Further experience is that generating "random" inputs systematically
can also reveal errors.

   for larger array sizes, generate an array with random contents
   (that is sorted), and check every position (and, perhaps, between
   every pair of positions).

### Use some magic validation tool

Not sure which one.  Student suggestion: DAFNY  
<https://github.com/dafny-lang/dafny>

Break
-----

5 min

Programming Project
-------------------

You can find the `bs.h` file and the `bs.c` file at
<https://rebelsky.cs.grinnell.edu/Courses/CSC282/2021SpT2/examples/binary-search/>.

Upload your results to the Task 3a channel on Teams.

Tests, Revisited
----------------

Our first version crashed.

* Add print statements.
* Use a debugger.
* Analyze the code by hand.

Side note: Commenting out code in C
-----------------------------------

As many of you know, there are times we want to "comment out" code
to make it unavailable to the compiler.  What are the techniques you know?

Thinking in C: Another example
------------------------------

_This example is adapted from Kernighan and Plauger._

What does this do? (TPS)

    for (int i = 1; i <= ROWS; i++)
    for (int j = 1; j <= COLS; j++)
    M[i-1][j-1] = (i/j)*(j/i);

How should you write it if you wanted to be clear?

Thinking in C: Yet another example
----------------------------------

To illustrate my point that understanding memory in C is important,
let’s continue with a problem that a friend gave to me a while ago.
He showed me the following fragment of C code.

    x = malloc (...);
    foo ();
    bar ();
    free (x);

The program was crashing on the call to `free`.

Here are some things they discovered.

* If they removed the call to `free`, the program ran through to completion.
* If they moved the call to `free` before the call to `bar`, the program ran 
  through to completion.
* They had no calls to `free` in `bar`.

What is likely to be wrong with their code? How would you trace the error?

_TPS_
