#include <stdlib.h>
#include <string.h>

#include "singly_linked_list.h"

void singly_linked_list_init(singly_linked_list *list)
{
    if(!list)
        return;
    list->head =NULL;
    list->tail = NULL;
}

int singly_linked_list_insert_at_first(singly_linked_list *list, const void *data, size_t dataSize)
{
    if(!list || !data || !dataSize)
        return 0;
    singly_linked_list_node *new = malloc(sizeof(singly_linked_list_node));
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
    new->next = list->head;
    if(!list->head)
        list->tail = new;
    list->head = new;
    return 1;
}

int singly_linked_list_insert_at_end(singly_linked_list *list, const void *data, size_t dataSize)
{
    if(!list || !data || !dataSize)
        return 0;
    singly_linked_list_node *new = malloc(sizeof(singly_linked_list_node));
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
    if(!list->head)
        list->head = new;
    else
        list->tail->next = new;
    list->tail = new;
    return 1;
}

int singly_linked_list_insert_at_position(singly_linked_list *list, const void *data, size_t dataSize, size_t position)
{
    if(!list || !data || !dataSize)
        return 0;
    if(!list->head)
    {
        return position == 0 ? singly_linked_list_insert_at_first(list,data,dataSize) : 0;
    }
    if(position == 0)
        return singly_linked_list_insert_at_first(list,data,dataSize);
    singly_linked_list_node *prevNode = list->head;
    while(prevNode->next && position > 1)
    {
        prevNode = prevNode->next;
        position --;
    }
    if(position > 1)
        return 0;

    singly_linked_list_node *new = malloc(sizeof(singly_linked_list_node));
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
    new->next = prevNode->next;
    prevNode->next = new;
    if(!new->next)
        list->tail = new;
    return 1;
}

int singly_linked_list_peek_at_first(const singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));
    return 1;
}

int singly_linked_list_peek_at_end(const singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail->data, MIN(list->tail->dataSize, dataSize));
    return 1;
}

int singly_linked_list_peek_at_position(const singly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    singly_linked_list_node *tempNode = list->head;
    while(tempNode->next && position)
    {
        tempNode = tempNode->next;
        position --;
    }
    if(position != 0)
        return 0;
    memcpy(data, tempNode->data, MIN(tempNode->dataSize, dataSize));
    return 1;
}

int singly_linked_list_delete_at_first(singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));

    singly_linked_list_node *tempNode = list->head;
    list->head = list->head->next;
    if(!list->head)
        list->tail = NULL;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int singly_linked_list_delete_at_end(singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail->data, MIN(list->tail->dataSize, dataSize));

    singly_linked_list_node *tempNode = list->head;
    if(tempNode == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        while(tempNode->next != list->tail)
            tempNode = tempNode->next;
        list->tail = tempNode;
        tempNode = tempNode->next;
        list->tail->next = NULL;
    }
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int singly_linked_list_delete_at_position(singly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !list->head || !data || !dataSize)
        return 0;
    if(position == 0)
    {
        if(singly_linked_list_delete_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    singly_linked_list_node *prevNode = list->head;
    while(prevNode->next && position > 1)
    {
        prevNode = prevNode->next;
        position --;
    }
    if(position > 1)
        return 0;
    singly_linked_list_node *tempNode = prevNode->next;
    prevNode->next = tempNode->next;

    if(tempNode == list->tail)
        list->tail = prevNode;

    free(tempNode->data);
    free(tempNode);
    return 1;
}

int singly_linked_list_is_empty(const singly_linked_list *list)
{
    return !list || !list->head;
}

void singly_linked_list_destroy(singly_linked_list *list)
{
    if(!list)
        return;
    while(list->head)
    {
        singly_linked_list_node *tempNode = list->head;
        list->head = list->head->next;
        free(tempNode->data);
        free(tempNode);
    }
    list->tail = NULL;
}
