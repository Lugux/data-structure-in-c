#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

size_t hash_function(const char *key)
{
    size_t hash = 5381;
    int c;
    while((c = *key++))
    {
        hash = hash * 33 + c;
    }
    return hash;
}

int hash_init(hash_table *ht, size_t capacity)
{
    if(!ht || !capacity)
        return 0;

    ht->buckets = calloc(capacity, sizeof(hash_node*));
    if(!ht->buckets)
        return 0;
    ht->capacity = capacity;
    ht->size = 0;
    return 1;
}

int hash_contains(const hash_table *ht, const char *key)
{
    if(!ht || !ht->buckets || !key)
        return 0;

    size_t index = hash_function(key) % ht->capacity;
    if(!ht->buckets[index])
        return 0;
    hash_node *temp_node = ht->buckets[index];
    while(temp_node && strcmp(key, temp_node->key))
        temp_node = temp_node->next;
    if(!temp_node)
        return 0;
    return 1;
}

int hash_insert(hash_table *ht, const char *key, const void *value, size_t size_value)
{
    if(!ht || !ht->buckets || !key || !value || !size_value)
        return 0;

    if((double)ht->size / ht->capacity > 0.75) //load factor
    {
        if(!hash_resize(ht, ht->capacity * 2))
            return 0;
    }

    size_t index = hash_function(key) % ht->capacity;

    hash_node *temp_node = ht->buckets[index];
    while(temp_node && strcmp(temp_node->key, key))
        temp_node = temp_node->next;
    if(temp_node)
        return 0;

    hash_node *new_node = malloc(sizeof(hash_node));
    if(!new_node)
        return 0;
    new_node->key = strdup(key);
    if(!new_node->key)
    {
        free(new_node);
        return 0;
    }
    new_node->value = malloc(size_value);
    if(!new_node->value)
    {
        free(new_node->key);
        free(new_node);
        return 0;
    }
    memcpy(new_node->value, value, size_value);
    new_node->size_value = size_value;

    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->size++;

    return 1;
}

int hash_update(hash_table *ht, const char *key, const void *new_value, size_t new_size_value)
{
    if(!ht || !ht->buckets || !key || !new_value || !new_size_value)
        return 0;

    size_t index = hash_function(key) % ht->capacity;
    if(!ht->buckets[index])
        return 0;
    hash_node *temp_node = ht->buckets[index];
    while(temp_node && strcmp(key, temp_node->key))
        temp_node = temp_node->next;
    if(!temp_node)
        return 0;
    void *temp_ptr = realloc(temp_node->value, new_size_value);
    if(!temp_ptr)
        return 0;
    temp_node->value = temp_ptr;
    temp_node->size_value = new_size_value;
    memcpy(temp_node->value, new_value, new_size_value);
    return 1;
}

int hash_upsert(hash_table *ht, const char *key, const void *value, size_t size_value) //function update or insert
{
    if(hash_contains(ht, key))
        return hash_update(ht, key, value, size_value);
    else
        return hash_insert(ht, key, value, size_value);
}

int hash_get(const hash_table *ht, const char *key, void *value, size_t size_value)
{
    if(!ht || !ht->buckets || !key || !value || !size_value)
        return 0;

    size_t index = hash_function(key) % ht->capacity;

    if(!ht->buckets[index])
        return 0;
    hash_node *temp_node = ht->buckets[index];
    while(temp_node && strcmp(key, temp_node->key))
        temp_node = temp_node->next;
    if(!temp_node)
        return 0;
    memcpy(value, temp_node->value, MIN(size_value, temp_node->size_value));
    return 1;
}

int hash_delete(hash_table *ht, const char *key, void *value, size_t size_value)
{
    if(!ht || !ht->buckets || !key)
        return 0;

    size_t index = hash_function(key) % ht->capacity;

    if(!ht->buckets[index])
        return 0;
    hash_node *temp_node = ht->buckets[index], *previous_node = NULL;
    while(temp_node && strcmp(key, temp_node->key))
    {
        previous_node = temp_node;
        temp_node = temp_node->next;
    }
    if(!temp_node)
        return 0;
    if(previous_node)
        previous_node->next = temp_node->next;
    else
        ht->buckets[index] = temp_node->next;

    if(value && size_value)
        memcpy(value, temp_node->value, MIN(size_value, temp_node->size_value));
    free(temp_node->key);
    free(temp_node->value);
    free(temp_node);
    ht->size--;

    return 1;
}

int hash_destroy(hash_table *ht)
{
    if(!ht || !ht->buckets)
        return 0;

    size_t i;
    for(i = 0; i < ht->capacity; i++)
    {
        if(ht->buckets[i])
        {
            hash_node *node = ht->buckets[i];
            while(node)
            {
                hash_node *temp_node = node;
                node = node->next;
                free(temp_node->key);
                free(temp_node->value);
                free(temp_node);
            }
        }
    }
    free(ht->buckets);
    ht->buckets = NULL;
    ht->capacity = 0;
    ht->size = 0;
    return 1;
}

int hash_resize(hash_table *ht, size_t new_capacity)
{
    if(!ht || !ht->buckets || !new_capacity)
        return 0;

    hash_node **new_buckets = calloc(new_capacity, sizeof(hash_node*));
    if(!new_buckets)
        return 0;

    size_t i;
    for(i = 0; i < ht->capacity; i++)
    {
        if(ht->buckets[i])
        {
            hash_node *node = ht->buckets[i];
            while(node)
            {
                hash_node *next = node->next;
                size_t index = hash_function(node->key) % new_capacity;

                node->next = new_buckets[index];
                new_buckets[index] = node;

                node = next;
            }
        }
    }
    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
    return 1;
}
