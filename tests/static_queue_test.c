#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../queues/static_queue.h"
#include "tests.h"

void static_queue_test()
{
    printf("Running static queue tests...\n");

    static_queue_test_init();
    printf("test init passed!\n");

    static_queue_test_enqueue_dequeue_int();
    printf("test enqueue/dequeue int passed!\n");

    static_queue_test_fifo();
    printf("test fifo passed!\n");

    static_queue_test_peek();
    printf("test peek passed!\n");

    static_queue_test_multiple_types();
    printf("test multiple types passed!\n");

    static_queue_test_wraparound();
    printf("test wraparound passed!\n");

    static_queue_test_overflow();
    printf("test overflow passed!\n");

    static_queue_test_underflow();
    printf("test underflow passed!\n");

    printf("\nAll static queue tests passed!\n");
}

void static_queue_test_init()
{
    static_queue q;
    assert(static_queue_init(&q, 100) == 1);
    assert(static_queue_is_empty(&q));
    static_queue_destroy(&q);
}

void static_queue_test_enqueue_dequeue_int()
{
    static_queue q;
    static_queue_init(&q, 100);

    int x = 42, y = 0;

    assert(static_queue_enqueue(&q, &x, sizeof(int)) == 1);
    assert(!static_queue_is_empty(&q));

    assert(static_queue_dequeue(&q, &y, sizeof(int)) == 1);
    assert(y == 42);

    assert(static_queue_is_empty(&q));

    static_queue_destroy(&q);
}

void static_queue_test_fifo()
{
    static_queue q;
    static_queue_init(&q, 100);

    int a = 1, b = 2, c = 3;
    int out;

    static_queue_enqueue(&q, &a, sizeof(int));
    static_queue_enqueue(&q, &b, sizeof(int));
    static_queue_enqueue(&q, &c, sizeof(int));

    static_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 1);

    static_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 2);

    static_queue_dequeue(&q, &out, sizeof(int));
    assert(out == 3);

    static_queue_destroy(&q);
}

void static_queue_test_peek()
{
    static_queue q;
    static_queue_init(&q, 100);

    int x = 99, y = 0;

    static_queue_enqueue(&q, &x, sizeof(int));

    assert(static_queue_peek(&q, &y, sizeof(int)) == 1);
    assert(y == 99);

    assert(!static_queue_is_empty(&q));

    static_queue_destroy(&q);
}

void static_queue_test_multiple_types()
{
    static_queue q;
    static_queue_init(&q, 200);

    int a = 10;
    double b = 3.14;
    char str[] = "hola";

    int outA;
    double outB;
    char outStr[10];

    static_queue_enqueue(&q, &a, sizeof(a));
    static_queue_enqueue(&q, &b, sizeof(b));
    static_queue_enqueue(&q, str, sizeof(str));

    static_queue_dequeue(&q, &outA, sizeof(outA));
    assert(outA == 10);

    static_queue_dequeue(&q, &outB, sizeof(outB));
    assert(outB == 3.14);

    static_queue_dequeue(&q, outStr, sizeof(outStr));
    assert(strcmp(outStr, "hola") == 0);

    static_queue_destroy(&q);
}

void static_queue_test_wraparound()
{
    static_queue q;
    static_queue_init(&q, 64);

    int i, out;

    for(i = 0; i < 3; i++)
        assert(static_queue_enqueue(&q, &i, sizeof(int)) == 1);

    for(i = 0; i < 2; i++)
        assert(static_queue_dequeue(&q, &out, sizeof(int)) == 1);

    for(i = 3; i < 7; i++)
        assert(static_queue_enqueue(&q, &i, sizeof(int)) == 1);

    int expected[] = {2,3,4,5,6};

    for(i = 0; i < 5; i++)
    {
        assert(static_queue_dequeue(&q, &out, sizeof(int)) == 1);
        assert(out == expected[i]);
    }

    static_queue_destroy(&q);
}

void static_queue_test_overflow()
{
    static_queue q;
    static_queue_init(&q, 16);

    int x = 1;

    while(static_queue_enqueue(&q, &x, sizeof(int)));

    assert(static_queue_is_full(&q, sizeof(int)));

    static_queue_destroy(&q);
}

void static_queue_test_underflow()
{
    static_queue q;
    static_queue_init(&q, 100);

    int x;

    assert(static_queue_dequeue(&q, &x, sizeof(int)) == 0);
    assert(static_queue_peek(&q, &x, sizeof(int)) == 0);

    static_queue_destroy(&q);
}
