#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../trees/binary_search_tree.h"
#include "tests.h"

int int_cmp(const void *a, const void *b)
{
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

void bst_test()
{
    printf("Running BST tests...\n");

    bst_test_insert_search();
    printf("test insert/search passed!\n");

    bst_test_min_max();
    printf("test min/max passed!\n");

    bst_test_traversals();
    printf("test traversals passed!\n");

    bst_test_remove();
    printf("test remove passed!\n");

    bst_test_properties();
    printf("test properties passed!\n");

    bst_test_clone();
    printf("test clone passed!\n");

    printf("\nAll BST tests passed!\n");
}

void bst_test_insert_search()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        assert(bst_insert(&tree, &values[i], sizeof(int), int_cmp) == 1);

    for(int i = 0; i < 7; i++)
        assert(bst_search(&tree, &values[i], int_cmp) == 1);

    int x = 10;
    assert(bst_search(&tree, &x, int_cmp) == 0);

    bst_destroy(&tree);
}

void bst_test_min_max()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        bst_insert(&tree, &values[i], sizeof(int), int_cmp);

    int min, max;

    assert(bst_min(&tree, &min, sizeof(int)) == 1);
    assert(min == 2);

    assert(bst_max(&tree, &max, sizeof(int)) == 1);
    assert(max == 8);

    bst_destroy(&tree);
}

static int inorder_result[100];
static int idx;

void collect_inorder(const void *data)
{
    inorder_result[idx++] = *(int*)data;
}

void bst_test_traversals()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        bst_insert(&tree, &values[i], sizeof(int), int_cmp);

    idx = 0;
    bst_inorder(&tree, collect_inorder);

    int expected[] = {2,3,4,5,6,7,8};

    for(int i = 0; i < 7; i++)
        assert(inorder_result[i] == expected[i]);

    bst_destroy(&tree);
}

void bst_test_remove()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        bst_insert(&tree, &values[i], sizeof(int), int_cmp);

    int x;

    x = 2;
    assert(bst_remove(&tree, &x, int_cmp) == 1);
    assert(bst_search(&tree, &x, int_cmp) == 0);

    x = 3;
    assert(bst_remove(&tree, &x, int_cmp) == 1);
    assert(bst_search(&tree, &x, int_cmp) == 0);

    x = 5;
    assert(bst_remove(&tree, &x, int_cmp) == 1);
    assert(bst_search(&tree, &x, int_cmp) == 0);

    bst_destroy(&tree);
}

void bst_test_properties()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        bst_insert(&tree, &values[i], sizeof(int), int_cmp);

    assert(bst_size(&tree) == 7);
    assert(bst_height(&tree) == 3);
    assert(bst_leaf_count(&tree) == 4);
    assert(bst_is_balanced(&tree) == 1);

    bst_destroy(&tree);
}

void bst_test_clone()
{
    bst tree;
    bst_init(&tree);

    int values[] = {5,3,7,2,4,6,8};

    for(int i = 0; i < 7; i++)
        bst_insert(&tree, &values[i], sizeof(int), int_cmp);

    bst clone = bst_clone(&tree);

    for(int i = 0; i < 7; i++)
        assert(bst_search(&clone, &values[i], int_cmp) == 1);

    int x = 2;
    bst_remove(&tree, &x, int_cmp);

    assert(bst_search(&tree, &x, int_cmp) == 0);
    assert(bst_search(&clone, &x, int_cmp) == 1);

    bst_destroy(&tree);
    bst_destroy(&clone);
}
