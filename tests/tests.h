#ifndef TESTS_H
#define TESTS_H

//static stack tests
void static_stack_test();
void static_stack_test_init();
void static_stack_test_push_pop_int();
void static_stack_test_lifo();
void static_stack_test_peek();
void static_stack_test_multiple_types();
void static_stack_test_overflow();
void static_stack_test_underflow();

//dynamic stack tests
void dynamic_stack_test();
void dynamic_stack_test_init();
void dynamic_stack_test_push_pop_int();
void dynamic_stack_test_lifo();
void dynamic_stack_test_peek();
void dynamic_stack_test_multiple_types();
void dynamic_stack_test_underflow();
void dynamic_stack_test_many_elements();

//static queue tests
void static_queue_test();
void static_queue_test_init();
void static_queue_test_enqueue_dequeue_int();
void static_queue_test_fifo();
void static_queue_test_peek();
void static_queue_test_multiple_types();
void static_queue_test_wraparound();
void static_queue_test_overflow();
void static_queue_test_underflow();

//dynamic queue tests
void dynamic_queue_test();
void dynamic_queue_test_init();
void dynamic_queue_test_enqueue_dequeue_int();
void dynamic_queue_test_fifo();
void dynamic_queue_test_peek();
void dynamic_queue_test_multiple_types();
void dynamic_queue_test_many_elements();
void dynamic_queue_test_underflow();

//singly linked list tests
void singly_linked_list_test();
void singly_linked_list_test_init();
void singly_linked_list_test_insert_first();
void singly_linked_list_test_insert_end();
void singly_linked_list_test_insert_position();
void singly_linked_list_test_peek();
void singly_linked_list_test_delete();
void singly_linked_list_test_many_elements();
void singly_linked_list_test_underflow();

//doubly linked list tests
void doubly_linked_list_test();
void doubly_linked_list_test_init();
void doubly_linked_list_test_insert();
void doubly_linked_list_test_insert_position();
void doubly_linked_list_test_peek();
void doubly_linked_list_test_delete();
void doubly_linked_list_test_bidirectional();
void doubly_linked_list_test_many_elements();

//binary search tree tests
void bst_test();
void bst_test_insert_search();
void bst_test_min_max();
void bst_test_traversals();
void bst_test_remove();
void bst_test_properties();
void bst_test_clone();

//hash table tests
void hash_table_test();
void hash_test_insert_get();
void hash_test_contains();
void hash_test_update();
void hash_test_upsert();
void hash_test_delete();
void hash_test_collision();
void hash_test_resize();
void hash_test_many_elements();

#endif // TESTS_H
