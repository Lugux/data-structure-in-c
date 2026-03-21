#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct hash_node
{
    char *key;
    void *value;
    size_t size_value;
    struct hash_node *next;
}hash_node;

typedef struct
{
    hash_node **buckets;
    size_t capacity;
    size_t size;
}hash_table;

size_t hash_function(const char *key);
int hash_init(hash_table *ht, size_t capacity);
int hash_contains(const hash_table *ht, const char *key);
int hash_insert(hash_table *ht, const char *key, const void *value, size_t size_value);
int hash_update(hash_table *ht, const char *key, const void *new_value, size_t new_size_value);
int hash_upsert(hash_table *ht, const char *key, const void *value, size_t size_value);
int hash_get(const hash_table *ht, const char *key, void *value, size_t size_value);
int hash_delete(hash_table *ht, const char *key, void *value, size_t size_value);
int hash_destroy(hash_table *ht);
int hash_resize(hash_table *ht, size_t new_capacity);

#endif // HASH_TABLE_H
