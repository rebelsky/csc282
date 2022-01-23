#ifndef __IQ_H__
#define __IQ_H__

/**
 * iq.h
 *   Queues of strings.  Queues are First-In, First-Out data structures.
 */

// +-------+---------------------------------------------------------
// | Types |
// +-------+

typedef struct iq IQ;


// +-----------+-----------------------------------------------------
// | Functions |
// +-----------+

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
IQ *iq_new ();

/**
 * Deallocate and clean up a queue.
 */
void iq_free (IQ *q);

/**
 * Determine the number of elements in the queue.
 */
int iq_size (IQ *q);

/**
 * Add str to the queue.
 *
 * Returns 1 for success and 0 for failure.  
 *
 * Does *not* make a copy of the string; if the underlying string
 * changes, then so does the string in the queue.
 *
 * Pre: str != INT_MIN
 */
int iq_enqueue (IQ *q, int str);

/**
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns INT_MIN if the queue is empty.
 */
int iq_peek (IQ *q);

/**
 * Remove and return the first element of the queue.
 *
 * Returns INT_MIN if the queue is empty.
 */
int iq_dequeue (IQ *q);

#endif // __IQ_H__
