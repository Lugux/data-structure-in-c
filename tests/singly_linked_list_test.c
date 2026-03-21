#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../lists/singly_linked_list.h"
#include "tests.h"

void singly_linked_list_test()
{
    printf("Running singly linked list tests...\n");

    singly_linked_list_test_init();
    printf("test init passed!\n");

    singly_linked_list_test_insert_first();
    printf("test insert first passed!\n");

    singly_linked_list_test_insert_end();
    printf("test insert end passed!\n");

    singly_linked_list_test_insert_position();
    printf("test insert position passed!\n");

    singly_linked_list_test_peek();
    printf("test peek passed!\n");

    singly_linked_list_test_delete();
    printf("test delete passed!\n");

    singly_linked_list_test_many_elements();
    printf("test many elements passed!\n");

    singly_linked_list_test_underflow();
    printf("test underflow passed!\n");

    printf("\nAll singly linked list tests passed!\n");
}

void singly_linked_list_test_init()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    assert(singly_linked_list_is_empty(&list));
}

void singly_linked_list_test_insert_first()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int a = 1, b = 2, out;

    singly_linked_list_insert_at_first(&list, &a, sizeof(int));
    singly_linked_list_insert_at_first(&list, &b, sizeof(int));

    singly_linked_list_peek_at_first(&list, &out, sizeof(int));
    assert(out == 2);
}

void singly_linked_list_test_insert_end()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int a = 1, b = 2, out;

    singly_linked_list_insert_at_end(&list, &a, sizeof(int));
    singly_linked_list_insert_at_end(&list, &b, sizeof(int));

    singly_linked_list_peek_at_end(&list, &out, sizeof(int));
    assert(out == 2);
}

void singly_linked_list_test_insert_position()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int a = 1, b = 2, c = 3, out;

    singly_linked_list_insert_at_end(&list, &a, sizeof(int));
    singly_linked_list_insert_at_end(&list, &b, sizeof(int));

    singly_linked_list_insert_at_position(&list, &c, sizeof(int), 1);

    singly_linked_list_peek_at_position(&list, &out, sizeof(int), 1);
    assert(out == 3);
}

void singly_linked_list_test_peek()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int a = 10, b = 20, c = 30;
    int out;

    singly_linked_list_insert_at_end(&list, &a, sizeof(int));
    singly_linked_list_insert_at_end(&list, &b, sizeof(int));
    singly_linked_list_insert_at_end(&list, &c, sizeof(int));

    singly_linked_list_peek_at_first(&list, &out, sizeof(int));
    assert(out == 10);

    singly_linked_list_peek_at_end(&list, &out, sizeof(int));
    assert(out == 30);

    singly_linked_list_peek_at_position(&list, &out, sizeof(int), 1);
    assert(out == 20);
}

void singly_linked_list_test_delete()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int a = 1, b = 2, c = 3;
    int out;

    singly_linked_list_insert_at_end(&list, &a, sizeof(int));
    singly_linked_list_insert_at_end(&list, &b, sizeof(int));
    singly_linked_list_insert_at_end(&list, &c, sizeof(int));

    singly_linked_list_delete_at_first(&list, &out, sizeof(int));
    assert(out == 1);

    singly_linked_list_delete_at_end(&list, &out, sizeof(int));
    assert(out == 3);

    singly_linked_list_delete_at_first(&list, &out, sizeof(int));
    assert(out == 2);

    assert(singly_linked_list_is_empty(&list));
}

void singly_linked_list_test_many_elements()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    const int N = 10000;
    int i;

    for(i = 0; i < N; i++)
        assert(singly_linked_list_insert_at_end(&list, &i, sizeof(int)) == 1);

    for(i = 0; i < N; i++)
    {
        int out;
        assert(singly_linked_list_delete_at_first(&list, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    assert(singly_linked_list_is_empty(&list));

    singly_linked_list_destroy(&list);
}

void singly_linked_list_test_underflow()
{
    singly_linked_list list;
    singly_linked_list_init(&list);

    int out;

    assert(singly_linked_list_delete_at_first(&list, &out, sizeof(int)) == 0);
    assert(singly_linked_list_peek_at_first(&list, &out, sizeof(int)) == 0);
}
