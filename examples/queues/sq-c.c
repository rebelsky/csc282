#include "sq.h"

#include <stdlib.h>

typedef struct sq_node
{
    char *contents;       
    struct sq_node *next; 
} sq_node;

//Struct for the whole queue
typedef struct sq
{
    int size;       
    sq_node *first; ´
    sq_node *last; 
} SQ;

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
SQ *
sq_new ()
{
	SQ * out = malloc(sizeof(SQ));
	// if the malloc failed then out will be NULL in which case we don't want to do anything
	if (out){
		out->size=0;
		out->first=NULL;
		out->last=NULL;
	}
	return out;
} // sq_new

/**
 * Deallocate and clean up a queue.
 */
void 
sq_free (SQ *q)
{
	// if q is empty then first is NULL, a false-ish value, ensuring proper ending
	while(q->first){
		// dequeue frees the memory
		dequeue(q)
	}
	// deallocate the queue itself
	free(q)

} // sq_free

/**
 * Determine the number of elements in the queue.
 */
int 
sq_size (SQ *q)
{
	return q->size;
} // sq_size

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
int 
sq_enqueue (SQ *q, char *str)
{
	sq_node * new_node = malloc(sizeof(sq_node));
	if (sq_node){
		new_node->contents = str; // store the contents without copying
		new_node->next = NULL; // ensure that the next element is NULL
		q->size++; // increment size
		if(q->size>0){
			q->last->next=new_node; // link the new element
			q->last = new_node; // move last forward
		}
		else{ // if the struct was empty we need to set both first and last
			q->first =new_node;
			q->last = new_node;
		}
		return 1;
	}
	return 0;
}

/**
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *
sq_peek (SQ *q)
{
	// if the struct is empty then first is NULL which is a false-ish value
	if (q->first)
	{
		return q->first->contents;
	} // if
	return NULL;
} // sq_peek

/**
 * Remove and return the first element of the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *
sq_dequeue (SQ *q)
{	// by default we return NULL
	char * out = NULL;
	if (q->size>0)
	{
		q->size--; // decrement size
		sq_node * temp = q->first;  // temporarily keep the first element so we can deallocate it later
		q->first = q->first->next; // update first
		out = temp->contents; // set out output
		free(temp); // free the first element
		if(q->size == 1)
		{
			// if size == 1 then first->next == NULL meaning we only needs this last line
			q->last = NULL;
		} //if
	}//if
	return out;
} //sq_dequeue
