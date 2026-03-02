#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct
{
    unsigned char *data;
    size_t capacity;
    size_t top; //number of bytes currently used
}static_stack;

int static_stack_init(static_stack *stack, size_t capacity);
int static_stack_push(static_stack *stack, const void *data, size_t dataSize);
int static_stack_peek(const static_stack *stack,void *data, size_t dataSize);
int static_stack_pop(static_stack *stack, void *data, size_t dataSize);
int static_stack_is_full(const static_stack *stack, size_t dataSize);
int static_stack_is_empty(const static_stack *stack);
void static_stack_destroy(static_stack *stack);

#endif // STATIC_STACK_H
