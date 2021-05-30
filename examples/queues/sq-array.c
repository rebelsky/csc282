/**
 * sq-array.c
 *   A simple implementation of queues of strings in arrays.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "sq.h"
#include <stdlib.h>

// +-----------+-----------------------------------------------------
// | Constants |
// +-----------+

/* The largest queues we support (not very big right now */
#ifndef QUEUE_CAP
#define QUEUE_CAP 5
#endif

// +-------+---------------------------------------------------------
// | Types |
// +-------+

/**
 * Our queues.
 */
struct sq
  {
    int size;           // The number of elements in the queue.
    int capacity;       // The capacity, just in case we make this variable.
    int front;          // The index of the front element.                  
    char **elements;    // The elements of the queue
  };


// +--------------------+--------------------------------------------
// | Exported Functions |
// +--------------------+

SQ *
sq_new ()
{
  SQ *q = (SQ *) malloc (sizeof (SQ));
  if (!q) return NULL;
  q->elements = (char **) malloc(QUEUE_CAP * sizeof (char *));
  if (!(q->elements ))
    {
      free (q);
      return NULL;
    }
  q->size = 0;
  q->capacity = QUEUE_CAP;
  q->front = 0;
  return q;
} // sq_new

void 
sq_free (SQ *q)
{
  if (!q) return;
  if (q->elements)
    {
      free (q->elements);
      q->elements = NULL;
    }
  free (q);
} // sq_free

int 
sq_size (SQ *q)
{
  return q->size;
} // sq_size

int 
sq_enqueue (SQ *q, char *str)
{
  if (q->size >= q->capacity)
    return 0;
  if (!str )
    return 0;
  q->elements[(q->front + q->size) % q->capacity] = str;
  q->size += 1;
  return 1;
} // sq_enqueue

char *
sq_peek (SQ *q)
{
  if (q->size <= 0)
    return NULL;
  return q->elements[q->front];
} // sq_peek

char *
sq_dequeue (SQ *q)
{
  if (q->size <= 0)
    return NULL;
  char *result = q->elements[q->front];
  q->front = (q->front + 1) % q->capacity;
  q->size -= 1;
  return result;
} // sq_dequeue

