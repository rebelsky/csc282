#define SQUARE_FUN(NAME, TYPE) \
  TYPE  \
  NAME (TYPE X) \
  { \
    printf ("Squareing\n"); \
    return X*X; \
  }

SQUARE_FUN(isquare, int)
SQUARE_FUN(dsquare, double)
SQUARE_FUN(lsquare, long)
