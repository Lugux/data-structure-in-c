#include <stdlib.h>
#include <string.h>

#include "dynamic_queue.h"

void dynamic_queue_init(dynamic_queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

int dynamic_queue_enqueue(dynamic_queue *queue, const void *data, size_t dataSize)
{
    if(!queue || !data || !dataSize)
        return 0;
    dynamic_queue_node *new_node = malloc(sizeof(dynamic_queue_node));
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
    new_node->next = NULL;

    if(!queue->head)
        queue->head = new_node;
    else
        queue->tail->next = new_node;
    queue->tail = new_node;
    return 1;
}

int dynamic_queue_peek(const dynamic_queue *queue,void *data, size_t dataSize)
{
    if(!queue || !queue->head || !data || !dataSize)
        return 0;
    memcpy(data, queue->head->data, MIN(queue->head->dataSize, dataSize));
    return 1;
}

int dynamic_queue_dequeue(dynamic_queue *queue, void *data, size_t dataSize)
{
    if(!queue || !queue->head || !data || !dataSize)
        return 0;
    memcpy(data, queue->head->data, MIN(queue->head->dataSize, dataSize));

    dynamic_queue_node *temp = queue->head;
    queue->head = queue->head->next;
    if(!queue->head)
        queue->tail = NULL;
    free(temp->data);
    free(temp);
    return 1;
}

int dynamic_queue_is_empty(const dynamic_queue *queue)
{
    return !queue || queue->head == NULL;
}

void dynamic_queue_destroy(dynamic_queue *queue)
{
    while(queue->head)
    {
        dynamic_queue_node *temp = queue->head;
        queue->head = queue->head->next;
        free(temp->data);
        free(temp);
    }
    queue->tail = NULL;
}
