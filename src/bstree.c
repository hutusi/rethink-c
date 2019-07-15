#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

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
    BSTreeNode *new_node;
    if (tree->root == NULL) {
        new_node = bs_tree_node_new(data);
        tree->root = new_node;
        ++(tree->num_nodes);
        return new_node;
    }

    BSTreeNode *rover = tree->root;
    while (rover != NULL) {
        int comp = (tree->compare_func)(data, rover->data);
        if (comp < 0) {
            if (rover->left == NULL) {
                new_node = bs_tree_node_new(data);
                rover->left = new_node;
                new_node->parent = rover;
                ++(tree->num_nodes);
                return new_node;
            }
            rover = rover->left;
        } else if (comp > 0) {
            if (rover->right == NULL) {
                new_node = bs_tree_node_new(data);
                rover->right = new_node;
                new_node->parent = rover;
                ++(tree->num_nodes);
                return new_node;
            }
            rover = rover->right;
        } else {
            // equal, do not insert.
            return rover;
        }
    }

    return NULL;
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
    } else {
        if (parent->left == node) {
            parent->left = replace;
        } else if (parent->right == node) {
            parent->right = replace;
        } else {
            // something wrong
            return NULL;
        }
    }

    if (replace != NULL) {
        replace->parent = parent;
    }

    --(tree->num_nodes);
    return node;
}

BSTreeNode *bs_tree_remove_node(BSTree *tree, BSTreeNode *node)
{
    BSTreeNode *parent = node->parent;
    BSTreeNode *left = node->left;
    BSTreeNode *right = node->right;
    BSTreeNode *removed = NULL;

    if (left == NULL && right == NULL) {
        removed = bs_tree_replace_node(tree, node, NULL);
    } else if (left == NULL) {
        removed = bs_tree_replace_node(tree, node, right);
    } else if (right == NULL) {
        removed = bs_tree_replace_node(tree, node, left);
    } else {
        if (right->left == NULL) {
            removed = bs_tree_replace_node(tree, node, right);

            right->left = left;
            left->parent = right;
        } else {
            BSTreeNode *leftmost = bs_tree_leftmost_node(right);
            BSTreeNode *old_parent = leftmost->parent;
            removed = bs_tree_replace_node(tree, node, leftmost);
            if (removed != NULL) {
                old_parent->left = NULL;

                leftmost->left = left;
                leftmost->right = right;

                left->parent = leftmost;
                right->parent = leftmost;
            }
        }
    }

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
