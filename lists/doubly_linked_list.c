#include <stdlib.h>
#include <string.h>

#include "doubly_linked_list.h"

void doubly_linked_list_init(doubly_linked_list *list)
{
    if(!list)
        return;
    list->head = NULL;
    list->tail = NULL;
}

int doubly_linked_list_insert_at_first(doubly_linked_list *list, const void *data, size_t dataSize)
{
    if(!list || !data || !dataSize)
        return 0;
    doubly_linked_list_node *new = malloc(sizeof(doubly_linked_list_node));
    if(!new)
        return 0;
    new->data = malloc(dataSize);
    if(!new->data)
    {
        free(new);
        return 0;
    }
    memcpy(new->data, data, dataSize);
    new->dataSize = dataSize;
    new->previous = NULL;
    new->next = list->head;
    if(list->head)
        list->head->previous = new;
    else
        list->tail = new;
    list->head = new;
    return 1;
}

int doubly_linked_list_insert_at_end(doubly_linked_list *list, const void *data, size_t dataSize)
{
    if(!list || !data || !dataSize)
        return 0;
    doubly_linked_list_node *new = malloc(sizeof(doubly_linked_list_node));
    if(!new)
        return 0;
    new->data = malloc(dataSize);
    if(!new->data)
    {
        free(new);
        return 0;
    }
    memcpy(new->data, data, dataSize);
    new->dataSize = dataSize;
    new->next = NULL;
    new->previous = list->tail;
    if(list->head)
        list->tail->next = new;
    else
        list->head = new;
    list->tail = new;
    return 1;
}

int doubly_linked_list_insert_at_position(doubly_linked_list *list, const void *data, size_t dataSize, size_t position)
{
    if(!list || !data || !dataSize)
        return 0;
    if(!list->head)
        return position == 0 ? doubly_linked_list_insert_at_first(list,data,dataSize) : 0;
    if(position == 0)
        return doubly_linked_list_insert_at_first(list,data,dataSize);

    doubly_linked_list_node *tempNode = list->head;
    while(tempNode->next && position > 1)
    {
        tempNode = tempNode->next;
        position --;
    }
    if(position > 1)
        return 0;

    doubly_linked_list_node *new = malloc(sizeof(doubly_linked_list_node));
    if(!new)
        return 0;
    new->data = malloc(dataSize);
    if(!new->data)
    {
        free(new);
        return 0;
    }
    memcpy(new->data, data, dataSize);
    new->dataSize = dataSize;
    if(tempNode->next)
        tempNode->next->previous = new;
    else
        list->tail = new;
    new->next = tempNode->next;
    new->previous = tempNode;
    tempNode->next = new;
    return 1;
}

int doubly_linked_list_peek_at_first(const doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_peek_at_end(const doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail->data, MIN(list->tail->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_peek_at_position(const doubly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    if(position == 0)
        return doubly_linked_list_peek_at_first(list,data,dataSize);
    doubly_linked_list_node *tempNode = list->head;
    while(tempNode->next && position)
    {
        tempNode = tempNode->next;
        position--;
    }
    if(position != 0)
        return 0;
    memcpy(data, tempNode->data, MIN(tempNode->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_delete_at_first(doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));
    doubly_linked_list_node *tempNode = list->head;
    list->head = list->head->next;
    if(list->head)
        list->head->previous = NULL;
    else
        list->tail = NULL;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int doubly_linked_list_delete_at_end(doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail->data, MIN(list->tail->dataSize, dataSize));
    doubly_linked_list_node *tempNode = list->tail;
    list->tail = list->tail->previous;
    if(list->tail)
        list->tail->next = NULL;
    else
        list->head = NULL;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int doubly_linked_list_delete_at_position(doubly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    if(position == 0)
        return doubly_linked_list_delete_at_first(list,data,dataSize);
    doubly_linked_list_node *tempNode = list->head;
    while(tempNode->next && position)
    {
        tempNode = tempNode->next;
        position --;
    }

    if(position != 0)
        return 0;
    memcpy(data, tempNode->data, MIN(tempNode->dataSize, dataSize));
    if(tempNode->next)
        tempNode->next->previous = tempNode->previous;
    else
        list->tail = tempNode->previous;
    tempNode->previous->next = tempNode->next;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int doubly_linked_list_is_empty(const doubly_linked_list *list)
{
    return !list || !list->head;
}

void doubly_linked_list_destroy(doubly_linked_list *list)
{
    while(list->head)
    {
        doubly_linked_list_node *tempNode = list->head;
        list->head = tempNode->next;
        free(tempNode->data);
        free(tempNode);
    }
    list->tail = NULL;
}
