---
title: "EBoard 9: More Fun with C and Macros"
number: 9
section: eboards
held: 2021-05-04
link: true
---
# {{ page.title }}

_This class will be recorded!  Its use will be limited to members
of the class.  Please do not share with others._

_Approximate overview_

* Administrative stuff
* Q&A (not on readings)
* Function calls and the stack
* Endian-ness
* Some important macro issues
* Q&A on Readings
* Detour: Exponentiation
* Avoiding repetitive code
* Parametric polymorphism, perhaps

Administrative stuff
--------------------

### General Notes

* Happy Tuesday!  I hope you had a wonderful weekend.
* I refuse to acknowledge the stupid phrase associated with today.
  (Or did I just do that?)
* Sympathy to those of you who were cut from Fall CS classes.  This was
  definitely a hard year in CS.
* I hope that those of you who had Covid shots are recovering.
* Congrats on solving last class's problem at the end of class.
* We have five class sessions left.  In addition to some random smallish
  topics, I have two big topics left to cover: debugging/tracing
  and command-line processing.  What else would you like to do?
    * Think about this question for Thursday.
    * And yes, I have other things up my sleeve.  These were just
      the ones on which I was focusing.

### Upcoming Activities

* Convocation Thursday May 6th at noon: the STEM Pipeline
* The Grinnellian is Saturday, 2-6pm (ish) on graduation stage?
* ISO Cultural Evening Sunday on graduation stage at 7pm.

### Work for Thursday

