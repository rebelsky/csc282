#include <stdio.h>
#include <stdlib.h>

#include "sq.h"

/* node data structure */
struct node {
  char *string;
  struct node *next;
};

/* queue data structure */
struct sq {
  struct node *front;
  struct node *back;
  int          size;
};

static void sq_print(SQ *q);

int
main(void)
{
  /* test */
  SQ *queue = sq_new();

  sq_enqueue(queue, "okra");
  sq_print(queue);

  sq_enqueue(queue, "milk");
  sq_print(queue);
  printf("peek result: %s\n", sq_peek(queue));

  sq_enqueue(queue, "bread");
  sq_print(queue);

  sq_print(queue);
  printf("peek result: %s\n", sq_peek(queue));

  sq_dequeue(queue);
  sq_print(queue);

  sq_dequeue(queue);
  sq_print(queue);

  sq_dequeue(queue);
  sq_print(queue);

  sq_enqueue(queue, "herman cain");
  sq_print(queue);

  sq_free(queue);
}

static
void sq_print(SQ *q)
{
  if (!(q->size))
    {
      printf("queue is empty!\n");
      return;
    }

  struct node *tmp = q->front;
  printf("[");
  while (tmp)
    {
      printf("%s, ", (tmp->string));
      tmp = tmp->next;
    }

  printf("\b\b]");
  printf(" (size = %d)\n", sq_size(q));
}

/*
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
SQ *
sq_new()
{
  SQ *str_queue    = malloc(sizeof(struct sq));

  /* if malloc failed, return NULL */
  if (!str_queue) {
      return NULL;
  }

  str_queue->front = NULL;
  str_queue->back  = NULL;
  str_queue->size  = 0;

  return str_queue;
}

/*
 * Deallocate and clean up a queue.
 */
void
sq_free(SQ *q)
{
  /* if queue is empty, we just need to free the queue */
  if (!(q->size))
    {
      free(q);
      return;
    }

  /* else, we need to free the nodes */
  struct node *tmp = q->front;
  struct node *tmp_next;

  /* iterate through the queue, freeing each node you find */
  while (tmp)
    {
      if (tmp->next)
        {
          tmp_next = tmp->next;
          free(tmp);
          tmp = tmp_next;
        }
      else
        {
          free(tmp);
          break;
        }
    }

  free(q);
}

/*
 * Determine the number of elements in the queue.
 */
int
sq_size(SQ *q)
{
  return q->size;
}

/*
 * Add str to the queue.
 *
 * Returns 1 for success and 0 for failure.  
 *
 * Does *not* make a copy of the string; if the underlying string
 * changes, then so does the string in the queue.
 *
 * Pre: str != NULL
 */
int
sq_enqueue(SQ *q, char *str)
{
  /* declares and initializes new node */
  struct node *new = malloc(sizeof(struct node));
  new->string      = str;
  new->next        = NULL;

  /* if malloc failed, return 0 */
  if (!new)
    {
      return 0;
    }

  /*
   * if queue is empty, then simply set front and back to new
   *
   * if queue is not empty, then set the next field of back to new, and
   * and then set back to new
   */
  if (q->size)
    {
      (q->back)->next = new;
      q->back = new;
    }
  else
    {
      q->front = new;
      q->back  = new;
    }

  q->size++;

  return 1;
}

/*
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *
sq_peek (SQ *q)
{
  if (!(q->size)) {
      return NULL;
  }

  return (q->front)->string;
}

/*
 * Remove and return the first element of the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *
sq_dequeue (SQ *q)
{
  char *first;

  /* if queue is empty, return NULL */
  if (!(q->size))
    {
      printf("queue is already empty!\n");
      return NULL;
    }

  /* keep first element so we can return it later */
  first = (q->front)->string;

  /* keep a temp ptr to the current front */
  struct node *tmp = q->front;

  /* 
   * if our queue is size 1, then front and back will both be NULL
   * 
   * if our queue size is greater than 1, then we set front to the next
   * field of the current front, and free it
   */
  if (q->size == 1)
    {
      q->front = NULL;
      q->back  = NULL;
      q->size--;

      return first;
    }
  else
    {
      q->front = (q->front)->next;
      free(tmp);
      q->size--;
    }

  return first;
}
