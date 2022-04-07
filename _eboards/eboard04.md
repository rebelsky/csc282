---
title: "EBoard 04: Back to Unix"
number: 4
section: eboards
held: 2022-02-17
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrivia
* Approaches to the problems from two weeks ago
* Generalizing those approaches
* Notes from TAoUP

Administrivia
-------------

* Don't forget to fill out the Data Buddies survey.
* Don't make fun of the second-year students for the joy of finding
  an advisor in the CS department.

### Upcoming work

* Readings are posted to the Web site.
* [Assignment: Write a shell script to do something nontrivial](../assignments/shell-scripts)

Review Approaches to Problems
-----------------------------

### Detour: `od`

`od` is "octal dump", useful for seeing hidden characters in files
(and also seeing different representatoins of binary files).

We used it to see carriage returns before newlines.

We discovered that a Project Gutenberg file had some hidden characters
at the beginning.  Why?

* The NSA is spying on us / It's part of new Russian/Israeli/??? spyware.
* At some point, some group decided to add some hidden characters to the
  start of not-quite-ASCII text files to indicate that they are not quite
  ASCII.

### Given a DOS-formatted text file (lines end with \r\n rather than just \n), convert it to a standard text file

Use `tr`.  `tr SET char < FILE.txt` replaces any element in the SET with
the given character.  (`tr` is short for translate)

        tr -d '\r' < FILE.txt

Use `sed`.  `sed` is the "stream editor", a non-interactive text editor.

        sed -i 's/\r//' FILE.txt

Note that that overwrites the file.

What else could you do?

        dos2unix FILE.txt

Write a C program

        /**
         * Strip all the \r's from a file.
         *
         * The CSC282 Collective.
         *
         * <Insert Arbitrary FLOSS license>
         */

        #include <stdio.h>

        int
        main (argc, char *argv[])
        {
          int ch;
          while (ch = fgetc (STDIN))
            {
              if ('\r' != ch)
                fputc (ch, STDOUT);
            } // while
          return 0;
        } // main

Note: We deleted the following because it was unclear.

              if ('\r' == ch)
                ;
              else
                fputc (ch, STDOUT);

And our fixed code looks like this.

    int
    main (int argc, char *argv[])
    {
      int ch;
      while ((ch = fgetc (stdin)) != EOF)
        {
          if ('\r' != ch)
            fputc (ch, stdout);
        } // while
      return 0;
    } // main

What would we do differently if we only wanted to remove the '\r' when
it comes before '\n'?

### Given a standard text file, convert all uppercase letters to lowercase

Use something very specific to the situation

* translatelctouc doesn't exist.

Use `tr`

* `tr [:lower:] [:upper:] < FILE.txt`

Use `sed`

* `sed -e 's/[a-z]/???/g'` ; Sam isn't sure, even though he uses Sed.

Use C

    #include <stdio.h>

    int
    main (int argc, char *argv[])
    {
      int ch;
      while ((ch = fgetc (stdin)) != EOF)
        {
          if (('a' <= ch) && (ch <= 'z'))
            fputc (ch-32, stdout);
          else
            fputc (ch, stdout);
        } // while
      return 0;
    } // main

### Given a standard text file, remove all blank spaces at the end of lines

* Sed is probably our best bet.
* The special cases in C will be hard.
* Sam uses vi.

### Make a list of all misspelled words in a text file

* Use the built-in spellcheck operation. (`spell`)

### Find the names of the people with the five highest grades on homework 2

Lines have the form

     LastName,FirstName,Assignment,NumericGrade 

Write a C program

* Wow, that took awhile.

Use a bunch of built-in Unix applications tied together.

* `awk` to select the right lines (or `grep`)
* `sort` to put them in order
* `head` or `tail` to grab the top five
* `???` to select the right columns

    $ grep ,HW2, grades.txt
    Rebelsky,Sam,HW2,25
    Smith,Jack,HW2,105
    Smith,Jane,HW2,110
    Jones,Fred,HW2,20
    Jones,Leumas,HW2,39
    Um,Ben,HW2,50
    Jimmy,Spanish,HW2,89
    Inappropriate,ForClass,HW2,50

This will behave less well if someone's name is "HW2".  
Solution? Use `awk`, Use a better pattern, Immediately fail anyone whose
name is HW2 so they are no longer in the class.

    $ sort -n -t, -k4 HW2.txt
    Jones,Fred,HW2,20
    Rebelsky,Sam,HW2,25
    Jones,Leumas,HW2,39
    Inappropriate,ForClass,HW2,50
    Um,Ben,HW2,50
    Jimmy,Spanish,HW2,89
    Smith,Jack,HW2,105
    Smith,Jane,HW2,110

    $ sort -n -t, -k4 HW2.txt | tail -5
    Inappropriate,ForClass,HW2,50
    Um,Ben,HW2,50
    Jimmy,Spanish,HW2,89
    Smith,Jack,HW2,105
    Smith,Jane,HW2,110

    $ grep ,HW2, grades.txt | sort -n -t, -k4 | tail -5 | cut -d, -f 1-2

### Given an HTML file, find the URLs of all images.

Generalize Approaches
---------------------

_What kinds of techniques did we use in solving the problems above?_

* Get bad advice from Stack Overflow.  
    * (We should experiment, fix.)
* Use some of the standard Unix utilities.
    * `tr`
    * `sed`
    * `grep`
    * `sort`
    * `cut`
    * `head` and `tail`
* Sometimes a problem is common enough that someone has designed an
  exact match.
    * `dos2unix`
* Write a C program.
* Pipe together programs to build something more powerful.
* Use the bash scripting language.
* Use a more general scripting language, such as Perl (or Python)

Ideas from TAoUP
----------------

_What other ideas did you take from *The Art of Unix Programming*?_

* Small tools that do one thing well.
* With a standard I/O model (text files).
* So we can join them together with pipes.
* An open philosophy, so we can use and build off of the work of others.
* Held together by C, because, um, it's C.

