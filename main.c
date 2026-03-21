#include <stdio.h>
#include "tests/tests.h"

int main()
{
    printf("Running all tests...\n");
    printf("\n-----\n\n");
    static_stack_test();
    printf("\n-----\n\n");
    dynamic_stack_test();
    printf("\n-----\n\n");
    static_queue_test();
    printf("\n-----\n\n");
    dynamic_queue_test();
    printf("\n-----\n\n");
    singly_linked_list_test();
    printf("\n-----\n\n");
    doubly_linked_list_test();
    printf("\n-----\n\n");
    bst_test();
    printf("\n-----\n\n");
    hash_table_test();
    printf("\n-----\n\n");
    return 0;
}
