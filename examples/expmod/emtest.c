#include "srtest.h"
#include "expmod.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_TESTS 100
#define LARGEST_EXP 10000

int main(int argc, char *argv[])
{
  sr_reset();
  srand(time(0));

  long val;
  long mod;
  long maxExp;

  for (int i = 0; i < NUM_TESTS; i++)
    {
      //Not strictly necessary, but makes the user feel better when waiting a long time
      fprintf(stderr,"Running test %d\n",i);
      //Set all the values randomly
      val = rand();
      mod = rand();
      maxExp = rand()%LARGEST_EXP;

      val %= mod;
      //Check 0 and 1 exponents
      SR_CHECK_LONG(stderr, expmod(val, 0, mod), 1);
      SR_CHECK_LONG(stderr, expmod(val, 1, mod), val);

      long current = val;
      //Check lots of other exponents
      for (long e = 2; e <= maxExp; e++)
        {
          current = (current * val) % mod;
          SR_CHECK_LONG(stderr, expmod(val, e, mod), current);
        }
    }

  if (sr_get_errors())
    {
      sr_report(stderr);
      return 1;
    }
  else
    {
      return 0;
    }
} // main
