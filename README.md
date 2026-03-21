# Data Structures in C

This repository contains my implementation of fundamental data structures in C, built from scratch as part of my learning process.

The goal of this project is to deeply understand how these structures work internally, focusing on memory management, efficiency, and clean API design.

## 📦 Implemented Structures

* Static Stack
* Dynamic Stack
* Static Queue
* Dynamic Queue
* Singly Linked List
* Doubly Linked List
* Binary Search Tree (BST)
* Hash Table (with chaining and dynamic resizing)

## 🧠 Key Concepts

Throughout this project, I focused on:

* Manual memory management (`malloc`, `calloc`, `realloc`, `free`)
* Pointer manipulation
* Time and space complexity
* Generic data handling using `void *`
* Collision handling in hash tables (separate chaining)
* Dynamic resizing and rehashing

## 🚧 Work in Progress

* Unit tests for each data structure
* Interactive menu to test all structures from a single program
* Code cleanup and documentation improvements

## 🛠️ Usage Example

```c
hash_table ht;

hash_init(&ht, 16);

int value = 42;
hash_insert(&ht, "example", &value, sizeof(int));

int result;
hash_get(&ht, "example", &result, sizeof(int));

printf("%d\n", result);

hash_destroy(&ht);
```

## 📁 Project Structure

```
/data-structures
│
├── stack/
├── queue/
├── list/
├── tree/
├── hash_table/
├── common/
└── main.c (coming soon)
```

## 🎯 Motivation

This project was built to strengthen my understanding of low-level programming and core computer science concepts.

Instead of using built-in libraries, I implemented everything manually to gain better intuition about how data is stored, accessed, and managed in memory.

## 📌 Notes

This is a learning-oriented project, but I aimed to keep the code clean, modular, and reusable.

Future improvements may include:

* Iterators
* Better abstraction layers
* Performance benchmarking

---

Thanks for checking out the project!
