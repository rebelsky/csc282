#ifndef __LOGMATH_H__
#define __LOGMATH_H__

/**
 * logmath.h
 *   A quick and dirty hack (aren't they all) to help us keep
 *   track of multiplications, divisions, moduli, and such.
 */
#ifdef LOGMATH
extern long _MULTIPLICATIONS;
extern long _DIVISIONS;
extern long _MODS;

#define MULTIPLY(X,Y) ((_MULTIPLICATIONS++ * 0) + ((X)*(Y)))
#define DIVIDE(X,Y) ((_DIVISIONS++ * 0) + ((X)/(Y)))
#define MOD(X,Y) ((_MODS++ * 0) + ((X)%(Y)))

#else
#define MULTIPLY(X,Y) ((X)*(Y))
#define DIVIDE(X,Y) ((X)/(Y))
#define MOD(X,Y) ((X)%(Y))

#endif

#endif // __LOGMATH_H__
