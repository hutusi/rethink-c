#include "bstree.h"
#include "test_helper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "alloc-testing.h"

typedef struct _CBValue {
    void *data[100];
    int index;
    int length;
} CBValue;
static void bs_tree_traverse_callback(BSTreeNode *node, void *args)
{
    CBValue *value = (CBValue *)args;
    value->data[(value->index)++] = node->data;
}

// static void bs_tree_traverse_print(BSTreeNode *node, void *args)
// {
//     printf("%d, ", *((int *)node->data));
// }

void test_bstree()
{
    int entries[] = { 38, 23, 42, 4, 16, 15, 8, 99, 50, 30 };
    int sorted[]  = { 4, 8, 15, 16, 23, 30, 38, 42, 50, 99 };
    int num_entries = sizeof(entries) / sizeof(int);

    BSTree *tree = bs_tree_new(int_compare);
    BSTreeNode *node;
    for (int i =0;i<num_entries; ++i) {
        node = bs_tree_insert(tree, &entries[i]);
        assert(int_equal(node->data, &entries[i]));
    }

    node = bs_tree_lookup_data(tree, &entries[3]);
    assert(int_equal(node->data, &entries[3]));

    CBValue cb;
    cb.index = 0;
    bs_tree_inorder_traverse(tree, bs_tree_traverse_callback, &cb);
    assert(cb.index == 10);
    for (int i = 0; i < num_entries; ++i) {
        // printf("%d ", *(int *)cb.data[i]);
        assert(int_equal(cb.data[i], &sorted[i]));
    }

    //                    38
    //                    /\
    //                  23  42
    //                  /\  /\
    //                 4 30   99
    //                /\      /
    //                  16   50
    //                  /
    //                 15
    //                 /
    //                8 

    // 38, 23, 42, 4, 16, 15, 8, 99, 50, 30 => 4
    node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[3]));
    free(node);
    // 38, 23, 42, 4, 16, 15, 8, 99, 50, 30 => 16
    node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[4]));
    free(node);
    // 38, 23, 42, 4, 16, 15, 8, 99, 50, 30 => 38
    node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[0]));
    free(node);

    // 8, 15, 23, 30, 42, 50, 99
    int remain[]  = { 8, 15, 23, 30, 42, 50, 99 };
    cb.index = 0;
    bs_tree_inorder_traverse(tree, bs_tree_traverse_callback, &cb);
    // printf("len === %d = %d ===\n", cb.index, tree->num_nodes);
    assert(cb.index == tree->num_nodes);
    for (int i = 0; i < tree->num_nodes; ++i) {
        // printf("%d ", *(int *)cb.data[i]);
        assert(int_equal(cb.data[i], &remain[i]));
    }

    bs_tree_free(tree);
}

void test_bstree_remove()
{
    int entries[] = { 38, 23, 42, 4, 16, 15, 8, 99, 50, 30, 2, 1, 3, 20, 120, 40, 39, 41, 45, 60 };
 
    int num_entries = sizeof(entries) / sizeof(int);

    BSTree *tree = bs_tree_new(int_compare);
    BSTreeNode *node;
    for (int i =0;i<num_entries; ++i) {
        node = bs_tree_insert(tree, &entries[i]);
        assert(int_equal(node->data, &entries[i]));
    }

    // 38, 23, 42, 4, 16, 15, 8, 99, 50, 30, 2, 1, 3, 20, 120, 40, 39, 41, 45, 60
    // 1, 2, 3, 4, 8, 15, 16, 20, 23, 30, 38, 39, 40, 41, 42, 45, 50, 60, 99, 120
    // bs_tree_inorder_traverse(tree, bs_tree_traverse_print, NULL);
    // printf("\n==========\n");

    //                       38
    //                       /\
    //                  23       42
    //                  /\       /\
    //                 4 30    40   99
    //                /\       /\   /\
    //               2  16   39 41 50 120
    //              /\   /\        /\
    //             1 3 15  20    45  60
    //                 /
    //                8 

    for (int i = 2; i < num_entries; i += 3) {
        node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[i]));
        free(node);
    }
    // bs_tree_inorder_traverse(tree, bs_tree_traverse_print, NULL);
    // printf("\n==========\n");

    for (int i = 0; i < num_entries; i += 3) {
        node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[i]));
        free(node);
    }
    // bs_tree_inorder_traverse(tree, bs_tree_traverse_print, NULL);
    // printf("\n==========\n");

    for (int i = 1; i < num_entries; i += 3) {
        node = bs_tree_remove_node(tree, bs_tree_lookup_data(tree, &entries[i]));
        free(node);
    }
    // bs_tree_inorder_traverse(tree, bs_tree_traverse_print, NULL);
    // printf("\n==========\n");
    
    assert(tree->num_nodes == 0);
    bs_tree_free(tree);
}
