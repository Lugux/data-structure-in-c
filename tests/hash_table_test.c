#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../hash/hash_table.h"
#include "tests.h"

void hash_table_test()
{
    printf("Running hash table tests...\n");

    hash_test_insert_get();
    printf("test insert/get passed!\n");

    hash_test_contains();
    printf("test contains passed!\n");

    hash_test_update();
    printf("test update passed!\n");

    hash_test_upsert();
    printf("test upsert passed!\n");

    hash_test_delete();
    printf("test delete passed!\n");

    hash_test_collision();
    printf("test collision passed!\n");

    hash_test_resize();
    printf("test resize passed!\n");

    hash_test_many_elements();
    printf("test many elements passed!\n");

    printf("\nAll hash table tests passed!\n");
}

void hash_test_insert_get()
{
    hash_table ht;
    hash_init(&ht, 8);

    int value = 42;
    int out;

    assert(hash_insert(&ht, "key1", &value, sizeof(int)) == 1);
    assert(hash_get(&ht, "key1", &out, sizeof(int)) == 1);
    assert(out == 42);

    hash_destroy(&ht);
}

void hash_test_contains()
{
    hash_table ht;
    hash_init(&ht, 8);

    int value = 10;

    hash_insert(&ht, "test", &value, sizeof(int));

    assert(hash_contains(&ht, "test") == 1);
    assert(hash_contains(&ht, "nope") == 0);

    hash_destroy(&ht);
}

void hash_test_update()
{
    hash_table ht;
    hash_init(&ht, 8);

    int value = 5;
    int new_value = 99;
    int out;

    hash_insert(&ht, "key", &value, sizeof(int));

    assert(hash_update(&ht, "key", &new_value, sizeof(int)) == 1);
    assert(hash_get(&ht, "key", &out, sizeof(int)) == 1);
    assert(out == 99);

    hash_destroy(&ht);
}

void hash_test_upsert()
{
    hash_table ht;
    hash_init(&ht, 8);

    int v1 = 1, v2 = 2, out;

    // insert
    assert(hash_upsert(&ht, "a", &v1, sizeof(int)) == 1);

    // update
    assert(hash_upsert(&ht, "a", &v2, sizeof(int)) == 1);

    hash_get(&ht, "a", &out, sizeof(int));
    assert(out == 2);

    hash_destroy(&ht);
}

void hash_test_delete()
{
    hash_table ht;
    hash_init(&ht, 8);

    int value = 50;
    int out;

    hash_insert(&ht, "x", &value, sizeof(int));

    assert(hash_delete(&ht, "x", &out, sizeof(int)) == 1);
    assert(out == 50);

    assert(hash_contains(&ht, "x") == 0);
    assert(hash_get(&ht, "x", &out, sizeof(int)) == 0);

    hash_destroy(&ht);
}

void hash_test_collision()
{
    hash_table ht;
    hash_init(&ht, 2);

    int a = 1, b = 2, c = 3;
    int out;

    hash_insert(&ht, "key1", &a, sizeof(int));
    hash_insert(&ht, "key2", &b, sizeof(int));
    hash_insert(&ht, "key3", &c, sizeof(int));

    assert(hash_get(&ht, "key1", &out, sizeof(int)) == 1 && out == 1);
    assert(hash_get(&ht, "key2", &out, sizeof(int)) == 1 && out == 2);
    assert(hash_get(&ht, "key3", &out, sizeof(int)) == 1 && out == 3);

    hash_destroy(&ht);
}

void hash_test_resize()
{
    hash_table ht;
    hash_init(&ht, 4);

    int i;

    for(i = 0; i < 100; i++)
    {
        char key[20];
        sprintf(key, "key%d", i);
        assert(hash_insert(&ht, key, &i, sizeof(int)) == 1);
    }

    for(i = 0; i < 100; i++)
    {
        char key[20];
        int out;
        sprintf(key, "key%d", i);
        assert(hash_get(&ht, key, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    hash_destroy(&ht);
}

void hash_test_many_elements()
{
    hash_table ht;
    hash_init(&ht, 8);

    const int N = 10000;

    for(int i = 0; i < N; i++)
    {
        char key[20];
        sprintf(key, "k%d", i);
        assert(hash_insert(&ht, key, &i, sizeof(int)) == 1);
    }

    for(int i = 0; i < N; i++)
    {
        char key[20];
        int out;
        sprintf(key, "k%d", i);
        assert(hash_get(&ht, key, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    hash_destroy(&ht);
}
