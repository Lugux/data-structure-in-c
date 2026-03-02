#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct
{
    unsigned char *data;
    size_t capacity;
    size_t bytes_avaible;
    size_t head;
    size_t tail;
}static_queue;

int static_queue_init(static_queue *queue, size_t capacity);
int static_queue_enqueue(static_queue *queue, const void *data, size_t dataSize);
int static_queue_peek(const static_queue *queue,void *data, size_t dataSize);
int static_queue_dequeue(static_queue *queue, void *data, size_t dataSize);
int static_queue_is_full(const static_queue *queue, size_t dataSize);
int static_queue_is_empty(const static_queue *queue);
void static_queue_destroy(static_queue *queue);


#endif // STATIC_QUEUE_H
