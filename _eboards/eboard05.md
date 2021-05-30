---
title: "EBoard 05: The Bash Shell, A Refresher (I hope)"
number: 5
section: eboards
held: 2021-04-20
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* About the shell
* Command I/O
* Combining commands
* Files and ownership

Administrative stuff
--------------------

### General Notes

* Happy Tuesday.  I hope your week has been good.
* Today's class will be review for some of you and new for others of you.
  At least I hope that's the case.  
    * I'd prefer it's new for all of you, but I know that's not the case.
* Apologies for failing to post stuff.

### Upcoming Activities

* Mando Memorial Lecture tonight: Reading at 7pm.
* Convo Thursday noon.  Shanna Benjamin
* CS Extras Thursday at 5pm: Rosario Robinson on Open Source
* CS Table Monday at Noon
* April 28: Nutting & Bakopoulos on "How _Made for Love_ got made".

### Work for Thursday 

* GNU Grep Manual, Sections 3 (Regular Expressions) and 4 (Usage).
  <https://www.gnu.org/software/grep/manual/>
* GNU Sed Manual, Sections 3 (`sed` scripts) and 4 (Addresses).
  <https://www.gnu.org/software/sed/manual/>
* For each post something you want to remember or share.
    * Regular expressions
    * Using `grep`
    * Using `sed`

Q&A
---

What is the difference between pinning and showing?

> Not everyone has the option to pin?

About the shell
---------------

* Unix is an operating system.
* What is an operating system?
    * That program that manages all the computer's resources, including
      the other programs that are running on the computer.
    * The user interface one uses to interact with the rest of the
      computer (e.g., to start or stop applications, to control where
      you store documents, etc. etc.)
    * Every OS has a set of device drivers (all of which someone wrote;
      new ones get written) that handle the communictions between the
      computer and the device we might attach to it.  "drive" == "control".
