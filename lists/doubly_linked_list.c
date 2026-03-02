#include <stdlib.h>
#include <string.h>

#include "doubly_linked_list.h"

void doubly_linked_list_init(doubly_linked_list *list)
{
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
    new->previus = NULL;
    new->next = list->head;
    if(list->head)
        list->head->previus = new;
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
    new->previus = list->tail;
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
    if(position == 0)
    {
        if(doubly_linked_list_insert_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    doubly_linked_list_node *prev, *post = list->head;
    while(post->next && position)
    {
        prev = post;
        post = post->next;
        position --;
    }
    if(position == 1)
    {
        if(doubly_linked_list_insert_at_end(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    if(position != 0)
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
    prev->next = new;
    new->previus = prev;
    post->previus = new;
    new->next = post;
    return 1;
}

int doubly_linked_list_peek_at_first(const doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head, MIN(list->head->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_peek_at_end(const doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail, MIN(list->tail->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_peek_at_position(const doubly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    if(position == 0)
    {
        if(doubly_linked_list_peek_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    doubly_linked_list_node *temp;
    while(temp->next && position)
    {
        temp = temp->next;
        position--;
    }
    if(position == 1)
    {
        if(doubly_linked_list_peek_at_end(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    if(position != 0)
        return 0;
    memcpy(data, temp->data, MIN(temp->dataSize, dataSize));
    return 1;
}

int doubly_linked_list_delete_at_first(doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head, MIN(list->head->dataSize, dataSize));
    doubly_linked_list_node *temp = list->head;
    list->head = list->head->next;
    if(!list->head)
        list->tail = NULL;
    free(temp->data);
    free(temp);
    return 1;
}

int doubly_linked_list_delete_at_end(doubly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail, MIN(list->tail->dataSize, dataSize));
    doubly_linked_list_node *temp = list->tail;
    list->tail = list->tail->previus;
    if(!list->tail)
        list->head = NULL;
    free(temp->data);
    free(temp);
    return 1;
}

int doubly_linked_list_delete_at_position(doubly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    if(position == 0)
    {
        if(doubly_linked_list_delete_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    doubly_linked_list_node *prev, *temp = list->head;
    while(temp->next && position)
    {
        prev = temp;
        temp = temp->next;
        position --;
    }
    if(position == 1)
    {
        if(doubly_linked_list_delete_at_end(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    if(position != 0)
        return 0;
    memcpy(data, temp->data, MIN(temp->dataSize, dataSize));
    prev->next = temp->next;
    temp->next->previus = prev;
    free(temp->data);
    free(temp);
    return 1;
}

int doubly_linked_list_is_empty(const doubly_linked_list *list)
{
    return list->head == NULL;
}

void doubly_linked_list_destroy(doubly_linked_list *list)
{
    while(list->head)
    {
        list->head = list->head->next;
        free(list->head->previus->data);
        free(list->head->previus);
    }
    list->tail = NULL;
}
