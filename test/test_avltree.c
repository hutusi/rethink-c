#include "avltree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

AVLTree *create_avl_tree(int size)
{
    AVLTree *tree = avl_tree_new(int_compare, free, NULL);
    // int arr[] = {5, 6, 3, 2, 8, 1, 4, 0, 9, 7};

    for (int i = 0; i < size; ++i) {
        int *key = intdup(i);
        int *value = key;
        assert(avl_tree_insert(tree, key, value));
    }

    return tree;
}

void test_avltree_insert()
{
    AVLTree *tree = create_avl_tree(100);

    unsigned int height = avl_tree_subtree_height(tree->root);
    assert(height <= 7);

    avl_tree_free(tree);
}

void test_avltree_delete()
{
    AVLTree *tree = create_avl_tree(10);

    int *key = intdup(7);
    AVLTreeNode *node = avl_tree_find_node(tree, key);
    assert(int_equal(node->key, key));

    AVLTreeNode *removed = avl_tree_remove_node(tree, node);
    assert(removed == node);
    assert(tree->num_nodes == 9);

    // printf("root => [%d]\n", *((int *)tree->root->key));
    unsigned int height = avl_tree_subtree_height(tree->root);
    assert(height <= 3);
    // avl_tree_subtree_print(tree->root, height);

    free(key);
    avl_tree_free_node(tree, removed);
    avl_tree_free(tree);
}

void test_avltree_print()
{
    AVLTree *tree = create_avl_tree(100);

    printf("root => [%d]\n", *((int *)tree->root->key));
    unsigned int height = avl_tree_subtree_height(tree->root);
    avl_tree_subtree_print(tree->root, height);

    avl_tree_free(tree);
}

void test_avltree()
{
    test_avltree_insert();
    test_avltree_delete();
    // test_avltree_print();
}
