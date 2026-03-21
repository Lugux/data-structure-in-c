#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include <stddef.h>

#include "../common/common_macros.h"

typedef struct bst_node
{
    void *data;
    size_t dataSize;
    struct bst_node *left;
    struct bst_node *right;
}bst_node;

typedef bst_node *bst;

void bst_init(bst *tree);
int bst_insert(bst *tree, const void *data, size_t dataSize, int (*cmp)(const void*, const void*));
int bst_search(const bst *tree, const void *data, int (*cmp)(const void*, const void*));
int bst_remove(bst *tree, const void *data, int (*cmp)(const void*, const void*));

void bst_inorder(const bst *tree, void (*act)(const void*));
void bst_preorder(const bst *tree, void (*act)(const void*));
void bst_postorder(const bst *tree, void (*act)(const void*));

int bst_min(const bst *tree, void *data, size_t dataSize);
int bst_max(const bst *tree, void *data, size_t dataSize);

size_t bst_height(const bst *tree);
size_t bst_size(const bst *tree);

int bst_is_empty(const bst *tree);
void bst_destroy(bst *tree);

size_t bst_leaf_count(const bst *tree);
const bst_node* bst_min_node(const bst *tree);
const bst_node* bst_max_node(const bst *tree);
int bst_is_balanced(const bst *tree);
bst bst_clone(const bst *tree);

#endif // BINARY_TREE_H_INCLUDED
