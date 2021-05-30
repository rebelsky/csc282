---
title: "EBoard 06: Regular Expressions and More"
number: 6
section: eboards
held: 2021-04-22
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Programming the shell
* Regular expressions
* Regexs in grep
* Regexs in sed

Administrative stuff
--------------------

### General Notes

* Happy Thursday.  I hope you have a great weekend
* Reminder: I do want to see you try the tasks, even if things don't
  go quite right.

### Upcoming Activities

* CS Extras Thursday at 5pm (immediately after class): Rosario Robinson 
  on Open Source.  PLEASE ATTEND!
* CS Table Monday at Noon
* April 28: Nutting & Bakopoulos on "How _Made for Love_ got made".

### Work for Tuesday

* Three readings on Make
* Make or find a Makefile.  Write about it.

Q&A
---

Programming the Shell
---------------------

For quick tasks, it's nice to know how to write loops and such.

Three important mechanisms

* In the shell
* We create shell scripts
    * Start with `#!/bin/bash`
* Sometimes, we put things in our `.bashrc` or `.bash_profile`.
    * A good place for functions.

### Variables

Declaring / initialize

    NAME=EXP

E.g.,

    hello="hello world"

Using

* We display/use with a dollar sign

E.g.,

    echo $hello   

Variables generally last until the shell/program is closed.  

Except ...  you can sometimes write `export VAR` to export the
variable to the enclosing shell (and beyond).  (It works in your
`.bashrc` and `.bash_profile`.)

### Detour: Environment variables

There are some variables that get used regularly by other programs.
We often to these as environmental variables and name them with all
caps.

* `PATH` is a colon-separated list of directories where the shell
  looks for the commands you type.

### Detour: Command-line history

When you are using the shell, it keeps a log of all the commands you've
typed, up to some number.

You can type `!number` to redo that command.

You can type `!letters` to redo the last command that started with
those letters.

`!$` refers to the last "word" on the previous line.

You can also redo a modified version of the previous command with 
`^pattern^replacement`

### Conditionals

    if [ TEST ]
    then
      COMMAND
    fi

    if [ -f file.c ]
    then
      echo "Whoo, you have file.c"
    else
      echo "Nope, no file.c"
    fi

### For-each Loops

    for VAR in LIST; do
      COMMANDS
    done

    for file in *.txt; do
      echo "$file"
    done

    for file in *.txt; do   
      newfile=`echo $file | sed -e 's/txt/bar/'`
      mv $file $newfile
    done

    for file in `grep -l Hello *.txt`; do   
      newfile=`echo $file | sed -e 's/txt/bar/'`
      mv $file $newfile
    done

### While Loops

    while (TEST) do
      COMMANDS
    done

    while (1) do
      ls -lt FILE
      sleep 10
    done

### Functions

    function NAME() {
      COMMANDS
    }

The arguments are $1, $2, $3, ...

    function compile() {
      cc $1.c -o $1
    }

    function rename() {
      for file in *.$1; do
        newfile=`echo $file | sed -e s/$1/$2/`
        mv $file $newfile
      done
    }

The moral

* If you find yourself writing the same (or similar) commands over and
  over in the shell, use your programming skills to write functions
  that you can use in the future.
* Loops are good when you want to do something to a lot of files, or
  observe a long process

Regular Expressions
-------------------

Core idea: Instead of writing programs to match text, we can write
"patterns" (declarative programs) to describe the text we want to
match.  The patterns we use are simple enough that we can efficiently
make pattern-matchers. 

* Convert regular expressions to nondeterministic finite automata (NFAs).
  Convert nondeterministic finite automata to deterministic finite
  automata (DFAs).  DFAs are pretty close to code.
* Problem the DFA for a particular NFA can be exponentially larger;
  Ton of hacks to avoid building all at one.
  
* In some tools, matching anywhere on a line is enough; in others, you
  can limit yourself to only the matching text.
Like so much in CS, regular expression patterns are defined recursively.

Most of the basic things before recursion.

* In most cases, any single character is a regular expression that matches 
  that character.
    * The regular expression `a` matches the letter `a`.  
    * The regular expression `b` matches the letter `b`.  
* However, there are some special characters.
    * `^` usually matches the start of a line (or a piece of text).
    * `$` usually matches the end of a line (or end of a piece of text).
    * `.` usually matches any one character.
    * `\` is used as a meta character.
* There are some special patterns that are prefixed with a backslash.
    * `\^` matches the caret
    * `\.` matches a period
    * `\w` matches a word character
    * `\B` matches a word boundary
    * `\\` matches the backslash.
* Sets: `[abcd]` matches any one thing that appears in the brackets.
* Sets: `[^abcd]` matches any one thing that doesn't in the brackets.
* Ranges: `[a-e]` matches anything between `a` and `e`
* Most modern regular expression enviornments also provide named sets
  `[:alnum:]` is a regular expression that names any alphabetic
  character or number character.  (Sam forgets the names and has to look them up.)
  `[:alumnium:]` does not match anything.

Recursion

* If `R1` and `R2` are regular expressions then `R1R2` is a regular
  expression that matches sequences whose first part matches R1 and
  whose second part matches R2.  `ab` matches `ab`, and `a[0-9]` matches
  `a0` and `a1` and `a2` and ... `a9`
* If `R` is a regular expression, `R*` is a regular expression matching
  0 or more copies of R.  `a*` matches sequences of 0 or more copies of
  `a`  (Repetition)
* If `R1` and `R2` are regular expressions, then `R1|R2` is a regular
  expression that matches either `R1` or `R2`
* We have parentheses to help disambiguate and work with precedence issues.

Using Regular Expressions with Grep
-----------------------------------

We may want to look for files that contain certain strings (e.g.,
to figure out where you've defined a function, to solve crossword
puzzles).

Some useful files for practice

* On Macs, `/usr/share/dict/words` contains 200,000+ words in the English
  language.
* To look for all the words in which the vowels (aeiou) appear in order, I could
  write the regular expression .... `a[^aeiou]*e[^aeiou]*i[^aeiou]*o[^aeiou]*u`
  We could do some variants of that for fun.
  `^[^aeiou]*a[^aeiou]*e[^aeiou]*i[^aeiou]*o[^aeiou]*u[^aeiou]*$`

Other fun things to do with grep

* Find out where a C function is defined `grep -r -l '^FUN' .

Fun arguments to grep

* `-l` - Lists all the files without printing the matching line
* `-n` - Gives line numbers
* `-v` - Reverse matching - only lines that don't match
* `-i` - Case insensitive 
* `-c` - Only get a count of lines (which is easier than `| wc -l`
* `-q` - Quiet mode.  Returns true or false.  Sam apparantly sucks at
  using it in the shell on the fly.
* `-w` - Match the pattern to words, rather than the line, and require
  that they match the whole word.

Using Regular Expressions with Sed
----------------------------------

Stream Editor: Intended for editing "streams" (sequences of text),
mostly good for batch editing.  But it does some fancy batch editing.

* Selector to indicate which lines to work on
    * Selectors can be regular expressions
    * Selectors can also be numbers
* Operation (insert, delete, replace)
* Parameters to that operation.
    * Replace can use regular expressions

Challenge: We have a file in the form "Last,First" and want to translate
to "First Last".  How?

\(RE\) gives you a numbered RE
\1 and \2 in the replacement give you the contents of the numbered RE
