#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../stacks/static_stack.h"

#define STACK_SIZE 64

static void test_basic_push_pop(void)
{
    static_stack s;
    assert(static_stack_init(&s, STACK_SIZE));

    int x = 42;
    int out = 0;

    assert(static_stack_push(&s, &x, sizeof(x)));
    assert(static_stack_pop(&s, &out, sizeof(out)));
    assert(out == 42);
    assert(static_stack_is_empty(&s));

    static_stack_destroy(&s);
    printf("test_basic_push_pop passed\n");
}

static void test_multiple_push_pop(void)
{
    static_stack s;
    assert(static_stack_init(&s, STACK_SIZE));

    int a = 1, b = 2, c = 3;
    int out;

    assert(static_stack_push(&s, &a, sizeof(a)));
    assert(static_stack_push(&s, &b, sizeof(b)));
    assert(static_stack_push(&s, &c, sizeof(c)));

    assert(static_stack_pop(&s, &out, sizeof(out)));
    assert(out == 3);

    assert(static_stack_pop(&s, &out, sizeof(out)));
    assert(out == 2);

    assert(static_stack_pop(&s, &out, sizeof(out)));
    assert(out == 1);

    assert(static_stack_is_empty(&s));

    static_stack_destroy(&s);
    printf("test_multiple_push_pop passed\n");
}

static void test_peek(void)
{
    static_stack s;
    assert(static_stack_init(&s, STACK_SIZE));

    int x = 99;
    int out = 0;

    assert(static_stack_push(&s, &x, sizeof(x)));
    assert(static_stack_peek(&s, &out, sizeof(out)));
    assert(out == 99);

    // peek no debe modificar el stack
    assert(!static_stack_is_empty(&s));

    static_stack_destroy(&s);
    printf("test_peek passed\n");
}

static void test_overflow(void)
{
    static_stack s;
    assert(static_stack_init(&s, 16)); // chico a propósito

    char big[32] = {0};

    // debería fallar
    assert(!static_stack_push(&s, big, sizeof(big)));

    static_stack_destroy(&s);
    printf("test_overflow passed\n");
}

static void test_underflow(void)
{
    static_stack s;
    assert(static_stack_init(&s, STACK_SIZE));

    int out;

    // pop vacío debe fallar
    assert(!static_stack_pop(&s, &out, sizeof(out)));
    assert(!static_stack_peek(&s, &out, sizeof(out)));

    static_stack_destroy(&s);
    printf("test_underflow passed\n");
}

static void test_partial_copy(void)
{
    static_stack s;
    assert(static_stack_init(&s, STACK_SIZE));

    long long big = 0x1122334455667788LL;
    int small;

    assert(static_stack_push(&s, &big, sizeof(big)));
    assert(static_stack_pop(&s, &small, sizeof(small)));

    // solo chequeamos que no crashee y copie algo
    printf("partial copy result: 0x%x\n", small);

    static_stack_destroy(&s);
    printf("test_partial_copy passed\n");
}

int main(void)
{
    test_basic_push_pop();
    test_multiple_push_pop();
    test_peek();
    test_overflow();
    test_underflow();
    test_partial_copy();

    printf("\nALL TESTS PASSED\n");
    return 0;
}
