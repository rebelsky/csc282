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
* Notes from surveys
* Sample C code

Administrative stuff
--------------------

### General Notes

* Welcome back to campus!
* Hi, I'm Sam (or SamR).  
* Ned (Learnèd) is our class mentor.
* The class Web site is (or will be) at 
  <https://rebelsky.cs.grinnell.edu/Courses/CSC282/2022Sp/>.
    * The class Web site is (always) a work in progress.
* I type our class notes in a format called "markdown".  You should
  find it relatively readable.  It permits me to make nice Web pages.
    * Don't just rely on mine; evidence suggests taking your own notes 
      helps you learn.
* I have four C programs (or programming problems) to discuss.  We 
  probably won't get to them all.
* Your GitHub username may reveal your identity to your classmates.
  (Required warning.)

### Upcoming Activities

* Thursday extras today!

### Work for next Thursday

* [Suggest Unix Tools/Commands](../assignments/unix-tools)
* [Try to solve simple problems in Unix](../assignments/unix-tasks)
* Read Raymond, Chapter 1.
* Read Git book, Chapters 1 and 2.

### Attendance

* Sam will (attempt to) call you by first name.
* You will respond with 
    * Hi, my name is PROPER-NAME FAMILY-NAME.
    * I prefer that you call me NAME.
    * (Optional pronouns.)
    * Class year and major.
    * Highlight of Winter break.
    * (Optional question for me.  You'll also have other chances later.)

Notes from attendance
---------------------

* Visiting San Francisco.
* Visiting Seattle.
* Visiting Portland.
* Visiting Miami.
* Family! [x4]
* Good sleep.
* Applications for REU.
* Back home far away.
* Removing wisdom teeth.
* Walking dog (or vice versa).
* Living along / Adulting.
* Unwinding.
* Winter Soccer.
* Climbing rocks and boulders.
* Running.
* Good food [x2]
* Reading books
* Tv Shows and Movies [x2]
* Cross-Country Skiing.
* Downhill skiing.
* Using inferior email programs.
* Snowboarding.
* Help Desk!
* Cabining along with sliding on ice and climbing mountains. 
* Doing very little!

About the course
----------------

### What I hope you get out of it

* More comfort with GitHub
    * ITS policies meant that some/many of you did not learn GitHub
      in 207/324.
* Think better about C (and development for C)
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

What I learned from the survey
------------------------------

Why?

* Majority of you interested in more C.
* A few "I need a one-credit class".
* A few "It's a Sam class." or "I want to take more classes with the
  other folks in the CS community."
* A bit less "I should know Unix"

GitHub

* More of you know more and are more confident than I had thought.
* I guess I was expecting more folks who had one of the recent 207's.
* Some folks know essentially nothing.  That's okay.
* Confidence seemed to switch with `.gitignore` (more strongly disagrees)
* "Although I understand-ish git, I have a healthy respect (fear) of its power."
* "I struggle with complicated branch conflicts and some of the lesser-used Git commands (rebase…? Reset, revert, etc)"

Make

* Fewer people can use or are confident with Make.
* A few more expert Make users.
* A non-trivial number have never used Make.
* Just so you know, Make is a program that lets you automate build
  processes.  It's most typically used to build larger C programs,
  but it can be used for almost any set of interdependent build tasks.
    * CC is building a better Make.

The C Programming Language

* I was surprised to see that about half of you have written macros.
* The vast majority of you seem comfortable with multi-file C projects.
* The vast majority do not or cannot use debuggers.
* One interesting comment: "Alarming".
* C is Powerful and fearesome.

Unix

* Confidence and knowledge generally low; a few experts.

Goals / Comments

* "All of the above"
* "I want the personal integrity to work on learning computer science in my personal life but I resent this obligation".
* "I'm beginning to wonder if I'm even ready for this course or not."
* "sockets, cross-platform C, some of the stuff that make https://justine.lol/ape.html work"
* "Anything else you think a "modern" computer scientist should be embarrassed not to know."

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

* This is `strcpy`.
* Copies string `s` to string `t`.
* Returns a string equivalent to s.

How does it work?

* Dereference `t` and `s` and assign.  (`*t = *s`).  This
  stores the current character in s in the locatoin that t points
  to.
* Incrementing a pointer moves to the next character.

Why does the while loop terminate?

* Requires that we understand the value of an assignment expression.
* When the value of the assignment statement is 0.
* The value of an assignment statement is the value assigned.
* When we assign the null terminator in a string, the value of the
  assignment is 0.

Where does `t` point after this is done?

* The memory location after the copied `s` (after the null terminator)
* Why return that instead of, say, the original `t` or the original `s`
  or ...
    * So that we know where the end of the first string is.
    * We could find that, but it's expensive.
    * If we are appending a lot of strings using strcpy, this is
      much cheaper.
        * `tmp = strcpy(list-of-students, "Sam");`
        * `tmp = strcpy (tmp-1, ",Janet");`
        * `tmp = strcpy (tmp-1, ",Evening");`

What are the preconditions?  What do we need to know for the code to
work correctly?

* In order for this not to screw up massively, we need to ensure that
  the memory pointed to by `t` has at least `strlen(s)` additional
  space.
* Of course, every good programmer knows exactly how much space they
  have available through close analysis.
    * Or uses tools to help them identify why things break.
* Not worrying about this is why the Internet regularly breaks.

Alternative

    char *
    fun (char *t, char *s)
    {
      // Continue until we reach the end of the source.
      while (*s != '\0') 
        {
          // Copy a character
          *t = *s;
          // Move on to the next space
          ++t;
          ++s;
        }
      // Add the null terminator
      *t = '\0';
      t++;
      // And we're done
      return t;
    } // fun

What does it do?  (What's the goal?)
What should we have learned?

* C programmers think differently. 
* Pay attention to memory.
* Concise to the point of difficulty.  (Concision may have been
  necessary to fit your program in RAM.)

Thinking in C: Your second example
----------------------------------

_This example is adapted from Kernighan and Plauger, I think._

What does this do?

    int M[ROWS][COLS];
    for (int i = 1; i <= ROWS; i++)
    for (int j = 1; j <= COLS; j++)
    M[i-1][j-1] = (i/j)*(j/i);

Written a more readable form.

    for (int i = 1; i <= ROWS; i++)
      {
        for (int j = 1; j <= COLS; j++)
          {
            M[i-1][j-1] = (i/j)*(j/i);
          } // for each column
      } // for each row

Hypothesis 1: It assigns 1 to each element of `M`.  (Fills the matrix with 1's)

Hypothesis 2: It creates the identity matrix, more or less.  If
i and j are equal, you fill in a 1.  If i and j are not equal, the
one of the terms will be 0 and so the product will be 0.

Note: C programmers like clever tricks (perhaps because it makes others
feel dumb).

Thinking in C: Your third example
---------------------------------

_I've inserted this one because many of you said you were comfortable
with multiple-file projects._

Suppose I'm working on a semi-reusable math library that includes
a procedure, `long gcd (long x, long y)`.

What files would be part of the project?

What commands would we use to build the various executables?

Thinking in C: Your fourth example
----------------------------------

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

