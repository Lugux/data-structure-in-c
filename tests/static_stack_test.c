#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tests.h"
#include "../stacks/static_stack.h"

void static_stack_test()
{
    printf("Running static stack tests...\n");
    static_stack_test_init();
    printf("test init passed!\n");
    static_stack_test_push_pop_int();
    printf("test push and pop passed!\n");
    static_stack_test_lifo();
    printf("test lifo passed!\n");
    static_stack_test_peek();
    printf("test peek passed!\n");
    static_stack_test_multiple_types();
    printf("test multiple types passed!\n");
    static_stack_test_overflow();
    printf("test overflow passed!\n");
    static_stack_test_underflow();
    printf("test underflow passed!\n");

    printf("\nAll static stack tests passed!\n");
}

void static_stack_test_init()
{
    static_stack s;
    assert(static_stack_init(&s, 100) == 1);
    assert(s.top == 0);
    assert(s.capacity == 100);
    static_stack_destroy(&s);
}

void static_stack_test_push_pop_int()
{
    static_stack s;
    static_stack_init(&s, 100);

    int x = 42;
    int y = 0;

    assert(static_stack_push(&s, &x, sizeof(int)) == 1);
    assert(!static_stack_is_empty(&s));

    assert(static_stack_pop(&s, &y, sizeof(int)) == 1);
    assert(y == 42);

    assert(static_stack_is_empty(&s));

    static_stack_destroy(&s);
}

void static_stack_test_lifo()
{
    static_stack s;
    static_stack_init(&s, 100);

    int a = 1, b = 2, c = 3;
    int out;

    static_stack_push(&s, &a, sizeof(int));
    static_stack_push(&s, &b, sizeof(int));
    static_stack_push(&s, &c, sizeof(int));

    static_stack_pop(&s, &out, sizeof(int));
    assert(out == 3);

    static_stack_pop(&s, &out, sizeof(int));
    assert(out == 2);

    static_stack_pop(&s, &out, sizeof(int));
    assert(out == 1);

    static_stack_destroy(&s);
}

void static_stack_test_peek()
{
    static_stack s;
    static_stack_init(&s, 100);

    int x = 99;
    int y = 0;

    static_stack_push(&s, &x, sizeof(int));

    assert(static_stack_peek(&s, &y, sizeof(int)) == 1);
    assert(y == 99);

    assert(!static_stack_is_empty(&s));

    static_stack_destroy(&s);
}

void static_stack_test_multiple_types()
{
    static_stack s;
    static_stack_init(&s, 200);

    int a = 10;
    double b = 3.14;
    char str[] = "hola";

    int outA;
    double outB;
    char outStr[10];

    static_stack_push(&s, &a, sizeof(a));
    static_stack_push(&s, &b, sizeof(b));
    static_stack_push(&s, str, sizeof(str));

    static_stack_pop(&s, outStr, sizeof(outStr));
    assert(strcmp(outStr, "hola") == 0);

    static_stack_pop(&s, &outB, sizeof(outB));
    assert(outB == 3.14);

    static_stack_pop(&s, &outA, sizeof(outA));
    assert(outA == 10);

    static_stack_destroy(&s);
}

void static_stack_test_overflow()
{
    static_stack s;
    static_stack_init(&s, 16);

    int x = 123;

    assert(static_stack_push(&s, &x, sizeof(int)) == 1);

    int result = static_stack_push(&s, &x, sizeof(int));
    assert(result == 0);

    static_stack_destroy(&s);
}

void static_stack_test_underflow()
{
    static_stack s;
    static_stack_init(&s, 100);

    int x;
    assert(static_stack_pop(&s, &x, sizeof(int)) == 0);

    static_stack_destroy(&s);
}
