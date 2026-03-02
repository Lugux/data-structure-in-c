#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct doubly_linked_list_node
{
    void *data;
    size_t dataSize;
    struct doubly_linked_list_node *next;
    struct doubly_linked_list_node *previus;
}doubly_linked_list_node;

typedef struct
{
    doubly_linked_list_node *head;
    doubly_linked_list_node *tail;
}doubly_linked_list;

void doubly_linked_list_init(doubly_linked_list *list);
int doubly_linked_list_insert_at_first(doubly_linked_list *list, const void *data, size_t dataSize);
int doubly_linked_list_insert_at_end(doubly_linked_list *list, const void *data, size_t dataSize);
int doubly_linked_list_insert_at_position(doubly_linked_list *list, const void *data, size_t dataSize, size_t position);
int doubly_linked_list_peek_at_first(const doubly_linked_list *list, void *data, size_t dataSize);
int doubly_linked_list_peek_at_end(const doubly_linked_list *list, void *data, size_t dataSize);
int doubly_linked_list_peek_at_position(const doubly_linked_list *list, void *data, size_t dataSize, size_t position);
int doubly_linked_list_delete_at_first(doubly_linked_list *list, void *data, size_t dataSize);
int doubly_linked_list_delete_at_end(doubly_linked_list *list, void *data, size_t dataSize);
int doubly_linked_list_delete_at_position(doubly_linked_list *list, void *data, size_t dataSize, size_t position);
int doubly_linked_list_is_empty(const doubly_linked_list *list);
void doubly_linked_list_destroy(doubly_linked_list *list);


#endif // DOUBLY_LINKED_LIST_H
