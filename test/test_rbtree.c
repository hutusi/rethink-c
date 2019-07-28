#include "rbtree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

RBTree *create_rb_tree(int size)
{
    RBTree *tree = rb_tree_new(int_compare, free, NULL);
    // int arr[] = {5, 6, 3, 2, 8, 1, 4, 0, 9, 7};

    for (int i = 0; i < size; ++i) {
        int *key = intdup(i);
        int *value = key;
        assert(rb_tree_insert(tree, key, value));
    }

    return tree;
}

void test_rbtree_insert()
{
    RBTree *tree = create_rb_tree(10);

    printf("root => [%d]\n", *((int *)tree->root->key));
    unsigned int height = rb_tree_subtree_height(tree->root);
    rb_tree_subtree_print(tree->root, height);

    rb_tree_free(tree);
}

void test_rb_tree_rotate()
{
    RBTree *tree = create_rb_tree(3);

    printf("root => [%d]\n", *((int *)tree->root->key));
    unsigned int height = rb_tree_subtree_height(tree->root);
    rb_tree_subtree_print(tree->root, height);

    RBTreeNode *mid = tree->root->right;
    RBTreeNode *new_node = rb_tree_rotate(tree, mid);

    printf("new => [%d]\n", *((int *)new_node->key));

    rb_tree_subtree_print(tree->root, height);
    
    rb_tree_free(tree);
}

void test_rbtree()
{
    // test_rb_tree_rotate();
    test_rbtree_insert();
}
