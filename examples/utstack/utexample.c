/**
 * utstack_example.c
 *   An example of utstack, based closely on the sample code
 *   in utstack.h.
 */

// +---------+-------------------------------------------------------
// | Headers |
// +---------+

#include "utstack.h"
#include <stdlib.h>

// +-------+---------------------------------------------------------
// | Types |
// +-------+

struct item 
  {
    int id;
    struct item *next;
  }

struct item2
  {
    char *str;
    struct item2* successor;
  }

// +------+----------------------------------------------------------
// | Main |
// +------+

int 
main() 
{
  struct item *stack = NULL:
  struct item2 *stack2 = NULL:

  int count;
  struct item *tmp;
  struct item *item = malloc(sizeof *item);
  item->id = 42;
  struct item2 *stack2 
  struct item2 *two, = malloc(sizeof *item2);
  two->str = "I am a string";

  STACK_PUSH2(stack2, two, successor);
  STACK_COUNT(stack, tmp, count); 
  STACK_PUSH(stack, item);
  STACK_COUNT(stack, tmp, count);
  STACK_POP(stack, item);
  free(item);
  STACK_COUNT(stack, tmp, count);
} // main


