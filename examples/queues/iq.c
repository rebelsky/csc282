#include "iq.h"

#include <limits.h>
#include <stdlib.h>

typedef struct iq_node
{
    int contents;       
    struct iq_node *next; 
} iq_node;

//Struct for the whole queue
typedef struct iq
{
    int size;       
    iq_node *first; ´
    iq_node *last; 
} IQ;

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
IQ *
iq_new ()
{
	IQ * out = malloc(sizeof(IQ));
	// if the malloc failed then out will be NULL in which case we don't want to do anything
	if (out){
		out->size=0;
		out->first=NULL;
		out->last=NULL;
	}
	return out;
} // iq_new

/**
 * Deallocate and clean up a queue.
 */
void 
iq_free (IQ *q)
{
	// if q is empty then first is NULL, a false-ish value, ensuring proper ending
	while(q->first){
		// dequeue frees the memory
		dequeue(q)
	}
	// deallocate the queue itself
	free(q)

} // iq_free

/**
 * Determine the number of elements in the queue.
 */
int 
iq_size (IQ *q)
{
	return q->size;
} // iq_size

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
iq_enqueue (IQ *q, int str)
{
	iq_node * new_node = malloc(sizeof(iq_node));
	if (iq_node){
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
int 
iq_peek (IQ *q)
{
	// if the struct is empty then first is NULL which is a false-ish value
	if (q->first)
	{
		return q->first->contents;
	} // if
	return NULL;
} // iq_peek

/**
 * Remove and return the first element of the queue.
 *
 * Returns INT_MIN if the queue is empty.
 */
int 
iq_dequeue (IQ *q)
{	// by default we return INT_MIN
	int  out = INT_MIN;
	if (q->size>0)
	{
		q->size--; // decrement size
		iq_node * temp = q->first;  // temporarily keep the first element so we can deallocate it later
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
} //iq_dequeue
