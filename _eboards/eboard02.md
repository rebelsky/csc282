---
title: "EBoard 02: Important *nix concepts"
number: 2
section: eboards
held: 2021-04-06
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Our problem sets
* Common approaches to problems in *nix
* Raymond review
* Break
* Some important *nix tools
* More fun with C

Administrative stuff
--------------------

### General Notes

* Hi, I'm still Sam (or SamR).
* The class Web site is still at
  <https://rebelsky.cs.grinnell.edu/Courses/CSC282/2021SpT2/>.
    * Sam: Don't forget to put that in the chat.
    * The class Web site is (always) a work in progress.
* I will not be here this Thursday, so there will be no class.  
    * That's okay, the College cleverly put 36 days in Spring Term 2
      so that we can still get 14 class days.
* Whoops!  I forgot the survey about background knowledge.  C'est
  la vie.  Maybe I'll post one this week.
* Things I keep forgetting to say: _This course falls into the
  "What you put into it is what you get out of it" model._  That
  is, although you will pass as long as you try, you'll get the
  most out of it by engaging actively and taking risks.
* I'm a bit concerned about how few of you tried the tasks.  At
  minimum, every one of those could have been solved with a small
  C program.

### Upcoming Activities

* Tuesday, 6 April 2021, 7 p.m.   Student Poetry reading.
  Students from the _Poetry & Performance_ short course (Eng/GWSS
  195) give a live Zoom reading of the poems they’ve crafted under
  the mentorship of award-winning poet jessica Care moore. In this
  course, students studied and wrote poetry that embodies language
  as an act of survival. Inspired by readings from Ntozake Shange,
  Sonia Sanchez and Audre Lorde, Rachel Eliza Griffiths, Honorée
  Jeffers, Tongo Eisen Martin and more, students explored the
  intersection of poetry on the page and interdisciplinary performances
  of poetry as spoken word. Hosted by jessica Care moore!
     * Zoom link: https://grinnellcollege.zoom.us/s/94032165359
* Thursday, 8 April 2021, 5 p.m.  MyroC with Robots: Motion, Timing,
  and Image Processing.
     * Meet in Events Channel in CS Team
     * <https://teams.microsoft.com/dl/launcher/launcher.html?url=%2F_%23%2Fl%2Fmeetup-join%2F19%3A38d7f998b38b475a8d40b9ff0f251590%40thread.tacv2%2F1617302166870%3Fcontext%3D%257b%2522Tid%2522%253a%2522524f9e3e-faca-4f64-b3ec-adb2baee8807%2522%252c%2522Oid%2522%253a%2522f7dc2dcf-f51e-4db6-8b36-8bb68a9c4b9e%2522%257d%26anon%3Dtrue&type=meetup-join&deeplinkId=1207c182-6182-41fe-b4cd-adadd194b4e4&directDl=true&msLaunch=true&enableMobilePage=true&suppressPrompt=true>
     * Robots are fun.

### Work for next Tuesday

* Stay tuned!  Coming via email.
* Generalize `top-five` to `top-n`.  **You _may_ limit the line size, but
  not the number of lines.**
* Write a procedure `pipe-to-file fname` that reads from stdin and puts
  output both to the given file and to stdout.
* Write a C program that strips spaces from the end of the line.
  **You may not rely on some arbitrary line size!**
* Readings forthcoming.

Q&A
---

Are the robots awesome?

> Yes, particularly when they fail to work properly.

Will you teach us Unix-style regexps?

> Yes.

Will you teach us a bit about vi/vim/neovim/emacs/whatever else?

> Maybe.

Will you teach us about the stupid !'s you use?

> Yes.

Our coding tasks
----------------

### Convert `\r\n` to just `\n`

A bit of (silly) history.  Typewriters had this lever that (a) moved
you to the next line and (b) shoved the carriage back to the right.
In the Unix world, we used `\n` to represent that action.  ("Newline")
It is possible to go to a new line without resetting the carriage.
The designers of DOS (aka Young Bill) decided we should have both
characters.  Amazingly, no one has ever reconciled the two worlds.
If you're not careful, things work poorly on the other platform.
Steve Jobs, unwilling to follow standards, forced his programmers
to use only `\r`.

What are strategies we can use to fix that problem?

* One option: Use `sed`.  Sed is the "stream editor".  Takes a sequence
  of characters as output, produces a sequence of characters as output,
  and does any list of commands to the input sequence.
    * `s/\r\n/\n/g`
    * "Substitute" (parameters separated by slashes)
    * For the pattern `\r\n` 
    * The result `\n`
    * g flag to say "every instance on the same line"
    * Note: sed permits regular expressions for patterns.
    * Reminder to Sam: Teach them (or ask them about) regular expressions
    * If you do not know *nix-style regular expressions, let me know.
