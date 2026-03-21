#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../lists/doubly_linked_list.h"
#include "tests.h"

void doubly_linked_list_test()
{
    printf("Running doubly linked list tests...\n");

    doubly_linked_list_test_init();
    printf("test init passed!\n");

    doubly_linked_list_test_insert();
    printf("test insert passed!\n");

    doubly_linked_list_test_insert_position();
    printf("test insert position passed!\n");

    doubly_linked_list_test_peek();
    printf("test peek passed!\n");

    doubly_linked_list_test_delete();
    printf("test delete passed!\n");

    doubly_linked_list_test_bidirectional();
    printf("test bidirectional passed!\n");

    doubly_linked_list_test_many_elements();
    printf("test many elements passed!\n");

    printf("\nAll doubly linked list tests passed!\n");
}

void doubly_linked_list_test_init()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    assert(doubly_linked_list_is_empty(&list));
}

void doubly_linked_list_test_insert()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    int a = 1, b = 2, c = 3;
    int out;

    doubly_linked_list_insert_at_first(&list, &b, sizeof(int));
    doubly_linked_list_insert_at_first(&list, &a, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &c, sizeof(int));

    doubly_linked_list_peek_at_first(&list, &out, sizeof(int));
    assert(out == 1);

    doubly_linked_list_peek_at_end(&list, &out, sizeof(int));
    assert(out == 3);
}

void doubly_linked_list_test_insert_position()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    int a = 1, b = 2, c = 3, out;

    doubly_linked_list_insert_at_end(&list, &a, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &c, sizeof(int));

    doubly_linked_list_insert_at_position(&list, &b, sizeof(int), 1);

    doubly_linked_list_peek_at_position(&list, &out, sizeof(int), 1);
    assert(out == 2);
}

void doubly_linked_list_test_peek()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    int a = 10, b = 20, c = 30;
    int out;

    doubly_linked_list_insert_at_end(&list, &a, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &b, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &c, sizeof(int));

    doubly_linked_list_peek_at_first(&list, &out, sizeof(int));
    assert(out == 10);

    doubly_linked_list_peek_at_end(&list, &out, sizeof(int));
    assert(out == 30);

    doubly_linked_list_peek_at_position(&list, &out, sizeof(int), 1);
    assert(out == 20);
}

void doubly_linked_list_test_delete()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    int a = 1, b = 2, c = 3;
    int out;

    doubly_linked_list_insert_at_end(&list, &a, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &b, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &c, sizeof(int));

    doubly_linked_list_delete_at_first(&list, &out, sizeof(int));
    assert(out == 1);

    doubly_linked_list_delete_at_end(&list, &out, sizeof(int));
    assert(out == 3);

    doubly_linked_list_delete_at_first(&list, &out, sizeof(int));
    assert(out == 2);

    assert(doubly_linked_list_is_empty(&list));
}

void doubly_linked_list_test_bidirectional()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    int a = 1, b = 2, c = 3;

    doubly_linked_list_insert_at_end(&list, &a, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &b, sizeof(int));
    doubly_linked_list_insert_at_end(&list, &c, sizeof(int));

    doubly_linked_list_node *node = list.tail;

    int expected[] = {3,2,1};
    int i = 0;

    while(node)
    {
        int value;
        memcpy(&value, node->data, sizeof(int));
        assert(value == expected[i++]);
        node = node->previous;
    }
}

void doubly_linked_list_test_many_elements()
{
    doubly_linked_list list;
    doubly_linked_list_init(&list);

    const int N = 10000;
    int i;

    for(i = 0; i < N; i++)
        assert(doubly_linked_list_insert_at_end(&list, &i, sizeof(int)) == 1);

    for(i = 0; i < N; i++)
    {
        int out;
        assert(doubly_linked_list_delete_at_first(&list, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    assert(doubly_linked_list_is_empty(&list));

    doubly_linked_list_destroy(&list);
}

