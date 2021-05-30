#ifndef __SQ_H__
#define __SQ_H__

/**
 * sq.h
 *   Queues of strings.  Queues are First-In, First-Out data structures.
 */

// +-------+---------------------------------------------------------
// | Types |
// +-------+

typedef struct sq SQ;


// +-----------+-----------------------------------------------------
// | Functions |
// +-----------+

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
SQ *sq_new ();

/**
 * Deallocate and clean up a queue.
 */
void sq_free (SQ *q);

/**
 * Determine the number of elements in the queue.
 */
int sq_size (SQ *q);

/**
 * Add str to the queue.
 *
 * Returns 1 for success and 0 for failure.  
 *
 * Does *not* make a copy of the string; if the underlying string
 * changes, then so does the string in the queue.
 *
 * Pre: str != NULL
 */
int sq_enqueue (SQ *q, char *str);

/**
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_peek (SQ *q);

/**
 * Remove and return the first element of the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_dequeue (SQ *q);

#endif // __SQ_H__
