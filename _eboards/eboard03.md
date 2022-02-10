---
title: "EBoard 03: It's Interview Day"
number: 3
section: eboards
held: 2022-02-10
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Introduction to the interview
* Interview, part 1: Binary search
* Interview, part 2: Your C package
* Interview, part 3: Code development
* Interview, part 4: Code critiques

Introduction to the Interview
-----------------------------

About binary search
-------------------

* Find an element in the array.
* Here's a sample declaration of a binary search

        int binary_search (char *val, char **vals, int n);

* Prerequisite: vals must be sorted in alphabetical order.
* Prerequisite: every string is non empty (although the array can be).
* Prerequisite: vals contains no duplicate elements.
* Prerequisite: vals contains at least n strings.
* Observation: You may use the ordering given by `strcmp`.
* Binary search is really fast.  O(log_2(n))
* Returns the position of val in vals.  Returns -1 if val is not vals.

The C package
-------------

* `search.c` which contains the implementation of `binary_search`
    * `YOURNAME.c`, which contains your implementation of binary-search.
* `search.h`, which contains the declaration of `binary_search`.
* `Makefile`, which contains instructions for building stuff.
* `test.c`, the tests we want to run on `binary_search`.
* `README.md`, which says something like

        binary_search
        -------------
        Git made me make this file.

Since it's in a git repo,

* There will be a .git directory that we don't care about.

What will we build with this Makefile?

* Some kind of executable?  Maybe our tests will be an executable.
* At some point, an object file.
* Potentially, a library file for your search library.

Code development time
---------------------

Start with the repo at

        https://github.com/grinnell-cs/csc282-2022sp

Copy _stub.c to YOURNAME.c.  E.g.,

        cp _stub.c yksleber.c

Code critiques
--------------

* Why did you edit files outside of your authorized scope?
    * Someone changed the .gitignore.
* What is this cruft you put in the repo?
    * `frank_test`
    * `paul.test`
    * `austin.test`
* Do you not know about the GNU coding standards? (Assigned reading
  for today.)
* At MicroGoogazonBook, we don't hire people who develop in Windows.
  Even that old-school place in Seattle with the Big Gates prefers people 
  who learned to develop on Unix.  (At least it used to.)

Followup
--------

Whoops.  You have now encountered the issue of multiple unices.  Macs
and MathLAN have different versions of, say, indent.

Professor Rebelsky will send out some notes for you to read and tasks for
you to complete for next week.
