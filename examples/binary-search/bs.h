#ifndef __BS_H__
#define __BS_H__

/**
 * Find an index of v in a, which is sorted in non-decreasing
 * order.  If v does not appear in a, returns -1.
 *
 * Pre: For all i, 0 < i < n, a[i-1] <= a[i].
 * Post: Let j = binarySearch(v, a, n).  If j == -1, then there
 *   does not exist an i s.t. v = a[i].  Otherwise, v == a[j].
 */
int binary_search_ints (int v, int a[], int n);

#endif // __BS_H__
