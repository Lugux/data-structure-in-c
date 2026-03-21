# Data Structures in C

## Overview

This repository contains a complete implementation of fundamental data structures in C, designed with a focus on:

* Generic data handling (void pointers)
* Memory safety and dynamic allocation
* Modular design
* Thorough testing

All structures are implemented from scratch without external dependencies and include dedicated test suites to validate correctness and edge cases.

---

## Implemented Data Structures

### Stacks

* Static Stack (array-based, contiguous memory)
* Dynamic Stack (linked list-based)

### Queues

* Static Queue (circular buffer with variable-sized elements)
* Dynamic Queue (linked list-based)

### Linked Lists

* Singly Linked List
* Doubly Linked List

### Trees

* Binary Search Tree (BST)

  * Insert, search, delete
  * Traversals (inorder, preorder, postorder)
  * Min / Max
  * Height, size, leaf count
  * Balance check
  * Clone

### Hash Table

* Separate chaining (linked lists)
* Dynamic resizing (rehashing)
* Insert, update, delete, upsert, get, contains

---

## Features

* Generic storage using `void*`
* Deep copy of stored elements
* Memory-safe operations (malloc, free, realloc)
* Collision handling in hash table
* Circular buffer implementation for static queue
* Full test coverage for each data structure
* Clean and modular architecture

---

## Project Structure

```
/common        -> shared macros and utilities
/stacks        -> static and dynamic stacks
/queues        -> static and dynamic queues
/lists         -> singly and doubly linked lists
/trees         -> binary search tree
/hash          -> hash table implementation
/tests         -> test suite for all structures
main.c         -> test runner
```

---

## How to Compile

Using GCC:

```
gcc main.c tests/*.c stacks/*.c queues/*.c lists/*.c trees/*.c hash/*.c -o program
```

Then run:

```
./program
```

---

## Running Tests

All data structures include dedicated test functions.

The main file runs all tests sequentially:

* Stack tests
* Queue tests
* Linked list tests
* Binary tree tests
* Hash table tests

Each test validates correctness, edge cases, and memory behavior using assertions.

---

## Design Decisions

* All structures are implemented generically using `void*` and explicit size tracking.
* Memory ownership is handled internally (deep copies on insert).
* Hash table uses separate chaining for collision resolution.
* Static queue supports variable-sized elements using a circular buffer.
* Binary Search Tree does not allow duplicate elements.

---

## Future Improvements (Coming Soon)

* Interactive CLI menu to manually test and explore structures
* Additional data structures and their tests

---

## Purpose

This project was developed as a learning and portfolio exercise to demonstrate:

* Strong understanding of data structures
* Low-level memory management in C
* Ability to design reusable and generic components
* Testing and validation practices

---

## License

This project is open-source and available for educational and personal use.

