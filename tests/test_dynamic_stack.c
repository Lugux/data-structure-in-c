#include <stdio.h>
#include <assert.h>
#include "../stacks/dynamic_stack.h"

void test_init_and_empty()
{
    DynamicStack stack;
    dynamic_stack_init(&stack);

    assert(dynamic_stack_is_empty(&stack));
}

void test_push_and_peek()
{
    DynamicStack stack;
    dynamic_stack_init(&stack);

    int value = 50;
    int out = 0;

    assert(dynamic_stack_push(&stack, &value, sizeof(value)));
    assert(!dynamic_stack_is_empty(&stack));

    assert(!dynamic_stack_push(&stack, NULL, sizeof(value)));
    assert(!dynamic_stack_push(&stack, &value, 0));


    assert(dynamic_stack_peek(&stack, &out, sizeof(out)));
    assert(out == 50);

    assert(!dynamic_stack_peek(&stack, &out, 0));
    assert(out == 50);

    dynamic_stack_destroy(&stack);
}

void test_push_and_pop()
{
    DynamicStack stack;
    dynamic_stack_init(&stack);

    int v1 = 10, v2 = 20;
    int out;

    assert(dynamic_stack_push(&stack, &v1, sizeof(v1)));
    assert(dynamic_stack_push(&stack, &v2, sizeof(v2)));

    assert(dynamic_stack_pop(&stack, &out, sizeof(out)));
    assert(out == 20); // LIFO

    assert(!dynamic_stack_pop(&stack, NULL, sizeof(out)));

    assert(dynamic_stack_pop(&stack, &out, sizeof(out)));
    assert(out == 10);

    assert(!dynamic_stack_pop(&stack, &out, 0));
    assert(!dynamic_stack_pop(&stack, &out, sizeof(out)));

    assert(dynamic_stack_is_empty(&stack));

    dynamic_stack_destroy(&stack);
}

void test_push_and_pop_loop()
{
    DynamicStack stack;
    dynamic_stack_init(&stack);
    int i, temp;

    for(i = 0; i < 100; i++)
    {
        temp = i;
        assert(dynamic_stack_push(&stack, &temp, sizeof(temp)));
    }
    for(i = 99; i >= 0; i--)
    {
        assert(dynamic_stack_pop(&stack,&temp,sizeof(temp)));
        assert(temp == i);
    }
    assert(dynamic_stack_is_empty(&stack));

    dynamic_stack_destroy(&stack);
}

int main()
{
    printf("Running dynamic stack tests...\n\n");

    test_init_and_empty();
    printf("test_init_and_empty passed!\n");
    test_push_and_peek();
    printf("test_push_and_peek passed!\n");
    test_push_and_pop();
    printf("test_push_and_pop passed!\n");
    test_push_and_pop_loop();
    printf("test_push_and_pop_loop passed!\n");


    printf("\nAll tests passed!\n");
    return 0;
}
