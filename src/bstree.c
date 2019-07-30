/**
 * @file bstree.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to bstree.h
 * @date 2019-07-20
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

BSTree *bs_tree_new(BSTreeCompareFunc compare_func)
{
    BSTree *tree = (BSTree *)malloc(sizeof(BSTree));
    tree->compare_func = compare_func;
    tree->root = NULL;
    tree->num_nodes = 0;
    return tree;
}

static void bs_tree_free_node_callback(BSTreeNode *node, void *args)
{
    // printf("free node: [%d]\n", *((int *)(node->data)));
    free(node);
}

void bs_tree_free(BSTree *tree)
{
    // free all nodes
    bs_tree_postorder_traverse(tree, bs_tree_free_node_callback, NULL);
    free(tree);
}

static BSTreeNode *bs_tree_node_new(BSTreeValue data)
{
    BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    node->data = data;
    node->parent = NULL;
    node->left = node->right = NULL;
    return node;
}

BSTreeNode *bs_tree_insert(BSTree *tree, BSTreeValue data)
{
    BSTreeNode *rover = tree->root;
    BSTreeNode *insert = NULL;
    int comp = 0;
    while (rover != NULL) {
        comp = (tree->compare_func)(data, rover->data);
        insert = rover;

        if (comp < 0) {
            rover = rover->left;
        } else if (comp > 0) {
            rover = rover->right;
        } else {
            // equal, do not insert.
            return rover;
        }
    }

    BSTreeNode *new_node = bs_tree_node_new(data);
    new_node->parent = insert;
    ++(tree->num_nodes);

    if (insert == NULL) {
        tree->root = new_node;
    } else if (comp < 0) {
        insert->left = new_node;
    } else if (comp > 0) {
        insert->right = new_node;
    } else {
        // impossible
        assert(0);
    }

    return new_node;
}

BSTreeNode *bs_tree_leftmost_node(BSTreeNode *node)
{
    BSTreeNode *rover = node;
    while (rover->left != NULL) {
        rover = rover->left;
    }
    return rover;
}

BSTreeNode *bs_tree_rightmost_node(BSTreeNode *node)
{
    BSTreeNode *rover = node;
    while (rover->right != NULL) {
        rover = rover->right;
    }
    return rover;
}

static BSTreeNode *
bs_tree_replace_node(BSTree *tree, BSTreeNode *node, BSTreeNode *replace)
{
    BSTreeNode *parent = node->parent;
    if (parent == NULL) { // root
        tree->root = replace;
    } else if (parent->left == node) {
        parent->left = replace;
    } else {
        parent->right = replace;
    }

    if (replace != NULL) {
        replace->parent = parent;
    }

    return node;
}

BSTreeNode *bs_tree_remove_node(BSTree *tree, BSTreeNode *node)
{
    if (node->left == NULL && node->right == NULL) {
        bs_tree_replace_node(tree, node, NULL);
    } else if (node->left == NULL) {
        bs_tree_replace_node(tree, node, node->right);
    } else if (node->right == NULL) {
        bs_tree_replace_node(tree, node, node->left);
    } else {
        BSTreeNode *replace = bs_tree_leftmost_node(node->right);

        if (replace != node->right) {
            bs_tree_replace_node(tree, replace, replace->right);
            replace->right = node->right;
            node->right->parent = replace;
        }
        bs_tree_replace_node(tree, node, replace);
        replace->left = node->left;
        node->left->parent = replace;
    }

    --(tree->num_nodes);
    return node;
}

BSTreeNode *bs_tree_lookup_data(BSTree *tree, BSTreeValue data)
{
    BSTreeNode *rover = tree->root;
    while (rover != NULL) {
        int comp = (tree->compare_func)(data, rover->data);
        if (comp < 0) {
            rover = rover->left;
        } else if (comp > 0) {
            rover = rover->right;
        } else /* (comp == 0) */ {
            return rover;
        }
    }
    return NULL;
}

static void bs_tree_preorder_internal(BSTreeNode *node,
                                      BSTreeTraverseFunc callback,
                                      void *cb_args)
{
    if (node != NULL) {
        if (callback != NULL) {
            callback(node, cb_args);
        }
        bs_tree_preorder_internal(node->left, callback, cb_args);
        bs_tree_preorder_internal(node->right, callback, cb_args);
    }
}
void bs_tree_preorder_traverse(BSTree *tree,
                               BSTreeTraverseFunc callback,
                               void *cb_args)
{
    bs_tree_preorder_internal(tree->root, callback, cb_args);
}

static void bs_tree_inorder_internal(BSTreeNode *node,
                                     BSTreeTraverseFunc callback,
                                     void *cb_args)
{
    if (node != NULL) {
        bs_tree_inorder_internal(node->left, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
        bs_tree_inorder_internal(node->right, callback, cb_args);
    }
}
void bs_tree_inorder_traverse(BSTree *tree,
                              BSTreeTraverseFunc callback,
                              void *cb_args)
{
    bs_tree_inorder_internal(tree->root, callback, cb_args);
}

static void bs_tree_postorder_internal(BSTreeNode *node,
                                       BSTreeTraverseFunc callback,
                                       void *cb_args)
{
    if (node != NULL) {
        bs_tree_postorder_internal(node->left, callback, cb_args);
        bs_tree_postorder_internal(node->right, callback, cb_args);
        if (callback != NULL) {
            callback(node, cb_args);
        }
    }
}
void bs_tree_postorder_traverse(BSTree *tree,
                                BSTreeTraverseFunc callback,
                                void *cb_args)
{
    bs_tree_postorder_internal(tree->root, callback, cb_args);
}
