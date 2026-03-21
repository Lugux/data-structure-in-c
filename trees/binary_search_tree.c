#include <stdlib.h>
#include <string.h>

#include "binary_search_tree.h"

void bst_init(bst *tree)
{
    *tree = NULL;
}

int bst_insert(bst *tree, const void *data, size_t dataSize, int (*cmp)(const void*, const void*))
{
    if(*tree == NULL)
    {
        bst_node *new_node = malloc(sizeof(bst_node));
        if(!new_node)
            return 0;
        new_node->data = malloc(dataSize);
        if(!new_node->data)
        {
            free(new_node);
            return 0;
        }
        memcpy(new_node->data, data, dataSize);
        new_node->dataSize = dataSize;
        new_node->left = NULL;
        new_node->right = NULL;
        *tree = new_node;
        return 1;
    }
    int comp = cmp(data,(*tree)->data);
    if(comp < 0)
        return bst_insert(&(*tree)->left, data, dataSize, cmp);
    if(comp > 0)
        return bst_insert(&(*tree)->right, data, dataSize, cmp);
    return 0;
}

int bst_search(const bst *tree, const void *data, int (*cmp)(const void*, const void*))
{
    if(*tree == NULL)
        return 0;
    int comp = cmp(data,(*tree)->data);
    if(comp < 0)
        return bst_search(&(*tree)->left, data, cmp);
    if(comp > 0)
        return bst_search(&(*tree)->right, data, cmp);
    return 1;
}

int bst_remove(bst *tree, const void *data, int (*cmp)(const void*, const void*))
{
    if(*tree == NULL)
        return 0;
    int comp = cmp(data,(*tree)->data);
    if(comp < 0)
        return bst_remove(&(*tree)->left, data, cmp);
    if(comp > 0)
        return bst_remove(&(*tree)->right, data, cmp);

    bst_node *temp_node = *tree;
    if(!temp_node->left && !temp_node->right)
    {
        free(temp_node->data);
        free(temp_node);
        *tree = NULL;
        return 1;
    }
    if(!temp_node->left || !temp_node->right)
    {
        bst_node *succ_node = temp_node->left ? temp_node->left : temp_node->right;
        free(temp_node->data);
        free(temp_node);
        *tree = succ_node;
        return 1;
    }
    bst_node *parent_node = temp_node;
    bst_node *succ_node = temp_node->right;
    while(succ_node->left)
    {
        parent_node = succ_node;
        succ_node = succ_node->left;
    }
    if(parent_node != temp_node)
        parent_node->left = succ_node->right;
    else
        parent_node->right = succ_node->right;

    succ_node->left = temp_node->left;
    if(succ_node != temp_node->right)
        succ_node->right = temp_node->right;

    free(temp_node->data);
    free(temp_node);

    *tree = succ_node;
    return 1;
}

void bst_inorder(const bst *tree, void (*act)(const void*))
{
    if(*tree == NULL)
        return;
    bst_inorder(&(*tree)->left, act);

    act((*tree)->data);

    bst_inorder(&(*tree)->right, act);
}

void bst_preorder(const bst *tree, void (*act)(const void*))
{
    if(*tree == NULL)
        return;

    act((*tree)->data);

    bst_preorder(&(*tree)->left, act);
    bst_preorder(&(*tree)->right, act);
}

void bst_postorder(const bst *tree, void (*act)(const void*))
{
    if(*tree == NULL)
        return;
    bst_postorder(&(*tree)->left, act);
    bst_postorder(&(*tree)->right, act);

    act((*tree)->data);
}

int bst_min(const bst *tree, void *data, size_t dataSize)
{
    if(!(*tree) || !data || !dataSize)
        return 0;
    if(!(*tree)->left)
    {
        memcpy(data, (*tree)->data, MIN((*tree)->dataSize, dataSize));
        return 1;
    }
    return bst_min(&(*tree)->left, data, dataSize);
}

int bst_max(const bst *tree, void *data, size_t dataSize)
{
    if(!(*tree) || !data || !dataSize)
        return 0;
    if(!(*tree)->right)
    {
        memcpy(data, (*tree)->data, MIN((*tree)->dataSize, dataSize));
        return 1;
    }
    return bst_max(&(*tree)->right, data, dataSize);
}

size_t bst_height(const bst *tree)
{
    if(*tree == NULL)
        return 0;
    size_t height_right, height_left;
    height_left = bst_height(&(*tree)->left);
    height_right = bst_height(&(*tree)->right);
    return MAX(height_left, height_right) + 1;
}

size_t bst_size(const bst *tree)
{
    if(*tree == NULL)
        return 0;
    size_t size_right, size_left;
    size_left = bst_size(&(*tree)->left);
    size_right = bst_size(&(*tree)->right);
    return size_left + size_right + 1;
}

int bst_is_empty(const bst *tree)
{
    return *tree == NULL;
}

void bst_destroy(bst *tree)
{
    if(*tree == NULL)
        return;
    bst_destroy(&(*tree)->left);
    bst_destroy(&(*tree)->right);

    free((*tree)->data);
    free(*tree);
    *tree = NULL;
}

size_t bst_leaf_count(const bst *tree)
{
    if(!*tree)
        return 0;
    if(!(*tree)->left && !(*tree)->right)
        return 1;

    return bst_leaf_count(&(*tree)->left) + bst_leaf_count(&(*tree)->right);
}

const bst_node* bst_min_node(const bst *tree)
{
    if(!*tree)
        return 0;
    if(!(*tree)->left)
        return *tree;
    return bst_min_node(&(*tree)->left);
}

const bst_node* bst_max_node(const bst *tree)
{
    if(!*tree)
        return 0;
    if(!(*tree)->right)
        return *tree;
    return bst_max_node(&(*tree)->right);
}

int bst_is_balanced(const bst *tree)
{
    if(!*tree)
        return 1;

    int left = bst_height(&(*tree)->left);
    int right = bst_height(&(*tree)->right);

    if(abs(left - right) > 1)
        return 0;

    return bst_is_balanced(&(*tree)->left) && bst_is_balanced(&(*tree)->right);
}

bst bst_clone(const bst *tree)
{
    if(!*tree)
        return NULL;
    bst_node *new_node = malloc(sizeof(bst_node));
    if(!new_node)
        return NULL;
    new_node->data = malloc((*tree)->dataSize);
    if(!new_node->data)
    {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, (*tree)->data, (*tree)->dataSize);
    new_node->dataSize = (*tree)->dataSize;
    new_node->left = bst_clone(&(*tree)->left);
    new_node->right = bst_clone(&(*tree)->right);
    return new_node;
}
