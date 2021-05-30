#include <stdio.h>
#include <stdlib.h>

#include "sq.h"

/*
these are in my sq.h

typedef struct node{
    char* str;
    struct node* next;
} node_t;

typedef struct sq{
    node_t* front;
    node_t* back;
} SQ;
*/


// +-----------+-----------------------------------------------------
// | Functions |
// +-----------+

/**
 * Allocate and initialize a new queue.
 *
 * Returns NULL if it is not possible to create a new queue.
 */
SQ *sq_new (){
    // Assume always possible to create new q
    // Allocate space for an SQ. Needs to be freed in main.
    SQ* sq = malloc(sizeof(SQ));
    if(sq == NULL){
        // malloc failed?
        return NULL;
    }
    // Set front and back to NULL
    sq->front = NULL;
    sq->back = NULL;
    // return the queue pointer
    return sq;
}

/**
 * Deallocate and clean up a queue.
 */
void sq_free (SQ *q){
    // deQ until the q is empty.
    while(sq_dequeue(q));
    // the Q can be used after it is sq_freed, will just have 0 elements,
    // unless i want to free it here
}

/**
 * Determine the number of elements in the queue.
 */
int sq_size (SQ *q){
    // Initialize the count to 0
    int count = 0;

    // Initialize a pointer to the back to iterate through each node.
    node_t* node = q->back;
    // Loop until we reach the front.
    while(node){
        // Increment count and move pointer to the next node.
        count++;
        node = node->next;
    }
    // When done looping return count.
    return count;
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
int sq_enqueue (SQ *q, char *str){
    // Make space for a new node
    node_t* node = malloc(sizeof(node_t));

    // Fill the node with the string
    node->str = str;

    // If this is the first insertion, node will be the front and the back
    // i'll have its next be NULL though, because this new node will be the front until removed
    if(q->front == NULL){
        q->front = node;
        q->back = node;
        node->next = NULL;
        return 0;
    }
    // Otherwise not the first insertion, insert new node to the back.
    else{
        // Its Next node will be the previous back.
        node->next = q->back;
        // and it'll be the new back.
        q->back = node;
        return 0;
    }
    // This never fails since there's no limit.
}

/**
 * Peek at the front of the queue.  Does not affect the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_peek (SQ *q){
    // q is empty if its front is NULL
    if(q->front == NULL){
        return NULL;
    }else{
        // If not empty, just return the front string
        return q->front->str;
    }
}

/**
 * Remove and return the first element of the queue.
 *
 * Returns NULL if the queue is empty.
 */
char *sq_dequeue (SQ *q){

    // If Q is empty return null.
    if(q->front == NULL){
        return NULL;
    } 
    // Otherwise, if there is only one node left,
    else if(sq_size(q) == 1){
         // Initialize pointer to the only node
        node_t* onlynode = q->front;
        // store onlynode's string
        char* element = onlynode->str;
        // Free the space pointed to by onlynode
        free(onlynode);
        // set front and back to be NULL
        q->front = NULL;
        q->back = NULL;
        // return the first element
        return element;
    } 
    // If there is more than one node
    else{

         // Initialize pointer to the old front
         node_t* oldfront = q->front;

        // store oldfront string
        char* element = oldfront->str;

        // initialize pointer to the back of the queue in order to iterate to find the new front
        node_t* newfront = q->back;

        // Loop until newfront points to the old front's previous node, which is the new front.
        while(newfront->next->next){
            newfront = newfront->next;
        }
        // newfront's next will be NULL.
        newfront->next = NULL;

        // Set the front to be newfront.
        q->front = newfront;

        // free the space pointed to by oldfront and return the (old) front element
        free(oldfront);
        return element;
    }
}


