#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct singly_linked_list_node
{
    void* data;
    size_t dataSize;
    struct singly_linked_list_node *next;
}singly_linked_list_node;

typedef struct
{
    singly_linked_list_node *head;
    singly_linked_list_node *tail;
}singly_linked_list;

void singly_linked_list_init(singly_linked_list *list);
int singly_linked_list_insert_at_first(singly_linked_list *list, const void *data, size_t dataSize);
int singly_linked_list_insert_at_end(singly_linked_list *list, const void *data, size_t dataSize);
int singly_linked_list_insert_at_position(singly_linked_list *list, const void *data, size_t dataSize, size_t position);
int singly_linked_list_peek_at_first(const singly_linked_list *list, void *data, size_t dataSize);
int singly_linked_list_peek_at_end(const singly_linked_list *list, void *data, size_t dataSize);
int singly_linked_list_peek_at_position(const singly_linked_list *list, void *data, size_t dataSize, size_t position);
int singly_linked_list_delete_at_first(singly_linked_list *list, void *data, size_t dataSize);
int singly_linked_list_delete_at_end(singly_linked_list *list, void *data, size_t dataSize);
int singly_linked_list_delete_at_position(singly_linked_list *list, void *data, size_t dataSize, size_t position);
int singly_linked_list_is_empty(const singly_linked_list *list);
void singly_linked_list_destroy(singly_linked_list *list);

#endif // SINGLY_LINKED_LIST_H
