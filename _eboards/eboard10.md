---
title: "EBoard 10: The C Preprocessor + Macros + More
number: 10
section: eboards
held: 2022-04-13
link: true
---
# {{ page.title }}

* This class will not be recorded.

_Approximate overview_

* Administrative stuff
* Quick Macro review
* The C preprocessor
* Header design
* An application: Verifying expectations
* Concatenation and metaprogramming

Administrivia
-------------

* Happy Thursday!
* Non-seniors: 
    * Updates on various department issues
* We miss all of you who are absent.
* Reminder: You may want to read 
  <https://gankra.github.io/blah/c-isnt-a-language/>
* You may also want to read
  <https://uwmadison.app.box.com/v/popets2022-mutebutton>
* Vote for the sheep!

C Macros
--------

* Key idea: Programmatic text replacement
* During the preprocessing stage, we replace the macro "call" with the macro
  body, substituting the _text_ of a macro's actuals in for the formals.
* E.g., 
    * Definition: `#define MAC(CROW) fprintf (stderr, "%s %s\n", CROW, CROW)`
    * "Call": `MAC("Sim, uh");`
    * Result `fprintf(stderr, "%s %s\n", "Sim, uh", "Sim, uh");`
* Observed issue: Because they do textual substitution, macros can sometimes
  create unexpected behavior if we do not parenthesize appropriately.
    * `#define SQUARE(X) ((X)*(X))`
    * And you thought there were a lot of parens in Scheme!

The C Preprocessor
------------------

Reminder; The first step of compilation.  Primarily does easy textual
transformations.

The big three

* `#include`
* `#ifdef` ... `#else` ... `#endif`
* `#define`

A common fourth

* `#if` ... `#else` ... `#endif`

And beyond

* `_Pragma` (formerly `#pragma`)
* `#line`
# Some random crap (e.g., `#ident`)

What else did you learn from skimming?

Header design
-------------

* It's bad to include the same header twice.  Why?

Stringification
---------------

_Hey, it's better than `stringizing`._

* `#PARAM` converts a parameter into a string.
* Simplified variant of the example from the manual
     * `#define VERIFY(EXP) if (! (EXP)) fprintf (stderr, "Warning!: %s\n", #EXP)`
* Sample usage
     * Input `VERIFY(x > 0)`
     * Output `if (! (x > 0)) fprintf (stderr, "Warning!: %s\n", "x > 0")`

Improving the example
---------------------

I don't know about you, but I'm uncomfortable with the lack of braces around
the body.

### A proposed solution:


```
#define VERIFY(EXP) if (! (EXP)) { fprintf (stderr, "Warning!: %s\n", #EXP); }
```

### A Problem

Input

```
VERIFY(x > 0);
```

Output

```
if (! (x > 0)) { fprintf (stderr, "Warning!: %s\n", "x > 0"); };
```

That makes us a bit uncomfortable.

### A worse problem

Input

```
if (TODAY_IS_THURSDAY)
  VERIFY(x > 0);
else
  x = max(x, 1);
```

Output

```
if (TODAY_IS_THURSDAY)
  if (! (x > 0)) fprintf (...); 
else
  x = max(x, 0);
```

### The traditional "solution" (aka "kludge")

Wrap the code in a `do { ... } while (0)`.

For example,

```
#define VERIFY(EXP) \
  do { if (! (EXP)) { fprintf (stderr, " Warning! %s\n", #EXP); } } while (0)
```

Now you can safely add a semicolon and use it in any situation.

### Further improvements

Further improvements ...

```
#define VERIFY(EXP) \
  do                                                            \
    {                                                           \
      if (! (EXP))                                              \
        {                                                       \
          fprintf (stderr, " Warning! %s on line %d of %s\n",   \
                           #EXP, __LINE__, __FILE__);           \
        }                                                       \
     }                                                          \
  while (0)
```

Wasn't that fun?

Note that you can play with `__LINE__` and `__FILE__` using `#line` and
`#file`.

## Concatenation

The `##` operation connects the text of a macro parameter along with
some other text.

```
#define RECURSIVE_ARRAY_FUNC(NAME, TYPE, CODE)                          \
  void NAME(TYPE array[], int n) { NAME ## _kernel (array, n, 0); }     \
  void NAME ## _kernel(TYPE array[], int n, int pos) {                  \
    if (< pos n) {                                                      \
      CODE;                                                             \
      NAME ## _kernel(array, n, (+ pos 1));                             \
    }
```

```
RECURSIVE_ARRAY_FUNC(increment, int, array[i] = array[i] + 1)
```

Isn't metaprogramming fun?

* _metaprogramming_: Writing code to write code

Challenge: Write `ARRAY_MAP(ARRAY, FUNC, N)`