* Read the LLDB Tutorial (https://lldb.llvm.org/use/tutorial.html)
* Think about the exponentiation function from the end of class.

Q&A
---

Function calls and the stack
----------------------------

_Last class, I mentioned function calls and the stack, and you all
indicated that you understood them.  I'll give you a few minutes to
talk in pairs and then I'll ask a lucky "volunteer" (voluntold?)
to explain._

```
      MEMORY, MORE OR LESS                 C CODE
         +------+  Stack v                 int sum(x,y) { return x+y; }
  0xFFFF |    2 | z                        ...
         +------+                          int foo() {
  0xFFFE |    5 | a                          int z; int a = 5;
         +------+----- STACK FRAME           z = sum(a,2); /* THIS CALL! */
  0xFFFD |    7 |                          }
         +------+                          
  0xFFFC |    5 | x                        UNDERLYING "OPERATIONS"/"ACTIONS"
         +------+                          * Allocate space on the stack
  0xFFFB |    2 | y                        * Copy the value from from the
         +------+                            address associated with a to
  0xFFFA |      |                            the address associated with x.
         +------+                          * Copy the constant 2 to the
  0xFFF9 |      |                            address associated with y.
         +------+                          * Do the computation, and put
  0xFFF8 |      |                            the result on the stack
         +------+                          * Copy the result back to z
  0xFFF7 |      |                          * Pop the stack
         +------+                          
  0xFFF6 |      |                          ANYTHING MISSING?
         +------+                          * Ints really take four bytes
           ...                             * We also have to put other
         +------+                            info on the stack (e.g., old
  0xF004 |      |                            stack pointer)
         +------+                          * We have to "do" the function
  0xF003 |      |                            call.  (Switch control
         +------+                            to another part of the code.)
  0xF002 |      |                          * At the end, return control.
         +------+
  0xF001 |      |
         +------+
  0xF000 |      |
         +------+ Heap ^ / Static Stuff v
  0xEFFF |      | 
         +------+ 
           ...
```

How does it access the memory?

> There is a register, called the stack pointer, and our memory
  references are in terms of the stack pointer.   So `x` is
  "one below the stack pointer" and `y` is "two below stack pointer"
  (depending on how you think of the stack pointer).

Moral: Even simple function calls can be expensive!  We may want
to avoid some of that.

Side note: Good optimizers avoid most of this work.

Don't worry if you don't fully understand this; they main idea is
that function calls are "expensive", requiring setup and takedown,
which is why some people dislike recursion.  It's also why some
people like macros.

You can learn more in CSC-211.  Or on the Interweb.  One is more
reliable than the other.

CS Wars: Little Endian vs Big Endian
------------------------------------

As long as we're thinking about memory layout.  Suppose you can fit
four bits in one cell.  How would you lay out the letter 'z', which has
decimal value 122 and binary value 0111 1010

```
          little     big
         | ...  |
         +------+
  0xF001 | 1010 | or 0111
         +------+
  0xF000 | 0111 |    1010
         +------+ The Stack ^ / Static Stuff v
         | ...  |
````

### Detour

When you think about memory horizontally, rather than vertically,
which way do you number?

```
     0xF002 0xF001 0xF000
   -+------+------+------+-
... |      | 1010 | 0111 | ...
   -+------+------+------+-
```

or

```
     0xF000 0xF001 0xF002
   -+------+------+------+-
... | 0111 | 1010 |      | ...
   -+------+------+------+-
```

### Back to the main question

If you put the higher-order (leftmost, in our traditional ordering)
bytes in higher addresses, you're using *big endian* notation.  If
you put the the higher-order bytes in lower addresses, you're using
little-endian notation.

There are advantages to each, which you can learn about when you
take CSC-211.

### Fun question

What happens when you try to store RGBA colors in an integer?

    color = (r << 24) + (g << 16) + (b << 8) + a;

This confused my research students for a bit.

### Sam's bonus rant

While I realize that "foolish consistency is a hobgoblin of little
minds", CS diagrams frustrate me.

* https://en.wikipedia.org/wiki/Endianness
* https://qph.fs.quoracdn.net/main-qimg-23fbf12935029f7f2350f2e7f366b38d

Macro issues
------------

### Macros vs. functions

* Function calls literally copy variables and such.  They require
  setup and takedown, and happen at runtime.
* Macros are processed at compile time, and copy text as opposed
  to any underlying representation.  (Macros work with text!)

### Ben's parens

Because macros copy text, we can get some weird behavior.

    #define DOUBLE(X) 2*X
    y = DOUBLE(2+3);
    ====
    y = 2*2+3;
    // Whoops!  Y is 7, rather than 10

Solution: Parenthesize variables in your macros.  (You may need
to parenthesize other things, too.)

    #define DOUBLE(X) 2*(X)
    y = DOUBLE(2+3);
    =====
    y = 2*(2+3);
    // Yay!  It's 10

Note: You need a *lot* of parentheses

    #define DOUBLE(X) (X)+(X)
    y = 2*DOUBLE(5)
    =====
    y = 2*(5)+(5)
    // Whoops 15, not 20

Solution: More parentheses!

    #define DOUBLE(X) ((X)+(X))

### Beware duplication (w side effects)

    int square(int x) { return x*x; }
    #define SQUARE(X) ((X)*(X))
    a = 1;
    b = 1;
    p = square(a++);
    q = SQUARE(b++); // expands to q = ((b++)*(b++))
    printf ("a=%d, b=%d, p=%d, q=%d\n", a, b, p, q);
    // Expected output? a=2, b=3, p=1, q=6
    // Expected output? a=2, b=3, p=1, q=1
    a = 1;
    b = 1;
    p = square(++a);
    q = SQUARE(++b);
    // Expected output? a=3, b=?, p=4, q=?

Why did Sam show you this?

* If you don't delve into the details of the macro, you assume
  `SQUARE(b++)` only increments `b` *once*.  That's a problem
  with the `SQUARE` macro, as I designed it.
* Because you need practice reading increment operations.
* So that you'd see that good C compilers groan about multiple
  increments in the same expression.

### More fun with duplication

    #define SILLY(X) ((X)-(X))

    int
    main (int argc, char *argv[])
    {
      int a, b, p, q;
      a = 1;
      p = SILLY(a++); // p = ((a++)-(a++))
      printf ("a=%d, p=%d\n", a, p);
      // Potential output? a=3, p=? -1,0,1
      b = 1;
      q = SILLY(++b); // q = ((++b)-(++b))
      printf ("b=%d, q=%d\n", b, q);
      // Potential output? b=3, q=?
    } // main

* Don't do this!

### Multi-line macros

Use backslashes to continue your line.

   #define MACRO(X) \  
     (X+X) * \
     (X+X)

### Multi-line macros, revisited

Sometimes, you want to execute multiple statements in one macro

```
#define STACK_POP2(head,result,next)                                 \
  (result) = (head);                                                 \
  (head) = (head)->next;                                            
```

What happens if we use it in a conditional or a loop?

```
if (x > 10)
  STACK_POP2(stck,tmp,next);
```

Translates to

```
if (x > 10)
  (tmp) = (stck); (stck) = (stck)->next;;
```

Two issues: 

* Only the (tmp) = (stck) is in the body of the if; this code
  will *always* execute the (stck) = (stck)->next.
* Now we have two semicolons at the end.

Solution: Wrap multiple statements in `do { ... } while (0)`

* That captures the semicolon we'd expect.
* It ensures that all the operations are grouped together, and so
  can serve as bodies in IF and other statements.

```
#define STACK_POP2(head,result,next)                                 \
do {                                                                 \
  (result) = (head);                                                 \
  (head) = (head)->next;                                             \
} while (0)
```

`utstack.h`
-----------

<https://github.com/troydhanson/uthash/blob/master/src/utstack.h>

What is puzzling/confusing about it?

* Those do/while loops.  (See above.)
* Why does the STACK_EMPTY macro work?
    * Because NULL is false.  !NULL is true.  !ANYTHING_ELSE is false.
      Isn't C wonderful?
* Where does `next` come from in, say `STACK_PUSH`?
    * It's text that gets substituted in.
* Why do we have both `STACK_PUSH` and `STACK_PUSH2`?
    * The first one assumes that the next pointer for our nodes
      is called next.  THe second one 

What is nice about it?

* You get library code without having to link it.
* It's widely used, which means you can be mostly sure it's correct.
  (At least multiple eyes have looked at it.)

Why doesn't Sam like it?  (Why do you hypothesize Sam doesn't like it?)

* Sam is not a real C programmer.
* You actually have to understand the behind-the-scenes manipulations
  to use it.  Sam likes more separation between interface and 
  implementation.
* Sam prefers to have stacks that contain their size.
* Sam hates looking at `STACK_PUSH(stack, item);` and knowing
  that `stack` is `NULL`.  My expectation is that `stack` doesn't
  change.  It should be `NULL` afterwards.

Why don't others like it

* Comments aren't in the code and you have to look for them elsewhere.
* Assumes the reader is a competent C programmer.

Sam's first improvement

```
#define STACK_POP(HEAD,RESULT)                                       \
  STACK_POP2(HEAD,RESULT,next)
```

Detour: Exponentiation
----------------------

_We'll start this today and continue it next time._

Goal: Compute `(x^n) mod m`, where `x`, `n`, and `m` are all non-negative long 
values.  

Assume: x < m and m < sqrt(LONG_MAX).

Obvious solution:

```
long
expmod(long x, long n, long m)
{
  long result = 1;
  for (i = 0; i < n; i++)
    {
      result = (result * x) % m;
    } // for
  return result;
} // expmod
```

* We want to do the `mod` each time through so that we don't overflow.

Can we do a more efficient solution?

```
long
expmod(long x, long n, long m)
{
  if (n == 0)                           // x^0 = 1
    {
      return 1;
    }
  else if ((n % 2) == 0) { // even
    long tmp = expmod(x, n/2, m);       // x^(2k) = x^k * x^k
    return (tmp * tmp) % m;
  }
  else {
    long tmp = expmod(x, n-1, m);       // x^(k+1) = x^k * x
    return (x * tmp) % m;
  }
} // expmod
```

This is much faster.  But it's recursive.

Write it non-recursively.

Q&A on Readings
---------------

* What, if anything, did you find confusing?
* What would you like me to spend class time on?
* What would you like to try to do during class?

Avoiding Repetitive Code
------------------------

How would our code change if we just wanted to compute `x^n`, where `x`
is a double and `n` is a non-negative long value?

### Detour: Meta-programming

### Meta-programming with macros

### Example, revisited

### Other examples

Parametric Polymorphism (Perhaps)
---------------------------------
