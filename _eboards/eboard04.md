---
title: "EBoard 04: Fun with C and Linux"
number: 4
section: eboards
held: 2021-04-15
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff.
* C, continued
    * Side note: Commenting out code in C.
    * Testing a C function, revisited.
    * A few of your tasks
    * Thinking in C, once again.
* Break
* Unix, revisited
    * Tools!
    * Raymond, Chapter 1

Administrative stuff
--------------------

### General Notes

* Reminder to self: Attempt to write binary-search in DAFNY.

### Upcoming Activities

* CS Table, Monday, Noon.  (Info forthcoming.)

### Work for Tuesday

_Remember to check the eboard for these tasks.  I'll try to get them in the syllabus, but I am imperfect and behind, on my best days._

Readings on Unix

* [Unix file basics](https://rebelsky.cs.grinnell.edu/musings/cnix-bash-basics-files)
* [Unix file permissions](https://rebelsky.cs.grinnell.edu/musings/cnix-file-permissions)
* [Command-line history](https://rebelsky.cs.grinnell.edu/musings/cnix-command-line-history)

Readings Sam hasn't written yet

* [The shell](https://rebelsky.cs.grinnell.edu/musings/cnix-bash) *forthcoming*
* [Input and output redirection](https://rebelsky.cs.grinnell.edu/musings/cnix-bash-io) *forthcoming*

Readings on binary search in C (optional)

* [Part the first](https://rebelsky.cs.grinnell.edu/musings/cnix-binary-search-1)
* [Part the second](https://rebelsky.cs.grinnell.edu/musings/cnix-binary-search-2)
* [Part the third](https://rebelsky.cs.grinnell.edu/musings/cnix-binary-search-3)

Fun tasks

* Pick three Unix command-line tools and find at least two useful command-line flag for each.
* Invent or find three pipes of at least three non-trivial commands (no `cat` or `less`) that do something fun, interesting, or surprising.

Q&A
---

Did you figure out why `indent` is not working correctly?

> Nope.

I own my code.

> Yes, you do.

I'd prefer that you post it with my name.

> That's fine.  But let me tell you a story.

Can we return to the binary search examples?

> Certainly.  It's up a little bit after we're done with Q&A.

Side note: Commenting and Commenting out code in C
--------------------------------------------------

As many of you know, there are times we want to "comment out" code
to make it unavailable to the compiler.  What are the techniques
you know?

There are a lot of reasons we comment.

* Comments on procedures to guide those who will use them in the future
  (including ourselves).
* Comments within code to help those stuck with maintaining or updating
  the code.
    * Comments on data structures / classes / globals / etc.
* Comments within code before the code to provide a high-level overview
  of what we plan to write.
* Comments to "remove" code.
* Jokes for the attentive reader.

The one comment in the code Sam was stuck translating.

        (define byte 8) ; bits

How do we "comment" or "comment out" code in C?  (How do you tell the
compiler to ignore text you've inserted in the file?)

* We can use `//` (double forward-slash).  Comments out everything from
  there to the end of the line.
* We can use `/*` to open a comment and a `*/` to end the comment and
  everything in between is ignored.
    * Unfortunately, in many/most versions of C, you cannot nest `/* ... */` 
      comment.
    * So ... If you like to comment out code with `/* ... */`, don't use
      those for "shorter" comments.
* Side question: What does the GNU standard say about comments
    * Do them. Use `/* ... */` in general.
    * <https://www.gnu.org/prep/standards/html_node/Comments.html#Comments>.

Detour

* "I want to index my C arrays starting at 1."
* So, `int *vals = malloc(10 * sizeof(int)); val -= 1;`
* You have no sense of beauty.

Back from detour.  How else do we comment out code?

* The C Preprocessor has a wonderful feature where you can include
  code only in certain situations.

        #ifdef NAME
        code
        #endif // NAME

* If you  must comment out code, that's a good strategy, perhaps 
  better than the `/* */` style.
* Note: If you use a good version control system, you should delete
  code instead of commenting it out.  (Yes, you can consider `git`
  a good version control system.  `mercurial`, `svn`, etc. are all
  good enough for those purposes.)
* `ifdef` is not designed for commenting out code; rather, it is
  designed to allow you to choose whether or not to include some
  code.

### Strange example

```
int
main (int argc, char *argv[])
{
#ifdef GREET
  /* Print a greeting. */
  printf ("Hello\n");
#endif

  /* Print a goodbye. */
  printf ("Bye\n");
} // main
```

Compiling and running with and without the greeting.

```
$ cc -DGREET silly.c -o silly
$ ./silly
Hello
Bye
$ cc silly.c -o silly
$ ./silly
Bye
```

Testing Binary Search, Continued
--------------------------------

History: We tried to write binary search on Tuesday.  We generally failed.
We could tell we failed because the awesome Bentley-inspired test suite
caught errors.  Amazingly, even though one procedure was recursive and
one was iterative, both failed on a similar input.

So let's figure out why ...

* Fixed!
* Testing helped us identify a sample input that failed.
* Debugger helped us identify where the code went wrong.
* Careful logic (thanks Stu) helped us fix the problem once we identified.

Break
-----

5 min

Top `n`
-------

_Whoops.  Harder than we thought.  Some of us spent too long._

Note: Insertion sort is your friend.

Piping to files
---------------

_Only two submissions.  So sad.  Which should we critique? _

Trimming
--------

### Here's a cool strategy

* Use getc and putc to do a character at a time.
* When you hit a space, start keeping track of the number of spaces
  you've seen.
* Three options:
    * Another space, increment counter.
    * Newline, reset the counter to 0 and print the newline
    * Otherwise, you print the appropriate number of spaces, print the
      character, and reset the counter to 0.
* This will fail if you have more than 2^31 or so spaces in the middle 
  of the line.

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

Linux Tools for your toolkit
----------------------------

_Taken from Task 2b._

How do you learn *nix tools?

* Finding they exist.
* When you have a related problem, do Web search to find the tool
* Use it
* Take notes
* Eventually, it becomes closer to second nature.

### `ls`

_No, that's not "ones"._

* Lists files, in multiple ways
* Most common uses `ls -l`, `ls -a`, `ls -R`, `ls -t`

### `man`

_Everyone's favorite gendered command._

* Gives you information on standard operations and library routines
* `man command` - basic information on a command
* `man SECTION command` - gives information from a particular section
  section 1 is command-line tools, 3 is library functions
* `man -k term` - Looks up all the man pages with the given term in their short description

### `du`

_What does du do?_

* Disk usage command
* `du -h DIR` tells you how much is used by DIR and everything within it.
* Detour: "Kilobyte" has two interpretations: 2^10 (1024) bytes or
  1000 bytes (which is what Kilo is supposed to mean).  Similarly,
  "Megabyte" can be 2^20 bytes or 1,000,000 bytes or 1.000.000 bytes

### `grep` (or `egrep`)

_Grinnell's excellent program_

* Procedure to search files and directories.
* `grep PATTERN FILES`
* `grep -R PATTERN DIR`
* `grep -l PATTERN FILES`

### `tr`

_Is that pronounced "tiara" because it's the crown of commands?_

* Translate characters.
* `tr 'SOURCE SET' 'TARGET SET'`
* Write your own Caesar Ciphers

### `tar`

_A sticky substance.  Also "**t**ape **ar**chive"._

* Combines files

### `uniq`

_Kind of like Unix, I think._

* Removes duplicate lines that apppear in immediate succession

### `sort`

_I wonder what this is an abbreviation for._

* Sorts.  Duh.

### `head` and `tail`

_Can you write Scheme in the shell?_

* Let you look at parts of files.

### `cut`

_Sounds dangerous._

* Extracts columns.

### `kill`

_Sounds even more dangerous._

* Stops runaway (and other) processes.
* `killall teams`

### `which`

_No, not `witch`._

* Where is a command

### `file`

_Learn about file types._

Raymond review (TPS)
--------------------

_Let's pretend that Sam has not reread Raymond in five years, and that
half of your classmates neglected to do the reading.  What are the key
takeaways from the Raymond reading?_

Scripting languages for your toolkit
------------------------------------

### bash (the Bourne-Again Shell)

Thinking in C: Another example
------------------------------

_This example is adapted from Kernighan and Plauger._

What does this do? (TPS)

    for (int i = 1; i <= ROWS; i++)
    for (int j = 1; j <= COLS; j++)
    M[i-1][j-1] = (i/j)*(j/i);

How should you write it if you wanted to be clear?

Thinking in C: A repeated example
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

