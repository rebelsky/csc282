---
title: Shell scripting
link: true
---
# Shell scripting

In this assignment, you will explore a bit of shell scripting.

## Introduction

As you may recall from CSC-161, a _shell script_ is a small program written in the shell's scripting language.
Since we tend to use bash in this course, we'll generally write bash scripts.

A bash script begins like this.

```
#!/bin/bash
```

Bash scripts must be marked as executable, which you will traditionally do with a command like

```
$ chmod 755 SCRIPT
```

or

```
$ chmod a+x SCRIPT
```

After the initial line, you can have any commands (or sequence of commands) that you would normally type at the command-line prompt.  
Here's a potential cleanup script.

```
#!/bin/bash

rm -f *.tmp
rm -f *~
rm -f *.o
```

## Assignment

Write a small bash script that does something you consider useful.

You may want to consider using some of the additional basic features of bash or bash scripts, such as variables or command-line parameters.

Be prepared to talk about your script and the techniques you learned.

Use the Teams channels for asking questions.

## Submitting

Add your script to the `shell-scripts` directory in the course archive.

Update the `README.md` file in that directory to add a note about the script.
