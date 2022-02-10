---
title: "EBoard 02: Thinking about Unix"
number: 2
section: eboards
held: 2022-02-03
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Very little administrative stuff
* Review ideas of Unix Tools
* Review ideas of Unix Tasks
* Review ideas from TAoUP Chapter 1

Administrative stuff
--------------------

### General Notes

* The class Web site is still at
  <https://rebelsky.cs.grinnell.edu/Courses/CSC282/2022Sp/>.
    * The class Web site is (always) a work in progress.
* Sorry about the GitHub confusion.  Let me know if you're still having 
  trouble.

### Upcoming Activities

* Thursday extras today!  Learn about the 4+1 program.

### Work for next Thursday

* Read [Sam's comments on formatting C code](https://rebelsky.cs.grinnell.edu/musings/cnix-formatting-c)
* Skim [Making the best use of C](https://www.gnu.org/prep/standards/html_node/Writing-C.html)
* Read [Chapter 1 of _Managing Projects with GNU Make_](https://www.oreilly.com/openbook/make3/book/ch01.pdf)
* Read Rob Pike's [Notes on Programming in C](http://www.literateprogramming.com/pikestyle.pdf)
* Think about how you would do unit testing in C.

Fun with GitHub
---------------

* Did anyone encounter merge conflicts?

Review Unix Tools
-----------------

* <https://github.com/grinnell-cs/csc282-2022sp/blame/main/unix-tools.md>
* I would have organized the file differently, but ...
* We'll read through it a bit; I may also make comments on your
  Git Commits and other issues.

Git notes

* Don't do independent changes in one commit.
* Please use sensible commit messages.
* When working in a shared file, PUT STUFF IN THE RIGHT PLACE!
* Do not add cruft to the repo.

Awk is good for text processing

* Example: Sam downloads class list in `"NAME","ID","STANDING","EMAIL"`
  form
* Sam usually wants class list in `"NAME" <EMAIL>` form or
  "FIRST","LAST" form.
* If it's a task Sam will do regularly, Sam should write an Awk script
  (or maybe a Sed script, since it's pretty simple).
* Note: "NAME" to "FIRST LAST" is difficult.

`cd` changes directories

* Relative or absolute
    * `cd /home/rebelsky` changes to my home directory. (absolute)
    * `cd fizzbuzz` changes to the fizzbuzz subdirectory. (relative)
    * `cd ../fizzbuzz` changes to the fizzbuzz sibling directory. (relative,
  using the magic of dotdot, which means "parent directory")
* cd's only command-line flags seem to have to do with following
  symbolic links.
* What's a symbolic link?
* Maybe we should ask what a link is, first.

Links in Unix

* A link is effectively an alias for a file (or other file-like thing,
  such as a directory).
* That is, it's another name for the same file (or ...)
* If we create the link with `ln source dest`, it's a hard link.
    * Modifications to the file through either name affect the other 
      because *they are the same file*.  
    * In essence, the symbol table maps both names to the same area
      on disk.
* We normally can't create hard links
    * To directories
                $ ln foo bar
                ln: foo: hard link not allowed for directory
    * To files on other disks
    * Both have technical barriers.
* Why link files?
    * We do it a lot: E.g., Make a link to this application on my
      desktop.
    * Sometimes we have a library we need in lots of folders (perhaps
      because we've made bad design decisions).
    * Links help ensure that if one thing changes, everything changes.
* Unix also allows "soft links".  These links don't reference a place
  on disk (or equivalent): They just use the path to reference the
  place.
* We use `ln -s source dest` for soft links.
* We can see soft links with `ls -F <FILE>`.
* We can see soft links with `file <FILE>`.
* Like paths for `cd`, symbolic links can be relative or absolute.
    * If you make a symbolic link, and move it, it now links to
      something different.

`cat` vs. `more` (`less`)

* `cat` is intended to show the contents of files.
* `cat <FILE1> <FILE2> ...`
* `more` is a pager.  It shows one screenful of a file at a time.
* We can use `cat` as a quick way to create files.
    * `cat > filename.txt`
    * That's because by default, cat takes standard input as the
      stuff to type.
* `cat` is short for "concatenate"
* `cat file1 file2 file3 > file4` will combine the contents of the
  first three files onto the last.

`ls <DIR>` lists the contents of a directory

* If the directory is not specified, lists the current directory.
* `-l` gives a long listing, which includes permissions and other
  info, including owner, group, last modification, sizeish, ...
* `-a` also shows "hidden" files.  Convention on Unix systems is that
  files and directories that begin with a dot are not shown unless you
  use this flag.
* `-F` adds a character after certain kinds of files
    * `/` after directories
    * `@` after symbolic links
    * `*` after executables
* `-d` does not expand directories
* `-H` follows symlinks
* `-R` recursive
* `-t` in order of modification time
* `-G` might use color to show differences (like -F)

Permissions will come another day

* There is a (disallowed in MathLAN) "setuid" permission, which makes
  an executable run as the owner of the file, rather than the person
  who executed the file.

`ps` and `top` list processes in different ways.

* ps gives all of them
* `top` gives the top ones

Review Approaches to Problems
-----------------------------

### Given a DOS-formatted text file (lines end with \r\n rather than just \n), 
convert it to a standard text file

### Given a standard text file, convert all uppercase letters to lowercase

### Given a standard text file, remove all blank spaces at the end of lines

### Make a list of all misspelled words in a text file

### Find the names of the five highest grades on homework 2

Lines have the form

     LastName,FirstName,Assignment,NumericGrade 

### Given an HTML file, find the URLs of all images.

Generalize Approaches
---------------------

Ideas from TAoUP
----------------


