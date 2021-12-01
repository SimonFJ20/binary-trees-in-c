#include <stdlib.h>
#include <assert.h>

#include "stack.h"

Stack* stack_new(size_t maxsize)
{
    assert(maxsize > 0 && "maxsize too smol");
    Stack* s = (Stack *) malloc(sizeof(Stack));
    s->index = 0;
    s->maxsize = maxsize;
    s->stack = (void **) malloc(sizeof(void**) * maxsize);
    return s;
}   

void* stack_free(Stack* s)
{
    free(s->stack);
    free(s);
    return NULL;
}

size_t stack_length(Stack* s)
{
    return s->index + 1;
}

int stack_can_push(Stack* s)
{
    return s->index < s->maxsize;
}

int stack_can_pop(Stack* s)
{
    return s->index > 0;
}

void stack_push(Stack* s, void* v)
{
    assert(stack_can_push(s) && "stack overflow");
    s->index++;
    s->stack[s->index] = v;
}

void* stack_pop(Stack* s)
{
    assert(stack_can_pop(s) && "stack underflow");
    void* v = s->stack[s->index];
    s->index--;
    return v;
}

void** stack_get_list(Stack* s)
{
    return s->stack;
}