* Device drivers can do all sorts of things
    * Send the obvious commands "Page feed"
    * Some more complicated, such as "Check status", which need to send
      info back to the user and may need translation.
    * Sometimes we need a lot of translation.  ASCII vs. EBCDIC.
      Big-endian vs. little endian.
        * We represent numbers in binary 01010001010
        * The rightmost digit is 2^0 (1's) digit
        * The next digit is 2^1 (2's) digit
        * The next digit is 2^2 (4's) digit
        * What happens when our number requires more than one byte?
          Do you put the lower byte first or second?  (Higher in memory
          or lower in memory?) It's a religious war!
    * UTF-8 files often have a special character at the front that tells
      you this (and irritates lots of people who don't know about it).
* Command-line UI.  You control everything by typing commands.
    * Typing commands can be much more efficient, particularly once
      you get used to it.
    * But it takes time to get used to.
* Early Unix effectively consisted of three things
    * An operating system that provided and managed resources.
    * A programming language (C) intended to help  you write programs
      within that OS.
    * A command-line interface (sh, short for shell) intended to help
      you manage things as a user (start programs, deal with files, 
      connect devices, etc.).  Some of these are "superuser" activities.
* Knowing "Unix" means knowing about the shell (or a shell) as well as
  some high-level capabilities associated with most shells.
* Unix has at least a dozen different shells (Sam made up that number).
    * The original shell, `sh`, written by Stephen Bourne
    * Some people wanted a C syntax for the shell, and wrote the C shell
      `csh`.
    * Some people wanted a better syntax, so they wrote the `tcsh`.
      (Sam assumes the t is silent.)
    * Extending the `sh`, naming it the Bourne Again Shell, or `bash`.
    * These days, Apple has embraced the Zshell, not least because it
      is clevely configurable.  (You can skin your shell.)
    * We are going to focus on the bash shell.

What can you do in the bash shell?
----------------------------------

* Start applications.
    * Type the name
    * We often type an ampersand after the application name to run it
      in the background.
    * When you type the name, the computer has to search for the application.
      It uses a variable called PATH to determine where to search.
    * You indicate which version you want to run by typing the full
      pathname.  E.g. /usr/local/bin/perl can be different than
      /usr/bin/perl.  If you just type perl, you get whichever appears
      first in your path.
    * You can find out which version you get with `which command`
* Provide information to those applications with command-line flags, such
  as the files to open.
* Play with files.  List them!
    * `ls` lists all the files and directories you have.
    * `ls -F` adds a suffix that tells you about the type.
    * `ls -a` shows the hidden ones, too.
    * `ls -l` shows additional data
    * `ls -t` shows them in newest-to-oldest order
* Rename them
    * `mv OLD NEW`
* Move them to other directories
    * `mv FILES DIR`
* Copy them
    * `cp OLD NEW`
    * `cp FILES DIR`
    * `cp -R DIR DIR` recursive copy 
        * WARNING!  Some Unix commands use -R for recursive and others
          use -r.
* Remove them
    * `rm FILE`
    * `rmdir DIR`
    * `rm -rf DIR`
    * Don't type `rm -rf *`
* Combine applications using pipes and other commands.

Command I/O
-----------

An important characteristic of Unix is that most Unix programs deal with
"plain text" files for both input and output.  We can think of the input,
the output, and files as streams of characters.

### Reading from files

* `program < file`
* By default, have your C programs run from `stdin`.

### Writing to files

* `program > file`  - creates the file.  overwrites if it exists.
* `program >> file` - appends to the file

### Stderr vs Stdout

* Traditionally, all Unix programs have two output channels, rather
  than one: "Standard Error" (stderr) and "Standard Output" (stdout).
* Traditionally, only the stuff printed to stdout gets sent to the
  `>` (or the pipe, when we get to that).  That's intentional; the
  assumption is that the errors need to be seen  or separated.

### Redirecting stderr

* If you want both to be combined into stdout, you can add 2>&1 
  to your command.  (That says "Take output stream 2 and
  redirecting it '>&' to output stream 1")
* `./sample > foo 2>&1`
* Note that the placement of the `2>&1` is important.

### Detour: Subtleties of C and output and error

```
int
main (int argc, char **argv)
{
  fprintf (stdout, "Starting Output ");
  fprintf (stderr, "Error\n");
  fprintf (stdout, "Ending output\n");
} // main
```

```
$ ./sample
Error
Starting Output Ending output
$ ./sample 2>&1
Error
Starting Output Ending output
```

```
int
main (int argc, char **argv)
{
  fprintf (stdout, "Starting Output\n");
  fprintf (stderr, "Error\n");
  fprintf (stdout, "Ending output\n");
} // main
```

```
Starting Output
Error
Ending output
```

Why did we see different output?

* Because output in C is buffered.  
* It is inefficent to transfer characters one at a time.  We would
  rather send them in a big chunk.  So we buffer the characters.
* The standard C print library (and the standard Java print library)
  have the policy that things printed to stdout are buffered until
  (1) the buffer fills, (2) we print a newline, (3) we flush the
  buffer.
* However, stderr is always flushed immediately after the print command.
* Sam's predictions don't always work.

Detour: Designing toolkits
--------------------------

How many command-line arguments should you have for a good tool?

> It depends on the tool.

> Usually: Input files (multiple ones if permitted)

> Usually: A way to specify an output file (beyond '> file'); often
  for convenience.  Convention `-o outfile`.

> Sam likes `-version` or `--version`

> Sam likes `-help` or equivalent for help.

> You should have a way for the user to invoke each natural option in
  your program.  Sorting needds things likes "number or text", "which
  column", "how to separate columns", but not "randomly"

> Most programs grow over time.

Combining programs
------------------

### Piping

* If you write `cmd1 | cmd2`, Unix takes the standard output of
  cmd1 and sends it as the standard input of cmd2.
* We often build long chains of pipes.
    * `grep "HW2" grades | sort -k2 -t, -n | cut 1-2 -d ',' | head -5`
      should give us the names of the people with the top five grades on
      HW2.
    * Long chains of pipes are a Unix tradition; Take simple commands
      and combining them in new and innovative ways to achieve more
      complex goals.
* Some interesting examples
    * `top -b -n 1 | tail -n +8 | grep root | awk '{print $1}'`
        * `top` gives you a list of processes
        * `tail` removes the header
        * `grep` searches
        * `awk` prints only the first column

### Other ways to combine commands

* "cmd1 `cmd2`" takes cmd2's output and uses it as cmd1's command-line 
  inputs

        vi `grep -l fprintf *.c`

Files and ownership (directories, too)
--------------------------------------

Programming the Shell
---------------------

The shell (at least the bash shell) is also a programming language.
Until you use it regularly, you'll find that DuckDuckGo (or other
search engine) is your friend.

Have a good afternoon.
