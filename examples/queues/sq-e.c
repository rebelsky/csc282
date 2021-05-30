#include "sq.h"

#include <stdlib.h>

//Struct for each element in the queue
typedef struct sq_node
{
    char *contents;       //The string contained in this node
    struct sq_node *next; //The next node in the linked structure
} sq_node;

//Struct for the whole queue
typedef struct sq
{
    int size;       //How many items are in the queue
    sq_node *first; //The next item to be returned
    sq_node *last;  //The item that was most recently added
} SQ;

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
SQ *sq_new()
{
    SQ *toReturn = malloc(sizeof(SQ));
    if (toReturn)
    {
        toReturn->size = 0;
        toReturn->first = NULL;
        toReturn->last = NULL;
    }
    return toReturn; //If malloc failed, toReturn will be null, so this fulfills the requirement
}

/**
 * Deallocate and clean up a queue.
 */
void sq_free(SQ *q)
{
    while (q->size > 0)
    {
        sq_dequeue(q);
    }
}

/**
 * Determine the number of elements in the queue.
 */
int sq_size(SQ *q)
{
    return q->size;
}

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
int sq_enqueue(SQ *q, char *str)
{
    //Make the new node
    sq_node *new = malloc(sizeof(sq_node));
    if (!new)
    {
        //Malloc failed, so the enqueue was not successful
        return 0;
    }

    new->contents = str;
    if (q->size == 0)
    {
        //If the queue is empty, the new node is both first and last
        q->first = new;
        q->last = new;
    }
    else
    {
        //Put the new node at the back of the queue
        q->last->next = new;
        q->last = new;
    }
    q->size++;
    //In all other cases, we were sucessful
    return 1;
}

/**
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_peek(SQ *q)
{
    if (q->size == 0)
    {
        //Return null if the queue is empty
        return NULL;
    }
    else
    {
        //Otherwise, return the contents of the first element on the queue
        return q->first->contents;
    }
}

/**
 * Remove and return the first element of the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_dequeue(SQ *q)
{
    if (q->size == 0)
    {
        //There is nothing on the queue
        return NULL;
    }
    else if (q->size == 1)
    {
        char *toReturn = q->first->contents;
        free(q->first);
        q->first = NULL;
        q->last = NULL;
        q->size--;
        return toReturn;
    }
    else
    {
        sq_node *temp = q->first;
        //Move the first pointer to the next item
        q->first = temp->next;
        char *toReturn = temp->contents;
        //Free the space for the node being removed
        free(temp);
        q->size--;
        return toReturn;
    }
}

