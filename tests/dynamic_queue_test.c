#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../queues/dynamic_queue.h"
#include "tests.h"

void dynamic_queue_test()
{
    printf("Running dynamic queue tests...\n");

    dynamic_queue_test_init();
    printf("test init passed!\n");

    dynamic_queue_test_enqueue_dequeue_int();
    printf("test enqueue/dequeue int passed!\n");

    dynamic_queue_test_fifo();
    printf("test fifo passed!\n");

    dynamic_queue_test_peek();
    printf("test peek passed!\n");

    dynamic_queue_test_multiple_types();
    printf("test multiple types passed!\n");

    dynamic_queue_test_many_elements();
    printf("test many elements passed!\n");

    dynamic_queue_test_underflow();
    printf("test underflow passed!\n");

    printf("\nAll dynamic queue tests passed!\n");
}

void dynamic_queue_test_init()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    assert(dynamic_queue_is_empty(&q));
}

void dynamic_queue_test_enqueue_dequeue_int()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    int x = 42, y = 0;

    assert(dynamic_queue_enqueue(&q, &x, sizeof(int)) == 1);
    assert(!dynamic_queue_is_empty(&q));

    assert(dynamic_queue_dequeue(&q, &y, sizeof(int)) == 1);
    assert(y == 42);

    assert(dynamic_queue_is_empty(&q));
}

void dynamic_queue_test_fifo()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    int a = 1, b = 2, c = 3;
    int out;

    dynamic_queue_enqueue(&q, &a, sizeof(int));
    dynamic_queue_enqueue(&q, &b, sizeof(int));
    dynamic_queue_enqueue(&q, &c, sizeof(int));

    dynamic_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 1);

    dynamic_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 2);

    dynamic_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 3);
}

void dynamic_queue_test_peek()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    int x = 99, y = 0;

    dynamic_queue_enqueue(&q, &x, sizeof(int));

    assert(dynamic_queue_peek(&q, &y, sizeof(int)) == 1);
    assert(y == 99);

    assert(!dynamic_queue_is_empty(&q));
}

void dynamic_queue_test_multiple_types()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    int a = 10;
    double b = 3.14;
    char str[] = "hola";

    int outA;
    double outB;
    char outStr[10];

    dynamic_queue_enqueue(&q, &a, sizeof(a));
    dynamic_queue_enqueue(&q, &b, sizeof(b));
    dynamic_queue_enqueue(&q, str, sizeof(str));

    dynamic_queue_dequeue(&q, &outA, sizeof(outA));
    assert(outA == 10);

    dynamic_queue_dequeue(&q, &outB, sizeof(outB));
    assert(outB == 3.14);

    dynamic_queue_dequeue(&q, outStr, sizeof(outStr));
    assert(strcmp(outStr, "hola") == 0);
}

void dynamic_queue_test_many_elements()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    const int N = 10000;
    int i;

    for(i = 0; i < N; i++)
        assert(dynamic_queue_enqueue(&q, &i, sizeof(int)) == 1);

    for(i = 0; i < N; i++)
    {
        int out = -1;
        assert(dynamic_queue_dequeue(&q, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    assert(dynamic_queue_is_empty(&q));

    dynamic_queue_destroy(&q);
}

void dynamic_queue_test_underflow()
{
    dynamic_queue q;
    dynamic_queue_init(&q);

    int x;

    assert(dynamic_queue_dequeue(&q, &x, sizeof(int)) == 0);
    assert(dynamic_queue_peek(&q, &x, sizeof(int)) == 0);
}
