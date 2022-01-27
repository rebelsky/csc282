---
title: Unix tools
link: true
---
# Unix tools

In this assignment, we will collaboratively make a list of Unix
tools and utilities that we've found useful (or even that we've
just heard of).  (The assignment will also end up being an exercise
in collaborative editing.)

Add at least two tools or commands or other useful information to
the `unix-tools.md` file in the primary course repository.  For
each entry, try to categorize and add a short description.

---

You can make a local copy of the repository with 

```
git clone git@github.com:grinnell-cs/csc282-2022sp.git
```

or

```
git clone https://github.com/grinnell-cs/csc282-2022sp.git
```

---

Your normal workflow should be something like the following.

* Use `git pull` to bring in the latest updates to the files.
* Make changes to the file.
* Use `git commit FILE -m "MESSAGE"` to commit your changes.  (Substitute
  the file name and the message.)
* Use `git pull` again to make sure that you incorporate any chances
  since you've started working.
* If there's a merge conflict
    * Edit the file to reserve the conflict.  (I tend to look for the
      text `HEAD`.)
    * Use `git add FILE`
    * Then do `git commit`.
* Push the updated file.
    * In production mode, you should probably use a pull request instead.
