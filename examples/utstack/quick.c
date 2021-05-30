#define STACK_PUSH2(head,add,next)                                   \
do {                                                                 \
  (add)->next = (head);                                              \
  (head) = (add);                                                    \
} while (0)

STACK_PUSH2(hello,goodbye,fred);
