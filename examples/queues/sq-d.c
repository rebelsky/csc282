#include "sq.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct strnode strnode;

typedef struct strnode {
  char * string;
  strnode * next;
} strnode;

struct sq {
  strnode * head;
  strnode * tail;
  int size;
};


/**
 * Allocate and initialize a new queue. 
 * 
 * Returns NULL if it is not possible to create a new queue.
 */
SQ * 
sq_new(){
  return malloc(sizeof(struct sq));
}

void 
sq_free (SQ *q){
  if (q == NULL){
    return;
  }

  for (strnode * n = (q->head); n != NULL; n = n->next){
    free(n);
  }
  free(q);
  return;
}

/**
 * Add str to the queue, provided we haven't reached the limit.
 * If we reach the limit, returns 0.  Otherwise, returns 1.
 *
 * The user is responsible for allocating and deallocating the string. 
 */
int 
sq_enqueue (SQ * q, char * str) {
  
  strnode * n = malloc(sizeof(strnode));
  if (n == NULL){
    return 0;
  }

  (*n).next = NULL;
  (*n).string = str;

  if (q->head == NULL){
    q->head = n;
    q->tail = n;
    q->size = 1;
    return 1;
  }
  
  strnode * t = q->tail;
  t->next = n;
  q->tail = n;
  (*q).size++;
  return 1;
} //snq (SQ * q, char * str)

/**
 * Remove something from the queue, provided the queue is not empty.
 *
 * The client is responsible for freeing this string.
 */
char * 
sq_dequeue (SQ * q) {
  
  if ((*q).head == NULL){
    return NULL;
  }

  strnode * h = q->head;
  char * str = h->string;
  q->head = NULL;
  if (h == q->tail){
    q->tail = NULL;
  }
  free(h);
  return str;
} //sdq (SQ * q)

/**
 * Check if the queue is empty
 */
int 
sq_empty (SQ * q) {

 if (q == NULL){
   return 1;
 }

 if (q->head == NULL){
   return 1;
 }
 return 0;

}

/**
 * Check the front element (if the queue is nonempty). 
 * 
 * If memory for a string cannot be allocated, returns NULL.
 */
char *
sq_peek (SQ * q) {
  strnode *  h = q->head;
  char * r = malloc(sizeof(char) * strlen(h->string));
  
  if (r == NULL){
    return NULL;
  }
  strcpy(r, h->string);
  return r;
}

/**
 * Determine the size of the queue
 */
int
sq_size (SQ * q) {
  if (q == NULL){
    return 0;
  }
  return q->size;
}

void 
printq (SQ * q) {
  if (q == NULL) {
    return;
  }

  strnode * n = q->head;
  
  printf("HEAD: ");
  if (n == NULL) {
    printf("[null]\tTAIL\n");
  } else {
    printf("%s", n->string);
    n = n->next;
    while (n != NULL) {
      printf("\n  -> %s", n->string);
      n = n->next;
    }
    printf("\tTAIL\n");
  }
  return;
}

