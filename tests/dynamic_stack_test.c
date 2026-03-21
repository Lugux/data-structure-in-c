#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../stacks/dynamic_stack.h"
#include "tests.h"

void dynamic_stack_test()
{
    printf("Running dynamic stack tests...\n");

    dynamic_stack_test_init();
    printf("test init passed!\n");

    dynamic_stack_test_push_pop_int();
    printf("test push/pop int passed!\n");

    dynamic_stack_test_lifo();
    printf("test lifo passed!\n");

    dynamic_stack_test_peek();
    printf("test peek passed!\n");

    dynamic_stack_test_multiple_types();
    printf("test multiple types passed!\n");

    dynamic_stack_test_underflow();
    printf("test underflow passed!\n");

    dynamic_stack_test_many_elements();
    printf("test many elements passed!\n");

    printf("\nAll dynamic stack tests passed!\n");
}

void dynamic_stack_test_init()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    assert(dynamic_stack_is_empty(&s));
}

void dynamic_stack_test_push_pop_int()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    int x = 42;
    int y = 0;

    assert(dynamic_stack_push(&s, &x, sizeof(int)) == 1);
    assert(!dynamic_stack_is_empty(&s));

    assert(dynamic_stack_pop(&s, &y, sizeof(int)) == 1);
    assert(y == 42);

    assert(dynamic_stack_is_empty(&s));
}

void dynamic_stack_test_lifo()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    int a = 1, b = 2, c = 3;
    int out;

    dynamic_stack_push(&s, &a, sizeof(int));
    dynamic_stack_push(&s, &b, sizeof(int));
    dynamic_stack_push(&s, &c, sizeof(int));

    dynamic_stack_pop(&s, &out, sizeof(int));
    assert(out == 3);

    dynamic_stack_pop(&s, &out, sizeof(int));
    assert(out == 2);

    dynamic_stack_pop(&s, &out, sizeof(int));
    assert(out == 1);

    assert(dynamic_stack_is_empty(&s));
}

void dynamic_stack_test_peek()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    int x = 99;
    int y = 0;

    dynamic_stack_push(&s, &x, sizeof(int));

    assert(dynamic_stack_peek(&s, &y, sizeof(int)) == 1);
    assert(y == 99);

    assert(!dynamic_stack_is_empty(&s));
}

void dynamic_stack_test_multiple_types()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    int a = 10;
    double b = 3.14;
    char str[] = "hola";

    int outA;
    double outB;
    char outStr[10];

    dynamic_stack_push(&s, &a, sizeof(a));
    dynamic_stack_push(&s, &b, sizeof(b));
    dynamic_stack_push(&s, str, sizeof(str));

    dynamic_stack_pop(&s, outStr, sizeof(outStr));
    assert(strcmp(outStr, "hola") == 0);

    dynamic_stack_pop(&s, &outB, sizeof(outB));
    assert(outB == 3.14);

    dynamic_stack_pop(&s, &outA, sizeof(outA));
    assert(outA == 10);
}

void dynamic_stack_test_underflow()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    int x;

    assert(dynamic_stack_pop(&s, &x, sizeof(int)) == 0);
    assert(dynamic_stack_peek(&s, &x, sizeof(int)) == 0);
}

void dynamic_stack_test_many_elements()
{
    DynamicStack s;
    dynamic_stack_init(&s);

    const int N = 1000;
    int i;

    for(i = 0; i < N; i++)
    {
        assert(dynamic_stack_push(&s, &i, sizeof(int)) == 1);
    }

    assert(!dynamic_stack_is_empty(&s));

    for(i = N - 1; i >= 0; i--)
    {
        int out = -1;
        assert(dynamic_stack_pop(&s, &out, sizeof(int)) == 1);
        assert(out == i);
    }

    assert(dynamic_stack_is_empty(&s));

    dynamic_stack_destroy(&s);
}
