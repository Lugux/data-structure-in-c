#include <stdlib.h>
#include <string.h>

#include "static_stack.h"

int static_stack_init(static_stack *stack, size_t capacity)
{
    if(!stack || !capacity)
        return 0;
    stack->data = malloc(capacity);
    if(!stack->data)
        return 0;
    stack->capacity = capacity;
    stack->top = 0;
    return 1;
}

int static_stack_push(static_stack *stack, const void *data, size_t dataSize)
{
    if(!stack || !data || !dataSize)
        return 0;
    if(stack->capacity < stack->top + dataSize + sizeof(size_t))
        return 0;
    stack->top += dataSize;
    memcpy(stack->data + stack->capacity - stack->top, data, dataSize);
    stack->top += sizeof(size_t);
    memcpy(stack->data + stack->capacity - stack->top, &dataSize, sizeof(size_t));
    return 1;
}

int static_stack_peek(const static_stack *stack,void *data, size_t dataSize)
{
    if(!stack || !stack->data || !data || !dataSize)
        return 0;
    if(stack->top < sizeof(size_t))
        return 0;
    size_t tempSize;
    memcpy(&tempSize, stack->data + stack->capacity - stack->top, sizeof(size_t));
    if(stack->top < tempSize + sizeof(size_t))
        return 0;
    memcpy(data, stack->data + stack->capacity - stack->top + sizeof(size_t), MIN(tempSize,dataSize));
    return 1;
}

int static_stack_pop(static_stack *stack, void *data, size_t dataSize)
{
    if(!stack || !stack->data || !data || !dataSize)
        return 0;
    if(stack->top < sizeof(size_t))
        return 0;
    size_t tempSize;
    memcpy(&tempSize, stack->data + stack->capacity - stack->top, sizeof(size_t));
    if(stack->top < tempSize + sizeof(size_t))
        return 0;
    memcpy(data, stack->data + stack->capacity - stack->top + sizeof(size_t), MIN(tempSize,dataSize));
    stack->top -= tempSize + sizeof(size_t);
    return 1;
}

int static_stack_is_full(const static_stack *stack, size_t dataSize)
{
    if(!stack)
        return 0;

    return stack->capacity - stack->top < dataSize + sizeof(size_t);
}

int static_stack_is_empty(const static_stack *stack)
{
    if(!stack)
        return 0;

    return stack->top == 0;
}

void static_stack_destroy(static_stack *stack)
{
    if(!stack || !stack->data)
        return;

    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->top = 0;
}
