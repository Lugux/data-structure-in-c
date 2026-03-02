#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct dynamic_queue_node
{
    void *data;
    size_t dataSize;
    struct dynamic_queue_node *next;
}dynamic_queue_node;

typedef struct
{
    dynamic_queue_node *head;
    dynamic_queue_node *tail;
}dynamic_queue;

void dynamic_queue_init(dynamic_queue *queue);
int dynamic_queue_enqueue(dynamic_queue *queue, const void *data, size_t dataSize);
int dynamic_queue_peek(const dynamic_queue *queue,void *data, size_t dataSize);
int dynamic_queue_dequeue(dynamic_queue *queue, void *data, size_t dataSize);
int dynamic_queue_is_empty(const dynamic_queue *queue);
void dynamic_queue_destroy(dynamic_queue *queue);


#endif // DYNAMIC_QUEUE_H
