#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct
{
    size_t index;
    size_t maxsize;
    void** stack;
}
Stack;

Stack*  stack_new(size_t maxsize);
void*   stack_free(Stack* s);

size_t  stack_length(Stack* s);
int     stack_can_push(Stack* s);
int     stack_can_pop(Stack* s);
void    stack_push(Stack* s, void* v);
void*   stack_pop(Stack* s);
void**  stack_get_list(Stack* s);

#endif