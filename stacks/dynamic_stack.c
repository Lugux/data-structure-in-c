#include <stdlib.h>
#include <string.h>

#include "dynamic_stack.h"

void dynamic_stack_init(DynamicStack *stack)
{
    *stack = NULL;
}

int dynamic_stack_push(DynamicStack *stack, const void *data, size_t dataSize)
{
    if(!stack || !data || dataSize == 0)
        return 0;
    DynamicStackNode *new_node = malloc(sizeof(DynamicStackNode));
    if(!new_node)
        return 0;
    new_node->data = malloc(dataSize);
    if(!new_node->data)
    {
        free(new_node);
        return 0;
    }

    memcpy(new_node->data, data, dataSize);
    new_node->dataSize = dataSize;
    new_node->next = *stack;
    *stack = new_node;
    return 1;
}

int dynamic_stack_peek(const DynamicStack *stack,void *data, size_t dataSize)
{
    if(!*stack || !data || dataSize == 0)
        return 0;
    memcpy(data,(*stack)->data,MIN((*stack)->dataSize,dataSize));
    return 1;
}

int dynamic_stack_pop(DynamicStack *stack, void *data, size_t dataSize)
{
    if(!*stack || !data || dataSize == 0)
        return 0;
    memcpy(data,(*stack)->data,MIN((*stack)->dataSize,dataSize));

    DynamicStackNode *tempNode = *stack;
    *stack = (*stack)->next;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int dynamic_stack_is_empty(const DynamicStack *stack)
{
    return !stack || !*stack;
}

void dynamic_stack_destroy(DynamicStack *stack)
{
    while(*stack)
    {
        DynamicStackNode *tempNode = *stack;
        *stack = (*stack)->next;
        free(tempNode->data);
        free(tempNode);
    }
}
