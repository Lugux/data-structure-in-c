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
    list->tail->next = new;
    if(!list->head)
        list->head = new;
    list->tail = new;
    return 1;
}

int singly_linked_list_insert_at_position(singly_linked_list *list, const void *data, size_t dataSize, size_t position)
{
    if(!list || !data || !dataSize)
        return 0;
    if(position == 0)
    {
        if(singly_linked_list_insert_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    singly_linked_list_node *prevNode, *posNode = list->head;
    while(posNode->next && position)
    {
        prevNode = posNode;
        posNode = posNode->next;
        position --;
    }
    if(position == 1)
    {
        if(singly_linked_list_insert_at_end(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    if(position != 0)
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
    new->next = posNode;
    prevNode->next = new;
    return 1;
}

int singly_linked_list_peek_at_first(const singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));
    return 1;
}

int singly_linked_list_peek_at_end(const singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->tail->data, MIN(list->tail->dataSize, dataSize));
    return 1;
}

int singly_linked_list_peek_at_position(const singly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list->head || !data || !dataSize)
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
    if(!list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));

    singly_linked_list_node *temp = list->head;
    list->head = list->head->next;
    free(temp->data);
    free(temp);
    return 1;
}

int singly_linked_list_delete_at_end(singly_linked_list *list, void *data, size_t dataSize)
{
    if(!list->head || !data || !dataSize)
        return 0;
    memcpy(data, list->head->data, MIN(list->head->dataSize, dataSize));

    singly_linked_list_node *temp = list->head;
    if(temp == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        while(temp->next != list->tail)
            temp = temp->next;
        list->tail = temp;
        temp = temp->next;
        list->tail->next = NULL;
    }
    free(temp->data);
    free(temp);
    return 1;
}

int singly_linked_list_delete_at_position(singly_linked_list *list, void *data, size_t dataSize, size_t position)
{
    if(!list || !data || !dataSize)
        return 0;
    if(position == 0)
    {
        if(singly_linked_list_delete_at_first(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    singly_linked_list_node *prevNode, *tempNode = list->head;
    while(tempNode->next && position)
    {
        prevNode = tempNode;
        tempNode = tempNode->next;
        position --;
    }
    if(position == 1)
    {
        if(singly_linked_list_delete_at_end(list,data,dataSize))
            return 1;
        else
            return 0;
    }
    if(position != 0)
        return 0;
    prevNode->next = tempNode->next;
    free(tempNode->data);
    free(tempNode);
    return 1;
}

int singly_linked_list_is_empty(const singly_linked_list *list)
{
    return list->head == NULL;
}

void singly_linked_list_destroy(singly_linked_list *list)
{
    while(list->head)
    {
        singly_linked_list_node *temp = list->head;
        list->head = list->head->next;
        free(temp->data);
        free(temp);
    }
    list->tail = NULL;
}
