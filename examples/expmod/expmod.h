#ifndef __EXPMOD_H__
#define __EXPMOD_H__

/**
 * Compute (x^n) % m, without overflow.
 *
 * Pre: 0 < m < sqrt(LONG_MAX)
 * Pre: x < m
 * Pre: n >= 0
 */
long expmod (long x, long n, long m);

#endif // __EXPMOD_H__
