---
title: "EBoard 05: Shell Scripting"
number: 5
section: eboards
held: 2022-02-24
link: true
---
# {{ page.title }}

_This class may be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrivia

Administrivia
-------------

* I have a plane to catch.  With the snow, I'm leaving at 3:20 instead
  of 3:50.
* Enjoy next Tuesday's "Work Differently" day.
* Please fill out the Data Buddies survey if you haven't already.
* Consider volunteering to be a CPU.
* Say hello to the little moppets (or something like that).

### Upcoming work

* To be determined.  Ned is teaching next week and I forgot to check
  with him.

Shell Scripting Basics
----------------------

_Just because I don't know how much of this you learned on your own._

### To write an algoirthm, you need ...

* Naming
* Conditionals
* Repetition
* Sequencing
* Subroutines
* Basic values and operations on those values

### Some core concepts

`VAR=VALUE`
  : Assign to a variable.  You access the variable with `$VAR`.
    ```
    $ X="Hello World"
    $ echo $X
    Hello World
    ```

`` VAR=`COMMAND` ``
  : Evaluate a command and assign to a variable.  You can also
    use the backtick form when you want to insert the result of
    a command on the command line.
    ```
    $ GITFILES=`grep -l git *.md`
    $ vi `grep -l git *.md`   # Sam edits all the files with git
    ```

`$((EXP_)`
  : Evaluate an expression
  ```
  $ echo $((3 + 4))
  7
  ```

`if [ TEST ]; then STATEMENTS; fi`
  : Conduct the test.  If it succeeds, evaluate the statement.  There's
    also an optional `else` clause.  And you can separate things with
    newlines rather than semicolons.
    ```
    $ X=10
    $ if [ $X -gt 0 ]; then echo "$X is positive."; fi
    10 is positive

    $ if [ $X -lt 100 ]
    > then
    >  echo "$X is smallish"
    > fi
    10 is smallish

    $ if [ -f ~/.bashrc ]; then
    >   echo "You have a bashrc file"
    > else
    >   echo "Your Unix life is incomplete"
    > fi

`while [ TEST ]; do STATEMENTS; done`
  : Conduct the test.  If it holds, run the statements and do it all
    over again.
    ```
    $ X=10
    while [ $X -gt 0 ]
    do
      echo -n "$X "
      X=$(($X - 1))     # I may have gotten this wrong; sometimes bash is annoying
    done
    ```

`for VAR in LIST; do STATEMENT; done`
  : Repeat the statement for each variable in a list.
    ```
    for X in *.txt
    do
      echo "Backing up $X"
      cp $X $X.bak
    done
    for X in `grep -l "Sam" *.txt`
    do
      echo "Backing up $X"
      cp $X $X.bak
    done
    ```

`function NAME { BODY }`
  : Define a function.  Within the function, parameters are given
    by $1, $2, etc.
    ```
    $ function add {
    >   RESULT=$(($1 + $2))
    >   echo $RESULT
    > }
    $ add 2 3
    6
    ```

Your shell scripts 
-------------------

... and what we learn from them

_Note: I appreciate the hard work I see in many of the scripts.  However,
I will still suggest improvements (i.e., make fun of them)._

Some comments as we go ...
