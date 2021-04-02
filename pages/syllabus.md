---
title: Thinking in C and Unix
permalink: /syllabus/
---
# Thinking in C and Unix

<dl class="dl-horizontal">
  <dt>Instructor</dt>
  <dd>
    <p><a href="{{ site.instructor_homepage }}">{{ site.instructor }}</a></p>
  </dd>

  <dt>Meeting Times</dt>
  <dd>
    <ul class="list-unstyled">
      {% for item in site.meeting_times %}
        <li>{{ item | markdownify | remove: "<p>" | remove: "</p>" }}</li>
      {% endfor %}
    </ul>
  </dd>

  <dt>Office Hours</dt>
  <dd>
    <ul class="list-unstyled">
      {% for item in site.office_hours %}
        <li>{{ item | markdownify | remove: "<p>" | remove: "</p>" }}</li>
      {% endfor %}
    </ul>
  </dd>

  {% if site.review_sessions %}
    <dt>Review Sessions</dt>
    <dd>
      <ul class="list-unstyled">
        {% for session in site.review_sessions %}
          <li>{{ session }}</li>
        {% endfor %}
      </ul>
    </dd>
  {% endif %}

  {% if site.textbook %}
    <dt>Textbook</dt>
    <dd>
      {{ site.textbook | markdownify | remove: "<p>" | remove: "</p>" }}
    </dd>
  {% endif %}

  {% if site.mentors %}
    <dt>Class Mentors</dt>
    <dd>
      <ul class="list-unstyled">
        {% for mentor in site.mentors %}
          <li>{{ mentor }}</li>
        {% endfor %}
      </ul>
    </dd>
  {% endif %}

  {% if site.mentor_sessions %}
    <dt>Mentor Sessions</dt>
    <dd>
      <ul class="list-unstyled">
        {% for session in site.mentor_sessions %}
          <li>{{ session | markdownify | remove: "<p>" | remove: "</p>" }}</li>
        {% endfor %}
      </ul>
    </dd>
  {% endif %}

  {% if site.tutors %}
    <dt>CS Tutors</dt>
    <dd>
      <ul class="list-unstyled">
        {% for tutor in site.tutors %}
          <li>{{ tutor }}</li>
        {% endfor %}
      </ul>
    </dd>
  {% endif %}
</dl>

## About this course

Welcome to {{ site.courseid }}! The official course description for this
class is:

> The most successful software designers master a variety of languages, algorithms, and software design methodologies. In this course, you will examine the Unix approach to software design. You will ground that examination, in part, by developing programs that deepen your understanding of advanced techniques of the C programming language. Includes laboratory work.

In other words, we will help you think in C and Unix/GNU Linux.

Learning Goals
--------------

Our major objectives for this course include:

  - Improving your overall software design skills
  - Enhancing your understanding of the C model of programming
  - Making you a more facile *nix user

Important Notices
-----------------

  - As is typical, I am over-booked this semester.  I apologize.
  - I wrote a series of essay for this course the last time I taught
    it.  I'm probably revising them this semester and writing a few
    more.  I apologize if they are less clear than professional
    writing.

Accommodations and adjustments
------------------------------

Please read [my policy on accommodations and adjustments]({{ site.baseurl }}/handouts/accommodations) and [my statement on accessiblity]({{ site.baseurl }}/handouts/accessibility).

Grading
-------

This course is offered for one credit and is graded as S/D/F.  College
guidelines dictate that one-credit courses require about forty-five
hours of total work.  All students are expected to ...

* attend at least eleven of the thirteen class meetings;
* do all of the assigned readings (about 30 minutes per class);
6 spend an appropriate amount of time on each homework assignment (about
  60 minutes per class); and
* participate actively in class.

Students who meet these criteria will earn a grade of S.  Students who
do not will likely earn a lower grade.

Textbooks and Other Readings
----------------------------

Mecklenburg, Robert (2004).  _Managing Projects with GNU Make_, Third
Edition. Sebastapol, CA: O'Reilly and Associates. Also available online
at <http://oreilly.com/catalog/make3/book/index.csp>.

Raymond, Eric S. (2003). _The Art of UNIX
Programming_. Addison-Wesley, Professional. Also available
online at <http://www.catb.org/esr/writings/taoup/html/>.

Rebelsky, Samuel A. (2021).  _Don't Embarrass Me; Don't
Embarrass Yourself: Thoughts on Thinking in C and *nix_.
An e-book (or something similar) in progress available at
<http://www.cs.grinnell.edu/~rebelsky/musings/index-cnix>.

Additional Readings
-------------------

*Here are some other things you might find useful.*

Gancarz, Mike.  1994. _The Unix Philosophy_.  Digital Press.

Kernighan, Brian W. &amp; Ritchie, Dennis, M. (1988). _The C Programming
Language, 2nd Edition: ANSI C_. Upper Saddle River, NJ: Prentice-Hall.

Attendance
----------

Your classmates and partners depend on your contributions to learn new material and complete the required work for this course. *Don't let them down!* You are expected to arrive on time and actively participate in every class.

If your are sick, *please do not come to class.* Stay in your room, rest, and seek medical care as needed. [Student Health and Counciling Services (SHACS)](http://www.grinnell.edu/about/offices-services/student-health) offers health and mental health services to students.

Participation
-------------

Because much of our work in this course involves collaboration and discussion, you will be evaluated on your participation.
Participating in class involves:

 - being present in class (physically and mentally)
 - coming to class on time
 - coming to class prepared
 - asking questions when appropriate
 - making positive contributions to class discussion by volunteering and when called upon
 - staying on task during lab exercises, and
 - working effectively with your partner(s)

In my experience, students come to this class with incredibly varied backgrounds.  Please don't let your experience negatively affect others.

Academic Honesty
----------------

Please read [my policies on academic honesty]({{ site.baseurl }}/handouts/academic-honesty) and [the CS department's academic integrity policy](https://www.cs.grinnell.edu/policies/academic-integrity).  I expect you to follow these policies.
