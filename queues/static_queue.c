#include <stdlib.h>
#include <string.h>

#include "static_queue.h"

int static_queue_init(static_queue *queue, size_t capacity)
{
    if(!queue || !capacity)
        return 0;
    queue->data = malloc(capacity);
    if(!queue->data)
        return 0;
    queue->capacity = capacity;
    queue->bytes_avaible = capacity;
    queue->head = 0;
    queue->tail = 0;
    return 1;
}

int static_queue_enqueue(static_queue *queue, const void *data, size_t dataSize)
{
    if(!queue || !data || !dataSize)
        return 0;
    if (dataSize + sizeof(size_t) > queue->capacity)
        return 0;
    if(queue->bytes_avaible < sizeof(size_t) + dataSize)
        return 0;
    size_t start, end;

    if((start = MIN(sizeof(size_t), queue->capacity - queue->tail)))
        memcpy(queue->data + queue->tail, &dataSize, start);
    if((end = sizeof(size_t) - start))
        memcpy(queue->data, (unsigned char*)&dataSize + start, end);
    queue->tail = (queue->tail + sizeof(size_t)) % queue->capacity;

    if((start = MIN(dataSize, queue->capacity - queue->tail)))
        memcpy(queue->data + queue->tail, data, start);
    if((end = dataSize - start))
        memcpy(queue->data, (unsigned char*)data + start, end);
    queue->tail = (queue->tail + dataSize) % queue->capacity;

    queue->bytes_avaible -= sizeof(size_t) + dataSize;

    return 1;
}

int static_queue_peek(const static_queue *queue,void *data, size_t dataSize)
{
    if(!queue || !data || !dataSize)
        return 0;
    if(queue->bytes_avaible == queue->capacity)
        return 0;
    size_t start, end, tempDataSize, position = queue->head;

    if((start = MIN(sizeof(size_t), queue->capacity - position)))
        memcpy(&tempDataSize, queue->data + position, start);
    if((end = sizeof(size_t) - start))
        memcpy((unsigned char*)&tempDataSize + start, queue->data, end);
    if (tempDataSize + sizeof(size_t) > queue->capacity)
        return 0;
    position = (queue->head + sizeof(size_t)) % queue->capacity;

    if((start = MIN(MIN(dataSize, tempDataSize), queue->capacity - position)))
        memcpy(data, queue->data + position, start);
    if((end = MIN(dataSize, tempDataSize) - start))
        memcpy((unsigned char*)data + start, queue->data, end);
    return 1;
}

int static_queue_dequeue(static_queue *queue, void *data, size_t dataSize)
{
    if(!queue || !data || !dataSize)
        return 0;
    if(queue->bytes_avaible == queue->capacity)
        return 0;
    size_t start, end, tempDataSize;

    if((start = MIN(sizeof(size_t), queue->capacity - queue->head)))
        memcpy(&tempDataSize, queue->data + queue->head, start);
    if((end = sizeof(size_t) - start))
        memcpy((unsigned char*)&tempDataSize + start, queue->data, end);
    if (tempDataSize + sizeof(size_t) > queue->capacity)
        return 0;
    queue->head = (queue->head + sizeof(size_t)) % queue->capacity;

    if((start = MIN(MIN(dataSize, tempDataSize), queue->capacity - queue->head)))
        memcpy(data, queue->data + queue->head, start);
    if((end = MIN(dataSize, tempDataSize) - start))
        memcpy((unsigned char*)data + start, queue->data, end);

    queue->head = (queue->head + tempDataSize) % queue->capacity;
    queue->bytes_avaible += sizeof(size_t) + tempDataSize;

    return 1;
}

int static_queue_is_full(const static_queue *queue, size_t dataSize)
{
    if(!queue)
        return 0;
    return queue->bytes_avaible < sizeof(size_t) + dataSize;
}
int static_queue_is_empty(const static_queue *queue)
{
    if(!queue)
        return 0;
    return queue->bytes_avaible == queue->capacity;
}

void static_queue_destroy(static_queue *queue)
{
    if(!queue || !queue->data)
        return;
    free(queue->data);
    queue->data = NULL;
    queue->capacity = 0;
    queue->bytes_avaible = 0;
    queue->head = 0;
    queue->tail = 0;
}
