#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct dynamic_stack_node
{
    void *data;
    size_t dataSize;
    struct dynamic_stack_node *next;
}DynamicStackNode;

typedef DynamicStackNode *DynamicStack;

void dynamic_stack_init(DynamicStack *stack);
int dynamic_stack_push(DynamicStack *stack, const void *data, size_t dataSize);
int dynamic_stack_peek(const DynamicStack *stack,void *data, size_t dataSize);
int dynamic_stack_pop(DynamicStack *stack, void *data, size_t dataSize);
int dynamic_stack_is_empty(const DynamicStack *stack);
void dynamic_stack_destroy(DynamicStack *stack);

#endif // DYNAMIC_STACK_H
