---
title: "EBoard 01: Getting Started"
number: 1
section: eboards
held: 2022-01-27
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Lots of administrative stuff, including attendance
* Some course background
* Approximate learning goals
* Sample C code

Administrative stuff
--------------------

### General Notes

* Welcome back to campus!
* Hi, I'm Sam (or SamR).  
* Ned is our class mentor.
* The class Web site is (or will be) at 
  <https://rebelsky.cs.grinnell.edu/Courses/CSC282/2022Sp/>.
    * Sam: Don't forget to put that in the chat.
    * The class Web site is (always) a work in progress.
* I type our class notes in a format called "markdown".  You should
  find it relatively readable.  It permits me to make nice Web pages.
    * Sam: Don't forget to show off today's eboard.
    * Don't just rely on mine; evidence suggests taking your own notes 
      helps you learn.

### Upcoming Activities

### Work for Tuesday

### Attendance

* Sam will (attempt to) call you by first name.
* You will respond with 
    * Hi, my name is PROPER NAME.
    * (Optional pronouns.)
    * If you must call me by last name, please call me Mr./Ms./Mx./Scholar
      FAMILY NAME.
    * I'm taking CSC-282 because ...
    * This semester , I am excited about ....
    * (Optional question for me.  You'll also have another chance later.)

Stuff from attendance
---------------------

### Taking CSC-282 because

### Excited about

### Q&A

About the course
----------------

### What I hope you get out of it

* Think better about C
    * Understand some command-line flags and how to (ab)use them
    * Think better about memory and how malloc works
    * Get used to building larger C program
    * Have you written a C program with multiple files?
    * Macros
    * Make
* Think better about Linux/Unix/etc., at least from the interaction level
    * Important tools: sed, grep, cat, tr, cut, ...
    * "Thinking in Unix": Small tools, combined well, using text files (and open)
    * Using bash (maybe other shells) and basics of bash scripting
    * Other scripting?
* Think better about programming?
    * Testing
    * Some design issues
    * Testing
    * Style

### Your roles and responsibilities

The class assigns one credit.  According to the registrar, that represents
45 hours of work.  45/14 = about three hours per class period.  You are
in class for 80/180 = 4/9 of those.  About 5/9 of three hours outside of 
class (which will probably end up being closer to two hours).

To get an S

* Show up to at least twelve of fourteen classes
* Participate actively during class
* Attempt homeworks and readings

### Some issues 

* Different backgrounds.  (Year in Grinnell, experience in 161, etc.)
  (Gap since last took C, etc.)
    * Be kind to others
    * Be willing to take risks
* Sam is trying to be kind to himself.
* We can still be successful together.
* And have fun!

### Site and schedule

* The site is now live-ish.  Time for a quick walkthrough.
* The schedule is adaptable.  I will plan for change.

Thinking in C: Your first example
---------------------------------

You might know this from the reading, but I'm repeating it anyway.
I've reformatted it slightly from the original in K&R.

    char *
    fun (char *t, char *s)
    {
      while (*t++ = *s++);
      return t;
    } // fun

What does it do?  (What's the goal?)

How does it work?

Where does `t` point after this is done?

What are the preconditions?  What do we need to know for the code to
work correctly?

How can we make it better?

What should we have learned?

Thinking in C: Your second example
----------------------------------

_This example is adapted from Kernighan and Plauger, I think._

What does this do?

    for (int i = 1; i <= ROWS; i++)
    for (int j = 1; j <= COLS; j++)
    M[i-1][j-1] = (i/j)*(j/i);


Thinking in C: Your third example
---------------------------------

_This one will be fun, because I'll need to figure it out again._

To illustrate my point that understanding memory in C is important,
let’s continue with a problem that a friend gave to me a while ago.
He showed me the following fragment of C code.

    x = malloc (...);
    foo ();
    bar ();
    free (x);

The program was crashing on the call to free.

Here are some things they discovered.

* If they removed the call to `free`, the program ran through to completion.
* If they moved the call to `free` before the call to `bar`, the program ran 
  through to completion.
* They had no calls to `free` in `bar`.

What is likely to be wrong with their code? How would you trace the error?