* Another: Use `tr`, which translates or deletes characters.
    * `tr -d '\r'
    * Problem: Will remove the `\r` anywhere in the line.  (But who
      uses `\r` except for `\r\n`?)  (See note above.)
* Another: Write a C program.
    * "I can write that C program in two minutes." 
* How can we see the `\r\n`?
    * The amazing `od` command: Octal dump.  It lets you look at the
      underlying data as characters or hex digits or ....
* Another: `dos2unix`, which is not installed by default on most Linux
  systems, but which should be.

### Remove blank spaces at the ends of lines

* We can use `sed` again.  
* We could write a C program.
* We could open the file in `vi` and type an appropriate command.

### Convert a file to lowercase

* We could write a C program.
* We could write a Sed one-liner.  `sed 's/\(.\)/\L\1/g'`
* We could  use `tr` (this is often a standard use of tr).
* We might use a text editor.
* We might use your favorite scripting language (e.g., Perl, Python)
* Warning! Don't be US centric!

### Find the names of the people with the five highest grades on HW2

* Chain together Unix commands: 
    * `grep` searches
    * `sort` sorts
    * `head` takes the first few values (or `tail`)
        * There are advantages to `head`
* Write a C program
* Write a script in one of our favorite scripting languages (bash,
  Perl, Python)
* But how do we extract just the names (last,first)?
    * Use `sed` again
        * `| sed -e 's/,[^,]*,[^,]*$//g'`
    * Use `cut` (the more Unix commands you know, the more efficient
      you are, at least until you start to confuse them with each other)

Common approaches to problems in *nix
-------------------------------------

_What are some strategies you saw here?_

* Chain together existing *nix commands (sometimes a chain of one)
* Write a C program (sometimes to put in your chain)
    * With enough practice, simple stuff in C can be churned out
      quickly, as long as you don't care about using it again.
* DuckDuckGo it.
* You can use a scripting environment, like R or Bash or Perl or Python
  or Racket.
    * The designer of Perl built it for combining all the everyday things
      you want to do in the shell, with a bit more uniform interface.

Fun with C (TPS)
----------------

Identify positive and negative aspects of each of these.

### Convert to lowercase

See [`examples/file-downcase/downcase.c`](../examples/file-downcase/downcase.c).

```
/* 
 * Some Student <student@grinnell.edu>
 *
 * TASK: Given a standard text file, convert all uppercase letters to
 * lowercase.
 *
 * Usage: To convert an input text file to all lowercase letters, pass the
 * name of the input file and the desired output file name as command-line
 * arguments.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    /* checks to see if there was a file argument passed */
    if (argc != 3) {
        fprintf(stderr, "usage: lower <input>.txt <output.txt>\n");
        exit(EXIT_FAILURE);
    }

    /* opens the input file for reading and checks for errors */
    FILE *in_fp;
    if (!(in_fp = fopen(argv[1], "r"))) {
        fprintf(stderr, "error: fopen failed\n");
        exit(EXIT_FAILURE);
    }

    /* opens output file for writing and checks for errors */
    FILE *out_fp;
    if (!(out_fp = fopen(argv[2], "w"))) {
        fprintf(stderr, "error: fopen failed\n");
        exit(EXIT_FAILURE);
    }

    /* 
     * iterates over the characters in the input file until it hits EOF,
     * writing the lower-case version of each character to the output file.
     *
     * note: tolower will leave non-alphabetical and lowercase letters
     * unchanged, so we don't have to check for either
     */
    char ch;
    while ((ch = getc(in_fp)) != EOF) {
        putc(tolower(ch), out_fp);
    }

    fclose(in_fp);
    fclose(out_fp);
}
```

* "I like that it verifies the parameters", except ...
    * Either go "whole hog" or do nothing.  This takes a middle ground.
    * We could write it so that fewer arguments have semantics
      (e.g., one argument is print to stdout rather than to a file,
      zero arguments is input from stdin and output to stdout).
    * You should use `argv[0]` as the command name, rather than
      hard-coding it.
    * Failed input file and failed output file should have different
      error messages.
    * If you can't open the output file, shouldn't you close the
      input file?
    * Should I issue errors if the `fclose` fails?
    * Will this work if the input file and the output file are the same?
      Nope.  It clobbers it.  We might fix that.  Or we might warn the
      user.
* Consider switching to `do { } while`. NO.
* "Foolish consistency is a hobgoblin of small brains" (like Sam's)
    * If you exit explicitly in one place, you should make sure to always
      explicitly exit.
    * Consider different return values for different error conditions.
* The core loop is nice and concise; written how most C programmers would
  write it.
    * Agreed!
    * `getc` returns an integer.  Should we really store it in a char?
    * And should we be comparing it to -1.
    * "It seems to work" and "I'm confident it will work on most platforms"
      are different things.
* The comments help!  I particularly like the comment about `tolower`.
* Please follow style guidelines.  Sam expects you to use the GNU Style
  Guidelines.

### Top five

See [`examples/top-five/top-five.c`](../examples/top-five/top-five.c).

```
/*
 ============================================================================
 Name        : grades.c
 Author      : Student Name
 Version     :
 Copyright   : Your copyright notice
 Description : Prints the five highest grades from HW2 in a CSV file
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATA_FILE "grades.csv"
#define LINE_LENGTH 100
#define STRING_LENGTH 256

int main(int argc, char* argv[])
{
    FILE* stream = fopen(DATA_FILE, "r");

    if(stream == NULL)
    {
        fprintf (stderr, "%s: Cannot open %s: %s\n",
                 argv[0], DATA_FILE, strerror(errno));
        return -1;
    }

    char line[LINE_LENGTH][STRING_LENGTH];
    int i;

    for(i = 0; i < LINE_LENGTH; ++i)
    {
        strcpy(line[i], "");
    }

    char storeString[STRING_LENGTH];

    i = 0;
    while(fgets(storeString, STRING_LENGTH, stream))
    {
        if(strstr(storeString, "HW2"))
        {
            int storeLength = strlen(storeString);
            int characterNum = 2;
            for(int j = storeLength - 1; j > storeLength - 4; --j)
            {
                line[i][characterNum--] = storeString[j];
            }
            ++i;
        }
    }

    int mainArr[5];
    for(i = 0; strcmp(line[i], "")/* line[i] != NULL */; ++i)
    {
        int currNum = atoi(line[i]);
        if(currNum > mainArr[0])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = mainArr[1];
            mainArr[1] = mainArr[0];
            mainArr[0] = currNum;
            continue;
        }
        if(currNum > mainArr[1])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = mainArr[1];
            mainArr[1] = currNum;
            continue;
        }
        if(currNum > mainArr[2])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = mainArr[2];
            mainArr[2] = currNum;
            continue;
        }
        if(currNum > mainArr[3])
        {
            mainArr[4] = mainArr[3];
            mainArr[3] = currNum;
            continue;
        }
        if(currNum > mainArr[4])
        {
            mainArr[4] = currNum;
            continue;
        }
    }

    for(i = 0; i < 5; ++i)
    {
        printf("%d ", mainArr[i]);
    }

    return 0;
} // end of program
```

Some thoughts

* Brave to try this.  It mostly works.
* Does not follow the GNU style guidelines.
* Comments!  What are comments?
* Line length is hardcoded.
    * How do we avoid that?  `malloc`
* Number of input lines is limited.
    * Note that the algorithm would not be much different if we
      just added each line as in the second half.
* Number of processed lines is limited.
* It's okay for quick hacks to have hardcoded values!
* Some stray comments.
* That middle code should be generalized.
* I would rather read from `stdin` than hard-code a file name.
* At some point, consider generalizing your comamnd-line processing code.

Break
-----

* Always plan for a break.
* Accept that sometimes it falls in the middle of an exercise.

Today's evil question (TPS)
---------------------------

How do I get rid of the cruft in this directory?

```
$ ls
'*'   important   MyThesis/   -rf  '-rf *'
```

Pause for Q&A
-------------

Why use stdin rather than a file name for a quick hack?

> Easier to test when things go wrong.

> Easier to use in more cases without changing it.  (You can always change
  your input with `<` or with `|`.)

> Filters are standard Unix approaches, which makes it easier to use
  with other files.

> No need to remember the file opening and closing commands.

What do `<` and `|` do?

> If you type `command < filename`, it reads the input from the given
  file.

> If you type `command-1 | command-2`, the output of `command-1` is the
  input to `command-2`.  

> The second allows us to chain things together.

> If you want `command-1` to take input from a file, you use
  `command-1 < file | command-2`.

> Most would type `cat file | command-1 | command-2`.

> `cat` is short for "can anybody type?"  (or "concatenate")

What happens if you have a command with no output, such as in
`command1 > file | command2`?

> In that particular case `command1` will put its output in the file,
  and command2 will read empty input.  (I think.)

> There is a command to split your output to a file, but I don't remember it.

> You could also write that command.

END OF CLASS!!!
---------------

We're done.  I'll move the rest to the next class (or maybe just "another
class").

Linux Tools for your toolkit
----------------------------

_Taken from Task 2b._

How do you learn *nix tools?

### `ls`

_No, that's not "ones"._

### `man`

_Everyone's favorite gendered command._

### `du`

_What does du do?_

### `grep` (or `egrep`)

_Grinnell's excellent program_

### `tr`

_Is that pronounced "tiara" because it's the crown of commands?_

### `tar`

_A sticky substance.  Also "**t**ape **ar**chive"._

### `uniq`

_Kind of like Unix, I think._

### `sort`

_I wonder what this is an abbreviation for._

### `head` and `tail`

_Can you write Scheme in the shell?_

### `cut`

_Sounds dangerous._

### `kill`

_Sounds even more dangerous._

### `which`

_No, not `witch`._

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

