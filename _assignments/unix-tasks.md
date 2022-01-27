---
title: Some simple Unix tasks
link: true
---
# Some simple Unix tasks

In this assignment, you will individually determine strategies for
solving a variety of tasks in Unix.

Find good solutions to each of the following tasks. (That is, write a program or command to solve the task.) Put them in a folder with your name in `unix-tasks` folder in the primary class GitHub repository.

* Given a DOS-formatted text file (lines end with \r\n rather than just \n), 
  convert it to a standard text file.
* Given a standard text file, convert all uppercase letters to lowercase.
* Given a standard text file, remove all blank spaces at the end of lines.
* Make a list of all misspelled words in a text file.
* Given a CSV file in which each line has the form  
  `LastName,FirstName,Assignment,NumericGrade` 
  find the the five highest grades on homework 2.
* Given an HTML file, find the URLs of all images. In case you don’t know 
  HTML, those will typically look like `<img ... src="*URL*" ...>`.  You
  might also want to address any of the following added complexities.
    * Added complexity: `img` can have any capitalization (`img`, `IMG`, `Img`, `iMg`, etc.)
    * Added complexity: There can be other text between the img and the src. (That text cannot include a greater than sign.)
    * Added complexity: There may be multiple image tags on the same line.
    * Added complexity: An image tag may span multiple lines.

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
